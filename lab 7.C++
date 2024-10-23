#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAP_SIZE_1 = 14;
const int MAP_SIZE_2 = 28;
const char PLAYER = '@';
const char WALL = '#';
const char ENEMY = 'E';
const char TREASURE = 'T';
const char EMPTY = ' ';

// Function to initialize the map with walls, empty spaces, and elements
void initializeMap(vector<vector<char>>& map, int size, int numEnemies) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                map[i][j] = WALL;  // Borders
            } else {
                map[i][j] = EMPTY; // Empty spaces
            }
        }
    }

    // Place enemies randomly
    srand(time(0));
    for (int i = 0; i < numEnemies; ++i) {
        int x, y;
        do {
            x = rand() % (size - 2) + 1;
            y = rand() % (size - 2) + 1;
        } while (map[x][y] != EMPTY);
        map[x][y] = ENEMY;
    }

    // Place the treasure in a random position
    int tx, ty;
    do {
        tx = rand() % (size - 2) + 1;
        ty = rand() % (size - 2) + 1;
    } while (map[tx][ty] != EMPTY);
    map[tx][ty] = TREASURE;
}

// Function to display the map on the console
void displayMap(const vector<vector<char>>& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Function to move the player and handle collisions with enemies and the treasure
void movePlayer(vector<vector<char>>& map, int& px, int& py, char move, int& health, bool& foundTreasure) {
    int newX = px, newY = py;

    if (move == 'W' || move == 'w') --newX;
    else if (move == 'S' || move == 's') ++newX;
    else if (move == 'A' || move == 'a') --newY;
    else if (move == 'D' || move == 'd') ++newY;

    if (map[newX][newY] == WALL) {
        cout << "You hit a wall!\n";
    } else if (map[newX][newY] == ENEMY) {
        cout << "You encountered an enemy! You lose 10 health points.\n";
        health -= 10;
        if (health <= 0) {
            cout << "You lost all your health! Game over.\n";
            exit(0);
        }
        map[px][py] = EMPTY;
        px = newX;
        py = newY;
        map[px][py] = PLAYER;
    } else if (map[newX][newY] == TREASURE) {
        cout << "You found the treasure!\n";
        foundTreasure = true;
    } else {
        map[px][py] = EMPTY;
        px = newX;
        py = newY;
        map[px][py] = PLAYER;
    }
}

int main() {
    // Personalized greeting
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "HELLO " << name << ", TODAY WE'RE GOING TO PLAY DUNGEONS.\n";
    cout << name << " YOU CAN MOVE THROUGH THE GRID USING THE KEYS:\n";
    cout << "W (to move up)\n";
    cout << "A (to move left)\n";
    cout << "S (to move down)\n";
    cout << "D (to move right)\n";

    // Initialize the first map
    vector<vector<char>> map1(MAP_SIZE_1, vector<char>(MAP_SIZE_1));
    initializeMap(map1, MAP_SIZE_1, 10);  // 10 enemies on the first map

    int playerX = 1, playerY = 1;
    int health = 100;
    bool foundTreasure = false;

    map1[playerX][playerY] = PLAYER;

    // Gameplay on the first map
    while (!foundTreasure) {
        displayMap(map1);
        cout << "Health: " << health << endl;
        cout << "Move (WASD): ";
        char move;
        cin >> move;
        movePlayer(map1, playerX, playerY, move, health, foundTreasure);
    }

    // Move to the second map
    vector<vector<char>> map2(MAP_SIZE_2, vector<char>(MAP_SIZE_2));
    initializeMap(map2, MAP_SIZE_2, 20);  // 20 enemies on the second map
    playerX = 1;
    playerY = 1;
    foundTreasure = false;

    map2[playerX][playerY] = PLAYER;
    cout << "You have moved to the second level!\n";

    // Gameplay on the second map
    while (!foundTreasure) {
        displayMap(map2);
        cout << "Health: " << health << endl;
        cout << "Move (WASD): ";
        char move;
        cin >> move;
        movePlayer(map2, playerX, playerY, move, health, foundTreasure);
    }

    cout << "Congratulations " << name << "! You won the game!\n";
    return 0;
}
