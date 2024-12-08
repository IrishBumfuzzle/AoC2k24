#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

vector<int> StartNumbers;
vector<int> EndNumbers;

int correction(vector<int> &numbers){
        int correct = 1;

        for (int i = numbers.size() - 2; i >= 0; i--)
        {
            int break1 = 0;
            vector<int> prev_numbers;

            for (int j = 0; j < EndNumbers.size(); j++)
            {
                if (StartNumbers[j] == numbers[i])
                {
                    prev_numbers.push_back(EndNumbers[j]);
                }
            }

            for (int j = i + 1; j < numbers.size(); j++)
            {
                int found = 0;

                for (auto &k : prev_numbers)
                {
                    if (k == numbers[j])
                        found = 1;
                }
                if (!found)
                {
                    break1 = 1;
                    break;
                }
            }

            if (break1)
            {
                int temp = numbers[i];
                numbers[i] = numbers[i+1];
                numbers[i+1] = temp;
                correction(numbers);
                return 1;
            }
        }
        return 0;
 
}

int main()
{
    ifstream f;
    f.open("input.txt");

    string buffer;

    while (getline(f, buffer) && buffer != "")
    {
        StartNumbers.push_back((buffer[0] - '0') * 10 + buffer[1] - '0');
        EndNumbers.push_back((buffer[3] - '0') * 10 + buffer[4] - '0');
    }

    int sum = 0;

    while (getline(f, buffer))
    {
        vector<int> numbers;
        for (int i = 0; i < buffer.length(); i += 3)
        {
            numbers.push_back((buffer[i] - '0') * 10 + buffer[i + 1] - '0');
        }
        if(correction(numbers)){
            sum += numbers[numbers.size()/2];
        }
    }

    cout << sum;
}