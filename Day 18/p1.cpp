#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main()
{
    const int gridSize = 71;
    const int bytesToSimulate = 1024;
    FILE *f = fopen64("input.txt", "r");
    int xf, yf;

    char grid[gridSize][gridSize];
    memset(grid, '.', gridSize * gridSize);
    map<pair<int, int>, int> distance;
    map<pair<int, int>, pair<int, int>> cameFrom;
    set<pair<int, pair<int, int>>> q;
    map<pair<int, int>, bool> qContains;

    int bytesCounter = 0;
    while (fscanf(f, "%d,%d", &xf, &yf) != EOF && bytesCounter < bytesToSimulate)
    {
        grid[yf][xf] = '#';
        bytesCounter++;
    }
    for (int i = 0; i < gridSize; i++)
        for (int j = 0; j < gridSize; j++)
            if (i == 0 && j == 0)
                distance[{i, j}] = 0, q.insert({0, {i, j}}), qContains.insert({{i, j}, true});
            else if (grid[i][j] != '#')
                distance[{i, j}] = INT32_MAX, q.insert({INT_MAX, {i, j}}), qContains.insert({{i, j}, true});

    pair<int, int> begin = {0, 0};
    pair<int, int> end = {gridSize - 1, gridSize - 1};

    while (q.size())
    {
        int dist = (*q.begin()).first;
        pair<int, int> node = (*q.begin()).second;
        q.erase({dist, node});
        qContains[node] = false;
        int y = node.first, x = node.second;

        if (y == end.first && x == end.second)
        {
            cout << distance[node] << '\n';
        }

        vector<pair<int, int>> neighbors;
        if (x > 0 && grid[y][x - 1] == '.')
            neighbors.push_back({y, x - 1});
        if (x < gridSize - 1 && grid[y][x + 1] == '.')
            neighbors.push_back({y, x + 1});
        if (y > 0 && grid[y - 1][x] == '.')
            neighbors.push_back({y - 1, x});
        if (y < gridSize - 1 && grid[y + 1][x] == '.')
            neighbors.push_back({y + 1, x});

        for (auto neighbor : neighbors)
        {
            int newDist = distance[node] + 1;
            if (newDist < distance[neighbor])
            {
                int oldDist = distance[neighbor];
                if (qContains[neighbor])
                    q.erase(q.find({oldDist, neighbor}));

                distance[neighbor] = newDist;
                q.insert({newDist, neighbor});
                cameFrom[neighbor] = node;
            }
        }
    }
}