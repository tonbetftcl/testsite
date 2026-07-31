const DIVISIONS = ['ФТКЛ 2', 'ФТКЛ 3'];
const normName = n => (n || '').trim().toLowerCase().replace(/\s+/g, ' ').replace(/ё/g, 'е');

const PERIOD_MULTIPLIERS = {
    '1H': { outcome: 1.10, draw: 1.05, total: 1.08, ts: 1.20 },
    '2H': { outcome: 1.15, draw: 1.10, total: 1.12, ts: 1.30 }
};

function getTeamStats(teamName) {
    const norm = normName(teamName);
    const finished = (window.matches || []).filter(m => m.score && (normName(m.team1) === norm || normName(m.team2) === norm));
    if (finished.length === 0) {
        return {
            matchesPlayed: 0, wins: 0, draws: 0, losses: 0,
            goalsScored: 0, goalsConceded: 0, goalDiff: 0,
            avgScored: 0, avgConceded: 0, winRate: 0, drawRate: 0, lossRate: 0,
            points: 0, formPoints: 0, attackStrength: 1.0, defenseStrength: 1.0, overallStrength: 1.0
        };
    }
    let wins = 0, draws = 0, losses = 0, goalsScored = 0, goalsConceded = 0, points = 0, recentPoints = 0;

    finished.forEach((m, idx) => {
        const isHome = normName(m.team1) === norm;
        const scored = isHome ? m.score.t1 : m.score.t2;
        const conceded = isHome ? m.score.t2 : m.score.t1;
        goalsScored += scored; goalsConceded += conceded;
        if (scored > conceded) {
            wins++; points += 3;
            if (idx >= finished.length - 5) recentPoints += 3;
        } else if (scored === conceded) {
            draws++; points += 1;
            if (idx >= finished.length - 5) recentPoints += 1;
        } else {
            losses++;
        }
    });

    const total = finished.length;
    const avgScored = goalsScored / total;
    const avgConceded = goalsConceded / total;
    let attackStrength = Math.max(0.5, Math.min(2.5, avgScored / 1.5));
    let defenseStrength = Math.max(0.5, Math.min(2.5, 1.5 / Math.max(0.1, avgConceded)));
    let overallStrength = Math.max(0.5, Math.min(2.5, ((attackStrength + defenseStrength) / 2) * 0.7 + (recentPoints / 15) * 1.5 * 0.3));

    return {
        matchesPlayed: total, wins, draws, losses,
        goalsScored, goalsConceded, goalDiff: goalsScored - goalsConceded,
        avgScored: avgScored.toFixed(2), avgConceded: avgConceded.toFixed(2),
        winRate: ((wins / total) * 100).toFixed(1),
        points, formPoints: recentPoints,
        attackStrength: attackStrength.toFixed(2), defenseStrength: defenseStrength.toFixed(2),
        overallStrength: overallStrength.toFixed(2)
    };
}

function getPeriodScore(match, period) {
    if (!match || !match.score) return null;
    if (period === 'match') return match.score;
    if (period === '1H') return match.score_ht || null;
    if (period === '2H') {
        if (!match.score_ht) return null;
        return { t1: match.score.t1 - match.score_ht.t1, t2: match.score.t2 - match.score_ht.t2 };
    }
    return null;
}

function getOddsForPeriod(match, outcome, period) {
    if (outcome === 'Pass1') return match.odds_pass1 || (match.odds['1'] * 0.95);
    if (outcome === 'Pass2') return match.odds_pass2 || (match.odds['2'] * 0.95);
    if (period === 'match') {
        if (outcome === 'TS') return match.odds_TS || 5.0;
        if (outcome === 'TB') return match.odds_TB || 1.8;
        if (outcome === 'TM') return match.odds_TM || 1.8;
        if (outcome === 'OZ') return match.odds_OZ || 1.7;
        return match.odds[outcome] || 2.0;
    }
    const mult = PERIOD_MULTIPLIERS[period] || PERIOD_MULTIPLIERS['1H'];
    if (outcome === 'TS') return match['odds_TS_' + period] || ((match.odds_TS || 5.0) * mult.ts);
    if (['TB', 'TM', 'OZ'].includes(outcome)) {
        const base = outcome === 'TB' ? match.odds_TB : (outcome === 'TM' ? match.odds_TM : match.odds_OZ);
        return match['odds_' + outcome + '_' + period] || ((base || 1.8) * mult.total);
    }
    const baseOdds = match.odds[outcome] || 2.0;
    return (match.odds && match.odds[period] && match.odds[period][outcome]) || (baseOdds * (outcome === 'X' ? mult.draw : mult.outcome));
}

