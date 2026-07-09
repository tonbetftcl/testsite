window.users = [], window.matches = [], window.promoCodes = [], window.promoLog = [], window.adminLog = [], window.newsList = [], window.loanLogs = [];
window.currentUsername = sessionStorage.getItem('tonbet_current') || null;
window.currentFilter = 'all', window.currentTab = 'matches';
window.adminDivision = 'ФТКЛ 2';

window.els = {
    welcome: document.getElementById('welcomeScreen'), auth: document.getElementById('authBlock'),
    main: document.getElementById('mainInterface'), tab: document.getElementById('tabContent'),
    bottomNav: document.getElementById('bottomNav'), adminNav: document.getElementById('adminBottomNav'),
    workerNav: document.getElementById('workerBottomNav'), headerRight: document.getElementById('headerRight')
};

function getCurrentUser() { return window.users.find(u => u.username === window.currentUsername); }

async function loadData() {
    const [usersSnap, matchesSnap, promosSnap, logSnap, adminLogSnap, newsSnap, loanSnap] = await Promise.all([
        db.ref('users').once('value'), db.ref('matches').once('value'),
        db.ref('promoCodes').once('value'), db.ref('promoLog').once('value'),
        db.ref('adminLog').once('value'), db.ref('news').once('value'),
        db.ref('loanLogs').once('value')
    ]);
    window.users = usersSnap.val() ? Object.values(usersSnap.val()) : [];
    window.matches = matchesSnap.val() ? Object.values(matchesSnap.val()) : [];
    window.promoCodes = promosSnap.val() ? Object.values(promosSnap.val()) : [];
    window.promoLog = logSnap.val() ? Object.values(logSnap.val()) : [];
    window.adminLog = adminLogSnap.val() ? Object.values(adminLogSnap.val()) : [];
    window.newsList = newsSnap.val() ? Object.values(newsSnap.val()) : [];
    window.loanLogs = loanSnap.val() ? Object.values(loanSnap.val()) : [];
    window.users.forEach(u => {
        u.bets = u.bets || [];
        if (!u.activatedPromos) u.activatedPromos = [];
        if (u.lastDailyBonus === undefined) u.lastDailyBonus = 0;
        if (u.muted === undefined) u.muted = false;
        if (u.creditTrust === undefined || u.creditTrust === null) u.creditTrust = 100;
        if (u.loanAmount === undefined || u.loanAmount === null) u.loanAmount = 0;
        if (u.loanTakenTimestamp === undefined || u.loanTakenTimestamp === null) u.loanTakenTimestamp = 0;
        if (u.loanRepaid === undefined || u.loanRepaid === null) u.loanRepaid = 0;
        if (u.frozenUntil === undefined || u.frozenUntil === null) u.frozenUntil = 0;
        if (u.trustRecoveryTimestamp === undefined || u.trustRecoveryTimestamp === null) u.trustRecoveryTimestamp = 0;
    });
    window.matches.forEach(m => { 
        if (m.archived === undefined) m.archived = false; 
        if (m.odds_TS === undefined) m.odds_TS = 7.0;
    });
    const knownAdmins = ['admin', 'V0rt3x', 'N3bulous'];
    const worker = 'worker1';
    let changed = false;
    window.users.forEach(u => {
        if (knownAdmins.includes(u.username) && u.role !== 'admin') { u.role = 'admin'; changed = true; }
        if (u.username === worker && u.role !== 'match_manager') { u.role = 'match_manager'; changed = true; }
    });
    const admins = [
        { username: 'admin', password: 'admin123', role: 'admin', balance: 99999, bets: [], creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 },
        { username: 'Astr0n', password: 'X7r!2pQa', role: 'match_manager', balance: 99999, bets: [], creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 },
        { username: 'V0rt3x', password: 'M9z_3kLw', role: 'admin', balance: 99999, bets: [], creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 },
        { username: 'N3bulous', password: 'R4s^8tUe', role: 'admin', balance: 99999, bets: [], creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 },
        { username: 'worker1', password: 'worker1', role: 'match_manager', balance: 99999, bets: [], creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 }
    ];
    admins.forEach(a => { if (!window.users.find(u => u.username === a.username)) { window.users.push({...a, bets: a.bets || [], activatedPromos: [], lastDailyBonus: 0, muted: false}); changed = true; } });
    if (changed) await saveUsers();
}

