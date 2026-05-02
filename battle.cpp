#include "battle.h"
#include <iostream>
using namespace std;

// print skill menu (short)
static void printSkillMenu(const Player &p, int atkBonus, int defBonus) {
    if (p.cls == WARRIOR) {
        cout << "1) Attack  dmg=" << p.baseDamage1 + atkBonus << "\n";
        cout << "2) Defend  blk=" << p.baseBlock2 + defBonus << "\n";
        cout << "3) Heal    +5 HP\n";
    } else {
        cout << "1) PStrike dmg=" << p.baseDamage1 + atkBonus
             << " + " << p.basePoison1 << " poison\n";
        cout << "2) Shield  blk=" << p.baseBlock2 + defBonus << "\n";
        cout << "3) MPoison +" << p.basePoison3 << " poison\n";
    }
}

// Enemy turn (uses pre-decided action)
static void enemyTurn(Player &p, Enemy &e, GameStats &stats, int action) {
    cout << "\n-- Enemy Turn --\n";
    if (e.isBoss) {
        // Boss: 1=attack, 2=defend, 3=poison
        if (action == 1) {
            int dmg = e.attackMin;
            cout << "Boss attacks for " << dmg << ".\n";
            applyDamageToTarget(dmg, p.block, p.hp, stats, true);
        } else if (action == 2) {
            cout << "Boss defends, +" << e.blockValue << " block.\n";
            e.block += e.blockValue;
        } else {
            cout << "Boss poisons you (+4 stacks).\n";
            p.poisonStacks += 4;
        }
    } else {
        // Minion: 1=attack, 2=defend
        if (action == 1) {
            int dmg = randInRange(e.attackMin, e.attackMax);
            cout << e.name << " strikes for " << dmg << ".\n";
            applyDamageToTarget(dmg, p.block, p.hp, stats, true);
        } else {
            cout << e.name << " defends, +" << e.blockValue << " block.\n";
            e.block += e.blockValue;
        }
    }

    // Enemy poison at end of its turn
    if (e.poisonStacks > 0) {
        cout << e.name << " takes " << e.poisonStacks << " poison.\n";
        e.hp -= e.poisonStacks;
        stats.totalDamageDealt += e.poisonStacks;
        e.poisonStacks--;
    }
}

// Player uses one skill
static void useOneSkill(Player &p, Enemy &e, GameStats &stats, int skillChoice, int attackBonus, int defendBonus) {
    if (p.cls == WARRIOR) {
        if (skillChoice == 1) {
            int dmg = p.baseDamage1 + attackBonus;
            cout << "You Attack, dmg=" << dmg << ".\n";
            int real = applyDamageToTarget(dmg, e.block, e.hp, stats, false);
            stats.totalDamageDealt += real;
        } else if (skillChoice == 2) {
            int blk = p.baseBlock2 + defendBonus;
            cout << "You Defend, block+=" << blk << ".\n";
            p.block += blk;
        } else {
            int healAmount = 5;
            cout << "You Heal, +" << healAmount << " HP.\n";
            p.hp += healAmount;
            if (p.hp > p.maxHP) p.hp = p.maxHP;
        }
    } else { // Mage
        if (skillChoice == 1) {
            int dmg = p.baseDamage1 + attackBonus;
            cout << "You Poison Strike, dmg=" << dmg
                 << ", poison+=" << p.basePoison1 << ".\n";
            int real = applyDamageToTarget(dmg, e.block, e.hp, stats, false);
            stats.totalDamageDealt += real;
            e.poisonStacks += p.basePoison1;
        } else if (skillChoice == 2) {
            int blk = p.baseBlock2 + defendBonus;
            cout << "You Shield, block+=" << blk << ".\n";
            p.block += blk;
        } else {
            cout << "You Mega Poison, poison+=" << p.basePoison3 << ".\n";
            e.poisonStacks += p.basePoison3;
        }
    }
}

// Single battle
bool fightOneEnemy(Player &p, Enemy &e, GameStats &stats,
                   int pendingAttackBonus, int pendingDefBonus,
                   int &nextAttackBonus, int &nextDefBonus) {
    int attackBonus = pendingAttackBonus;
    int defendBonus = pendingDefBonus;

    // Reset block at the start of each battle
    p.block = 0;
    e.block = 0;

    cout << "\n=============================\n";
    cout << "Encounter: " << e.name << "\n";
    cout << "Battle bonuses - atk+" << attackBonus
         << ", def+" << defendBonus << " on Skill 2.\n";

    nextAttackBonus = 0;
    nextDefBonus = 0;
    int turnIndex = 0; // enemy turn counter

    while (p.hp > 0 && e.hp > 0) {
        cout << "\n";
        showPlayerStatus(p);
        showEnemyStatus(e);

        // Decide enemy intent (deterministic pattern)
        int intendedAction;
        if (e.isBoss) {
            int cycle = (turnIndex % 3); // 0,1,2
            if (cycle == 0) intendedAction = 1; // attack
            else if (cycle == 1) intendedAction = 2; // defend
            else intendedAction = 3; // poison
            cout << "[Intent] Boss: "
                 << (intendedAction == 1 ? "Attack" :
                     intendedAction == 2 ? "Defend" : "Poison")
                 << "\n";
        } else {
            // Minion: Attack -> Defend -> Attack ...
            if (turnIndex % 2 == 0) intendedAction = 1;
            else intendedAction = 2;
            cout << "[Intent] Minion: "
                 << (intendedAction == 1 ? "Strike" : "Defend")
                 << "\n";
        }

        cout << "\n-- Your Turn (2 skills) --\n";
        printSkillMenu(p, attackBonus, defendBonus);

        for (int i = 1; i <= 2; ++i) {
            string prompt = "Choose skill " + to_string(i) + " (1-3): ";
            int choice = readIntInRange(prompt.c_str(), 1, 3);
            useOneSkill(p, e, stats, choice, attackBonus, defendBonus);
            if (e.hp <= 0) break;
        }

        // Player poison at end of player turn
        if (p.poisonStacks > 0) {
            cout << "You take " << p.poisonStacks << " poison.\n";
            p.hp -= p.poisonStacks;
            p.poisonStacks--;
        }

        if (e.hp <= 0 || p.hp <= 0) break;

        // Enemy acts
        enemyTurn(p, e, stats, intendedAction);
        turnIndex++;
    }

    // Clear block at the end of the battle
    p.block = 0;

    if (p.hp <= 0) {
        cout << "You were defeated.\n";
        return false;
    } else {
        cout << "You defeated " << e.name << "!\n";
        stats.monstersDefeated++;

        // Random potion: 3 types
        cout << "You find a random potion:\n";
        int potion = randInRange(1, 3);
        if (potion == 1) {
            cout << "Attack Potion: next battle Skill 1 +2 damage.\n";
            nextAttackBonus += 2;
        } else if (potion == 2) {
            cout << "Defense Potion: next battle Skill 2 +2 block.\n";
            nextDefBonus += 2;
        } else {
            cout << "Healing Potion: heal 10 HP now.\n";
            p.hp += 10;
            if (p.hp > p.maxHP) p.hp = p.maxHP;
        }
        return true;
    }
}