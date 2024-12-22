#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <set>
#include <regex>
#include <queue>
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

    for (int i = 0; i < guardPositions.size(); i++)
    {
        guardPositions[i].first = (((guardPositions[i].first + guardVelocity[i].first * 100) % wide) + wide) % wide;
        guardPositions[i].second = (((guardPositions[i].second + guardVelocity[i].second * 100) % height) + height) % height;
    }

    int quadrants[4] = {0, 0, 0, 0};

    for (auto &i : guardPositions)
    {
        if (i.first < wide / 2)
        {
            if (i.second < height / 2)
                quadrants[0]++;
            else if (i.second > height / 2)
                quadrants[3]++;
        }
        else if (i.first > wide / 2)
        {
            if (i.second < height / 2)
                quadrants[1]++;
            else if (i.second > height / 2)
                quadrants[2]++;
        }
    }

    cout << quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3] << '\n';
}