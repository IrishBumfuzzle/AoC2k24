#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

int main()
{
    ifstream f;
    f.open("input.txt");
    string buffer;
    int safe = 0;

    while (getline(f, buffer))
    {
        
        istringstream s(buffer);
        
        int numbers[20];

        int i = 0;
        while ((s >> numbers[i]))
        {
            i++;
        }

        for (int k = -1; k < i; k++)
        {
            int safev = 1;
            int way = 0;
            for (int j = 1; j < i; j++)
            {
                if(j == k || (j == 1 && k == 0)) continue;

                int num = numbers[j];
                int num_prev = j == k+1 ? numbers[j - 2] : numbers[j-1];
                if (abs(num - num_prev) > 3 || abs(num - num_prev) < 1)
                {
                    safev = 0;
                    break;
                }
                if (way == 0)
                {
                    way = num > num_prev ? 1 : -1;
                }
                else if (way == 1)
                {
                    if (num < num_prev)
                    {
                        safev = 0;
                        break;
                    }
                }
                else
                {
                    if (num > num_prev)
                    {
                        safev = 0;
                        break;
                    }
                }
                num_prev = num;
            }

            if (safev)
            {
                safe++;
                break;
            }
        }
    }

    cout << safe;
}