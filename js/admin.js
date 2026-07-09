// ========== АДМИНКА: Управление матчами ==========
function renderAdminManage() {
    const divMatches = window.matches.filter(m => m.division === window.adminDivision && !m.archived);
    const archivedDivMatches = window.matches.filter(m => m.division === window.adminDivision && m.archived);
    let html = `<div class="section-title">Управление матчами</div>`;
    html += `<div class="division-grid" style="margin-bottom:20px;">`;
    DIVISIONS.forEach(d => {
        html += `<div class="division-card ${d === window.adminDivision ? 'selected' : ''}" onclick="window._selectAdminDivision('${d}')" style="${d === window.adminDivision ? 'background:rgba(233,69,96,0.2);border-color:var(--primary);' : ''}">${d}</div>`;
    });
    html += `</div>`;
    html += `<div style="margin-bottom:15px;">
        <button class="action-btn small" onclick="window._massOpenDivision()">Открыть все линии в ${window.adminDivision}</button>
        <button class="action-btn small red" onclick="window._massCloseDivision()">Закрыть все линии в ${window.adminDivision}</button>
        <button class="action-btn small" onclick="window._deleteAllInDivision()">Удалить все матчи в ${window.adminDivision}</button>
    </div>`;
    html += `<div style="font-weight:600;margin-bottom:10px;">Активные матчи (${divMatches.length})</div>`;
    if (divMatches.length === 0) html += '<p style="color:#aaa;">Нет активных матчей</p>';
    else divMatches.forEach(m => {
        const isOpen = m.status === 'open';
        html += `<div class="admin-match-card">
            <div class="admin-match-header"><strong>${m.team1} — ${m.team2}</strong></div>
            <div class="admin-match-status">Статус: <span style="color:${isOpen?'#2ecc71':'#e74c3c'};">${isOpen?'ОТКРЫТ':'ЗАКРЫТ'}</span>${m.score ? ` | Счёт: ${m.score.t1}:${m.score.t2}` : ''}</div>
            <div class="admin-match-odds">П1: ${m.odds['1'].toFixed(2)} | X: ${m.odds['X'].toFixed(2)} | П2: ${m.odds['2'].toFixed(2)} | ТБ: ${m.odds_TB.toFixed(2)} | ТМ: ${m.odds_TM.toFixed(2)} | ОЗ: ${m.odds_OZ.toFixed(2)} | ТС: ${m.odds_TS.toFixed(2)}</div>
            <div style="margin-top:8px;">
                <button class="action-btn small ${isOpen?'red':'green'}" onclick="window._toggleMatchStatus('${m.id}')">${isOpen?'Закрыть линию':'Открыть линию'}</button>
                ${!m.score ? `<button class="action-btn small" onclick="window._editMatch('${m.id}')">Изменить</button>` : ''}
                <button class="action-btn small" onclick="window._deleteMatch('${m.id}')">Удалить</button>
                <button class="action-btn small" onclick="window._viewMatchBets('${m.id}')">Ставки</button>
                ${!isOpen && !m.score ? `<button class="action-btn small green" onclick="window._setMatchScore('${m.id}')">Ввести счёт</button>` : ''}
                ${m.score ? `<button class="action-btn small" onclick="window._editMatchScore('${m.id}')">Изменить счёт</button>` : ''}
                <button class="action-btn small" onclick="window._archiveMatch('${m.id}')">Архивировать</button>
            </div>
        </div>`;
    });
    if (archivedDivMatches.length > 0) {
        html += `<div style="font-weight:600;margin:20px 0 10px;">Архив (${archivedDivMatches.length})</div>`;
        archivedDivMatches.forEach(m => {
            html += `<div class="admin-match-card" style="opacity:0.7;">
                <div class="admin-match-header"><strong>${m.team1} — ${m.team2}</strong></div>
                <div class="admin-match-status">Счёт: ${m.score ? m.score.t1+':'+m.score.t2 : '—'} | Результат: ${m.result || '—'}</div>
                <div style="margin-top:8px;">
                    <button class="action-btn small" onclick="window._restoreMatch('${m.id}')">Восстановить</button>
                    ${m.score ? `<button class="action-btn small" onclick="window._editMatchScore('${m.id}')">Изменить счёт</button>` : ''}
                </div>
            </div>`;
        });
    }
    window.els.tab.innerHTML = html;
}

window._selectAdminDivision = function(d) { window.adminDivision = d; renderTab('adminManage'); };
window._massOpenDivision = async function() { window.matches.forEach(m => { if (m.division === window.adminDivision && !m.archived) m.status = 'open'; }); await saveMatches(); await logAdminAction(`Открыл все линии в ${window.adminDivision}`); renderTab('adminManage'); };
window._massCloseDivision = async function() { window.matches.forEach(m => { if (m.division === window.adminDivision && !m.archived) m.status = 'closed'; }); await saveMatches(); await logAdminAction(`Закрыл все линии в ${window.adminDivision}`); renderTab('adminManage'); };
window._deleteAllInDivision = async function() { if (!confirm(`Удалить ВСЕ матчи в ${window.adminDivision}? Это действие необратимо!`)) return; window.matches = window.matches.filter(m => !(m.division === window.adminDivision && !m.archived)); await saveMatches(); await logAdminAction(`Удалил все матчи в ${window.adminDivision}`); renderTab('adminManage'); };
window._toggleMatchStatus = async function(matchId) { const m = window.matches.find(x => x.id === matchId); if (m) { m.status = m.status === 'open' ? 'closed' : 'open'; await saveMatches(); await logAdminAction(`${m.status === 'open' ? 'Открыл' : 'Закрыл'} линию матча ${m.team1} — ${m.team2}`); renderTab('adminManage'); } };
window._deleteMatch = async function(matchId) { if (!confirm('Удалить матч безвозвратно?')) return; const m = window.matches.find(x => x.id === matchId); window.matches = window.matches.filter(x => x.id !== matchId); await saveMatches(); if (m) await logAdminAction(`Удалил матч ${m.team1} — ${m.team2}`); renderTab('adminManage'); };
window._archiveMatch = async function(matchId) { const m = window.matches.find(x => x.id === matchId); if (m) { m.archived = true; m.status = 'closed'; await saveMatches(); await logAdminAction(`Архивировал матч ${m.team1} — ${m.team2}`); renderTab('adminManage'); } };
window._restoreMatch = async function(matchId) { const m = window.matches.find(x => x.id === matchId); if (m) { m.archived = false; m.status = 'closed'; await saveMatches(); await logAdminAction(`Восстановил матч ${m.team1} — ${m.team2} из архива`); renderTab('adminManage'); } };

