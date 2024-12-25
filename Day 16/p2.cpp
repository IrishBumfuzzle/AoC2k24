#include <bits/stdc++.h>
#define ll long long int
using namespace std;
#define INF INT_MAX

enum Direction
{
    Up,
    Right,
    Down,
    Left
};

vector<string> grid;
pair<int, int> source, target;
set<pair<pair<int, int>, Direction>> optimalPath;
map<pair<pair<int, int>, Direction>, int> optimalGScore;

int heuristic(pair<int, int> curr, pair<int, int> end, Direction dir)
{
    int diff = 0;
    if (curr.first - end.first > 0)
        diff += abs(dir - Left);
    else if (curr.first - end.first < 0)
        diff += abs(dir - Right);
    if (diff == 3)
        diff = 1;

    if (curr.second - end.second > 0)
        diff += abs(dir - Up);
    else if (curr.second - end.second < 0)
        diff += abs(dir - Down);
    if (abs(dir - Up) == 3)
        diff -= 2;

    return abs(curr.first - end.first) + abs(curr.second - end.second) + 1000 * diff;
}

void aStar(int &optimalScore)
{
    map<pair<pair<int, int>, Direction>, int> gScore;
    map<pair<pair<int, int>, Direction>, int> fScore;
    set<pair<pair<int, pair<int, int>>, Direction>> nextSet;
    set<pair<pair<int, int>, Direction>> existsInSet;
    map<pair<pair<int, int>, Direction>, pair<pair<int, int>, Direction>> cameFrom;

    fScore[{source, Right}] = heuristic(source, target, Right);
    gScore[{source, Right}] = 0;
    existsInSet.insert({source, Right});
    nextSet.insert({{heuristic(source, target, Right), source}, Right});

    while (!nextSet.empty())
    {
        auto curr = (*nextSet.begin()).first.second;
        Direction dir = (*nextSet.begin()).second;
        int x = curr.first, y = curr.second;
        nextSet.erase(nextSet.begin());
        existsInSet.erase(existsInSet.find({curr, dir}));

        if (curr.first == target.first && curr.second == target.second)
        {
            int fScr = gScore[{curr, dir}];
            int op = 0;
            if (optimalScore == 0)
            {
                optimalScore = fScr;
                op = 1;
            }
            if (optimalScore != fScr)
                continue;

            while (cameFrom.find({curr, dir}) != cameFrom.end())
            {
                optimalPath.insert({curr, dir});
                Direction dir_new = cameFrom[{curr, dir}].second;
                curr = cameFrom[{curr, dir}].first;
                dir = dir_new;
            }
            for (auto &i : optimalPath)
                if (!optimalGScore.contains(i))
                    optimalGScore[i] = gScore[i];

            if (op)
                break;
            continue;
        }

        vector<pair<int, int>> neighbors;
        vector<Direction> directions;
        if (x > 0 && grid[x - 1][y] == '.')
            neighbors.push_back(pair<int, int>{x - 1, y}), directions.push_back(Up);
        if (x < grid.size() - 1 && grid[x + 1][y] == '.')
            neighbors.push_back(pair<int, int>{x + 1, y}), directions.push_back(Down);
        if (y > 0 && grid[x][y - 1] == '.')
            neighbors.push_back(pair<int, int>{x, y - 1}), directions.push_back(Left);
        if (y < grid[0].size() - 1 && grid[x][y + 1] == '.')
            neighbors.push_back(pair<int, int>{x, y + 1}), directions.push_back(Right);

        for (auto neighbor : neighbors)
        {
            Direction dirNeighbor = directions[find(neighbors.begin(), neighbors.end(), neighbor) - neighbors.begin()];
            int dirDiffernce = abs(dir - dirNeighbor);
            if (dirDiffernce == 3)
                dirDiffernce = 1;

            int newGScore = gScore[{curr, dir}] + 1 + 1000 * dirDiffernce;
            if (!gScore.contains({neighbor, dirNeighbor}))
                gScore[{neighbor, dirNeighbor}] = INF;
            if (newGScore < gScore[{neighbor, dirNeighbor}])
            {
                cameFrom[{neighbor, dirNeighbor}] = {curr, dir};
                gScore[{neighbor, dirNeighbor}] = newGScore;
                int oldFScore = fScore[{neighbor, dirNeighbor}];
                fScore[{neighbor, dirNeighbor}] = heuristic(neighbor, target, dirNeighbor) + newGScore;
                if (existsInSet.find({neighbor, dirNeighbor}) == existsInSet.end())
                    existsInSet.insert({neighbor, dirNeighbor});
                else
                    nextSet.erase(nextSet.find({{oldFScore, neighbor}, dirNeighbor}));

                nextSet.insert({{fScore[{neighbor, dirNeighbor}], neighbor}, dirNeighbor});
            }
            else if (optimalPath.contains({neighbor, dirNeighbor}) && newGScore == optimalGScore[{neighbor, dirNeighbor}])
            {
                while (cameFrom.find({curr, dir}) != cameFrom.end())
                {
                    optimalPath.insert({curr, dir});
                    Direction dir_new = cameFrom[{curr, dir}].second;
                    curr = cameFrom[{curr, dir}].first;
                    dir = dir_new;
                }

                for (auto &i : optimalPath)
                    if (!optimalGScore.contains(i))
                        optimalGScore[i] = gScore[i];

                // nextSet.insert({{fScore[{neighbor, dirNeighbor}], neighbor}, dirNeighbor});
            }
        }
    }
}

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;

    while (getline(f, buffer))
        grid.push_back(buffer);

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 'S')
                source.first = i, source.second = j;
            else if (grid[i][j] == '.' || grid[i][j] == 'E')
            {
                pair<int, int> curr;
                curr.first = i, curr.second = j;
                if (grid[i][j] == 'E')
                    target.first = i, target.second = j, grid[i][j] = '.';
            }
        }
    }

    int optimalScore = 0;
    int newScore = 0;
    aStar(optimalScore);

    while (optimalPath.size() != newScore)
    {
        newScore = optimalPath.size();
        aStar(optimalScore);
    }
    optimalPath.insert({source, Right});

    int unique = 0;
    for (auto &i : optimalPath)
        if (grid[i.first.first][i.first.second] != 'O')
        {
            grid[i.first.first][i.first.second] = 'O';
            unique++;
        }

    cout << unique;
}