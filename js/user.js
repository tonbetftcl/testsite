window.expressState = { step:'divisions', sel:[], div:null, outcomes:{}, totalOdds:0, period:'match' };
window.matchState = { view:'divisions', div:null, match:null, period:'match' };

document.addEventListener('click', function(e) {
    const periodBtn = e.target.closest('.period-btn');
    if (periodBtn) {
        const period = periodBtn.dataset.period;
        if (window.expressState.step === 'outcomes') {
            window.expressState.period = period;
            renderExpress();
        } else if (window.matchState.view === 'bet') {
            window.matchState.period = period;
            renderMatches();
        }
        return;
    }

    const backLink = e.target.closest('.back-link');
    if (backLink) {
        if (window.expressState.step === 'outcomes') {
            window.expressState.step = 'matches';
            renderExpress();
        } else if (window.expressState.step === 'bet') {
            window.expressState.step = 'outcomes';
            window.expressState.outcomes = {};
            renderExpress();
        } else if (window.expressState.step === 'matches') {
            window.expressState.step = 'divisions';
            renderExpress();
        } else if (window.matchState.view === 'bet') {
            window.matchState.view = 'matches';
            renderMatches();
        } else if (window.matchState.view === 'matches') {
            window.matchState.view = 'divisions';
            renderMatches();
        }
        return;
    }
});