window._editMatch = function(matchId) {
    const m = window.matches.find(x => x.id === matchId);
    if (!m) return;
    window.els.tab.innerHTML = `<div class="back-link" onclick="renderTab('adminManage')">← Назад</div><div class="section-title">Редактировать матч</div>
        <div class="input-group"><label>Команда 1</label><input type="text" id="editTeam1" value="${m.team1}"></div>
        <div class="input-group"><label>Команда 2</label><input type="text" id="editTeam2" value="${m.team2}"></div>
        <div class="input-group"><label>Коэф. П1</label><input type="number" step="0.01" id="editOdds1" value="${m.odds['1']}"></div>
        <div class="input-group"><label>Коэф. Ничья</label><input type="number" step="0.01" id="editOddsX" value="${m.odds['X']}"></div>
        <div class="input-group"><label>Коэф. П2</label><input type="number" step="0.01" id="editOdds2" value="${m.odds['2']}"></div>
        <div class="input-group"><label>ТБ 2.5</label><input type="number" step="0.01" id="editOddsTB" value="${m.odds_TB}"></div>
        <div class="input-group"><label>ТМ 2.5</label><input type="number" step="0.01" id="editOddsTM" value="${m.odds_TM}"></div>
        <div class="input-group"><label>ОЗ</label><input type="number" step="0.01" id="editOddsOZ" value="${m.odds_OZ}"></div>
        <div class="input-group"><label>Точный счёт</label><input type="number" step="0.01" id="editOddsTS" value="${m.odds_TS}"></div>
        <div class="input-group"><label>Коэф. 1-го тайма (П1/Х/П2/ТБ/ТМ/ОЗ/ТС через запятую)</label>
        <input type="text" id="editOdds1H" value="${m.odds_1H ? Object.values(m.odds_1H).join(',') : ''}"></div>
        <div class="input-group"><label>Коэф. 2-го тайма (через запятую)</label>
        <input type="text" id="editOdds2H" value="${m.odds_2H ? Object.values(m.odds_2H).join(',') : ''}"></div>
        <button class="action-btn" id="saveEditBtn">Сохранить</button>`;
    document.getElementById('saveEditBtn').onclick = async () => {
        m.team1 = document.getElementById('editTeam1').value.trim();
        m.team2 = document.getElementById('editTeam2').value.trim();
        m.odds = { '1': +document.getElementById('editOdds1').value, 'X': +document.getElementById('editOddsX').value, '2': +document.getElementById('editOdds2').value };
        m.odds_TB = +document.getElementById('editOddsTB').value;
        m.odds_TM = +document.getElementById('editOddsTM').value;
        m.odds_OZ = +document.getElementById('editOddsOZ').value;
        m.odds_TS = +document.getElementById('editOddsTS').value;

        const parsePeriodOdds = (str) => {
            const parts = str.split(',').map(Number);
            if (parts.length !== 7) return null;
            return {
                '1': parts[0], 'X': parts[1], '2': parts[2],
                'TB': parts[3], 'TM': parts[4], 'OZ': parts[5],
                'TS': parts[6]
            };
        };
        m.odds_1H = parsePeriodOdds(document.getElementById('editOdds1H').value);
        m.odds_2H = parsePeriodOdds(document.getElementById('editOdds2H').value);

        await saveMatches(); await logAdminAction(`Изменил матч ${m.team1} — ${m.team2}`); alert('Матч обновлён'); renderTab('adminManage');
    };
};

window._viewMatchBets = function(matchId) {
    const m = window.matches.find(x => x.id === matchId);
    if (!m) return;
    const allBets = [];
    window.users.forEach(u => (u.bets||[]).forEach(b => { 
        if (b.type === 'single' && b.matchId === matchId) allBets.push({...b, username: u.username});
        if (b.type === 'express' && b.legs) {
            b.legs.forEach(leg => { if (leg.matchId === matchId) allBets.push({...leg, username: u.username, type: 'express_leg', amount: b.amount, status: b.status}); });
        }
    }));
    let html = `<div class="back-link" onclick="renderTab('adminManage')">← Назад</div><div class="section-title">Ставки на ${m.team1} — ${m.team2}</div>`;
    if (allBets.length === 0) html += '<p style="color:#aaa;">Нет ставок</p>';
    else {
        const totalAmount = allBets.reduce((s,b) => s + (b.amount || 0), 0);
        html += `<p>Всего ставок: ${allBets.length}, общая сумма: ${totalAmount.toFixed(2)}</p>`;
        allBets.forEach(b => {
            const outcome = b.outcome === 'TS' ? `Точный счёт ${b.exactScore.t1}:${b.exactScore.t2}` : b.outcome==='TB'?'ТБ 2.5':b.outcome==='TM'?'ТМ 2.5':b.outcome==='OZ'?'ОЗ':(b.outcome==='1'?'П1':b.outcome==='X'?'Ничья':'П2');
            html += `<div style="background:var(--card-bg);border-radius:12px;padding:10px;margin-bottom:6px;"><strong>${b.username}</strong> — ${outcome} @ ${b.odds ? b.odds.toFixed(2) : '?'} | Сумма: ${(b.amount || 0).toFixed(2)} | Статус: ${b.status}</div>`;
        });
    }
    window.els.tab.innerHTML = html;
};

