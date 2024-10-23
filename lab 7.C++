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

// Función para inicializar el mapa con paredes, espacios vacíos y elementos
void initializeMap(vector<vector<char>>& map, int size, int numEnemies) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                map[i][j] = WALL;  // Bordes
            } else {
                map[i][j] = EMPTY; // Espacios vacíos
            }
        }
    }

    // Colocar enemigos de manera aleatoria
    srand(time(0));
    for (int i = 0; i < numEnemies; ++i) {
        int x, y;
        do {
            x = rand() % (size - 2) + 1;
            y = rand() % (size - 2) + 1;
        } while (map[x][y] != EMPTY);
        map[x][y] = ENEMY;
    }

    // Colocar el tesoro en una posición aleatoria
    int tx, ty;
    do {
        tx = rand() % (size - 2) + 1;
        ty = rand() % (size - 2) + 1;
    } while (map[tx][ty] != EMPTY);
    map[tx][ty] = TREASURE;
}

// Función para mostrar el mapa en la consola
void displayMap(const vector<vector<char>>& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Función para mover al jugador y manejar las colisiones con enemigos y el tesoro
void movePlayer(vector<vector<char>>& map, int& px, int& py, char move, int& health, bool& foundTreasure) {
    int newX = px, newY = py;

    if (move == 'W' || move == 'w') --newX;
    else if (move == 'S' || move == 's') ++newX;
    else if (move == 'A' || move == 'a') --newY;
    else if (move == 'D' || move == 'd') ++newY;

    if (map[newX][newY] == WALL) {
        cout << "¡Chocaste contra una pared!\n";
    } else if (map[newX][newY] == ENEMY) {
        cout << "¡Has encontrado un enemigo! Pierdes 10 de salud.\n";
        health -= 10;
        if (health <= 0) {
            cout << "¡Has perdido toda tu salud! Fin del juego.\n";
            exit(0);
        }
        map[px][py] = EMPTY;
        px = newX;
        py = newY;
        map[px][py] = PLAYER;
    } else if (map[newX][newY] == TREASURE) {
        cout << "¡Has encontrado el tesoro!\n";
        foundTreasure = true;
    } else {
        map[px][py] = EMPTY;
        px = newX;
        py = newY;
        map[px][py] = PLAYER;
    }
}

int main() {
    // Saludo personalizado
    string nombre;
    cout << "Ingrese su nombre: ";
    cin >> nombre;
    cout << "HOLA " << nombre << ", EL DÍA DE HOY VAMOS A JUGAR A MAZMORRAS.\n";
    cout << nombre << " TU TE PUEDES MOVER POR LA CUADRÍCULA CON LAS TECLAS:\n";
    cout << "W (para moverse hacia arriba)\n";
    cout << "A (para moverse hacia la izquierda)\n";
    cout << "S (para moverse hacia abajo)\n";
    cout << "D (para moverse hacia la derecha)\n";

    // Inicializar el primer mapa
    vector<vector<char>> map1(MAP_SIZE_1, vector<char>(MAP_SIZE_1));
    initializeMap(map1, MAP_SIZE_1, 10);  // 10 enemigos en el primer mapa

    int playerX = 1, playerY = 1;
    int health = 100;
    bool foundTreasure = false;

    map1[playerX][playerY] = PLAYER;

    // Juego en el primer mapa
    while (!foundTreasure) {
        displayMap(map1);
        cout << "Salud: " << health << endl;
        cout << "Mover (WASD): ";
        char move;
        cin >> move;
        movePlayer(map1, playerX, playerY, move, health, foundTreasure);
    }

    // Pasar al segundo mapa
    vector<vector<char>> map2(MAP_SIZE_2, vector<char>(MAP_SIZE_2));
    initializeMap(map2, MAP_SIZE_2, 20);  // 20 enemigos en el segundo mapa
    playerX = 1;
    playerY = 1;
    foundTreasure = false;

    map2[playerX][playerY] = PLAYER;
    cout << "¡Has pasado al segundo nivel!\n";

    // Juego en el segundo mapa
    while (!foundTreasure) {
        displayMap(map2);
        cout << "Salud: " << health << endl;
        cout << "Mover (WASD): ";
        char move;
        cin >> move;
        movePlayer(map2, playerX, playerY, move, health, foundTreasure);
    }

    cout << "¡Felicidades " << nombre << "! ¡Has ganado el juego!\n";
    return 0;
}
