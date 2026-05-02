#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int randInRange(int l, int r) {
    return l + rand() % (r - l + 1);
}

int applyDamageToTarget(int dmg, int &targetBlock, int &targetHP,
                        GameStats &stats, bool countBlocked) {
    if (dmg <= 0) return 0;
    int blocked = (targetBlock > dmg) ? dmg : targetBlock;
    targetBlock -= blocked;
    if (countBlocked && blocked > 0) {
        stats.totalDamageBlocked += blocked;
    }
    int realDmg = dmg - blocked;
    targetHP -= realDmg;
    if (realDmg < 0) realDmg = 0;
    return realDmg;
}

int readIntInRange(const char *prompt, int minVal, int maxVal) {
    int x;
    while (true) {
        if (prompt) {
            cout << prompt;
        }
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (x < minVal || x > maxVal) {
            cout << "Invalid choice. Please enter a number between "
                 << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return x;
    }
}

string readWholeFile(const string &filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Failed to open input file: " << filename
             << ". Treating as empty.\n";
        return "";
    }
    stringstream buffer;
    buffer << fin.rdbuf();
    return buffer.str();
}

void writeResultFile(const string &filename,
                     const string &original,
                     const GameStats &stats) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Failed to write output file: " << filename << "\n";
        return;
    }
    fout << original;
    if (!original.empty() && original.back() != '\n') fout << "\n";

    fout << "==== Run Statistics ====\n";
    fout << "Total damage dealt: " << stats.totalDamageDealt << "\n";
    fout << "Total damage blocked (by player): "
         << stats.totalDamageBlocked << "\n";
    fout << "Monsters defeated: " << stats.monstersDefeated << "\n";
    fout << "Victory: " << (stats.victory ? "YES" : "NO") << "\n";
}