async function saveUsers() { const obj = {}; window.users.forEach((u, i) => obj[i] = u); await db.ref('users').set(obj); }
async function saveMatches() { const obj = {}; window.matches.forEach((m, i) => obj[i] = m); await db.ref('matches').set(obj); }
async function savePromoCodes() { const obj = {}; window.promoCodes.forEach((p, i) => obj[i] = p); await db.ref('promoCodes').set(obj); }
async function savePromoLog() { const obj = {}; window.promoLog.forEach((l, i) => obj[i] = l); await db.ref('promoLog').set(obj); }
async function saveAdminLog() { const obj = {}; window.adminLog.forEach((l, i) => obj[i] = l); await db.ref('adminLog').set(obj); }
async function saveNews() { const obj = {}; window.newsList.forEach((n, i) => obj[i] = n); await db.ref('news').set(obj); }
async function saveLoanLogs() { const obj = {}; window.loanLogs.forEach((l, i) => obj[i] = l); await db.ref('loanLogs').set(obj); }
async function logAdminAction(action) { window.adminLog.push({ username: window.currentUsername, action, timestamp: Date.now() }); await saveAdminLog(); }

function showWelcome() { window.els.welcome.classList.remove('hidden'); window.els.auth.classList.add('hidden'); window.els.main.classList.add('hidden'); window.els.bottomNav.classList.add('hidden'); window.els.adminNav.classList.add('hidden'); window.els.workerNav.classList.add('hidden'); }
function showAuth() { window.els.welcome.classList.add('hidden'); window.els.auth.classList.remove('hidden'); window.els.main.classList.add('hidden'); window.els.bottomNav.classList.add('hidden'); window.els.adminNav.classList.add('hidden'); window.els.workerNav.classList.add('hidden'); document.getElementById('loginForm').classList.remove('hidden'); document.getElementById('registerForm').classList.add('hidden'); }
async function logout() { 
    sessionStorage.removeItem('tonbet_current'); 
    localStorage.removeItem('tonbet_remembered'); 
    window.currentUsername = null; 
    window.els.headerRight.innerHTML = ''; 
    showAuth(); 
}
async function showMain() {
    window.els.welcome.classList.add('hidden'); window.els.auth.classList.add('hidden'); window.els.main.classList.remove('hidden');
    const user = getCurrentUser(); window.els.headerRight.innerHTML = '';
    if (user && (user.role === 'admin' || user.role === 'match_manager')) {
        window.els.bottomNav.classList.add('hidden');
        if (user.role === 'admin') { window.els.adminNav.classList.remove('hidden'); window.els.workerNav.classList.add('hidden'); window.currentTab = 'adminManage'; }
        else { window.els.adminNav.classList.add('hidden'); window.els.workerNav.classList.remove('hidden'); window.currentTab = 'adminManage'; }
    } else { window.els.bottomNav.classList.remove('hidden'); window.els.adminNav.classList.add('hidden'); window.els.workerNav.classList.add('hidden'); window.currentTab = 'matches'; }
    const logoutBtn = document.createElement('button'); logoutBtn.className = 'logout-header-btn'; logoutBtn.textContent = 'Выйти'; logoutBtn.onclick = logout;
    window.els.headerRight.appendChild(logoutBtn);
    renderTab(window.currentTab);
    checkPendingBets();
    checkAdminNotification();
    if (user && user.role !== 'admin' && user.role !== 'match_manager') {
        checkLoanStatus(user);
        await saveUsers();
    }
}

