// Состояния для пользовательских табов
window.expressState = { step:'divisions', sel:[], div:null, outcomes:{}, totalOdds:0 };
window.matchState = { view:'divisions', div:null, match:null };

function renderExpress() {
    if (window.expressState.step === 'divisions') {
        window.els.tab.innerHTML = `<div class="section-title">Экспресс — Выберите дивизион</div><div class="division-grid"></div>`;
        const grid = window.els.tab.querySelector('.division-grid');
        DIVISIONS.forEach(d => { const c = document.createElement('div'); c.className = 'division-card'; c.textContent = d; c.onclick = () => { window.expressState.div = d; window.expressState.step = 'matches'; renderExpress(); }; grid.appendChild(c); });
    } else if (window.expressState.step === 'matches') {
        const allNotArchived = window.matches.filter(m => m.division === window.expressState.div && !m.archived);
        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">Экспресс – ${window.expressState.div}</div><div class="match-list"></div><button class="action-btn" id="readyBtn" disabled>Готово (0)</button>`;
        window.els.tab.querySelector('.back-link').onclick = () => { window.expressState.step = 'divisions'; renderExpress(); };
        const list = window.els.tab.querySelector('.match-list');
        if (allNotArchived.length === 0) list.innerHTML = '<div style="color:#aaa;text-align:center;padding:20px;">Нет матчей</div>';
        else allNotArchived.forEach(m => {
            const d = document.createElement('div'); d.className = `match-item ${window.expressState.sel.includes(m.id) && m.status==='open' ? 'selected' : ''}`; d.dataset.id = m.id;
            d.innerHTML = `<span>${m.team1} — ${m.team2}</span>${m.status==='open' ? `<div class="check-icon">${window.expressState.sel.includes(m.id) ? '✓' : ''}</div>` : `<span style="color:#ffaa00;font-size:0.8rem;">Закрыт</span>`}`;
            d.onclick = () => { if (m.status !== 'open') return alert('Приём ставок на этот матч закрыт'); if (window.expressState.sel.includes(m.id)) window.expressState.sel = window.expressState.sel.filter(x => x !== m.id); else window.expressState.sel.push(m.id); renderExpress(); };
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
            let tot = 1; selMatches.forEach(m => { const out = window.expressState.outcomes[m.id]; let o = out === 'TS' ? m.odds_TS : out === 'TB' ? m.odds_TB : out === 'TM' ? m.odds_TM : out === 'OZ' ? m.odds_OZ : m.odds[out]; tot *= o; });
            window.expressState.totalOdds = +tot.toFixed(2); window.expressState.step = 'bet'; renderExpress(); return;
        }
        const m = selMatches[idx];
        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">Исход ${idx+1}/${selMatches.length}</div><div style="font-size:1.5rem;text-align:center;margin:20px 0;">${m.team1} — ${m.team2}</div>
            <div class="odds-row">
                <div class="odd-block" data-out="1"><div>П1</div><div class="odd-value">${m.odds['1'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="X"><div>Ничья</div><div class="odd-value">${m.odds['X'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="2"><div>П2</div><div class="odd-value">${m.odds['2'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="TB"><div>ТБ 2.5</div><div class="odd-value">${m.odds_TB.toFixed(2)}</div></div>
                <div class="odd-block" data-out="TM"><div>ТМ 2.5</div><div class="odd-value">${m.odds_TM.toFixed(2)}</div></div>
                <div class="odd-block" data-out="OZ"><div>ОЗ</div><div class="odd-value">${m.odds_OZ.toFixed(2)}</div></div>
                <div class="odd-block" data-out="TS"><div>Точный счёт</div><div class="odd-value">${m.odds_TS.toFixed(2)}</div></div>
            </div>`;
        window.els.tab.querySelector('.back-link').onclick = () => { window.expressState.step = 'matches'; renderExpress(); };
        window.els.tab.querySelectorAll('.odd-block').forEach(b => b.onclick = function() {
            const out = this.dataset.out;
            if (out === 'TS') {
                promptExactScore(m, (score) => {
                    window.expressState.outcomes[m.id] = { type: 'TS', exactScore: score };
                    renderExpress();
                });
            } else {
                window.expressState.outcomes[m.id] = out;
                renderExpress();
            }
        });
    } else if (window.expressState.step === 'bet') {
        window.els.tab.innerHTML = `<div class="back-link">← Изменить исходы</div><div class="section-title">Коэффициент: ${window.expressState.totalOdds.toFixed(2)}</div>
            <div style="display:flex;gap:10px;align-items:center;margin-top:20px;">
                <input type="number" class="bet-amount-input" id="expAmount" placeholder="Сумма" min="1">
                <button class="action-btn" id="placeExpBet">Сделать ставку</button>
            </div>`;
        window.els.tab.querySelector('.back-link').onclick = () => { window.expressState.step = 'outcomes'; window.expressState.outcomes = {}; renderExpress(); };
        window.els.tab.querySelector('#placeExpBet').onclick = async () => {
            const user = getCurrentUser(); if (!user) return;
            const amount = +window.els.tab.querySelector('#expAmount').value;
            if (isNaN(amount) || amount <= 0) return alert('Некорректная сумма');
            if (amount > user.balance) return alert('Недостаточно средств');
            if (user.frozenUntil > Date.now()) return alert('Ставки заморожены до ' + new Date(user.frozenUntil).toLocaleString());
            const legs = window.expressState.sel.map(id => { 
                const m = window.matches.find(x => x.id === id); 
                const outData = window.expressState.outcomes[id];
                let outcome, odds, exactScore = null;
                if (typeof outData === 'object' && outData.type === 'TS') {
                    outcome = 'TS';
                    odds = m.odds_TS;
                    exactScore = outData.exactScore;
                } else {
                    outcome = outData;
                    odds = outcome === 'TB' ? m.odds_TB : outcome === 'TM' ? m.odds_TM : outcome === 'OZ' ? m.odds_OZ : m.odds[outcome];
                }
                return { matchId: id, team1: m.team1, team2: m.team2, outcome, odds, exactScore };
            });
            user.balance -= amount;
            user.bets.push({ type: 'express', legs, totalOdds: window.expressState.totalOdds, amount, status: 'pending', winAmount: 0 });
            await saveUsers();
            alert('Ставка принята!');
            window.expressState = { step:'divisions', sel:[], div:null, outcomes:{}, totalOdds:0 };
            renderTab('express');
        };
    }
}

function renderMatches() {
    if (window.matchState.view === 'divisions') {
        window.els.tab.innerHTML = `<div class="section-title">Выберите дивизион</div><div class="division-grid"></div>`;
        const grid = window.els.tab.querySelector('.division-grid');
        DIVISIONS.forEach(d => { const c = document.createElement('div'); c.className = 'division-card'; c.textContent = d; c.onclick = () => { window.matchState.div = d; window.matchState.view = 'matches'; renderMatches(); }; grid.appendChild(c); });
    } else if (window.matchState.view === 'matches') {
        const list = window.matches.filter(m => m.division === window.matchState.div && !m.archived);
        window.els.tab.innerHTML = `<div class="back-link">← Назад</div><div class="section-title">${window.matchState.div}</div><div class="match-list"></div>`;
        window.els.tab.querySelector('.back-link').onclick = () => { window.matchState.view = 'divisions'; renderMatches(); };
        const ml = window.els.tab.querySelector('.match-list');
        if (list.length === 0) ml.innerHTML = '<div style="color:#aaa;text-align:center;padding:20px;">Нет матчей</div>';
        else list.forEach(m => {
            const d = document.createElement('div'); d.className = 'match-item';
            d.innerHTML = `<span>${m.team1} — ${m.team2}</span><span style="color:${m.status==='open'?'#aaa':'#ffaa00'};">${m.status==='open'?'Ставка':'Закрыт'}</span>`;
            d.onclick = () => { window.matchState.match = m; window.matchState.view = 'bet'; renderMatches(); };
            ml.appendChild(d);
        });
    } else if (window.matchState.view === 'bet') {
        const m = window.matchState.match;
        window.els.tab.innerHTML = `<div class="back-link">← К матчам</div><div class="bet-detail">
            <div style="font-size:1.5rem;text-align:center;margin-bottom:15px;">${m.team1} — ${m.team2}</div>
            <div class="odds-row">
                <div class="odd-block" data-out="1"><div>П1</div><div class="odd-value">${m.odds['1'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="X"><div>Ничья</div><div class="odd-value">${m.odds['X'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="2"><div>П2</div><div class="odd-value">${m.odds['2'].toFixed(2)}</div></div>
                <div class="odd-block" data-out="TB"><div>ТБ 2.5</div><div class="odd-value">${m.odds_TB.toFixed(2)}</div></div>
                <div class="odd-block" data-out="TM"><div>ТМ 2.5</div><div class="odd-value">${m.odds_TM.toFixed(2)}</div></div>
                <div class="odd-block" data-out="OZ"><div>ОЗ</div><div class="odd-value">${m.odds_OZ.toFixed(2)}</div></div>
                <div class="odd-block" data-out="TS"><div>Точный счёт</div><div class="odd-value">${m.odds_TS.toFixed(2)}</div></div>
            </div>
            ${m.status === 'open' ? `<div style="display:flex;gap:10px;align-items:center;margin-top:20px;">
                <input type="number" class="bet-amount-input" id="betAmount" placeholder="Сумма" min="1">
                <button class="action-btn" id="placeBet">Ставка</button>
            </div>` : `<div style="margin-top:20px;color:#ffaa00;">Приём ставок закрыт</div>`}
        </div>`;
        window.els.tab.querySelector('.back-link').onclick = () => { window.matchState.view = 'matches'; renderMatches(); };
        if (m.status === 'open') {
            let selOut = null;
            let exactScore = null;
            window.els.tab.querySelectorAll('.odd-block').forEach(b => b.onclick = function() {
                window.els.tab.querySelectorAll('.odd-block').forEach(x => x.classList.remove('selected'));
                const out = this.dataset.out;
                if (out === 'TS') {
                    promptExactScore(m, (score) => {
                        selOut = 'TS';
                        exactScore = score;
                        this.classList.add('selected');
                    });
                } else {
                    this.classList.add('selected');
                    selOut = out;
                    exactScore = null;
                }
            });
            window.els.tab.querySelector('#placeBet').onclick = async () => {
                const user = getCurrentUser(); if (!user) return;
                if (!selOut) return alert('Выберите исход');
                if (selOut === 'TS' && !exactScore) return alert('Введите точный счёт');
                const amount = +window.els.tab.querySelector('#betAmount').value;
                if (isNaN(amount) || amount <= 0) return alert('Некорректная сумма');
                if (amount > user.balance) return alert('Недостаточно средств');
                if (user.frozenUntil > Date.now()) return alert('Ставки заморожены до ' + new Date(user.frozenUntil).toLocaleString());
                let odds = selOut === 'TS' ? m.odds_TS : selOut === 'TB' ? m.odds_TB : selOut === 'TM' ? m.odds_TM : selOut === 'OZ' ? m.odds_OZ : m.odds[selOut];
                user.balance -= amount;
                user.bets.push({ type:'single', matchId:m.id, team1:m.team1, team2:m.team2, outcome:selOut, amount, odds, status:'pending', winAmount:0, exactScore });
                await saveUsers();
                alert('Ставка принята!');
                document.getElementById('betAmount').value = '';
                window.els.tab.querySelectorAll('.odd-block').forEach(x => x.classList.remove('selected'));
                selOut = null;
                exactScore = null;
            };
        }
    }
}

function promptExactScore(match, callback) {
    const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
    overlay.innerHTML = `
        <div class="modal-content">
            <div style="font-size:1.3rem;margin-bottom:15px;">Точный счёт: ${match.team1} — ${match.team2}</div>
            <div class="exact-score-inputs">
                <input type="number" id="exactT1" placeholder="${match.team1}" min="0" value="0">
                <span>:</span>
                <input type="number" id="exactT2" placeholder="${match.team2}" min="0" value="0">
            </div>
            <button class="modal-btn green" id="confirmExactScore">Подтвердить</button>
            <button class="modal-btn red" id="cancelExactScore">Отмена</button>
        </div>
    `;
    document.body.appendChild(overlay);
    document.getElementById('confirmExactScore').onclick = () => {
        const t1 = parseInt(document.getElementById('exactT1').value);
        const t2 = parseInt(document.getElementById('exactT2').value);
        if (isNaN(t1) || isNaN(t2) || t1 < 0 || t2 < 0) return alert('Введите корректный счёт');
        overlay.remove();
        callback({ t1, t2 });
    };
    document.getElementById('cancelExactScore').onclick = () => overlay.remove();
}

function renderMyBets() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }
    let bets = (user.bets || []).slice().reverse();
    if (window.currentFilter === 'pending') bets = bets.filter(b => b.status === 'pending');
    else if (window.currentFilter === 'win') bets = bets.filter(b => b.status === 'win');
    else if (window.currentFilter === 'lose') bets = bets.filter(b => b.status === 'lose');
    let html = '<div class="section-title">Мои Ставки</div>';
    html += `<div class="filter-tabs"><div class="filter-tab ${window.currentFilter==='all'?'active':''}" data-f="all">Все</div><div class="filter-tab ${window.currentFilter==='pending'?'active':''}" data-f="pending">Действующие</div><div class="filter-tab ${window.currentFilter==='win'?'active':''}" data-f="win">Выигрышные</div><div class="filter-tab ${window.currentFilter==='lose'?'active':''}" data-f="lose">Проигрыши</div></div>`;
    if (bets.length === 0) html += '<div style="color:#aaa;text-align:center;padding:20px;">Нет ставок</div>';
    else bets.forEach(bet => {
        const origIndex = user.bets.indexOf(bet);
        if (bet.type === 'express') {
            const legs = bet.legs.map(l => `${l.team1} — ${l.team2} (${l.outcome==='TS' ? `Точный счёт ${l.exactScore.t1}:${l.exactScore.t2}` : l.outcome==='TB'?'ТБ 2.5':l.outcome==='TM'?'ТМ 2.5':l.outcome==='OZ'?'ОЗ':(l.outcome==='1'?'П1':l.outcome==='X'?'Ничья':'П2')}) @${l.odds.toFixed(2)}`).join('<br>');
            const st = bet.status === 'win' ? `<span class="status-win"><svg class="status-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3"><polyline points="20 6 9 17 4 12"/></svg>Выигрыш</span>` : bet.status === 'lose' ? `<span class="status-lose"><svg class="status-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>Проигрыш</span>` : '<span style="color:#aaa">Ожидание</span>';
            html += `<div style="background:var(--card-bg);border-radius:16px;padding:14px;margin-bottom:10px;" data-bet-index="${origIndex}">
                <div><strong>Экспресс</strong> (${bet.legs.length} событий, коэф. ${bet.totalOdds.toFixed(2)})</div>
                <div style="font-size:0.85rem;margin:8px 0;">${legs}</div>
                <div style="display:flex;justify-content:space-between;"><span>Сумма: ${bet.amount.toFixed(2)}</span>${st}</div>
            </div>`;
        } else {
            const out = bet.outcome === 'TS' ? `Точный счёт ${bet.exactScore.t1}:${bet.exactScore.t2}` : bet.outcome==='TB'?'ТБ 2.5':bet.outcome==='TM'?'ТМ 2.5':bet.outcome==='OZ'?'ОЗ':(bet.outcome==='1'?'П1':bet.outcome==='X'?'Ничья':'П2');
            const st = bet.status === 'win' ? `<span class="status-win"><svg class="status-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3"><polyline points="20 6 9 17 4 12"/></svg>Выигрыш</span>` : bet.status === 'lose' ? `<span class="status-lose"><svg class="status-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>Проигрыш</span>` : '<span style="color:#aaa">Ожидание</span>';
            html += `<div style="background:var(--card-bg);border-radius:16px;padding:14px;margin-bottom:10px;" data-bet-index="${origIndex}">
                <div style="display:flex;justify-content:space-between;"><strong>${bet.team1} — ${bet.team2}</strong><span>${out} @ ${bet.odds.toFixed(2)}</span></div>
                <div style="display:flex;justify-content:space-between;margin-top:6px;"><span>Сумма: ${bet.amount.toFixed(2)}</span>${st}</div>
            </div>`;
        }
    });
    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.filter-tab').forEach(t => t.onclick = () => { window.currentFilter = t.dataset.f; renderMyBets(); });
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
        if (user.activatedPromos && user.activatedPromos.includes(code)) { alert('Вы уже активировали этот промокод ранее.'); return; }
        const promo = window.promoCodes.find(p => p.code === code && p.remaining > 0);
        if (!promo) { alert('Промокод недействителен или исчерпан.'); return; }
        promo.remaining--;
        if (!user.activatedPromos) user.activatedPromos = [];
        user.activatedPromos.push(code);
        addBalanceWithLoan(user, promo.bonus);
        window.promoLog.push({ username: user.username, promoCode: code, amount: promo.bonus, timestamp: Date.now() });
        await Promise.all([saveUsers(), savePromoCodes(), savePromoLog()]);
        const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
        overlay.innerHTML = `<div class="modal-content"><div style="font-size:1.3rem;margin-bottom:15px;">Промокод Активирован!</div><div>Вы успешно активировали промокод, ваша награда составила: ${promo.bonus} коинов!</div><button class="modal-btn green closeModal">Ок</button></div>`;
        document.body.appendChild(overlay);
        overlay.querySelector('.closeModal').onclick = () => overlay.remove();
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
    const promoCount = user.activatedPromos ? user.activatedPromos.length : 0;
    const now = Date.now();
    const last = user.lastDailyBonus || 0;
    const cooldown = 24 * 60 * 60 * 1000;
    const canClaim = now - last >= cooldown;

    let html = `<div class="section-title">Профиль</div>
        <div class="profile-stat"><span>Ник</span><strong>${user.username}</strong></div>
        <div class="profile-stat"><span>Баланс</span><strong style="color:var(--success);">${user.balance.toFixed(2)}</strong></div>
        <div class="profile-stat"><span>Ставок</span><strong>${fin.length}</strong></div>
        <div class="profile-stat"><span>Выигрышей</span><strong>${wins}</strong></div>
        <div class="profile-stat"><span>Винрейт</span><strong>${wr}%</strong></div>
        <div class="profile-stat"><span>Промокодов</span><strong>${promoCount}</strong></div>
        <div class="profile-stat"><span>Кредитная доверенность</span><strong>${user.creditTrust}%</strong></div>`;
    if (user.frozenUntil > Date.now()) {
        html += `<div class="profile-stat" style="color:var(--danger);">Ставки заморожены до ${new Date(user.frozenUntil).toLocaleString()}</div>`;
    }
    if (canClaim) {
        html += `<button class="action-btn" id="claimDailyBtn" style="margin-top:15px;">
            <svg width="18" height="18" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2" fill="none" style="vertical-align:middle;margin-right:8px;"><path d="M20 12v8H4v-8M12 2v6m0 0l4-4m-4 4L8 8"/></svg>Получить бонус
        </button>`;
    } else {
        html += `<div class="bonus-timer" id="bonusTimerContainer">
            <div class="timer-title">СЛЕДУЮЩИЙ БОНУС ЧЕРЕЗ</div>
            <div class="timer-numbers" id="bonusTimer">--:--:--</div>
        </div>`;
    }
    html += `<div class="push-status" id="pushStatus">Проверка уведомлений...</div>
             <button class="action-btn small" id="togglePushBtn">Включить уведомления</button>`;
    html += `<button class="action-btn" id="logoutProfileBtn" style="margin-top:20px;">Выйти</button>`;
    window.els.tab.innerHTML = html;

    checkPushSubscription().then(hasSub => {
        const statusDiv = document.getElementById('pushStatus');
        if (statusDiv) statusDiv.innerHTML = hasSub 
            ? '<span style="color:var(--success);">Уведомления включены</span>' 
            : '<span style="color:var(--danger);">Уведомления не настроены</span>';
    });

    document.getElementById('togglePushBtn').onclick = async () => {
        const hasSub = await checkPushSubscription();
        if (hasSub) {
            if (confirm('Отключить уведомления?')) {
                await db.ref(`pushSubscriptions/${window.currentUsername}`).remove();
                renderProfile();
            }
        } else {
            const granted = await requestPushPermission();
            if (granted) {
                alert('Уведомления включены!');
                renderProfile();
            } else {
                alert('Не удалось получить разрешение.');
            }
        }
    };

    if (!canClaim) {
        const timerEl = document.getElementById('bonusTimer');
        function updateTimer() {
            const now2 = Date.now();
            const remaining = last + cooldown - now2;
            if (remaining <= 0) { timerEl.textContent = '00:00:00'; renderTab('profile'); return; }
            const hours = Math.floor(remaining / 3600000);
            const minutes = Math.floor((remaining % 3600000) / 60000);
            const seconds = Math.floor((remaining % 60000) / 1000);
            timerEl.textContent = `${String(hours).padStart(2,'0')}:${String(minutes).padStart(2,'0')}:${String(seconds).padStart(2,'0')}`;
        }
        updateTimer();
        const interval = setInterval(updateTimer, 1000);
        if (window._bonusInterval) clearInterval(window._bonusInterval);
        window._bonusInterval = interval;
    }

    if (canClaim) {
        document.getElementById('claimDailyBtn').onclick = async () => {
            const rand = Math.random();
            let bonus;
            if (rand < 0.7) bonus = Math.floor(Math.random() * 451) + 50;
            else if (rand < 0.95) bonus = Math.floor(Math.random() * 451) + 500;
            else bonus = Math.floor(Math.random() * 2000) + 500;
            addBalanceWithLoan(user, bonus);
            user.lastDailyBonus = Date.now();
            await saveUsers();
            const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
            overlay.innerHTML = `<div class="modal-content"><div style="font-size:1.5rem;font-weight:700;margin-bottom:15px;">БОНУС</div><div>Поздравляем, вы получили ежедневный бонус в размере ${bonus} коинов! Приходите завтра и получайте бонус ещё раз!</div><button class="modal-btn green closeModal">Продолжить</button></div>`;
            document.body.appendChild(overlay);
            overlay.querySelector('.closeModal').onclick = () => overlay.remove();
            renderTab('profile');
        };
    }
    document.getElementById('logoutProfileBtn').onclick = logout;
}

function renderNews() {
    let html = '<div class="section-title">Новости</div>';
    if (window.newsList.length === 0) html += '<p style="color:#aaa;">Новостей пока нет</p>';
    else {
        window.newsList.slice().reverse().forEach(n => {
            html += `<div class="news-item" data-idx="${n.id}">${n.title}</div><div class="news-detail hidden" id="nd${n.id}">${n.text}</div>`;
        });
    }
    html += `<div style="margin-top:20px;"><a href="https://t.me/tonboxftcl" target="_blank" class="contact-btn"><svg width="18" height="18" viewBox="0 0 24 24"><path fill="currentColor" d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm4.64 6.8c-.15 1.58-.8 5.42-1.13 7.19-.14.75-.42 1-.68 1.03-.58.05-1.02-.38-1.58-.75-.88-.58-1.38-.94-2.23-1.5-.99-.65-.35-1.01.22-1.59.15-.15 2.71-2.48 2.76-2.69.01-.03.01-.14-.05-.2-.06-.06-.16-.04-.23-.02-.1.02-1.66 1.06-4.68 3.09-.44.3-.84.45-1.2.44-.4-.01-1.16-.22-1.72-.41-.69-.23-1.24-.35-1.19-.73.03-.2.3-.41.83-.62 3.24-1.41 5.41-2.35 6.5-2.8 3.09-1.29 3.74-1.51 4.16-1.52.09 0 .3.02.43.13.11.09.14.22.15.31-.01.02-.02.1-.03.16z"/></svg>Телеграм Канал</a><a href="https://t.me/fanziks" target="_blank" class="contact-btn"><svg width="18" height="18" viewBox="0 0 24 24"><path fill="currentColor" d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm4.64 6.8c-.15 1.58-.8 5.42-1.13 7.19-.14.75-.42 1-.68 1.03-.58.05-1.02-.38-1.58-.75-.88-.58-1.38-.94-2.23-1.5-.99-.65-.35-1.01.22-1.59.15-.15 2.71-2.48 2.76-2.69.01-.03.01-.14-.05-.2-.06-.06-.16-.04-.23-.02-.1.02-1.66 1.06-4.68 3.09-.44.3-.84.45-1.2.44-.4-.01-1.16-.22-1.72-.41-.69-.23-1.24-.35-1.19-.73.03-.2.3-.41.83-.62 3.24-1.41 5.41-2.35 6.5-2.8 3.09-1.29 3.74-1.51 4.16-1.52.09 0 .3.02.43.13.11.09.14.22.15.31-.01.02-.02.1-.03.16z"/></svg>Связаться с создателем</a></div><div class="user-counter"><div class="counter-title">КОЛ-ВО ЛУДОМАНОВ TONBET</div><div class="counter-number">${window.users.filter(u => u.role !== 'admin').length}</div></div>`;
    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.news-item').forEach(n => n.onclick = () => document.getElementById(`nd${n.dataset.idx}`).classList.toggle('hidden'));
}

function renderLeaderboard() {
    const stats = window.users.filter(u => u.role !== 'admin').map(u => {
        const bets = u.bets || [];
        let profit = 0;
        bets.forEach(b => { if (b.status === 'win') profit += b.winAmount - b.amount; else if (b.status === 'lose') profit -= b.amount; });
        return { username: u.username, profit };
    }).sort((a, b) => b.profit - a.profit).slice(0, 10);
    let html = '<div class="section-title">Топ 10 TonBet</div>';
    if (stats.length === 0) html += '<p style="color:#aaa;text-align:center;padding:20px;">Пока пусто</p>';
    else {
        html += '<table class="leaderboard-table"><thead><tr><th>#</th><th>Ник</th><th>Чистый доход</th></tr></thead><tbody>';
        stats.forEach((s, i) => html += `<tr><td>${i+1}</td><td>${s.username}</td><td class="profit-positive">${s.profit >= 0 ? '+' : ''}${s.profit.toFixed(2)}</td></tr>`);
        html += '</tbody></table>';
    }
    window.els.tab.innerHTML = html;
}

function renderCredit() {
    const user = getCurrentUser();
    if (!user) { window.els.tab.innerHTML = '<div class="section-title">Войдите заново</div>'; return; }
    checkLoanStatus(user);
    let html = '<div class="section-title">Кредит</div>';

    if (user.loanAmount) {
        const details = getLoanDetails(user);
        html += `<div class="credit-card">
            <div><strong>Текущий кредит:</strong> ${user.loanAmount.toFixed(0)} коинов</div>
            <div class="loan-info">Взято: ${new Date(user.loanTakenTimestamp).toLocaleDateString()}</div>
            <div class="loan-info">Дней прошло: ${details.daysPassed}</div>
            <div class="loan-info">Проценты: +${details.interest} коинов</div>
            <div class="loan-info">Всего к погашению: ${details.totalDue.toFixed(0)} коинов</div>
            <div class="loan-info">Погашено: ${details.repaid.toFixed(0)} коинов</div>
            <div class="loan-info">Осталось: ${details.remaining.toFixed(0)} коинов</div>
            ${details.isOverdue ? '<div style="color:var(--danger);">Просрочен! Автосписание возможно.</div>' : ''}
            <button class="action-btn" id="repayLoanBtn">Погасить</button>
        </div>`;
    } else {
        const maxLoan = user.creditTrust === 100 ? 25000 : user.creditTrust === 75 ? 20000 : user.creditTrust === 50 ? 10000 : user.creditTrust === 25 ? 5000 : 0;
        html += `<div class="credit-card">
            <div>Кредитная доверенность: ${user.creditTrust}%</div>
            <div class="trust-bar"><div class="trust-fill" style="width:${user.creditTrust}%"></div></div>
            <div class="loan-info">Максимальная сумма: ${maxLoan} коинов</div>
            ${user.creditTrust > 0 ? `
            <div class="input-group">
                <label>Сумма кредита</label>
                <input type="range" class="credit-slider" id="loanAmountSlider" min="1000" max="${maxLoan}" step="1000" value="1000">
                <input type="number" id="loanAmountInput" value="1000" min="1000" max="${maxLoan}" style="width:100%; margin-top:10px;">
            </div>
            <button class="action-btn" id="takeLoanBtn">Взять кредит</button>
            ` : `<div>Кредит недоступен. Восстановление через ${Math.ceil((user.trustRecoveryTimestamp - Date.now()) / (1000 * 60 * 60 * 24))} дн.</div>`}
        </div>`;
    }
    if (user.frozenUntil > Date.now()) {
        html += `<div class="credit-card" style="border-color:var(--danger);">
            <div style="color:var(--danger);">Ставки заморожены до ${new Date(user.frozenUntil).toLocaleString()}</div>
        </div>`;
    }
    window.els.tab.innerHTML = html;

    window.els.tab.addEventListener('click', async (e) => {
        const target = e.target;
        if (target.id === 'takeLoanBtn') {
            const amount = parseInt(document.getElementById('loanAmountInput').value);
            const maxLoan = user.creditTrust === 100 ? 25000 : user.creditTrust === 75 ? 20000 : user.creditTrust === 50 ? 10000 : user.creditTrust === 25 ? 5000 : 0;
            if (isNaN(amount) || amount < 1000 || amount > maxLoan) return alert('Некорректная сумма');
            user.loanAmount = amount;
            user.loanTakenTimestamp = Date.now();
            user.loanRepaid = 0;
            user.balance += amount;
            window.loanLogs.push({ username: user.username, action: 'taken', amount, timestamp: Date.now() });
            await saveUsers(); await saveLoanLogs();
            alert('Кредит получен!');
            renderCredit();
        } else if (target.id === 'repayLoanBtn') {
            const details = getLoanDetails(user);
            const remaining = details.remaining;
            const maxPay = Math.min(user.balance, remaining);
            const payAmount = prompt(`Введите сумму для погашения (макс: ${maxPay.toFixed(0)})`, maxPay.toFixed(0));
            if (payAmount === null) return;
            const amount = parseInt(payAmount);
            if (isNaN(amount) || amount <= 0 || amount > maxPay) return alert('Некорректная сумма');
            user.balance -= amount;
            applyLoanPayment(user, amount);
            await saveUsers(); await saveLoanLogs();
            alert('Платёж принят!');
            renderCredit();
        }
    });

    const slider = document.getElementById('loanAmountSlider');
    const input = document.getElementById('loanAmountInput');
    if (slider && input) {
        slider.oninput = () => { input.value = slider.value; };
        input.oninput = () => { slider.value = input.value; };
    }
}