window._setMatchScore = function(matchId) {
    const m = window.matches.find(x => x.id === matchId);
    if (!m) return;
    window.els.tab.innerHTML = `<div class="back-link" onclick="renderTab('adminManage')">← Назад</div><div class="section-title">Ввод счёта: ${m.team1} — ${m.team2}</div>
        <div style="margin:10px 0;"><strong>Первый тайм:</strong></div>
        <div style="display:flex;gap:10px;align-items:center;margin-bottom:10px;">
            <input type="number" class="scoreT1_1H" placeholder="${m.team1}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
            <span>:</span>
            <input type="number" class="scoreT2_1H" placeholder="${m.team2}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
        </div>
        <div style="margin:10px 0;"><strong>Второй тайм:</strong></div>
        <div style="display:flex;gap:10px;align-items:center;margin-bottom:15px;">
            <input type="number" class="scoreT1_2H" placeholder="${m.team1}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
            <span>:</span>
            <input type="number" class="scoreT2_2H" placeholder="${m.team2}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
        </div>
        <button class="action-btn" id="saveScoreBtn">Сохранить</button>`;
    document.getElementById('saveScoreBtn').onclick = async () => {
        const ht1 = +document.querySelector('.scoreT1_1H').value;
        const ht2 = +document.querySelector('.scoreT2_1H').value;
        const ht1_2 = +document.querySelector('.scoreT1_2H').value;
        const ht2_2 = +document.querySelector('.scoreT2_2H').value;
        if (isNaN(ht1)||isNaN(ht2)||isNaN(ht1_2)||isNaN(ht2_2)) return alert('Введите все числа');
        m.score_ht = { t1: ht1, t2: ht2 };
        m.score = { t1: ht1 + ht1_2, t2: ht2 + ht2_2 };
        m.result = (m.score.t1 > m.score.t2) ? '1' : (m.score.t1 === m.score.t2) ? 'X' : '2';
        m.archived = true;
        resolveBetsForMatch(m);
        await saveMatches(); await saveUsers();
        await logAdminAction(`Ввёл счёт матча ${m.team1} — ${m.team2} (1Т ${ht1}:${ht2}, 2Т ${ht1_2}:${ht2_2})`);
        alert('Счёт сохранён, матч перемещён в архив, ставки рассчитаны');
        renderTab('adminManage');
    };
};

window._editMatchScore = function(matchId) {
    const m = window.matches.find(x => x.id === matchId);
    if (!m || !m.score) return;
    const ht = m.score_ht || { t1: 0, t2: 0 };
    const ht2_t1 = m.score.t1 - ht.t1;
    const ht2_t2 = m.score.t2 - ht.t2;
    window.els.tab.innerHTML = `<div class="back-link" onclick="renderTab('adminManage')">← Назад</div><div class="section-title">Изменить счёт: ${m.team1} — ${m.team2}</div>
        <div style="margin:10px 0;"><strong>Первый тайм:</strong></div>
        <div style="display:flex;gap:10px;align-items:center;margin-bottom:10px;">
            <input type="number" class="scoreT1_1H" value="${ht.t1}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
            <span>:</span>
            <input type="number" class="scoreT2_1H" value="${ht.t2}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
        </div>
        <div style="margin:10px 0;"><strong>Второй тайм:</strong></div>
        <div style="display:flex;gap:10px;align-items:center;margin-bottom:15px;">
            <input type="number" class="scoreT1_2H" value="${ht2_t1}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
            <span>:</span>
            <input type="number" class="scoreT2_2H" value="${ht2_t2}" style="width:60px;background:#0f0f1a;color:white;padding:10px;border-radius:12px;">
        </div>
        <button class="action-btn" id="saveNewScoreBtn">Сохранить изменения</button>`;
    document.getElementById('saveNewScoreBtn').onclick = async () => {
        const ht1 = +document.querySelector('.scoreT1_1H').value;
        const ht2 = +document.querySelector('.scoreT2_1H').value;
        const ht1_2 = +document.querySelector('.scoreT1_2H').value;
        const ht2_2 = +document.querySelector('.scoreT2_2H').value;
        if (isNaN(ht1)||isNaN(ht2)||isNaN(ht1_2)||isNaN(ht2_2)) return alert('Введите все числа');
        const newScore_ht = { t1: ht1, t2: ht2 };
        const newScore = { t1: ht1 + ht1_2, t2: ht2 + ht2_2 };
        const newResult = (newScore.t1 > newScore.t2) ? '1' : (newScore.t1 === newScore.t2) ? 'X' : '2';
        m.score_ht = newScore_ht;
        m.score = newScore;
        m.result = newResult;
        for (const u of window.users) {
            (u.bets || []).forEach(bet => {
                if (bet.matchId === matchId || (bet.legs && bet.legs.some(l => l.matchId === matchId))) {
                    if (bet.status === 'win') { u.balance -= bet.winAmount; u.balance += bet.amount; }
                    bet.status = 'pending';
                    bet.winAmount = 0;
                }
            });
        }
        resolveBetsForMatch(m);
        await saveMatches(); await saveUsers();
        await logAdminAction(`Изменил счёт матча ${m.team1} — ${m.team2}`);
        alert('Счёт изменён, ставки пересчитаны');
        renderTab('adminManage');
    };
};

