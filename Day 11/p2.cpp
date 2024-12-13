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
    map<ll, ll> numbers;
    ll temp;
    while (f >> temp)
    {
        numbers.insert({temp, 1});
    }
    numbers.insert({1, 0});

    for (int count = 0; count < 75; count++)
    {
        map<ll, ll> toBeInserted;
        toBeInserted.insert({1, 0});
        for (auto &i : numbers)
        {
            if (i.first == 0)
            {
                toBeInserted[1] += i.second;
                i.second = 0;
            }
            else if (to_string(i.first).length() % 2 == 0)
            {
                string numStr = to_string(i.first);
                ll num1 = stoll(numStr.substr(0, numStr.length() / 2));
                ll num2 = stoll(numStr.substr(numStr.length() / 2));
                ll occurs = i.second;
                i.second = 0;
                if (toBeInserted.contains(num1))
                {
                    toBeInserted[num1] += occurs;
                }
                else
                {
                    toBeInserted[num1] = occurs;
                }
                if (toBeInserted.contains(num2))
                {
                    toBeInserted[num2] += occurs;
                }
                else
                {
                    toBeInserted[num2] = occurs;
                }
            }
            else
            {
                if (toBeInserted.contains(i.first * 2024))
                    toBeInserted[i.first * 2024] += i.second;
                else
                    toBeInserted[i.first * 2024] = i.second;
                i.second = 0;
            }
        }

        for (auto &i : toBeInserted)
        {
            if (numbers.contains(i.first))
                numbers[i.first] += i.second;
            else
                numbers[i.first] = i.second;
        }
    }

    ll sum = 0;
    for (auto &i : numbers)
    {
        sum += i.second;
    }
    cout << sum;
}