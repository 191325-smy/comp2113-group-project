#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Generate a random integer between l and r (inclusive)
int randInRange(int l, int r) {
    return l + rand() % (r - l + 1);
}

// Apply damage to target, considering block. Returns actual damage dealt.
int applyDamageToTarget(int dmg, int &targetBlock, int &targetHP, GameStats &stats, bool countBlocked) {
    if (dmg <= 0) return 0;
    int blocked = (targetBlock > dmg) ? dmg : targetBlock;
    targetBlock -= blocked;
    if (countBlocked && blocked > 0) {
        stats.totalDamageBlocked += blocked;
    }
    int realDmg = dmg - blocked;
    if (realDmg < 0) realDmg = 0;
    targetHP -= realDmg;
    return realDmg;
}

// Read an integer from user input within [minVal, maxVal]. Re-prompt on invalid input.
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

// Read and return entire content of a file. Return empty string if file cannot be opened.
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

// Write original content and game statistics to the output file.
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