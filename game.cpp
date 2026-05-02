#include "game.h"
#include "utils.h"
#include <iostream>
using namespace std;

// ---------- Player functions ----------

void initPlayer(Player &p, ClassType c) {
    p.cls = c;
    if (c == WARRIOR) {
        p.maxHP = 70;
        p.hp = 70;
        p.baseDamage1 = 7;
        p.baseBlock2  = 6;
        p.basePoison1 = 0;
        p.basePoison3 = 0;
    } else {
        p.maxHP = 50;
        p.hp = 50;
        p.baseDamage1 = 4;  // direct damage of Poison Strike
        p.baseBlock2  = 5;
        p.basePoison1 = 3;  // poison stacks of skill 1
        p.basePoison3 = 4;  // poison stacks of skill 3
    }
    p.poisonStacks = 0;
    p.block = 0;
    p.skill1Level = p.skill2Level = p.skill3Level = 0;
}

void showPlayerStatus(const Player &p) {
    cout << "Player HP: " << p.hp << "/" << p.maxHP
         << "  Block: " << p.block
         << "  Poison: " << p.poisonStacks << "\n";
}

void upgradeSkill(Player &p) {
    cout << "\n--- Choose a skill to upgrade ---\n";
    int ch;
    if (p.cls == WARRIOR) {
        cout << "1. Skill 1 (Attack)   +3 damage\n";
        cout << "2. Skill 2 (Defense)  +2 block\n";
        cout << "3. Skill 3 (Heal)     +2 max HP\n";
        ch = readIntInRange("Your choice: ", 1, 3);
        if (ch == 2) {
            p.baseBlock2 += 2; p.skill2Level++;
        } else if (ch == 3) {
            p.maxHP += 2;
            p.hp += 2;
            p.skill3Level++;
        } else {
            p.baseDamage1 += 3; p.skill1Level++;
        }
    } else {
        cout << "1. Skill 1 (Poison Strike)  +1 poison stack\n";
        cout << "2. Skill 2 (Shield)         +2 block\n";
        cout << "3. Skill 3 (Mega Poison)    +4 poison stacks\n";
        ch = readIntInRange("Your choice: ", 1, 3);
        if (ch == 2) {
            p.baseBlock2 += 2; p.skill2Level++;
        } else if (ch == 3) {
            p.basePoison3 += 2; p.skill3Level++;
        } else {
            p.basePoison1 += 1; p.skill1Level++;
        }
    }
    cout << "Skill upgraded!\n";
}

// ---------- Enemy functions ----------

Enemy generateNormalEnemy(int floor, int difficulty) {
    Enemy e;
    e.isBoss = false;
    e.name = "Minion Floor " + to_string(floor);

    int baseHP      = 30 + floor * 10;
    int baseAtkMin  = 5  + floor * 2;
    int baseAtkMax  = 8  + floor * 3;
    int baseBlock   = 4  + floor * 2;

    int hpBonus   = (difficulty - 1) * 10;
    int atkBonus  = (difficulty - 1) * 2;
    int blkBonus  = (difficulty - 1) * 1;

    e.maxHP      = e.hp = baseHP + hpBonus;
    e.attackMin  = baseAtkMin + atkBonus;
    e.attackMax  = baseAtkMax + atkBonus;
    e.blockValue = baseBlock + blkBonus;

    e.poisonStacks = 0;
    e.block = 0;
    return e;
}

Enemy generateBoss(int difficulty) {
    Enemy e;
    e.isBoss = true;
    e.name = "Boss";

    int baseHP   = 80;
    int baseAtk  = 7;
    int baseBlk  = 5;

    int hpBonus  = (difficulty - 1) * 15;
    int atkBonus = (difficulty - 1) * 2;
    int blkBonus = (difficulty - 1) * 2;

    e.maxHP      = e.hp = baseHP + hpBonus;
    e.attackMin  = e.attackMax = baseAtk + atkBonus;
    e.blockValue = baseBlk + blkBonus;
    e.poisonStacks = 0;
    e.block = 0;
    return e;
}

void showEnemyStatus(const Enemy &e) {
    cout << e.name << " HP: " << e.hp << "/" << e.maxHP
         << "  Block: " << e.block
         << "  Poison: " << e.poisonStacks << "\n";
}