#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#include <queue>
#define ll long long int
using namespace std;

int ResultMaker(queue<ll> numbers, ll result)
{
    if (numbers.size() == 1)
        return result == numbers.front() ? 1 : 0;
    ll first = numbers.front();
    numbers.pop();
    if (first > result)
        return 0;

    numbers.front() *= first;
    int multiply = ResultMaker(numbers, result);
    if (multiply)
        return 1;
    numbers.front() /= first;

    numbers.front() += first;
    int add = ResultMaker(numbers, result);
    if (add)
        return 1;
    numbers.front() -= first;

    ostringstream new_num;
    new_num << first << numbers.front();
    numbers.front() = stoll(new_num.str());
    int combine = ResultMaker(numbers, result);

    return combine;
}

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;
    ll sum = 0;
    while (getline(f, buffer))
    {
        istringstream s(buffer);
        ll result, number;
        queue<ll> numbers;
        s >> result;
        char colon;
        s >> colon;
        while (s >> number)
        {
            numbers.push(number);
        }
        if (ResultMaker(numbers, result))
        {
            sum += result;
        }
    }

    cout << sum;
}