function renderExpress() {
    if (window.expressState.step === 'divisions') {
        window.els.tab.innerHTML = `<div class="section-title">Экспресс — Выберите дивизион</div><div class="division-grid"></div>`;
        const grid = window.els.tab.querySelector('.division-grid');
        if (typeof DIVISIONS !== 'undefined') {
            DIVISIONS.forEach(d => {
                const c = document.createElement('div');
                c.className = 'division-card';
                c.textContent = d;
                c.onclick = () => { window.expressState.div = d; window.expressState.step = 'matches'; renderExpress(); };
                grid.appendChild(c);
            });
        }
    } else if (window.expressState.step === 'matches') {
        const allNotArchived = (window.matches || []).filter(m => m.division === window.expressState.div && !m.archived);
        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">Экспресс – ${window.expressState.div}</div><div class="match-list"></div><button class="action-btn" id="readyBtn" style="margin-top:10px;" disabled>Готово (0)</button>`;
        const list = window.els.tab.querySelector('.match-list');
        if (allNotArchived.length === 0) list.innerHTML = '<div style="color:#aaa;text-align:center;padding:20px;">Нет матчей</div>';
        else allNotArchived.forEach(m => {
            const d = document.createElement('div');
            d.className = `match-item ${window.expressState.sel.includes(m.id) && m.status==='open' ? 'selected' : ''}`;
            d.innerHTML = `<span>${m.team1} — ${m.team2}</span>${m.status==='open' ? `<div>${window.expressState.sel.includes(m.id) ? '✓' : ''}</div>` : `<span style="color:#ffaa00;font-size:0.75rem;">Закрыт</span>`}`;
            d.onclick = () => {
                if (m.status !== 'open') return alert('Приём ставок на этот матч закрыт');
                if (window.expressState.sel.includes(m.id)) window.expressState.sel = window.expressState.sel.filter(x => x !== m.id);
                else window.expressState.sel.push(m.id);
                renderExpress();
            };
            list.appendChild(d);
        });
        const btn = window.els.tab.querySelector('#readyBtn');
        const openSelected = window.expressState.sel.filter(id => window.matches.find(m => m.id === id && m.status === 'open')).length;
        btn.textContent = `Готово (выбрано ${openSelected})`;
        btn.disabled = openSelected < 2;
        btn.onclick = () => { if (openSelected >= 2) { window.expressState.step = 'outcomes'; window.expressState.outcomes = {}; renderExpress(); } };
    } else if (window.expressState.step === 'outcomes') {
        const selMatches = window.expressState.sel.map(id => window.matches.find(m => m.id === id && m.status === 'open')).filter(m => m);
        const idx = Object.keys(window.expressState.outcomes).length;
        if (idx >= selMatches.length) {
            let tot = 1; 
            selMatches.forEach(m => { 
                const out = window.expressState.outcomes[m.id]; 
                let o = (typeof out === 'object' && out.type === 'TS') ? getOddsForPeriod(m, 'TS', window.expressState.period) : getOddsForPeriod(m, out, window.expressState.period); 
                tot *= o; 
            });
            window.expressState.totalOdds = +tot.toFixed(2); 
            window.expressState.step = 'bet'; 
            renderExpress(); 
            return;
        }
        const m = selMatches[idx];
        const period = window.expressState.period || 'match';

        let outcomesHtml = `
            <div class="odd-block" data-out="1"><div>П1</div><div class="odd-value">${getOddsForPeriod(m, '1', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="X"><div>Ничья</div><div class="odd-value">${getOddsForPeriod(m, 'X', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="2"><div>П2</div><div class="odd-value">${getOddsForPeriod(m, '2', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="TB"><div>ТБ 2.5</div><div class="odd-value">${getOddsForPeriod(m, 'TB', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="TM"><div>ТМ 2.5</div><div class="odd-value">${getOddsForPeriod(m, 'TM', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="OZ"><div>ОЗ</div><div class="odd-value">${getOddsForPeriod(m, 'OZ', period).toFixed(2)}</div></div>
        `;

        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">Исход ${idx+1}/${selMatches.length}</div>
            <div style="font-size:1.1rem;font-weight:600;text-align:center;margin:12px 0;">${m.team1} — ${m.team2}</div>
            <div style="margin-bottom:12px; display:flex; gap:6px; justify-content:center;">
                <button class="action-btn small period-btn ${period==='match'?'selected':''}" data-period="match">Весь матч</button>
                <button class="action-btn small period-btn ${period==='1H'?'selected':''}" data-period="1H">1-й тайм</button>
                <button class="action-btn small period-btn ${period==='2H'?'selected':''}" data-period="2H">2-й тайм</button>
            </div>
            <div class="odds-row">${outcomesHtml}</div>`;
        
        window.els.tab.querySelectorAll('.odd-block').forEach(b => b.onclick = function() {
            window.expressState.outcomes[m.id] = this.dataset.out;
            renderExpress();
        });
    } else if (window.expressState.step === 'bet') {
        window.els.tab.innerHTML = `<div class="back-link">← Изменить исходы</div><div class="section-title">Коэффициент: ${window.expressState.totalOdds.toFixed(2)}</div>
            <div style="display:flex;gap:8px;align-items:center;margin-top:16px;">
                <input type="number" class="bet-amount-input" id="expAmount" placeholder="Сумма" min="1">
                <button class="action-btn" id="placeExpBet" style="width:140px;">Ставка</button>
            </div>`;
        window.els.tab.querySelector('#placeExpBet').onclick = async () => {
            const user = getCurrentUser(); if (!user) return;
            const amount = +window.els.tab.querySelector('#expAmount').value;
            if (isNaN(amount) || amount <= 0) return alert('Некорректная сумма');
            if (amount > user.balance) return alert('Недостаточно средств');
            const period = window.expressState.period;
            const legs = window.expressState.sel.map(id => { 
                const m = window.matches.find(x => x.id === id); 
                const outcome = window.expressState.outcomes[id];
                const odds = getOddsForPeriod(m, outcome, period);
                return { matchId: id, team1: m.team1, team2: m.team2, outcome, odds, period };
            });
            user.balance -= amount;
            if (!user.bets) user.bets = [];
            user.bets.push({ type: 'express', legs, totalOdds: window.expressState.totalOdds, amount, status: 'pending', winAmount:0, period });
            await saveUsers();
            alert('Ставка принята!');
            window.expressState = { step:'divisions', sel:[], div:null, outcomes:{}, totalOdds:0, period:'match' };
            renderTab('express');
        };
    }
}

function renderMatches() {
    if (window.matchState.view === 'divisions') {
        window.els.tab.innerHTML = `<div class="section-title">Выберите дивизион</div><div class="division-grid"></div>`;
        const grid = window.els.tab.querySelector('.division-grid');
        if (typeof DIVISIONS !== 'undefined') {
            DIVISIONS.forEach(d => {
                const c = document.createElement('div');
                c.className = 'division-card';
                c.textContent = d;
                c.onclick = () => { window.matchState.div = d; window.matchState.view = 'matches'; renderMatches(); };
                grid.appendChild(c);
            });
        }
    } else if (window.matchState.view === 'matches') {
        const list = (window.matches || []).filter(m => m.division === window.matchState.div && !m.archived);
        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">${window.matchState.div}</div><div class="match-list"></div>`;
        const ml = window.els.tab.querySelector('.match-list');
        if (list.length === 0) ml.innerHTML = '<div style="color:#aaa;text-align:center;padding:20px;">Нет матчей</div>';
        else list.forEach(m => {
            const d = document.createElement('div'); d.className = 'match-item';
            d.innerHTML = `<span>${m.team1} — ${m.team2}</span><span style="color:${m.status==='open'?'#22c55e':'#ffaa00'};">${m.status==='open'?'Открыт':'Закрыт'}</span>`;
            d.onclick = () => { 
                window.matchState.match = m; 
                window.matchState.view = 'bet'; 
                window.matchState.period = 'match';
                renderMatches(); 
            };
            ml.appendChild(d);
        });
    } else if (window.matchState.view === 'bet') {
        const m = window.matchState.match;
        const period = window.matchState.period || 'match';
        let outcomesHtml = `
            <div class="odd-block" data-out="1"><div>П1</div><div class="odd-value">${getOddsForPeriod(m, '1', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="X"><div>Ничья</div><div class="odd-value">${getOddsForPeriod(m, 'X', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="2"><div>П2</div><div class="odd-value">${getOddsForPeriod(m, '2', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="TB"><div>ТБ 2.5</div><div class="odd-value">${getOddsForPeriod(m, 'TB', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="TM"><div>ТМ 2.5</div><div class="odd-value">${getOddsForPeriod(m, 'TM', period).toFixed(2)}</div></div>
            <div class="odd-block" data-out="OZ"><div>ОЗ</div><div class="odd-value">${getOddsForPeriod(m, 'OZ', period).toFixed(2)}</div></div>
        `;

        window.els.tab.innerHTML = `<div class="back-link">← К матчам</div>
            <div style="font-size:1.1rem;font-weight:600;text-align:center;margin-bottom:12px;">${m.team1} — ${m.team2}</div>
            <div style="margin-bottom:12px; display:flex; gap:6px; justify-content:center;">
                <button class="action-btn small period-btn ${period==='match'?'selected':''}" data-period="match">Весь матч</button>
                <button class="action-btn small period-btn ${period==='1H'?'selected':''}" data-period="1H">1-й тайм</button>
                <button class="action-btn small period-btn ${period==='2H'?'selected':''}" data-period="2H">2-й тайм</button>
            </div>
            <div class="odds-row">${outcomesHtml}</div>
            ${m.status === 'open' ? `<div style="display:flex;gap:8px;align-items:center;margin-top:16px;">
                <input type="number" class="bet-amount-input" id="betAmount" placeholder="Сумма" min="1">
                <button class="action-btn" id="placeBet" style="width:140px;">Ставка</button>
            </div>` : `<div style="margin-top:16px;color:#ffaa00;text-align:center;">Приём ставок закрыт</div>`}`;

        let selOut = null;
        window.els.tab.querySelectorAll('.odd-block').forEach(b => b.onclick = function() {
            window.els.tab.querySelectorAll('.odd-block').forEach(x => x.classList.remove('selected'));
            this.classList.add('selected');
            selOut = this.dataset.out;
        });

        const placeBetBtn = document.getElementById('placeBet');
        if (placeBetBtn) {
            placeBetBtn.onclick = async () => {
                const user = getCurrentUser(); if (!user) return;
                if (!selOut) return alert('Выберите исход');
                const amount = +document.getElementById('betAmount').value;
                if (isNaN(amount) || amount <= 0) return alert('Некорректная сумма');
                if (amount > user.balance) return alert('Недостаточно средств');
                const odds = getOddsForPeriod(m, selOut, window.matchState.period);
                user.balance -= amount;
                if (!user.bets) user.bets = [];
                user.bets.push({ type:'single', matchId:m.id, team1:m.team1, team2:m.team2, outcome:selOut, amount, odds, status:'pending', winAmount:0, period: window.matchState.period });
                await saveUsers();
                alert('Ставка принята!');
                renderTab('matches');
            };
        }
    }
}

