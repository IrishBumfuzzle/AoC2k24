#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <set>
#include <regex>
#include <queue>
#include <numeric>
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
        price.push_back({price_x + 10000000000000, price_y + 10000000000000});
    }

    ll sum = 0;
    for (ll i = 0; i < price.size(); i++)
    {
        ll first = (price[i].second * button_b[i].first - button_b[i].second * price[i].first);
        ll second = (button_b[i].first * button_a[i].second - button_b[i].second * button_a[i].first);
        if (first % second != 0)
            continue;
        ll x = first / second;
        ll y = (price[i].first - button_a[i].first * x) / button_b[i].first;

        if (button_a[i].second * x + button_b[i].second * y == price[i].second && x > 0 && y > 0)
        {
            sum += x * 3 + y;
        }
    }

    cout << sum << endl;
}