function renderAdminAdd() {
    window.els.tab.innerHTML = `<div class="section-title">Добавить матч</div>
        <div class="input-group"><label>Дивизион</label><select id="newDivision">${DIVISIONS.map(d => `<option>${d}</option>`).join('')}</select></div>
        <div class="input-group"><label>Команда 1 (хозяева)</label><input type="text" id="newTeam1" placeholder="Название"></div>
        <div class="input-group"><label>Команда 2 (гости)</label><input type="text" id="newTeam2" placeholder="Название"></div>
        <div class="input-group"><label>Коэф. точного счёта</label><input type="number" step="0.01" id="newOddsTS" value="7.0"></div>
        <div class="input-group"><label>Коэф. 1-го тайма (П1/Х/П2/ТБ/ТМ/ОЗ/ТС через запятую, или пусто для авто)</label>
        <input type="text" id="newOdds1H" placeholder="напр: 2.5,3.2,2.8,2.6,2.4,2.7,7.5"></div>
        <div class="input-group"><label>Коэф. 2-го тайма (через запятую или пусто)</label>
        <input type="text" id="newOdds2H" placeholder="напр: 2.7,3.5,3.0,2.8,2.6,2.9,8.0"></div>
        <div id="calculatedOdds" style="margin:15px 0; display:none;">
            <div style="display:flex; gap:10px; flex-wrap:wrap;">
                <div class="odd-block"><div>П1</div><div class="odd-value" id="odd1">—</div></div>
                <div class="odd-block"><div>Ничья</div><div class="odd-value" id="oddX">—</div></div>
                <div class="odd-block"><div>П2</div><div class="odd-value" id="odd2">—</div></div>
                <div class="odd-block"><div>ТБ 2.5</div><div class="odd-value" id="oddTB">—</div></div>
                <div class="odd-block"><div>ТМ 2.5</div><div class="odd-value" id="oddTM">—</div></div>
                <div class="odd-block"><div>ОЗ</div><div class="odd-value" id="oddOZ">—</div></div>
            </div>
            <div id="teamStatsInfo" style="margin-top:10px;"></div>
        </div>
        <button class="action-btn" id="calcOddsBtn">Рассчитать коэффициенты</button>
        <button class="action-btn" id="addMatchBtn" style="display:none; margin-top:10px;">Добавить матч</button>`;
    document.getElementById('calcOddsBtn').onclick = () => {
        const t1 = document.getElementById('newTeam1').value.trim();
        const t2 = document.getElementById('newTeam2').value.trim();
        if (!t1 || !t2) return alert('Введите названия обеих команд');
        const stats1 = getTeamStats(t1);
        const stats2 = getTeamStats(t2);
        const odds = smartOdds(stats1, stats2, t1, t2);
        document.getElementById('odd1').textContent = odds['1'].toFixed(2);
        document.getElementById('oddX').textContent = odds['X'].toFixed(2);
        document.getElementById('odd2').textContent = odds['2'].toFixed(2);
        document.getElementById('oddTB').textContent = odds['TB'].toFixed(2);
        document.getElementById('oddTM').textContent = odds['TM'].toFixed(2);
        document.getElementById('oddOZ').textContent = odds['OZ'].toFixed(2);
        document.getElementById('calculatedOdds').style.display = 'block';
        document.getElementById('addMatchBtn').style.display = 'inline-block';

        document.getElementById('teamStatsInfo').innerHTML = `
            <div class="team-stats">
                <strong>${t1} (хозяева)</strong>
                Матчей: ${stats1.matchesPlayed}, Побед: ${stats1.wins}, Ничьих: ${stats1.draws}, Поражений: ${stats1.losses}<br>
                Голов забито: ${stats1.goalsScored}, пропущено: ${stats1.goalsConceded} (разница: ${stats1.goalDiff})<br>
                Среднее забито: ${stats1.avgScored}, пропущено: ${stats1.avgConceded}<br>
                Сила атаки: ${stats1.attackStrength}, защиты: ${stats1.defenseStrength}, общая: ${stats1.overallStrength}<br>
                Процент побед: ${stats1.winRate}%, ничьих: ${stats1.drawRate}%, поражений: ${stats1.lossRate}%
            </div>
            <div class="team-stats">
                <strong>${t2} (гости)</strong>
                Матчей: ${stats2.matchesPlayed}, Побед: ${stats2.wins}, Ничьих: ${stats2.draws}, Поражений: ${stats2.losses}<br>
                Голов забито: ${stats2.goalsScored}, пропущено: ${stats2.goalsConceded} (разница: ${stats2.goalDiff})<br>
                Среднее забито: ${stats2.avgScored}, пропущено: ${stats2.avgConceded}<br>
                Сила атаки: ${stats2.attackStrength}, защиты: ${stats2.defenseStrength}, общая: ${stats2.overallStrength}<br>
                Процент побед: ${stats2.winRate}%, ничьих: ${stats2.drawRate}%, поражений: ${stats2.lossRate}%
            </div>
        `;
        window._calculatedOddsData = odds;
    };
    document.getElementById('addMatchBtn').onclick = async () => {
        const odds = window._calculatedOddsData;
        if (!odds) return;
        const div = document.getElementById('newDivision').value;
        const t1 = document.getElementById('newTeam1').value.trim();
        const t2 = document.getElementById('newTeam2').value.trim();
        const ts = +document.getElementById('newOddsTS').value || 7.0;

        const parsePeriodOdds = (str) => {
            const parts = str.split(',').map(Number);
            if (parts.length !== 7) return null;
            return {
                '1': parts[0], 'X': parts[1], '2': parts[2],
                'TB': parts[3], 'TM': parts[4], 'OZ': parts[5],
                'TS': parts[6]
            };
        };
        const odds1H = parsePeriodOdds(document.getElementById('newOdds1H').value);
        const odds2H = parsePeriodOdds(document.getElementById('newOdds2H').value);

        const matchObj = {
            id:'m_'+Date.now(), division:div, team1:t1, team2:t2, 
            odds:{ '1':odds['1'], 'X':odds['X'], '2':odds['2'] }, 
            odds_TB:odds['TB'], odds_TM:odds['TM'], odds_OZ:odds['OZ'], 
            odds_TS: ts,
            status:'open', score:null, score_ht:null, result:null, archived:false,
            odds_1H: odds1H, odds_2H: odds2H
        };
        window.matches.push(matchObj);
        await saveMatches(); await logAdminAction(`Добавил матч ${t1} — ${t2} в ${div}`);
        alert('Матч добавлен!');
        document.getElementById('newTeam1').value = ''; 
        document.getElementById('newTeam2').value = '';
        document.getElementById('calculatedOdds').style.display = 'none'; 
        document.getElementById('addMatchBtn').style.display = 'none';
        window._calculatedOddsData = null;
    };
}