function renderMyBets() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }
    let bets = (user.bets || []).slice().reverse();
    if (window.currentFilter === 'pending') bets = bets.filter(b => b.status === 'pending');
    else if (window.currentFilter === 'win') bets = bets.filter(b => b.status === 'win');
    else if (window.currentFilter === 'lose') bets = bets.filter(b => b.status === 'lose');

    let html = '<div class="section-title">Мои Ставки</div>';
    html += `<div class="filter-tabs">
        <div class="filter-tab ${window.currentFilter==='all'?'active':''}" data-f="all">Все</div>
        <div class="filter-tab ${window.currentFilter==='pending'?'active':''}" data-f="pending">Действующие</div>
        <div class="filter-tab ${window.currentFilter==='win'?'active':''}" data-f="win">Выигрыши</div>
        <div class="filter-tab ${window.currentFilter==='lose'?'active':''}" data-f="lose">Проигрыши</div>
    </div>`;

    if (bets.length === 0) {
        html += '<div style="color:#aaa;text-align:center;padding:20px;">Нет ставок</div>';
    } else {
        bets.forEach(bet => {
            const icon = bet.status === 'win' 
                ? `<span class="status-icon-mini status-win-mini">✓</span>` 
                : bet.status === 'lose' 
                ? `<span class="status-icon-mini status-lose-mini">✕</span>` 
                : `<span class="status-icon-mini status-pending-mini">⏱</span>`;

            const periodStr = bet.period && bet.period !== 'match' ? ` (${bet.period === '1H' ? '1-й тайм' : '2-й тайм'})` : '';

            if (bet.type === 'express') {
                html += `<div class="bet-card">
                    <div class="bet-card-header">
                        <span>${icon} <strong>Экспресс${periodStr}</strong> (${bet.legs.length})</span>
                        <strong>k=${bet.totalOdds.toFixed(2)}</strong>
                    </div>
                    <div class="bet-card-sub">
                        <span>Сумма: ${bet.amount}</span>
                        <span>${bet.status === 'win' ? '+' + bet.winAmount.toFixed(0) : ''}</span>
                    </div>
                </div>`;
            } else {
                const outName = bet.outcome==='TB'?'ТБ 2.5':bet.outcome==='TM'?'ТМ 2.5':bet.outcome==='OZ'?'ОЗ':(bet.outcome==='1'?'П1':bet.outcome==='X'?'Ничья':'П2');
                html += `<div class="bet-card">
                    <div class="bet-card-header">
                        <span>${icon} <strong>${bet.team1} — ${bet.team2}${periodStr}</strong></span>
                        <strong>k=${bet.odds.toFixed(2)}</strong>
                    </div>
                    <div class="bet-card-sub">
                        <span>Исход: ${outName} | Сумма: ${bet.amount}</span>
                        <span>${bet.status === 'win' ? '+' + bet.winAmount.toFixed(0) : ''}</span>
                    </div>
                </div>`;
            }
        });
    }
    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.filter-tab').forEach(t => t.onclick = () => { window.currentFilter = t.dataset.f; renderMyBets(); });
}

