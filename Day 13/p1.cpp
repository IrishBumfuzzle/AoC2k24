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

ll sorts(ll a, ll b)
{
    return a < b;
}

int main()
{
    FILE *f = fopen64("input.txt", "r");

    ll a_x, a_y, b_x, b_y, price_x, price_y;
    vector<pair<ll, ll>> button_a, button_b, price;
    while (fscanf(f, " Button A: X+%lld, Y+%lld", &a_x, &a_y) != EOF)
    {
        fscanf(f, " Button B: X+%lld, Y+%lld", &b_x, &b_y);
        fscanf(f, " Prize: X=%lld, Y=%lld", &price_x, &price_y);
        button_a.push_back({a_x, a_y});
        button_b.push_back({b_x, b_y});
        price.push_back({price_x, price_y});
    }

    ll sum = 0;
    for (ll i = 0; i < price.size(); i++)
    {
        vector<ll> allSums;
        for (ll j = 0;; j++)
        {
            if ((price[i].first - j * button_a[i].first) < 0 || (price[i].second - j * button_a[i].second) < 0)
                break;
            if (((price[i].first - j * button_a[i].first) % button_b[i].first == 0) && ((price[i].second - j * button_a[i].second) % button_b[i].second == 0))
            {
                ll b_times = (price[i].first - j * button_a[i].first) / button_b[i].first;
                if (button_a[i].first * j + b_times * button_b[i].first == price[i].first && button_a[i].second * j + b_times * button_b[i].second == price[i].second)
                    allSums.push_back((j * 3) + (b_times));
            }
        }
        if (allSums.size())
        {
            sort(allSums.begin(), allSums.end(), sorts);
            sum += allSums[0];
        }
    }

    cout << sum << endl;
}