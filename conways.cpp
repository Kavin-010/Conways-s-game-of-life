#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_COMMAND "cls"
#else
#include <unistd.h>
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

const int GAME_WIDTH = 30;
const int GAME_HEIGHT = 15;

bool isAlive(array<array<int, GAME_HEIGHT>, GAME_WIDTH>& game, const int x, const int y)
{
    int alive = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < GAME_WIDTH && ny >= 0 && ny < GAME_HEIGHT)
                alive += game[nx][ny];
        }
    }

    if (game[x][y] == 1 && alive < 2) return false;
    if (game[x][y] == 1 && (alive == 2 || alive == 3)) return true;
    if (game[x][y] == 1 && alive > 3) return false;
    if (game[x][y] == 0 && alive == 3) return true;

    return false;
}

void printGrid(const array<array<int, GAME_HEIGHT>, GAME_WIDTH>& grid, int generation)
{
    system(CLEAR_COMMAND);
    cout << "Conway's Game of Life | Generation: " << generation << "\n";

    // Top border
    cout << "+";
    for (int i = 0; i < GAME_WIDTH; ++i) cout << "-";
    cout << "+\n";

    for (int y = 0; y < GAME_HEIGHT; ++y)
    {
        cout << "|";
        for (int x = 0; x < GAME_WIDTH; ++x)
        {
            cout << (grid[x][y] ? '#' : ' ');
        }
        cout << "|\n";
    }

    // Bottom border
    cout << "+";
    for (int i = 0; i < GAME_WIDTH; ++i) cout << "-";
    cout << "+\n";
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    array<array<int, GAME_HEIGHT>, GAME_WIDTH> display {};
    array<array<int, GAME_HEIGHT>, GAME_WIDTH> swap {};

    for (auto& row : display)
        generate(row.begin(), row.end(), []() { return rand() % 6 == 0 ? 1 : 0; });

    int generation = 0;

    while (true)
    {
        for (int i = 0; i < GAME_WIDTH; ++i)
        {
            for (int k = 0; k < GAME_HEIGHT; ++k)
            {
                swap[i][k] = isAlive(display, i, k) ? 1 : 0;
            }
        }

        generation++;
        printGrid(swap, generation);
        display = swap;
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    return 0;
}
