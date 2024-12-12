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

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;
    getline(f, buffer);
    ll sum = 0;

    vector<int> file_storage;
    int file_num = 0;
    for (int i = 0; i < buffer.size(); i++)
    {
        if (i % 2 != 0)
        {
            for (int j = 0; j < buffer[i] - '0'; j++)
                file_storage.push_back(-1);
        }
        else
        {
            for (int j = 0; j < buffer[i] - '0'; j++)
                file_storage.push_back(file_num);
            file_num++;
        }
    }

    int begin = 0;
    int end = file_storage.size() - 1;
    while (begin != end)
    {
        if (file_storage[begin] != -1)
        {
            begin++;
            continue;
        }
        if (file_storage[end] == -1)
        {
            end--;
            continue;
        }
        file_storage[begin] = file_storage[end];
        begin++;
        end--;
    }

    for (int i = 0; i < end + 1; i++)
    {
        if (file_storage[i] == -1)
            break;
        sum += i * file_storage[i];
    }

    cout << sum;
}