// ========== АДМИНКА: ПОЛЬЗОВАТЕЛИ ==========
function renderAdminUsers() {
    let html = '<div class="section-title">Пользователи</div>';
    window.users.forEach(u => {
        if (u.role === 'admin') return;
        html += `<div style="background:var(--card-bg);border-radius:14px;padding:12px;margin-bottom:8px;">
            <strong>${u.username}</strong> (Баланс: ${u.balance.toFixed(2)}) ${u.banned ? '<span style="color:red;">ЗАБАНЕН</span>' : ''}<br>
            <input type="number" placeholder="Новый баланс" class="newBalance" data-uid="${u.username}" style="width:100px; margin-right:5px;">
            <button class="action-btn small setBalance" data-uid="${u.username}">Уст. баланс</button>
            <button class="action-btn small toggleBan" data-uid="${u.username}">${u.banned ? 'Разбанить' : 'Забанить'}</button>
            <button class="action-btn small viewProfile" data-uid="${u.username}">Профиль</button>
            <button class="action-btn small sendPersonal" data-uid="${u.username}">Отправить ЛС</button>
            <button class="action-btn small editCreditTrust" data-uid="${u.username}">Кредитная Дов. (${u.creditTrust}%)</button>
        </div>`;
    });
    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.setBalance').forEach(b => b.onclick = async () => {
        const user = window.users.find(u => u.username === b.dataset.uid);
        const input = window.els.tab.querySelector(`.newBalance[data-uid="${b.dataset.uid}"]`);
        const val = +input.value;
        if (isNaN(val)) return alert('Введите число');
        user.balance = val;
        await saveUsers(); await logAdminAction(`Изменил баланс ${user.username} на ${val}`);
        renderTab('adminUsers');
    });
    window.els.tab.querySelectorAll('.toggleBan').forEach(b => b.onclick = async () => {
        const user = window.users.find(u => u.username === b.dataset.uid);
        user.banned = !user.banned;
        await saveUsers(); await logAdminAction(`${user.banned ? 'Забанил' : 'Разбанил'} ${user.username}`);
        renderTab('adminUsers');
    });
    window.els.tab.querySelectorAll('.viewProfile').forEach(b => b.onclick = () => {
        const user = window.users.find(u => u.username === b.dataset.uid);
        if (!user) return;
        const bets = user.bets || [];
        const fin = bets.filter(x => x.status !== 'pending');
        const wins = fin.filter(x => x.status === 'win').length;
        const wr = fin.length ? ((wins / fin.length) * 100).toFixed(1) : 0;
        const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
        overlay.innerHTML = `<div class="modal-content">
            <div style="font-size:1.3rem;margin-bottom:15px;">Профиль ${user.username}</div>
            <div class="profile-stat"><span>Баланс</span><strong>${user.balance.toFixed(2)}</strong></div>
            <div class="profile-stat"><span>Ставок</span><strong>${fin.length}</strong></div>
            <div class="profile-stat"><span>Выигрышей</span><strong>${wins}</strong></div>
            <div class="profile-stat"><span>Винрейт</span><strong>${wr}%</strong></div>
            <button class="modal-btn green closeModal">Закрыть</button>
        </div>`;
        document.body.appendChild(overlay);
        overlay.querySelector('.closeModal').onclick = () => overlay.remove();
    });
    window.els.tab.querySelectorAll('.sendPersonal').forEach(b => b.onclick = () => {
        const uid = b.dataset.uid;
        const msg = prompt('Введите сообщение для ' + uid + ':');
        if (msg) {
            window.db.ref('personalNotifications/' + uid).set(msg);
            alert('Отправлено!');
            logAdminAction(`Отправил личное сообщение пользователю ${uid}`);
        }
    });
    window.els.tab.querySelectorAll('.editCreditTrust').forEach(btn => {
        btn.onclick = async () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            const newTrust = prompt('Введите новую кредитную доверенность (100, 75, 50, 25, 0):', user.creditTrust);
            if (newTrust === null) return;
            const trust = parseInt(newTrust);
            if (![100, 75, 50, 25, 0].includes(trust)) return alert('Некорректное значение');
            user.creditTrust = trust;
            if (trust === 0) {
                user.trustRecoveryTimestamp = Date.now() + 5 * 24 * 60 * 60 * 1000;
            } else {
                user.trustRecoveryTimestamp = 0;
            }
            await saveUsers();
            renderTab('adminUsers');
        };
    });
}

