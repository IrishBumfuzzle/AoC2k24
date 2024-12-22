#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main()
{
    FILE *f = fopen64("input.txt", "r");
    ll pos_x, pos_y, vel_x, vel_y;
    vector<pair<ll, ll>> guardPositions, guardVelocity;
    while (fscanf(f, " p=%lld,%lld v=%lld,%lld", &pos_x, &pos_y, &vel_x, &vel_y) != EOF)
    {
        guardPositions.push_back({pos_x, pos_y});
        guardVelocity.push_back({vel_x, vel_y});
    }

    int wide = 101;
    int height = 103;

    for (int j = 0;; j++)
    {
        char grid[wide][height];
        memset(grid, ' ', wide * height);
        int same{0};
        for (int i = 0; i < guardPositions.size(); i++)
        {
            guardPositions[i].first = (((guardPositions[i].first + guardVelocity[i].first * 1) % wide) + wide) % wide;
            guardPositions[i].second = (((guardPositions[i].second + guardVelocity[i].second * 1) % height) + height) % height;
            if (grid[guardPositions[i].first][guardPositions[i].second] == '.')
                same = 1;
            else
                grid[guardPositions[i].first][guardPositions[i].second] = '.';
        }
        if (!same)
        {
            cout << j + 1;
            break;
        }
    }
}