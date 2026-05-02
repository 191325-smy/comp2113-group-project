#ifndef GAME_H
#define GAME_H

#include <string>

// ---- Game statistics ----
struct GameStats {
    int totalDamageDealt = 0;     // total damage dealt to enemies
    int totalDamageBlocked = 0;   // total damage blocked by player's block
    int monstersDefeated = 0;     // includes boss
    bool victory = false;         // defeated boss or not
};

// ---- Player / Class ----
enum ClassType { WARRIOR = 1, MAGE = 2 };

struct Player {
    ClassType cls;
    int maxHP;
    int hp;
    int baseDamage1;     // Warrior: attack; Mage: Poison Strike direct dmg
    int baseBlock2;      // block amount of skill 2
    int basePoison1;     // Mage: poison stacks of skill 1
    int basePoison3;     // Mage: poison stacks of skill 3
    int poisonStacks;    // poison on player
    int block;           // current block
    int skill1Level;
    int skill2Level;
    int skill3Level;
};

// ---- Enemy ----
struct Enemy {
    std::string name;
    int maxHP;
    int hp;
    int attackMin;
    int attackMax;
    int blockValue;
    bool isBoss;
    int poisonStacks;
    int block;
};

// Player-related functions
void initPlayer(Player &p, ClassType c);
void showPlayerStatus(const Player &p);
void upgradeSkill(Player &p);

// Enemy-related functions
Enemy generateNormalEnemy(int floor, int difficulty);
Enemy generateBoss(int difficulty);
void showEnemyStatus(const Enemy &e);

#endif