async function checkAdminNotification() {
    const user = getCurrentUser();
    if (!user) return;
    if (user.role !== 'admin' && user.role !== 'match_manager') {
        const snap = await db.ref('personalNotifications/' + user.username).once('value');
        const text = snap.val();
        if (text) {
            const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
            overlay.innerHTML = `<div class="modal-content"><div style="font-size:1.3rem;margin-bottom:15px;">Уведомление от администратора ЛИЧНО ВАМ</div><div>${text}</div><button class="modal-btn green closeModal">Ок</button></div>`;
            document.body.appendChild(overlay);
            overlay.querySelector('.closeModal').onclick = () => { overlay.remove(); db.ref('personalNotifications/' + user.username).set(null); };
            setTimeout(() => { if (overlay.parentNode) overlay.remove(); db.ref('personalNotifications/' + user.username).set(null); }, 10000);
            return;
        }
    }
    if (user && (user.role === 'admin' || user.role === 'match_manager')) return;
    if (sessionStorage.getItem('notif_shown')) return;
    const snap = await db.ref('notification').once('value');
    const text = snap.val();
    if (text) {
        const overlay = document.createElement('div'); overlay.className = 'modal-overlay';
        overlay.innerHTML = `<div class="modal-content"><div style="font-size:1.3rem;margin-bottom:15px;">Сообщение от администратора</div><div>${text}</div><button class="modal-btn green closeModal">Ок</button></div>`;
        document.body.appendChild(overlay);
        overlay.querySelector('.closeModal').onclick = () => { overlay.remove(); sessionStorage.setItem('notif_shown', '1'); };
        setTimeout(() => { if (overlay.parentNode) overlay.remove(); sessionStorage.setItem('notif_shown', '1'); }, 10000);
    }
}

function checkPendingBets() {
    const user = getCurrentUser(); if (!user || user.role === 'admin' || user.role === 'match_manager') return;
    const resolved = [];
    (user.bets || []).forEach(bet => {
        if (bet.status !== 'pending') return;
        if (bet.type === 'single') {
            const m = window.matches.find(x => x.id === bet.matchId);
            if (m && m.score) {
                let win = false;
                if (bet.outcome === 'TS') win = m.score.t1 === bet.exactScore.t1 && m.score.t2 === bet.exactScore.t2;
                else if (['1','X','2'].includes(bet.outcome)) win = bet.outcome === m.result;
                else if (bet.outcome === 'TB') win = (m.score.t1 + m.score.t2) > 2.5;
                else if (bet.outcome === 'TM') win = (m.score.t1 + m.score.t2) < 2.5;
                else if (bet.outcome === 'OZ') win = m.score.t1 > 0 && m.score.t2 > 0;
                bet.status = win ? 'win' : 'lose';
                if (win) { bet.winAmount = bet.amount * bet.odds; addBalanceWithLoan(user, bet.winAmount); }
                resolved.push({ bet, match: m });
            }
        } else if (bet.type === 'express') {
            const allRes = bet.legs.every(l => { const m = window.matches.find(x => x.id === l.matchId); return m && m.score; });
            if (allRes) {
                const allWin = bet.legs.every(l => {
                    const m = window.matches.find(x => x.id === l.matchId);
                    if (l.outcome === 'TS') return m.score.t1 === l.exactScore.t1 && m.score.t2 === l.exactScore.t2;
                    if (['1','X','2'].includes(l.outcome)) return l.outcome === m.result;
                    if (l.outcome === 'TB') return (m.score.t1 + m.score.t2) > 2.5;
                    if (l.outcome === 'TM') return (m.score.t1 + m.score.t2) < 2.5;
                    if (l.outcome === 'OZ') return m.score.t1 > 0 && m.score.t2 > 0;
                });
                bet.status = allWin ? 'win' : 'lose';
                if (allWin) { bet.winAmount = bet.amount * bet.totalOdds; addBalanceWithLoan(user, bet.winAmount); }
                resolved.push({ bet, match: null });
            }
        }
    });
    saveUsers().then(() => {
        resolved.forEach(({ bet, match }) => {
            if (bet.type === 'single') {
                const msg = bet.status === 'win' ? `Поздравляем, ваша ставка на матч ${match.team1} — ${match.team2} сыграла!` : `К сожалению, ваша ставка на матч ${match.team1} — ${match.team2} не сыграла!`;
                showToast(msg, bet.status === 'win' ? 'success' : 'error');
            } else {
                const msg = bet.status === 'win' ? 'Поздравляем, ваш экспресс зашёл!' : 'К сожалению ваш экспресс не зашёл!';
                showToast(msg, bet.status === 'win' ? 'success' : 'error');
            }
        });
    });
}

