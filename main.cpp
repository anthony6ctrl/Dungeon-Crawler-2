#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Using a struct to organize Player data
struct Player {
    int health = 100;
    int maxHealth = 100;
    int exp = 0;
    int level = 1;
    int x = 0;
    int y = 0;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    Player p; // Create our player object
    vector<string> inventory;
    bool hasSword = false;
    bool gameRunning = true;

    cout << "Welcome to the Final Version of Dungeon Crawler!" << endl;

    while (gameRunning && p.health > 0) {
        cout << "\n[LVL: " << p.level << " | XP: " << p.exp << "/50]" << endl;
        cout << "HP: " << p.health << "/" << p.maxHealth << " | Pos: (" << p.x << ", " << p.y << ")" << endl;
        
        cout << "Move (w/a/s/d): ";
        char move;
        cin >> move;

        bool moved = false;
        if (move == 'w' && p.y < 2) { p.y++; moved = true; }
        else if (move == 's' && p.y > 0) { p.y--; moved = true; }
        else if (move == 'a' && p.x > 0) { p.x--; moved = true; }
        else if (move == 'd' && p.x < 2) { p.x++; moved = true; }

        if (moved) {
            p.exp += 10;
            if (p.exp >= 50) {
                p.level++;
                p.exp = 0;
                p.maxHealth += 20;
                p.health = p.maxHealth;
                cout << ">>> LEVEL UP! Now Level " << p.level << "!" << endl;
            }
        }

        if (p.x == 1 && p.y == 1 && !hasSword) {
            cout << ">>> Found a Rusty Sword!" << endl;
            inventory.push_back("Rusty Sword");
            hasSword = true;
        }

        if (p.x == 2 && p.y == 2) {
            int bossHP = 50;
            cout << "\n!!! BOSS BATTLE !!!" << endl;
            while (bossHP > 0 && p.health > 0) {
                int dmg = hasSword ? (rand() % 15 + 10) : (rand() % 10 + 5);
                bossHP -= dmg;
                if (bossHP > 0) p.health -= (rand() % 12 + 5);
            }
            if (p.health > 0) {
                cout << "VICTORY! You conquered the dungeon." << endl;
                gameRunning = false;
            }
        }
    }

    // Final Stats Display
    cout << "\n--- FINAL SCORECARD ---" << endl;
    cout << "Final Level: " << p.level << endl;
    cout << "Items Found: " << inventory.size() << endl;
    
    return 0;
}