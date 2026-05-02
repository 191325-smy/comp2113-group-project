#include <iostream>
#include <ctime>
#include <cstdlib>
#include "game.h"
#include "utils.h"
#include "battle.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(static_cast<unsigned>(time(nullptr)));

    // 1. Read input file
    cout << "Enter input file name: ";
    string inFile;
    cin >> inFile;
    string originalContent = readWholeFile(inFile);

    // 2. Difficulty selection (re-prompt on invalid input)
    cout << "Choose difficulty: 1. Easy  2. Normal  3. Hard\n";
    int difficulty = readIntInRange("Your choice: ", 1, 3);

    // 3. Class selection (re-prompt on invalid input)
    cout << "Choose class: 1. Warrior (70 HP)  2. Mage (50 HP)\n";
    int cls = readIntInRange("Your choice: ", 1, 2);

    Player player;
    initPlayer(player, (ClassType)cls);
    GameStats stats;

    int pendingAttackBonus = 0;  // +damage to Skill 1 in next battle
    int pendingDefBonus    = 0;  // +block to Skill 2 in next battle
    bool alive = true;

    // 4. Allocate enemies dynamically (dynamic memory requirement)
    int totalBattles = 4; // 3 minions + 1 boss
    Enemy *enemies = new Enemy[totalBattles];
    for (int i = 0; i < 3; ++i) {
        enemies[i] = generateNormalEnemy(i + 1, difficulty);
    }
    enemies[3] = generateBoss(difficulty);

    // 5. Loop through all enemies
    for (int i = 0; i < totalBattles && alive; ++i) {
        int nextAttack = 0, nextDef = 0;
        bool win = fightOneEnemy(player, enemies[i], stats, pendingAttackBonus, pendingDefBonus, nextAttack, nextDef);
        if (!win) {
            alive = false;
            break;
        }
        // Upgrade skill after each victory except after final boss
        if (i < totalBattles - 1) {
            upgradeSkill(player);
        }
        pendingAttackBonus = nextAttack;
        pendingDefBonus    = nextDef;
    }

    // 6. Free dynamic memory
    delete[] enemies;

    // 7. Set victory flag
    if (alive && stats.monstersDefeated == totalBattles) {
        stats.victory = true;
    }

    // 8. Final stats to screen
    cout << "\n=== Game Over ===\n";
    cout << "Total damage dealt: " << stats.totalDamageDealt << "\n";
    cout << "Total damage blocked: " << stats.totalDamageBlocked << "\n";
    cout << "Monsters defeated: " << stats.monstersDefeated << "\n";
    cout << "Victory: " << (stats.victory ? "YES" : "NO") << "\n";

    // 9. Output file (stats only + original content)
    writeResultFile(inFile, originalContent, stats);
    cout << "Result written to: " << inFile << "\n";

    return 0;
}
