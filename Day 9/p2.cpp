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

    vector<vector<int>> file_storage;
    int file_num = 0;
    for (int i = 0; i < buffer.size(); i++)
    {
        if (i % 2 != 0)
        {
            file_storage.push_back({-1, buffer[i] - '0'});
        }
        else
        {
            file_storage.push_back({file_num, buffer[i] - '0'});
            file_num++;
        }
    }

    for (int i = file_storage.size() - 1; i > 0; i--)
    {
        if (file_storage[i][0] != -1 && file_storage[i][0] < file_num)
        {
            for (int j = 1; j < i; j++)
            {
                if (file_storage[j][0] == -1 && file_storage[j][1] >= file_storage[i][1])
                {
                    file_storage[j][1] -= file_storage[i][1];
                    vector<int> temp = file_storage[i];
                    file_storage[i][0] = -1;
                    file_storage.insert(file_storage.begin() + j, temp);
                    break;
                }
            }
            file_num--;
        }
    }

    int counter = 0;
    for (int i = 0; i < file_storage.size(); i++)
    {
        if (file_storage[i][0] != -1)
        {
            for (int j = 0; j < file_storage[i][1]; j++)
            {
                sum += counter * file_storage[i][0];
                counter++;
            }
        }
        else
        {
            counter += file_storage[i][1];
        }
    }

    cout << sum;
}