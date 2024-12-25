#include <bits/stdc++.h>
#define ll long long int
using namespace std;
#define INF INT_MAX

vector<string> grid;
enum Direction
{
    Up,
    Right,
    Down,
    Left
};

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

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;

    while (getline(f, buffer))
        grid.push_back(buffer);

    pair<int, int> source, end;
    vector<vector<bool>> nodeVisited;
    map<pair<pair<int, int>, Direction>, int> gScore;
    map<pair<pair<int, int>, Direction>, int> fScore;
    for (int i = 0; i < grid.size(); i++)
    {
        vector<bool> nodes;
        for (int j = 0; j < grid[0].size(); j++)
        {

            if (grid[i][j] == 'S')
                source.first = i, source.second = j, gScore[{source, Right}] = 0;
            else if (grid[i][j] == '.' || grid[i][j] == 'E')
            {
                pair<int, int> curr;
                curr.first = i, curr.second = j;
                if (grid[i][j] == 'E')
                    end.first = i, end.second = j, grid[i][j] = '.';
            }

            nodes.push_back(false);
        }
        nodeVisited.push_back(nodes);
    }
    fScore[{source, Right}] = heuristic(source, end, Right);

    set<pair<pair<int, pair<int, int>>, Direction>> nextSet;
    set<pair<pair<int, int>, Direction>> existsInSet;
    map<pair<pair<int, int>, Direction>, pair<pair<int, int>, Direction>> cameFrom;
    nextSet.insert({{heuristic(source, end, Right), source}, Right});
    existsInSet.insert({source, Right});

    while (!nextSet.empty())
    {
        auto curr = (*nextSet.begin()).first.second;
        Direction dir = (*nextSet.begin()).second;
        int x = curr.first, y = curr.second;
        nextSet.erase(nextSet.begin());
        existsInSet.erase(existsInSet.find({curr, dir}));

        if (curr.first == end.first && curr.second == end.second)
        {
            int fScr = gScore[{curr, dir}];
            cout << fScr;
            break;
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
                fScore[{neighbor, dirNeighbor}] = heuristic(neighbor, end, dirNeighbor) + newGScore;
                if (existsInSet.find({neighbor, dirNeighbor}) == existsInSet.end())
                    existsInSet.insert({neighbor, dirNeighbor});
                else
                    nextSet.erase(nextSet.find({{oldFScore, neighbor}, dirNeighbor}));

                nextSet.insert({{fScore[{neighbor, dirNeighbor}], neighbor}, dirNeighbor});
            }
        }
    }
}