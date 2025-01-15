#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <algorithm>
#include <ctime>


#define SIZE 4

using namespace std;



void Grid(vector<vector<int>>& grid) {
    grid = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));
}

void addRandomTile(vector<vector<int>>& grid) {
    vector<pair<int, int>> emptyTiles;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0) {
                emptyTiles.emplace_back(i, j);
            }
        }
    }

    if (!emptyTiles.empty()) {
        int randIndex = rand() % emptyTiles.size();
        int value = (rand() % 2 + 1) * 2;
        grid[emptyTiles[randIndex].first][emptyTiles[randIndex].second] = value;
    }
}

void printGrid(const vector<vector<int>>& grid) {
   // for (int i = 0; i < (SIZE*5); i++)          cout << char(216);
    cout<<endl;
    
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout <<" "<< cell <<" ";
        }
        cout << endl;
    }

    //for (int i = 0; i < (SIZE*5); i++)          cout << char(216);
    cout<<endl;
}

bool moveLeft(vector<vector<int>>& grid) {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        vector<int> newRow(SIZE, 0);
        int idx = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] != 0) {
                if (newRow[idx] == grid[i][j]) {
                    newRow[idx] *= 2;
                    idx++;
                } else if (newRow[idx] == 0) {
                    newRow[idx] = grid[i][j];
                } else {
                    idx++;
                    newRow[idx] = grid[i][j];
                }
            }
        }
        if (grid[i] != newRow) {
            grid[i] = newRow;
            moved = true;
        }
    }
    return moved;
}

bool moveRight(vector<vector<int>>& grid) {
    // Flip the grid horizontally, move left, then flip back.
    for (int i = 0; i < SIZE; ++i) {
        reverse(grid[i].begin(), grid[i].end());
    }
    bool moved = moveLeft(grid);
    for (int i = 0; i < SIZE; ++i) {
        reverse(grid[i].begin(), grid[i].end());
    }
    return moved;
}

bool moveUp(vector<vector<int>>& grid) {
    // Transpose the grid, move left, then transpose back.
    vector<vector<int>> transposed(SIZE, vector<int>(SIZE, 0));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            transposed[i][j] = grid[j][i];
        }
    }
    bool moved = moveLeft(transposed);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grid[j][i] = transposed[i][j];
        }
    }
    return moved;
}

bool moveDown(vector<vector<int>>& grid) {
    // Transpose the grid, move right, then transpose back.
    vector<vector<int>> transposed(SIZE, vector<int>(SIZE, 0));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            transposed[i][j] = grid[j][i];
        }
    }
    bool moved = moveRight(transposed);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grid[j][i] = transposed[i][j];
        }
    }
    return moved;
}

bool isGameOver(const vector<vector<int>>& grid) {
    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0) {
                return false;
            }
            if (i > 0 && grid[i][j] == grid[i-1][j]) return false;
            if (j > 0 && grid[i][j] == grid[i][j-1]) return false;
        }
    }

    return true;
}











int main() {
    int score = 0;
    srand(static_cast<unsigned>(time(0)));
    vector<vector<int>> grid;
    Grid(grid);
    addRandomTile(grid);
    addRandomTile(grid);

    while (true) {
        system("cls");
        printGrid(grid);

        if (isGameOver(grid)) {    
            for (int i = 0;i<SIZE;++i){
                for( int j = 0;j<SIZE;++j){
            score += grid[i][j];
                }
            }
            cout << "Game Over!" << endl <<"Score : " << score;
            break;
        }

        char move;
        cout << "Enter move (w/a/s/d): ";
        cin >> move;

        bool moved = false;
        switch (move) {
            case 'w': moved = moveUp(grid); break;
            case 'a': moved = moveLeft(grid); break;
            case 's': moved = moveDown(grid); break;
            case 'd': moved = moveRight(grid); break;
            default: cout << "Invalid move!" << endl; continue;
        }

        if (moved) {
            addRandomTile(grid);
        }
    }

    return 0;
}
