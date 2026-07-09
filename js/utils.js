const DIVISIONS = ['ФТКЛ 2', 'ФТКЛ 3'];
const normName = n => n.trim().toLowerCase().replace(/\s+/g, ' ').replace(/ё/g, 'е');
const PERIOD_MULTIPLIERS = { '1H': 1.4, '2H': 1.6 };

function getTeamStats(teamName) {
    const norm = normName(teamName);
    const finished = window.matches.filter(m => m.score && (normName(m.team1) === norm || normName(m.team2) === norm));
    if (finished.length === 0) {
        return {
            matchesPlayed: 0, wins: 0, draws: 0, losses: 0,
            goalsScored: 0, goalsConceded: 0, goalDiff: 0,
            avgScored: 0, avgConceded: 0,
            winRate: 0, drawRate: 0, lossRate: 0,
            points: 0, formPoints: 0,
            attackStrength: 1.0, defenseStrength: 1.0, overallStrength: 1.0,
            homeWins: 0, homeDraws: 0, homeLosses: 0,
            awayWins: 0, awayDraws: 0, awayLosses: 0
        };
    }
    let wins = 0, draws = 0, losses = 0;
    let goalsScored = 0, goalsConceded = 0;
    let homeWins = 0, homeDraws = 0, homeLosses = 0;
    let awayWins = 0, awayDraws = 0, awayLosses = 0;
    let points = 0, recentPoints = 0;

    finished.forEach(m => {
        const isHome = normName(m.team1) === norm;
        const scored = isHome ? m.score.t1 : m.score.t2;
        const conceded = isHome ? m.score.t2 : m.score.t1;
        goalsScored += scored; goalsConceded += conceded;
        if (scored > conceded) {
            wins++; points += 3;
            if (isHome) homeWins++; else awayWins++;
            if (finished.indexOf(m) >= finished.length - 5) recentPoints += 3;
        } else if (scored === conceded) {
            draws++; points += 1;
            if (isHome) homeDraws++; else awayDraws++;
            if (finished.indexOf(m) >= finished.length - 5) recentPoints += 1;
        } else {
            losses++;
            if (isHome) homeLosses++; else awayLosses++;
        }
    });

    const total = finished.length;
    const avgScored = goalsScored / total;
    const avgConceded = goalsConceded / total;
    const goalDiff = goalsScored - goalsConceded;
    const winRate = wins / total;
    const drawRate = draws / total;
    const lossRate = losses / total;

    const leagueAvgScored = 1.5;
    let attackStrength = avgScored / leagueAvgScored;
    attackStrength = Math.max(0.5, Math.min(2.5, attackStrength));
    const leagueAvgConceded = 1.5;
    let defenseStrength = leagueAvgConceded / Math.max(0.1, avgConceded);
    defenseStrength = Math.max(0.5, Math.min(2.5, defenseStrength));
    let overallStrength = (attackStrength + defenseStrength) / 2;
    const maxRecentPoints = 5 * 3;
    const recentFormFactor = recentPoints / maxRecentPoints;
    overallStrength = overallStrength * 0.7 + recentFormFactor * 1.5 * 0.3;
    overallStrength = Math.max(0.5, Math.min(2.5, overallStrength));

    return {
        matchesPlayed: total, wins, draws, losses,
        goalsScored, goalsConceded, goalDiff,
        avgScored: avgScored.toFixed(2), avgConceded: avgConceded.toFixed(2),
        winRate: (winRate * 100).toFixed(1), drawRate: (drawRate * 100).toFixed(1), lossRate: (lossRate * 100).toFixed(1),
        points, formPoints: recentPoints,
        attackStrength: attackStrength.toFixed(2), defenseStrength: defenseStrength.toFixed(2),
        overallStrength: overallStrength.toFixed(2),
        homeWins, homeDraws, homeLosses,
        awayWins, awayDraws, awayLosses
    };
}