// ========== АДМИНКА: КЛУБЫ ==========
function renderAdminClubs() {
    const clubSet = new Set();
    window.matches.forEach(m => { if (m.team1) clubSet.add(m.team1.trim()); if (m.team2) clubSet.add(m.team2.trim()); });
    const clubs = Array.from(clubSet).sort();
    let html = '<div class="section-title">Управление клубами</div>';
    if (clubs.length === 0) html += '<p style="color:#aaa;">Нет добавленных клубов</p>';
    else clubs.forEach(club => {
        html += `<div style="background:var(--card-bg);border-radius:14px;padding:12px;margin-bottom:8px;display:flex;align-items:center;justify-content:space-between;">
            <strong>${club}</strong>
            <div>
                <button class="action-btn small renameClub" data-club="${club}" style="margin-right:5px;">Переименовать</button>
                <button class="action-btn small mergeClub" data-club="${club}">Объединить</button>
                <button class="action-btn small red deleteClub" data-club="${club}" style="margin-left:5px;">Удалить</button>
            </div>
        </div>`;
    });
    window.els.tab.innerHTML = html;
    window.els.tab.querySelectorAll('.renameClub').forEach(btn => {
        btn.onclick = () => {
            const oldName = btn.dataset.club;
            const newName = prompt('Введите новое название клуба:', oldName);
            if (!newName || newName.trim() === oldName.trim()) return;
            const newNameTrimmed = newName.trim();
            window.matches.forEach(m => {
                if (m.team1 && m.team1.trim() === oldName) m.team1 = newNameTrimmed;
                if (m.team2 && m.team2.trim() === oldName) m.team2 = newNameTrimmed;
            });
            window.users.forEach(u => (u.bets || []).forEach(bet => {
                if (bet.type === 'single') {
                    if (bet.team1 && bet.team1.trim() === oldName) bet.team1 = newNameTrimmed;
                    if (bet.team2 && bet.team2.trim() === oldName) bet.team2 = newNameTrimmed;
                } else if (bet.type === 'express' && bet.legs) {
                    bet.legs.forEach(leg => {
                        if (leg.team1 && leg.team1.trim() === oldName) leg.team1 = newNameTrimmed;
                        if (leg.team2 && leg.team2.trim() === oldName) leg.team2 = newNameTrimmed;
                    });
                }
            }));
            saveMatches().then(() => saveUsers()).then(() => renderTab('adminClubs'));
        };
    });
    window.els.tab.querySelectorAll('.mergeClub').forEach(btn => {
        btn.onclick = () => {
            const sourceClub = btn.dataset.club;
            const targetClub = prompt(`Введите название клуба, с которым объединить "${sourceClub}":`);
            if (!targetClub || targetClub.trim() === sourceClub.trim() || !clubs.includes(targetClub.trim())) {
                alert('Некорректное название или такой клуб не найден'); return;
            }
            const target = targetClub.trim();
            window.matches.forEach(m => {
                if (m.team1 && m.team1.trim() === sourceClub) m.team1 = target;
                if (m.team2 && m.team2.trim() === sourceClub) m.team2 = target;
            });
            window.users.forEach(u => (u.bets || []).forEach(bet => {
                if (bet.type === 'single') {
                    if (bet.team1 && bet.team1.trim() === sourceClub) bet.team1 = target;
                    if (bet.team2 && bet.team2.trim() === sourceClub) bet.team2 = target;
                } else if (bet.type === 'express' && bet.legs) {
                    bet.legs.forEach(leg => {
                        if (leg.team1 && leg.team1.trim() === sourceClub) leg.team1 = target;
                        if (leg.team2 && leg.team2.trim() === sourceClub) leg.team2 = target;
                    });
                }
            }));
            saveMatches().then(() => saveUsers()).then(() => renderTab('adminClubs'));
        };
    });
    window.els.tab.querySelectorAll('.deleteClub').forEach(btn => {
        btn.onclick = () => {
            const club = btn.dataset.club;
            if (!confirm(`Удалить клуб "${club}"? Во всех матчах и ставках название будет заменено на "???".`)) return;
            window.matches.forEach(m => {
                if (m.team1 && m.team1.trim() === club) m.team1 = '???';
                if (m.team2 && m.team2.trim() === club) m.team2 = '???';
            });
            window.users.forEach(u => (u.bets || []).forEach(bet => {
                if (bet.type === 'single') {
                    if (bet.team1 && bet.team1.trim() === club) bet.team1 = '???';
                    if (bet.team2 && bet.team2.trim() === club) bet.team2 = '???';
                } else if (bet.type === 'express' && bet.legs) {
                    bet.legs.forEach(leg => {
                        if (leg.team1 && leg.team1.trim() === club) leg.team1 = '???';
                        if (leg.team2 && leg.team2.trim() === club) leg.team2 = '???';
                    });
                }
            }));
            saveMatches().then(() => saveUsers()).then(() => renderTab('adminClubs'));
        };
    });
}