// Новая функция переводов
function renderTransfers() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }

    let html = '<div class="section-title">Переводы</div>';

    if (!user.accountNumber) {
        html += `<div class="transparent-bordered-card">
            <div style="margin-bottom:10px;color:var(--text-secondary);">У вас еще нет личного счёта для быстрых переводов</div>
            <button class="action-btn" id="openAccountBtn">Открыть Счёт</button>
        </div>`;
        window.els.tab.innerHTML = html;
        document.getElementById('openAccountBtn').onclick = async () => {
            let acc = '';
            do {
                acc = Math.floor(100000 + Math.random() * 900000).toString();
            } while (window.users.some(u => u.accountNumber === acc));
            user.accountNumber = acc;
            await saveUsers();
            renderTransfers();
        };
        return;
    }

    html += `<div class="transparent-bordered-card">
        <div style="font-size:0.75rem;color:var(--text-secondary);margin-bottom:4px;">Номер Счёта</div>
        <div style="border:1px dashed var(--accent);padding:8px;border-radius:var(--radius-sm);font-weight:700;letter-spacing:2px;font-size:1.1rem;color:#fff;">${user.accountNumber}</div>
    </div>`;

    html += `<div style="display:flex;gap:8px;margin-bottom:14px;">
        <button class="action-btn" id="transferActionBtn">Перевод</button>
        <button class="action-btn" id="transferHistoryBtn" style="background:var(--card-bg);border:1px solid var(--card-border);">История</button>
    </div><div id="transferSubContent"></div>`;

    window.els.tab.innerHTML = html;

    const renderSub = (type) => {
        const container = document.getElementById('transferSubContent');
        if (type === 'form') {
            container.innerHTML = `<div class="input-group">
                <label>Номер счёта получателя</label>
                <input type="number" id="targetAccInput" placeholder="6 цифр">
            </div>
            <div class="input-group">
                <label>Сумма перевода</label>
                <input type="number" id="transferAmountInput" placeholder="Коины" min="1">
            </div>
            <button class="action-btn" id="submitTransferBtn">Подать заявку</button>`;

            document.getElementById('submitTransferBtn').onclick = async () => {
                const targetAcc = document.getElementById('targetAccInput').value.trim();
                const amount = parseInt(document.getElementById('transferAmountInput').value);
                if (!targetAcc || targetAcc === user.accountNumber) return alert('Некорректный номер счёта');
                const recipient = window.users.find(u => u.accountNumber === targetAcc);
                if (!recipient) return alert('Получатель с таким счётом не найден');
                if (isNaN(amount) || amount <= 0) return alert('Укажите некорректную сумму');
                if (amount > user.balance) return alert('Недостаточно средств');

                if (!window.transferRequests) window.transferRequests = [];
                const reqObj = {
                    id: Date.now().toString(),
                    sender: user.username,
                    senderAcc: user.accountNumber,
                    recipient: recipient.username,
                    recipientAcc: recipient.accountNumber,
                    amount: amount,
                    status: 'pending',
                    timestamp: Date.now()
                };
                window.transferRequests.push(reqObj);
                await saveTransferRequests();
                alert('Заявка на перевод успешно подана админу!');
                renderSub('history');
            };
        } else {
            let histHtml = '<div style="font-weight:600;margin-bottom:8px;">История операций</div>';
            const reqs = (window.transferRequests || []).filter(r => r.sender === user.username || r.recipient === user.username).slice().reverse();
            if (reqs.length === 0) histHtml += '<div style="color:#aaa;">Заявок пока нет</div>';
            else {
                reqs.forEach(r => {
                    const isSender = r.sender === user.username;
                    const stColor = r.status === 'approved' ? 'var(--success)' : r.status === 'rejected' ? 'var(--danger)' : '#ffaa00';
                    const stText = r.status === 'approved' ? 'Одобрен' : r.status === 'rejected' ? 'Отклонен' : 'Ожидание';
                    histHtml += `<div style="background:var(--card-bg);border:1px solid var(--card-border);padding:8px 10px;border-radius:8px;margin-bottom:6px;font-size:0.8rem;">
                        <div style="display:flex;justify-content:space-between;">
                            <span>${isSender ? 'Кому: ' + r.recipient : 'От: ' + r.sender}</span>
                            <span style="color:${stColor};">${stText}</span>
                        </div>
                        <div style="display:flex;justify-content:space-between;margin-top:4px;color:var(--text-secondary);">
                            <span>Сумма: ${r.amount}</span>
                            <span>${new Date(r.timestamp).toLocaleDateString()}</span>
                        </div>
                    </div>`;
                });
            }
            container.innerHTML = histHtml;
        }
    };

    document.getElementById('transferActionBtn').onclick = () => renderSub('form');
    document.getElementById('transferHistoryBtn').onclick = () => renderSub('history');
    renderSub('form');
}