function smartOdds(homeStats, awayStats, homeName, awayName) {
    let homePower = parseFloat(homeStats.overallStrength);
    let awayPower = parseFloat(awayStats.overallStrength);
    const HOME_BONUS = 1.18;
    homePower *= HOME_BONUS;

    const totalPower = homePower + awayPower;
    let homeProb = homePower / totalPower;
    let awayProb = awayPower / totalPower;
    const powerDiff = Math.abs(homePower - awayPower);
    const normalizedDiff = powerDiff / Math.max(homePower, awayPower);
    const drawBase = 0.33;
    const drawFactor = drawBase * (1 - normalizedDiff * 0.7);
    const drawProb = Math.min(0.38, Math.max(0.15, drawFactor));
    const scale = (1 - drawProb) / (homeProb + awayProb);
    homeProb *= scale; awayProb *= scale;

    const margin = 0.92;
    let homeOdds = margin / homeProb;
    let drawOdds = margin / drawProb;
    let awayOdds = margin / awayProb;
    homeOdds = Math.min(2.30, Math.max(1.15, homeOdds));
    drawOdds = Math.min(4.50, Math.max(1.80, drawOdds));
    awayOdds = Math.min(2.30, Math.max(1.15, awayOdds));

    const avgTotal = parseFloat(homeStats.avgScored) + parseFloat(homeStats.avgConceded) + parseFloat(awayStats.avgScored) + parseFloat(awayStats.avgConceded);
    const expectedGoals = avgTotal / 2;
    const overProb = Math.min(0.72, Math.max(0.28, expectedGoals / 4.0));
    const underProb = 1 - overProb;
    let overOdds = margin / overProb;
    let underOdds = margin / underProb;
    overOdds = Math.min(2.40, Math.max(1.30, overOdds));
    underOdds = Math.min(2.40, Math.max(1.30, underOdds));

    const bttsProb = Math.min(0.68, Math.max(0.32, expectedGoals / 3.5));
    const noBttsProb = 1 - bttsProb;
    let bttsOdds = margin / bttsProb;
    let noBttsOdds = margin / noBttsProb;
    bttsOdds = Math.min(2.20, Math.max(1.40, bttsOdds));
    noBttsOdds = Math.min(2.20, Math.max(1.40, noBttsOdds));

    return {
        '1': +homeOdds.toFixed(2),
        'X': +drawOdds.toFixed(2),
        '2': +awayOdds.toFixed(2),
        'TB': +overOdds.toFixed(2),
        'TM': +underOdds.toFixed(2),
        'OZ': +bttsOdds.toFixed(2)
    };
}

// Функции для таймов
function getPeriodScore(match, period) {
    if (!match.score) return null;
    if (period === 'match') return match.score;
    if (period === '1H') return match.score_ht || null;
    if (period === '2H') {
        if (!match.score_ht) return null;
        return {
            t1: match.score.t1 - match.score_ht.t1,
            t2: match.score.t2 - match.score_ht.t2
        };
    }
    return null;
}

function getOddsForPeriod(match, outcome, period) {
    if (period === 'match') {
        if (outcome === 'TS') return match.odds_TS;
        if (outcome === 'TB') return match.odds_TB;
        if (outcome === 'TM') return match.odds_TM;
        if (outcome === 'OZ') return match.odds_OZ;
        return match.odds[outcome];
    }
    const suffix = period === '1H' ? '_1H' : '_2H';
    const multiplier = PERIOD_MULTIPLIERS[period];
    if (outcome === 'TS') {
        return match['odds_TS' + suffix] || (match.odds_TS * multiplier);
    }
    if (outcome === 'TB') {
        return match['odds_TB' + suffix] || (match.odds_TB * multiplier);
    }
    if (outcome === 'TM') {
        return match['odds_TM' + suffix] || (match.odds_TM * multiplier);
    }
    if (outcome === 'OZ') {
        return match['odds_OZ' + suffix] || (match.odds_OZ * multiplier);
    }
    return (match.odds && match.odds[suffix] && match.odds[suffix][outcome]) 
        || (match.odds[outcome] * multiplier);
}

function resolveBetsForMatch(match) {
    if (!match.score) return;
    window.users.forEach(user => {
        (user.bets || []).forEach(bet => {
            if (bet.status !== 'pending') return;
            let matchInBet = false;
            if (bet.type === 'single' && bet.matchId === match.id) matchInBet = true;
            else if (bet.type === 'express' && bet.legs.some(l => l.matchId === match.id)) matchInBet = true;
            if (!matchInBet) return;

            if (bet.type === 'single') {
                const periodScore = getPeriodScore(match, bet.period || 'match');
                if (!periodScore) return;
                let win = false;
                const { t1, t2 } = periodScore;
                if (bet.outcome === 'TS') win = t1 === bet.exactScore.t1 && t2 === bet.exactScore.t2;
                else if (['1','X','2'].includes(bet.outcome)) win = bet.outcome === ((t1 > t2) ? '1' : (t1 === t2) ? 'X' : '2');
                else if (bet.outcome === 'TB') win = (t1 + t2) > 2.5;
                else if (bet.outcome === 'TM') win = (t1 + t2) < 2.5;
                else if (bet.outcome === 'OZ') win = t1 > 0 && t2 > 0;
                bet.status = win ? 'win' : 'lose';
                if (win) { bet.winAmount = bet.amount * bet.odds; addBalanceWithLoan(user, bet.winAmount); }
            } else if (bet.type === 'express') {
                const allResolved = bet.legs.every(l => {
                    const m = window.matches.find(x => x.id === l.matchId);
                    return m && getPeriodScore(m, l.period || bet.period || 'match');
                });
                if (!allResolved) return;
                const allWin = bet.legs.every(l => {
                    const m = window.matches.find(x => x.id === l.matchId);
                    const periodScore = getPeriodScore(m, l.period || bet.period || 'match');
                    const { t1, t2 } = periodScore;
                    if (l.outcome === 'TS') return t1 === l.exactScore.t1 && t2 === l.exactScore.t2;
                    if (['1','X','2'].includes(l.outcome)) return l.outcome === ((t1 > t2) ? '1' : (t1 === t2) ? 'X' : '2');
                    if (l.outcome === 'TB') return (t1 + t2) > 2.5;
                    if (l.outcome === 'TM') return (t1 + t2) < 2.5;
                    if (l.outcome === 'OZ') return t1 > 0 && t2 > 0;
                });
                bet.status = allWin ? 'win' : 'lose';
                if (allWin) { bet.winAmount = bet.amount * bet.totalOdds; addBalanceWithLoan(user, bet.winAmount); }
            }
        });
    });
}