// ========== АДМИНКА: ПРОМОКОДЫ ==========
function renderAdminPromo() {
    let html = '<div class="section-title">Управление промокодами</div>';
    html += '<div class="input-group"><label>Название промокода</label><input type="text" id="newPromoCode" placeholder="Код"></div><div class="input-group"><label>Бонус (коины)</label><input type="number" id="newPromoBonus" placeholder="Сумма"></div><div class="input-group"><label>Количество активаций</label><input type="number" id="newPromoLimit" placeholder="Лимит"></div><button class="action-btn" id="createPromoBtn">Создать промокод</button><div class="section-title" style="margin-top:20px;">Список промокодов</div>';
    window.promoCodes.forEach(p => { html += `<div style="background:var(--card-bg);border-radius:14px;padding:12px;margin-bottom:8px;"><strong>${p.code}</strong> | Бонус: ${p.bonus} | Осталось активаций: ${p.remaining} ${p.remaining === 0 ? `<button class="action-btn small red deletePromo" data-code="${p.code}">Удалить</button>` : ''}</div>`; });
    html += '<div class="section-title" style="margin-top:20px;">Лог активаций</div>';
    if (window.promoLog.length === 0) html += '<p style="color:#aaa;">Нет активаций</p>';
    else { window.promoLog.slice().reverse().forEach(entry => { const date = new Date(entry.timestamp).toLocaleString(); html += `<div style="background:var(--card-bg);border-radius:12px;padding:10px;margin-bottom:6px;"><strong>${entry.username}</strong> активировал "${entry.promoCode}" — ${entry.amount} коинов, ${date}</div>`; }); }
    window.els.tab.innerHTML = html;
    document.getElementById('createPromoBtn').onclick = async () => { const code = document.getElementById('newPromoCode').value.trim(); const bonus = +document.getElementById('newPromoBonus').value; const limit = +document.getElementById('newPromoLimit').value; if (!code || isNaN(bonus) || isNaN(limit) || bonus <= 0 || limit <= 0) return alert('Заполните все поля корректно'); if (window.promoCodes.some(p => p.code === code)) { alert('Промокод с таким названием уже существует'); return; } window.promoCodes.push({ code, bonus, remaining: limit }); await savePromoCodes(); alert('Промокод создан'); renderTab('adminPromo'); };
    window.els.tab.querySelectorAll('.deletePromo').forEach(b => b.onclick = async () => { if (confirm('Удалить промокод?')) { window.promoCodes = window.promoCodes.filter(p => p.code !== b.dataset.code); await savePromoCodes(); renderTab('adminPromo'); } });
}

// ========== АДМИНКА: НОВОСТИ ==========
function renderAdminNews() {
    let html = '<div class="section-title">Управление новостями</div>';
    html += '<div class="input-group"><label>Заголовок</label><input type="text" id="newsTitle" placeholder="Заголовок"></div>';
    html += '<div class="input-group"><label>Текст</label><textarea id="newsText" style="width:100%;padding:10px;background:#0f0f1a;color:white;border-radius:12px;height:100px;"></textarea></div>';
    html += '<button class="action-btn" id="addNewsBtn">Добавить новость</button>';
    html += '<div class="section-title" style="margin-top:20px;">Список новостей</div>';
    window.newsList.forEach(n => {
        html += `<div style="background:var(--card-bg);border-radius:14px;padding:12px;margin-bottom:8px;"><strong>${n.title}</strong><br><small>${n.text}</small><br><button class="action-btn small red deleteNews" data-id="${n.id}">Удалить</button></div>`;
    });
    window.els.tab.innerHTML = html;
    document.getElementById('addNewsBtn').onclick = async () => {
        const title = document.getElementById('newsTitle').value.trim();
        const text = document.getElementById('newsText').value.trim();
        if (!title || !text) return alert('Заполните оба поля');
        window.newsList.push({ id: Date.now().toString(), title, text });
        await saveNews(); await logAdminAction(`Добавил новость: ${title}`); renderTab('adminNews');
    };
    window.els.tab.querySelectorAll('.deleteNews').forEach(b => b.onclick = async () => {
        if (confirm('Удалить новость?')) { window.newsList = window.newsList.filter(n => n.id !== b.dataset.id); await saveNews(); await logAdminAction('Удалил новость'); renderTab('adminNews'); }
    });
}

// ========== АДМИНКА: ЛОГ ==========
function renderAdminLog() {
    let html = '<div class="section-title">Лог действий</div>';
    if (window.adminLog.length === 0) html += '<p style="color:#aaa;">Действий пока нет</p>';
    else window.adminLog.slice().reverse().forEach(entry => {
        const date = new Date(entry.timestamp).toLocaleString();
        html += `<div style="background:var(--card-bg);border-radius:12px;padding:10px;margin-bottom:6px;"><strong>${entry.username}</strong> — ${entry.action}<br><small>${date}</small></div>`;
    });
    window.els.tab.innerHTML = html;
}

// ========== АДМИНКА: PUSH ==========
function renderAdminPush() {
    let html = '<div class="section-title">Push-уведомления</div>';
    html += `<div class="input-group"><label>Заголовок</label><input type="text" id="pushTitle" placeholder="TonBet"></div>
             <div class="input-group"><label>Текст</label><input type="text" id="pushText" placeholder="Сообщение"></div>
             <button class="action-btn" id="sendPushBtn">Отправить всем</button>
             <div id="pushSendStatus" style="margin-top:10px;"></div>`;
    window.els.tab.innerHTML = html;

    document.getElementById('sendPushBtn').onclick = async () => {
        const title = document.getElementById('pushTitle').value.trim() || 'TonBet';
        const body = document.getElementById('pushText').value.trim();
        if (!body) return alert('Введите текст уведомления');
        try {
            await window.db.ref('pushMessages').push({
                title,
                body,
                to: 'all',
                timestamp: Date.now()
            });
            document.getElementById('pushSendStatus').innerHTML = '<span style="color:var(--success);">Отправлено!</span>';
            await logAdminAction(`Отправил push-уведомление: ${body}`);
        } catch (e) {
            document.getElementById('pushSendStatus').innerHTML = '<span style="color:var(--danger);">Ошибка отправки</span>';
        }
    };
}

