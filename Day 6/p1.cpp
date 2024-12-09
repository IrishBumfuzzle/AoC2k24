#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

int ObstacleInFront(vector<string> &grid, int row, int column, int dir)
{
    switch (dir)
    {
    case 0:
        row--;
        break;
    case 1:
        column++;
        break;
    case 2:
        row++;
        break;
    case 3:
        column--;
        break;
    default:
        break;
    }

    if (row < grid.size() && column < grid[row].size() && grid[row][column] == '#')
        return 1;
    return 0;
}

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;
    vector<string> grid;
    while (getline(f, buffer))
    {
        grid.push_back(buffer);
    }

    int row, column;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '^')
            {
                row = i;
                column = j;
                break;
            }
        }
    }

    int steps = 0;
    int dir = 0;
    while (row < grid.size() && column < grid[row].size())
    {
        if (ObstacleInFront(grid, row, column, dir))
        {
            dir = dir == 3 ? 0 : dir + 1;
        }
        else
        {
            if (grid[row][column] != 'X')
            {
                grid[row][column] = 'X';
                steps++;
            }
            switch (dir)
            {
            case 0:
                row--;
                break;
            case 1:
                column++;
                break;
            case 2:
                row++;
                break;
            case 3:
                column--;
                break;
            default:
                break;
            }
        }
    }

    cout << steps;
}