// Кредитная система (без изменений)
function getLoanDetails(user) {
    if (!user || !user.loanAmount || user.loanAmount <= 0) return null;
    const now = Date.now();
    const taken = user.loanTakenTimestamp;
    const daysPassed = Math.floor((now - taken) / (1000 * 60 * 60 * 24));
    const interestDays = Math.max(0, daysPassed - 3);
    const interest = interestDays * 500;
    const totalDue = user.loanAmount + interest;
    const repaid = user.loanRepaid || 0;
    const remaining = totalDue - repaid;
    const isOverdue = daysPassed >= 7;
    return { taken, daysPassed, interest, totalDue, repaid, remaining, isOverdue };
}

function applyLoanPayment(user, amount) {
    const details = getLoanDetails(user);
    if (!details) return 0;
    const payAmount = Math.min(amount, details.remaining);
    user.loanRepaid = (user.loanRepaid || 0) + payAmount;
    if (user.loanRepaid >= details.totalDue) {
        const completedDate = Date.now();
        const daysToRepay = Math.floor((completedDate - user.loanTakenTimestamp) / (1000 * 60 * 60 * 24));
        let newTrust = 100;
        if (daysToRepay >= 4 && daysToRepay < 5) newTrust = 75;
        else if (daysToRepay >= 5 && daysToRepay < 6) newTrust = 50;
        else if (daysToRepay >= 6 && daysToRepay < 7) newTrust = 25;
        else if (daysToRepay >= 7) newTrust = 0;
        user.creditTrust = newTrust;
        if (newTrust === 0) user.trustRecoveryTimestamp = Date.now() + 5 * 24 * 60 * 60 * 1000;
        window.loanLogs.push({
            username: user.username,
            action: 'repaid',
            amount: user.loanAmount,
            totalPaid: user.loanRepaid,
            timestamp: Date.now()
        });
        user.loanAmount = 0;
        user.loanTakenTimestamp = 0;
        user.loanRepaid = 0;
        if (user.frozenUntil > Date.now()) user.frozenUntil = 0;
    }
    return payAmount;
}

function checkLoanStatus(user) {
    if (!user || !user.loanAmount) return;
    const details = getLoanDetails(user);
    if (!details) return;
    const now = Date.now();
    if (details.isOverdue && details.remaining > 0) {
        if (user.balance > 0) {
            const payAmount = applyLoanPayment(user, user.balance);
            user.balance -= payAmount;
        }
        if (details.remaining > 0 && user.frozenUntil < now) user.frozenUntil = now + 3 * 24 * 60 * 60 * 1000;
    }
    if (details.remaining <= 0 && user.frozenUntil > now) user.frozenUntil = 0;
    if (user.creditTrust === 0 && user.trustRecoveryTimestamp && user.trustRecoveryTimestamp <= now) {
        user.creditTrust = 100;
        user.trustRecoveryTimestamp = 0;
    }
}

function handleBalanceIncrease(user, amount) {
    checkLoanStatus(user);
    if (user.loanAmount && getLoanDetails(user) && getLoanDetails(user).remaining > 0) {
        const payAmount = applyLoanPayment(user, amount);
        return amount - payAmount;
    }
    return amount;
}

function addBalanceWithLoan(user, amount) {
    const effective = handleBalanceIncrease(user, amount);
    user.balance += effective;
}

function showToast(message, type = 'success') {
    const toast = document.createElement('div'); toast.className = `toast ${type}`;
    toast.innerHTML = `<div style="flex:1;">${message}</div>`;
    document.body.appendChild(toast);
    setTimeout(() => { if (toast.parentNode) toast.remove(); }, 3000);
}

async function requestPushPermission() {
    if (!('Notification' in window)) {
        alert('Ваш браузер не поддерживает уведомления');
        return false;
    }
    try {
        const permission = await Notification.requestPermission();
        if (permission === 'granted') {
            await window.db.ref(`pushSubscriptions/${window.currentUsername}`).set({
                subscribed: true,
                timestamp: Date.now()
            });
            return true;
        }
        return false;
    } catch (err) {
        console.error('Ошибка запроса разрешения:', err);
        return false;
    }
}

async function checkPushSubscription() {
    if (!window.currentUsername) return false;
    const snap = await window.db.ref(`pushSubscriptions/${window.currentUsername}`).once('value');
    return snap.exists();
}