function resolveBetsForMatch(match) {
    if (!match || !match.score) return;
    (window.users || []).forEach(user => {
        (user.bets || []).forEach(bet => {
            if (bet.status !== 'pending') return;
            let matchInBet = false;
            if (bet.type === 'single' && bet.matchId === match.id) matchInBet = true;
            else if (bet.type === 'express' && bet.legs && bet.legs.some(l => l.matchId === match.id)) matchInBet = true;
            if (!matchInBet) return;

            const processBet = (b) => {
                if (b.outcome === 'Pass1' || b.outcome === 'Pass2') {
                    if (match.type === 'cup' && match.stage === 'single') {
                        const passedTeam1 = (match.score.t1 > match.score.t2) || (match.score.t1 === match.score.t2 && match.winner === 'team1');
                        return ((b.outcome === 'Pass1' && passedTeam1) || (b.outcome === 'Pass2' && !passedTeam1)) ? 'win' : 'lose';
                    }
                    return null;
                }
                const periodScore = getPeriodScore(match, b.period || 'match');
                if (!periodScore) return null;
                const { t1, t2 } = periodScore;
                if (b.outcome === 'TS') return (t1 === b.exactScore.t1 && t2 === b.exactScore.t2) ? 'win' : 'lose';
                if (['1','X','2'].includes(b.outcome)) {
                    const res = (t1 > t2) ? '1' : (t1 === t2) ? 'X' : '2';
                    return b.outcome === res ? 'win' : 'lose';
                }
                if (b.outcome === 'TB') return (t1 + t2) > 2.5 ? 'win' : 'lose';
                if (b.outcome === 'TM') return (t1 + t2) < 2.5 ? 'win' : 'lose';
                if (b.outcome === 'OZ') return (t1 > 0 && t2 > 0) ? 'win' : 'lose';
                return null;
            };

            if (bet.type === 'single') {
                const res = processBet(bet);
                if (res) {
                    bet.status = res;
                    if (res === 'win') {
                        bet.winAmount = bet.amount * bet.odds;
                        user.balance += bet.winAmount;
                    }
                }
            } else if (bet.type === 'express') {
                let allWin = true;
                let resolvedCount = 0;
                for (const leg of bet.legs) {
                    const m = window.matches.find(x => x.id === leg.matchId);
                    if (!m || !m.score) break;
                    const res = processBet(leg);
                    if (!res) break;
                    resolvedCount++;
                    if (res !== 'win') allWin = false;
                }
                if (resolvedCount === bet.legs.length) {
                    bet.status = allWin ? 'win' : 'lose';
                    if (allWin) {
                        bet.winAmount = bet.amount * bet.totalOdds;
                        user.balance += bet.winAmount;
                    }
                }
            }
        });
    });
}

function showToast(message, type = 'success') {
    const toast = document.createElement('div');
    toast.className = `toast ${type}`;
    toast.style.cssText = 'position:fixed;bottom:70px;left:50%;transform:translateX(-50%);background:#1f293d;border:1px solid rgba(255,255,255,0.1);padding:8px 16px;border-radius:20px;z-index:1000;font-size:0.8rem;box-shadow:0 4px 12px rgba(0,0,0,0.3);';
    toast.textContent = message;
    document.body.appendChild(toast);
    setTimeout(() => { if (toast.parentNode) toast.remove(); }, 2500);
}