function renderTab(tab) {
    window.els.tab.innerHTML = '';
    const user = getCurrentUser();
    if (user && (user.role === 'admin' || user.role === 'match_manager')) {
        if (tab === 'adminManage') renderAdminManage();
        else if (tab === 'adminAdd') renderAdminAdd();
        else if (tab === 'adminUsers' && user.role === 'admin') renderAdminUsers();
        else if (tab === 'adminClubs' && user.role === 'admin') renderAdminClubs();
        else if (tab === 'adminPromo' && user.role === 'admin') renderAdminPromo();
        else if (tab === 'adminNews' && user.role === 'admin') renderAdminNews();
        else if (tab === 'adminLog' && user.role === 'admin') renderAdminLog();
        else if (tab === 'adminPush' && user.role === 'admin') renderAdminPush();
        else if (tab === 'adminExport' && user.role === 'admin') renderAdminExport();
        else if (tab === 'adminCredits' && user.role === 'admin') renderAdminCredits();
    } else {
        if (tab === 'matches') renderMatches();
        else if (tab === 'express') renderExpress();
        else if (tab === 'mybets') renderMyBets();
        else if (tab === 'promo') renderPromo();
        else if (tab === 'profile') renderProfile();
        else if (tab === 'news') renderNews();
        else if (tab === 'leaderboard') renderLeaderboard();
        else if (tab === 'credit') renderCredit();
    }
}

document.getElementById('continueBtn').onclick = () => { if (window.currentUsername && window.users.some(u => u.username === window.currentUsername)) showMain(); else showAuth(); };
document.getElementById('showRegisterLink').onclick = e => { e.preventDefault(); document.getElementById('loginForm').classList.add('hidden'); document.getElementById('registerForm').classList.remove('hidden'); };
document.getElementById('showLoginLink').onclick = e => { e.preventDefault(); document.getElementById('registerForm').classList.add('hidden'); document.getElementById('loginForm').classList.remove('hidden'); };
document.getElementById('loginBtn').onclick = async () => {
    const u = document.getElementById('loginUsername').value.trim(), p = document.getElementById('loginPassword').value;
    if (!u || !p) return document.getElementById('loginError').textContent = 'Заполните все поля';
    const user = window.users.find(x => x.username === u && x.password === p);
    if (!user) return document.getElementById('loginError').textContent = 'Неверный ник или пароль';
    if (user.banned) return document.getElementById('loginError').textContent = 'Аккаунт заблокирован';
    window.currentUsername = u; sessionStorage.setItem('tonbet_current', u);
    const remember = document.getElementById('rememberMeCheckbox').checked;
    if (remember) { localStorage.setItem('tonbet_remembered', u); } else { localStorage.removeItem('tonbet_remembered'); }
    document.getElementById('loginUsername').value = ''; document.getElementById('loginPassword').value = '';
    showMain();
};
document.getElementById('registerBtn').onclick = async () => {
    const u = document.getElementById('regUsername').value.trim(), p = document.getElementById('regPassword').value, pc = document.getElementById('regConfirmPassword').value;
    if (!u || !p || !pc) return document.getElementById('regError').textContent = 'Заполните все поля';
    if (p !== pc) return document.getElementById('regError').textContent = 'Пароли не совпадают';
    if (window.users.some(x => x.username === u)) return document.getElementById('regError').textContent = 'Ник занят';
    window.users.push({ username: u, password: p, balance: 1000, bets: [], role: 'user', banned: false, activatedPromos: [], lastDailyBonus: 0, muted: false, creditTrust: 100, loanAmount: 0, loanTakenTimestamp: 0, loanRepaid: 0, frozenUntil: 0, trustRecoveryTimestamp: 0 });
    await saveUsers(); alert('Регистрация успешна!');
    document.getElementById('regUsername').value = ''; document.getElementById('regPassword').value = ''; document.getElementById('regConfirmPassword').value = '';
    document.getElementById('registerForm').classList.add('hidden'); document.getElementById('loginForm').classList.remove('hidden');
};

