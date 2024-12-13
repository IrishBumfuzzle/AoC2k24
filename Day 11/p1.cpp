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
    ifstream f;
    f.open("input.txt");
    vector<ll> numbers;
    ll temp;
    while (f >> temp)
    {
        numbers.push_back(temp);
    }

    for (int ways = 0; ways < 25; ways++)
    {
        for (auto i = numbers.begin(); i != numbers.end(); i++)
        {
            ll number = *i;
            string numStr = to_string(number);
            if (number == 0)
            {
                *i = 1;
            }
            else if (numStr.length() % 2 == 0)
            {
                *i = stoll(numStr.substr(0, numStr.length() / 2));
                ll num2 = stoll(numStr.substr(numStr.length() / 2, numStr.length() / 2));
                i = numbers.insert(i + 1, num2);
            }
            else
            {
                *i *= 2024;
            }
        }
    }

    cout << numbers.size() << '\n';
}