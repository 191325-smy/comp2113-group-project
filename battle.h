#ifndef BATTLE_H
#define BATTLE_H

#include "game.h"
#include "utils.h"

// Single battle vs one enemy
// pendingAttackBonus / pendingDefBonus: bonuses from previous battle (for next battle start)
// nextAttackBonus / nextDefBonus: bonuses granted to the following battle
bool fightOneEnemy(Player &p, Enemy &e, GameStats &stats,
                   int pendingAttackBonus, int pendingDefBonus,
                   int &nextAttackBonus, int &nextDefBonus);

#endif