function renderPromo() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }
    let html = '<div class="section-title">Промокод</div>';
    html += '<div class="input-group"><label>Введите промокод</label><input type="text" id="promoInput" placeholder="Код"></div>';
    html += '<button class="action-btn" id="activatePromoBtn">Активировать</button>';
    window.els.tab.innerHTML = html;
    document.getElementById('activatePromoBtn').onclick = async () => {
        const code = document.getElementById('promoInput').value.trim();
        if (!code) return alert('Введите промокод');
        if (user.activatedPromos && user.activatedPromos.includes(code)) return alert('Вы уже активировали этот промокод');
        const promo = (window.promoCodes || []).find(p => p.code === code && p.remaining > 0);
        if (!promo) return alert('Промокод недействителен или исчерпан');
        promo.remaining--;
        if (!user.activatedPromos) user.activatedPromos = [];
        user.activatedPromos.push(code);
        user.balance += promo.bonus;
        await Promise.all([saveUsers(), savePromoCodes()]);
        alert(`Промокод активирован! +${promo.bonus} коинов`);
        renderTab('promo');
    };
}

function renderProfile() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }
    const bets = user.bets || [];
    const fin = bets.filter(b => b.status !== 'pending');
    const wins = fin.filter(b => b.status === 'win').length;
    const wr = fin.length ? ((wins / fin.length) * 100).toFixed(1) : 0;
    const now = Date.now();
    const last = user.lastDailyBonus || 0;
    const cooldown = 24 * 60 * 60 * 1000;
    const canClaim = now - last >= cooldown;

    if (window._bonusInterval) { clearInterval(window._bonusInterval); window._bonusInterval = null; }

    let html = `<div class="section-title">Профиль</div>
        <div class="profile-stat"><span>Ник</span><strong>${user.username}</strong></div>
        <div class="profile-stat"><span>Баланс</span><strong style="color:var(--success);">${user.balance.toFixed(2)}</strong></div>
        <div class="profile-stat"><span>Всего ставок</span><strong>${fin.length}</strong></div>
        <div class="profile-stat"><span>Винрейт</span><strong>${wr}%</strong></div>`;

    if (canClaim) {
        html += `<button class="action-btn" id="claimDailyBtn" style="margin-top:12px;">Получить бонус</button>`;
    } else {
        html += `<div class="transparent-bordered-card" style="margin-top:12px;">
            <div style="font-size:0.7rem;color:var(--text-secondary);margin-bottom:4px;letter-spacing:1px;">СЛЕДУЮЩИЙ БОНУС ЧЕРЕЗ</div>
            <div style="font-size:1.2rem;font-weight:700;color:var(--accent);" id="bonusTimer">--:--:--</div>
        </div>`;
    }

    html += `<button class="action-btn" id="logoutProfileBtn" style="margin-top:16px;background:rgba(239, 68, 68, 0.2);color:var(--danger);border:1px solid rgba(239,68,68,0.3);">Выйти</button>`;
    window.els.tab.innerHTML = html;

    if (!canClaim) {
        const timerEl = document.getElementById('bonusTimer');
        function updateTimer() {
            const remaining = last + cooldown - Date.now();
            if (remaining <= 0) { renderTab('profile'); return; }
            const h = Math.floor(remaining / 3600000);
            const m = Math.floor((remaining % 3600000) / 60000);
            const s = Math.floor((remaining % 60000) / 1000);
            if (timerEl) timerEl.textContent = `${String(h).padStart(2,'0')}:${String(m).padStart(2,'0')}:${String(s).padStart(2,'0')}`;
        }
        updateTimer();
        window._bonusInterval = setInterval(updateTimer, 1000);
    } else {
        document.getElementById('claimDailyBtn').onclick = async () => {
            const bonus = Math.floor(Math.random() * 451) + 50;
            user.balance += bonus;
            user.lastDailyBonus = Date.now();
            await saveUsers();
            alert(`Вы получили ежедневный бонус: ${bonus} коинов!`);
            renderTab('profile');
        };
    }
    document.getElementById('logoutProfileBtn').onclick = logout;
}

