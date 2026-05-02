#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "game.h"

// random int in [l, r]
int randInRange(int l, int r);

// apply damage with block
// if countBlocked = true, blocked damage is added to stats.totalDamageBlocked
int applyDamageToTarget(int dmg, int &targetBlock, int &targetHP,
                        GameStats &stats, bool countBlocked);

// safe integer input with range checking; will loop until valid
int readIntInRange(const char *prompt, int minVal, int maxVal);

// file I/O
std::string readWholeFile(const std::string &filename);
void writeResultFile(const std::string &filename,
                     const std::string &original,
                     const GameStats &stats);

#endif