// ========== АДМИНКА: ЭКСПОРТ ==========
function renderAdminExport() {
    let csv = 'Username,Balance,Bets,Role,Banned\n';
    window.users.forEach(u => { csv += `${u.username},${u.balance.toFixed(2)},${(u.bets||[]).length},${u.role},${u.banned||false}\n`; });
    window.els.tab.innerHTML = `<div class="section-title">Экспорт</div><textarea style="width:100%;height:200px;background:#0f0f1a;color:white;border-radius:12px;padding:10px;">${csv}</textarea><button class="action-btn" id="copyCsvBtn">Копировать</button>`;
    document.getElementById('copyCsvBtn').onclick = () => { navigator.clipboard.writeText(csv).then(() => alert('Скопировано')); };
}

// ========== АДМИНКА: КРЕДИТЫ ==========
function renderAdminCredits() {
    let html = '<div class="section-title">Управление кредитами</div>';
    const debtors = window.users.filter(u => u.loanAmount > 0);
    if (debtors.length === 0) html += '<p style="color:#aaa;">Нет активных кредитов</p>';
    else debtors.forEach(user => {
        const details = getLoanDetails(user);
        html += `<div class="admin-match-card">
            <div><strong>${user.username}</strong></div>
            <div>Сумма: ${user.loanAmount} | Остаток: ${details.remaining.toFixed(0)} | Дней: ${details.daysPassed}</div>
            <div style="margin-top:8px;">
                <button class="action-btn small viewLoanInfo" data-uid="${user.username}">Информация</button>
                <button class="action-btn small toggleFreeze" data-uid="${user.username}">${user.frozenUntil > Date.now() ? 'Разморозить' : 'Заморозить'} ставки</button>
                <button class="action-btn small green payOffLoan" data-uid="${user.username}">Погасить долг</button>
                <button class="action-btn small editTrust" data-uid="${user.username}">Изменить КД</button>
                <button class="action-btn small addDays" data-uid="${user.username}">Добавить дни</button>
            </div>
        </div>`;
    });

    html += '<div class="section-title" style="margin-top:20px;">Логи кредитов</div>';
    if (window.loanLogs.length === 0) html += '<p style="color:#aaa;">Нет записей</p>';
    else window.loanLogs.slice().reverse().forEach(log => {
        const date = new Date(log.timestamp).toLocaleString();
        html += `<div style="background:var(--card-bg);border-radius:12px;padding:10px;margin-bottom:6px;">
            <strong>${log.username}</strong> — ${log.action === 'taken' ? 'Взял' : 'Погасил'} ${log.amount} коинов, ${date}
        </div>`;
    });

    window.els.tab.innerHTML = html;

    window.els.tab.querySelectorAll('.viewLoanInfo').forEach(btn => {
        btn.onclick = () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            const details = getLoanDetails(user);
            const info = `
                Сумма кредита: ${user.loanAmount}
                Взято: ${new Date(user.loanTakenTimestamp).toLocaleString()}
                Дней прошло: ${details.daysPassed}
                Проценты: ${details.interest}
                Всего к погашению: ${details.totalDue}
                Погашено: ${details.repaid}
                Осталось: ${details.remaining}
                Кредитная доверенность: ${user.creditTrust}%
                Ставки заморожены: ${user.frozenUntil > Date.now() ? 'Да, до ' + new Date(user.frozenUntil).toLocaleString() : 'Нет'}
            `;
            alert(info);
        };
    });

    window.els.tab.querySelectorAll('.toggleFreeze').forEach(btn => {
        btn.onclick = async () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            if (user.frozenUntil > Date.now()) {
                user.frozenUntil = 0;
            } else {
                user.frozenUntil = Date.now() + 3 * 24 * 60 * 60 * 1000;
            }
            await saveUsers();
            renderAdminCredits();
        };
    });

    window.els.tab.querySelectorAll('.payOffLoan').forEach(btn => {
        btn.onclick = async () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            if (confirm(`Погасить кредит пользователя ${user.username}?`)) {
                user.loanAmount = 0;
                user.loanTakenTimestamp = 0;
                user.loanRepaid = 0;
                user.frozenUntil = 0;
                user.creditTrust = 100;
                window.loanLogs.push({ username: user.username, action: 'repaid_by_admin', amount: user.loanAmount, timestamp: Date.now() });
                await saveUsers(); await saveLoanLogs();
                renderAdminCredits();
            }
        };
    });

    window.els.tab.querySelectorAll('.editTrust').forEach(btn => {
        btn.onclick = async () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            const newTrust = prompt('Введите новую кредитную доверенность (100, 75, 50, 25, 0):', user.creditTrust);
            if (newTrust === null) return;
            const trust = parseInt(newTrust);
            if (![100, 75, 50, 25, 0].includes(trust)) return alert('Некорректное значение');
            user.creditTrust = trust;
            if (trust === 0) {
                user.trustRecoveryTimestamp = Date.now() + 5 * 24 * 60 * 60 * 1000;
            } else {
                user.trustRecoveryTimestamp = 0;
            }
            await saveUsers();
            renderAdminCredits();
        };
    });

    window.els.tab.querySelectorAll('.addDays').forEach(btn => {
        btn.onclick = async () => {
            const user = window.users.find(u => u.username === btn.dataset.uid);
            if (!user) return;
            const daysInput = prompt('Введите количество дней от 1 до 7, которое будет считаться с момента взятия кредита:', '');
            if (daysInput === null) return;
            const days = parseInt(daysInput);
            if (isNaN(days) || days < 1 || days > 7) return alert('Некорректное число дней');
            user.loanTakenTimestamp = Date.now() - days * 24 * 60 * 60 * 1000;
            await saveUsers();
            renderAdminCredits();
        };
    });
}