function renderNews() {
    let html = '<div class="section-title">Новости</div>';
    const visibleNews = (window.newsList || []).slice().reverse().slice(0, 3);
    
    if (visibleNews.length === 0) html += '<p style="color:#aaa;">Новостей пока нет</p>';
    else {
        visibleNews.forEach(n => {
            html += `<div class="news-item" data-idx="${n.id}">${n.title}</div><div class="news-detail hidden" id="nd${n.id}">${n.text}</div>`;
        });
    }

    const nonAdminUsers = (window.users || []).filter(u => u.role !== 'admin').length;
    html += `<div class="transparent-bordered-card" style="margin-top:16px;">
        <div style="font-size:0.7rem;color:var(--text-secondary);margin-bottom:4px;letter-spacing:1px;">КОЛ-ВО ЛУДОМАНОВ TONBET</div>
        <div style="font-size:1.3rem;font-weight:700;color:#fff;">${nonAdminUsers}</div>
    </div>`;

    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.news-item').forEach(n => n.onclick = () => document.getElementById(`nd${n.dataset.idx}`).classList.toggle('hidden'));
}

function renderLeaderboard() {
    const stats = (window.users || []).filter(u => u.role !== 'admin').map(u => {
        let profit = 0;
        (u.bets || []).forEach(b => { if (b.status === 'win') profit += b.winAmount - b.amount; else if (b.status === 'lose') profit -= b.amount; });
        return { username: u.username, profit };
    }).sort((a, b) => b.profit - a.profit).slice(0, 10);

    let html = '<div class="section-title">Топ 10 TonBet</div>';
    if (stats.length === 0) html += '<p style="color:#aaa;text-align:center;">Пока пусто</p>';
    else {
        html += '<table class="leaderboard-table"><thead><tr><th>#</th><th>Ник</th><th>Доход</th></tr></thead><tbody>';
        stats.forEach((s, i) => html += `<tr><td>${i+1}</td><td>${s.username}</td><td style="color:${s.profit>=0?'var(--success)':'var(--danger)'}">${s.profit >= 0 ? '+' : ''}${s.profit.toFixed(0)}</td></tr>`);
        html += '</tbody></table>';
    }
    window.els.tab.innerHTML = html;
}