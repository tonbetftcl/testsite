function renderAdminPanel() {
    const user = getCurrentUser();
    if (!user || user.role !== 'admin') {
        window.els.tab.innerHTML = '<div class="section-title">Доступ запрещен</div>';
        return;
    }

    const pendingTransfers = (window.transferRequests || []).filter(r => r.status === 'pending');

    let html = `<div class="section-title">Панель Администратора</div>`;

    if (pendingTransfers.length > 0) {
        html += `<div style="background:rgba(46,104,245,0.15);border:1px solid var(--accent);padding:10px;border-radius:var(--radius-md);margin-bottom:14px;">
            <div style="font-weight:700;margin-bottom:8px;">Заявки на перевод (${pendingTransfers.length})</div>`;
        pendingTransfers.forEach(r => {
            const senderUser = window.users.find(u => u.username === r.sender);
            const recipientUser = window.users.find(u => u.username === r.recipient);

            const senderRem = senderUser ? (senderUser.balance - r.amount) : 0;
            const recipientAdd = recipientUser ? (recipientUser.balance + r.amount) : 0;

            html += `<div style="background:var(--card-bg);padding:8px;border-radius:6px;margin-bottom:6px;font-size:0.8rem;">
                <div><strong>Кто:</strong> ${r.sender}</div>
                <div><strong>Счёт отпр:</strong> ${r.senderAcc} <span style="color:var(--text-secondary);">(Ост. баланс: ${senderRem.toFixed(0)})</span></div>
                <div><strong>Кому:</strong> ${r.recipient}</div>
                <div><strong>Счёт получ:</strong> ${r.recipientAcc} <span style="color:var(--text-secondary);">(Станет: ${recipientAdd.toFixed(0)})</span></div>
                <div style="font-weight:600;margin:4px 0;">Сумма: ${r.amount}</div>
                <div style="display:flex;gap:6px;margin-top:6px;">
                    <button class="action-btn small" onclick="approveTransfer('${r.id}')" style="background:var(--success);">Одобрить</button>
                    <button class="action-btn small" onclick="rejectTransfer('${r.id}')" style="background:var(--danger);">Отказать</button>
                </div>
            </div>`;
        });
        html += `</div>`;
    }

    html += `<div style="display:flex;flex-direction:column;gap:8px;">
        <button class="action-btn" onclick="adminCreateMatch()">Создать Матч</button>
        <button class="action-btn" onclick="adminManageNews()">Управление Новостями</button>
    </div>`;

    window.els.tab.innerHTML = html;
}

async function approveTransfer(reqId) {
    const req = (window.transferRequests || []).find(r => r.id === reqId);
    if (!req) return;
    const sender = window.users.find(u => u.username === req.sender);
    const recipient = window.users.find(u => u.username === req.recipient);

    if (!sender || sender.balance < req.amount) return alert('У отправителя недостаточно средств!');
    if (!recipient) return alert('Получатель не найден!');

    sender.balance -= req.amount;
    recipient.balance += req.amount;
    req.status = 'approved';

    await Promise.all([saveUsers(), saveTransferRequests()]);
    alert('Перевод успешно одобрен!');
    renderAdminPanel();
}

async function rejectTransfer(reqId) {
    const req = (window.transferRequests || []).find(r => r.id === reqId);
    if (!req) return;
    req.status = 'rejected';
    await saveTransferRequests();
    alert('Перевод отклонён!');
    renderAdminPanel();
}

function adminCreateMatch() {
    const t1 = prompt('Команда 1:'); if (!t1) return;
    const t2 = prompt('Команда 2:'); if (!t2) return;
    const div = prompt('Дивизион (ФТКЛ 2 / ФТКЛ 3):', 'ФТКЛ 2');
    
    const newMatch = {
        id: Date.now().toString(),
        team1: t1, team2: t2, division: div,
        status: 'open', archived: false,
        odds: { '1': 1.9, 'X': 3.2, '2': 2.1 },
        odds_TB: 1.85, odds_TM: 1.85, odds_OZ: 1.75, odds_TS: 5.0
    };
    if (!window.matches) window.matches = [];
    window.matches.push(newMatch);
    saveMatches();
    alert('Матч создан!');
}

function adminManageNews() {
    const title = prompt('Заголовок новости:'); if (!title) return;
    const text = prompt('Текст новости:'); if (!text) return;
    if (!window.newsList) window.newsList = [];
    window.newsList.push({ id: Date.now().toString(), title, text });
    saveNews();
    alert('Новость добавлена!');
}