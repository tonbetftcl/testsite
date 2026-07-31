window.users = window.users || [];
window.matches = window.matches || [];
window.newsList = window.newsList || [];
window.promoCodes = window.promoCodes || [];
window.transferRequests = window.transferRequests || [];
window.currentUsername = localStorage.getItem('tonbet_user') || null;
window.currentFilter = 'all';

window.els = {};

document.addEventListener('DOMContentLoaded', () => {
    window.els.tab = document.getElementById('tabContent');
    window.els.userHeader = document.getElementById('userHeaderInfo');

    initNavigation();
    loadAllData().then(() => {
        if (!window.currentUsername) {
            showAuthModal();
        } else {
            updateUserHeader();
            renderTab('matches');
        }
    });
});

function getCurrentUser() {
    return window.users.find(u => u.username === window.currentUsername);
}

function updateUserHeader() {
    const u = getCurrentUser();
    if (u && window.els.userHeader) {
        window.els.userHeader.textContent = `${u.username} (${u.balance.toFixed(0)})`;
    }
}

function initNavigation() {
    document.querySelectorAll('.nav-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.nav-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            const tab = btn.dataset.tab;
            renderTab(tab);
        });
    });
}

function renderTab(tabName) {
    if (window._bonusInterval) { clearInterval(window._bonusInterval); window._bonusInterval = null; }
    updateUserHeader();

    switch(tabName) {
        case 'matches': renderMatches(); break;
        case 'express': renderExpress(); break;
        case 'mybets': renderMyBets(); break;
        case 'transfers': renderTransfers(); break;
        case 'promo': renderPromo(); break;
        case 'leaderboard': renderLeaderboard(); break;
        case 'news': renderNews(); break;
        case 'profile': renderProfile(); break;
        case 'admin': renderAdminPanel(); break;
        default: renderMatches();
    }
}

function showAuthModal() {
    const overlay = document.createElement('div');
    overlay.className = 'modal-overlay';
    overlay.innerHTML = `<div class="modal-content">
        <div class="section-title">Вход / Регистрация</div>
        <div class="input-group">
            <label>Никнейм</label>
            <input type="text" id="authNick" placeholder="Ник">
        </div>
        <button class="action-btn" id="loginBtn">Войти</button>
    </div>`;
    document.body.appendChild(overlay);

    document.getElementById('loginBtn').onclick = async () => {
        const nick = document.getElementById('authNick').value.trim();
        if (!nick) return alert('Введите ник');
        let user = window.users.find(u => u.username.toLowerCase() === nick.toLowerCase());
        if (!user) {
            user = { username: nick, balance: 1000, role: 'user', bets: [], accountNumber: null };
            window.users.push(user);
        }
        window.currentUsername = user.username;
        localStorage.setItem('tonbet_user', user.username);
        await saveUsers();
        overlay.remove();
        updateUserHeader();
        renderTab('matches');
    };
}

function logout() {
    localStorage.removeItem('tonbet_user');
    window.currentUsername = null;
    location.reload();
}

/* Firebase / LocalStorage Sync Helpers */
async function loadAllData() {
    const localU = localStorage.getItem('tb_users_data');
    if (localU) window.users = JSON.parse(localU);
    const localM = localStorage.getItem('tb_matches_data');
    if (localM) window.matches = JSON.parse(localM);
    const localN = localStorage.getItem('tb_news_data');
    if (localN) window.newsList = JSON.parse(localN);
    const localT = localStorage.getItem('tb_transfers_data');
    if (localT) window.transferRequests = JSON.parse(localT);
}

async function saveUsers() {
    localStorage.setItem('tb_users_data', JSON.stringify(window.users));
    updateUserHeader();
}

async function saveMatches() {
    localStorage.setItem('tb_matches_data', JSON.stringify(window.matches));
}

async function saveNews() {
    localStorage.setItem('tb_news_data', JSON.stringify(window.newsList));
}

async function saveTransferRequests() {
    localStorage.setItem('tb_transfers_data', JSON.stringify(window.transferRequests));
}

async function savePromoCodes() {
    localStorage.setItem('tb_promo_data', JSON.stringify(window.promoCodes));
}