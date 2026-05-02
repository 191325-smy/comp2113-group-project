# COMP2113 Course Project
## Text-Based Turn-Based Battle Game

---

## 1. Team Members
| Name          | Student ID   | GitHub Username | Contribution                     |
|---------------|--------------|-----------------|----------------------------------|
| Sun Mingyuan  | 3036590403   | 191325-smy      | main, battle, make file          |
| Wang Youzi    | 3036588541   | WangYouzi-yugo  | game, util                       |

---

## 2. Game Description
This is a text-based turn-based battle game. We use standard C++ to make it. Players can choose Warrior or Mage. Players need to fight 3 groups of enemies, then Players can get potions and upgrade skills. At the end, players need to fight a boss. The game has 3 difficulty levels, and attack, block, poison, healing and skill systems.

---

## 3. Core Game Rules
- Players can use **two skills** in each turn.
- Block value stacks up. It only disappears when taking damage during a battle.
- Block resets to 0 after each battle.
- Poison damage reduces HP directly. It does not reduce block.
- Attack damage is calculated before enemy actions.
- Poison damage is calculated after enemy actions.
- The game asks the user to input again if the input is invalid.

---

## 4. Class and Skill Details
### Warrior (70 HP)
- Skill 1: Deal 7 damage
- Skill 2: Gain 6 block
- Skill 3: Heal 5 HP
- Upgrade:
  - Skill 1: +3 damage
  - Skill 2: +2 block
  - Skill 3: +2 max HP

### Mage (50 HP)
- Skill 1: Deal 4 damage and apply 3 poison stacks
- Skill 2: Gain 5 block
- Skill 3: Apply 4 poison stacks
- Upgrade:
  - Skill 1: +1 poison stack
  - Skill 2: +2 block
  - Skill 3: +2 poison stacks

Poison deals damage equal to poison stacks. Poison stacks decrease by 1 each turn.

---

## 5. Potion System (Random After Battle)
Players get one random potion after winning a battle.
1. Attack Potion: for both character Skill 1 damage +2 in next battle
2. Block Potion: Block +2 in next battle
3. Heal Potion: Heal 10 HP at once

Bonus values are shown on the status panel.

---

## 6. Features Implemented
- Two playable character classes: Warrior & Mage
- Three difficulty levels: Easy, Normal, Hard
- To let player choose again while having invalid input.(like input number 4)
- Turn-based combat system
- Random potion drops after battles
- Player skill upgrade system
- Poison damage over time
- Damage block mechanics
- Battle log recording
- Final statistics summary
- Input/output file support

---

## 7. Mandatory Coding Elements
1. Random events
   The game uses random values for potion drops.

2. Data structures
   We use Player, Enemy, GameStats and BattleLog structures to store game data.

3. Dynamic memory management
   The game uses dynamic memory for battle logs. Memory is created and deleted correctly.

4. File I/O
   The game reads an input file. It writes game results to an output file. Results include total damage, total blocked damage, monster count and victory status.

5. Multiple file structure
   The code is split into many .cpp and .h files. The code is clear and easy to manage.

---

## 8. Compilation & Execution

### Compile
g++ -std=c++11 *.cpp -o game

### Run (Windows)
game.exe

### Run (macOS / Linux)
./game

---

## 9. How to Play
1. Enter an input file name (can be any name).
2. Select difficulty (1/2/3).
3. Select class (1 = Warrior, 2 = Mage).
4. Each turn choose TWO skills.
5. Enemy intent is displayed before their action.
6. After battles, choose a skill to upgrade.
7. Defeat all enemies and boss to win.
8. Enter output file name to save full battle log.

---

## 10. Project Files
- main.cpp
- battle.cpp / battle.h
- game.cpp / game.h
- utils.cpp / utils.h
- README.md