document.querySelectorAll('#bottomNav .nav-item').forEach(item => item.onclick = () => {
    document.querySelectorAll('#bottomNav .nav-item').forEach(i => i.classList.remove('active'));
    item.classList.add('active'); window.currentTab = item.dataset.tab; window.currentFilter = 'all';
    renderTab(window.currentTab);
});
document.querySelectorAll('#adminBottomNav .nav-item').forEach(item => item.onclick = () => {
    document.querySelectorAll('#adminBottomNav .nav-item').forEach(i => i.classList.remove('active'));
    item.classList.add('active'); window.currentTab = item.dataset.tab;
    renderTab(window.currentTab);
});
document.querySelectorAll('#workerBottomNav .nav-item').forEach(item => item.onclick = () => {
    document.querySelectorAll('#workerBottomNav .nav-item').forEach(i => i.classList.remove('active'));
    item.classList.add('active'); window.currentTab = item.dataset.tab;
    renderTab(window.currentTab);
});

window.onload = async () => {
    await loadData();
    if (!window.currentUsername) {
        const remembered = localStorage.getItem('tonbet_remembered');
        if (remembered && window.users.some(u => u.username === remembered)) {
            window.currentUsername = remembered;
            sessionStorage.setItem('tonbet_current', remembered);
        }
    }
    if (window.currentUsername && window.users.some(u => u.username === window.currentUsername)) {
        const user = getCurrentUser();
        if (user) checkLoanStatus(user);
        await showMain();
    } else {
        showWelcome();
    }
    db.ref('matches').on('value', s => { window.matches = s.val() ? Object.values(s.val()) : []; window.matches.forEach(m => { if (m.archived === undefined) m.archived = false; }); if (!window.els.welcome.classList.contains('hidden') && window.currentTab) renderTab(window.currentTab); });
    db.ref('users').on('value', s => { 
        window.users = s.val() ? Object.values(s.val()) : []; 
        window.users.forEach(u => { 
            u.bets = u.bets || []; 
            if (!u.activatedPromos) u.activatedPromos = []; 
            if (u.muted === undefined) u.muted = false; 
            if (u.creditTrust === undefined || u.creditTrust === null) u.creditTrust = 100;
            if (u.loanAmount === undefined || u.loanAmount === null) u.loanAmount = 0;
            if (u.loanTakenTimestamp === undefined || u.loanTakenTimestamp === null) u.loanTakenTimestamp = 0;
            if (u.loanRepaid === undefined || u.loanRepaid === null) u.loanRepaid = 0;
            if (u.frozenUntil === undefined || u.frozenUntil === null) u.frozenUntil = 0;
            if (u.trustRecoveryTimestamp === undefined || u.trustRecoveryTimestamp === null) u.trustRecoveryTimestamp = 0;
        }); 
        if (window.currentTab === 'news') renderTab('news'); 
    });
    db.ref('promoCodes').on('value', s => { window.promoCodes = s.val() ? Object.values(s.val()) : []; if (window.currentTab === 'adminPromo') renderTab('adminPromo'); });
    db.ref('promoLog').on('value', s => { window.promoLog = s.val() ? Object.values(s.val()) : []; if (window.currentTab === 'adminPromo') renderTab('adminPromo'); });
    db.ref('adminLog').on('value', s => { window.adminLog = s.val() ? Object.values(s.val()) : []; if (window.currentTab === 'adminLog') renderTab('adminLog'); });
    db.ref('news').on('value', s => { window.newsList = s.val() ? Object.values(s.val()) : []; if (window.currentTab === 'news' || window.currentTab === 'adminNews') renderTab(window.currentTab); });
    db.ref('loanLogs').on('value', s => { window.loanLogs = s.val() ? Object.values(s.val()) : []; if (window.currentTab === 'adminCredits') renderTab('adminCredits'); });
};
