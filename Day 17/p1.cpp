#include <bits/stdc++.h>
using namespace std;
#define ll long long int

int main()
{
    FILE *f = fopen64("input.txt", "r");

    ll registers[7] = {0, 1, 2, 3};
    vector<int> program;

    char programLine[100];
    fscanf(f, "Register A: %lld", &registers[4]);
    fscanf(f, " Register B: %lld", &registers[5]);
    fscanf(f, " Register C: %lld", &registers[6]);
    fscanf(f, " Program: %s", programLine);

    for (int i = 0; i < strlen(programLine); i++)
        if (programLine[i] != ',')
            program.push_back(programLine[i] - '0');

    for (int i = 0; i < program.size();)
    {
        switch (program[i])
        {
        case 0:
            registers[4] = registers[4] / pow(2, registers[program[i + 1]]);
            i += 2;
            break;
        case 1:
            registers[5] = registers[5] ^ program[i + 1];
            i += 2;
            break;
        case 2:
            registers[5] = registers[program[i + 1]] % 8;
            i += 2;
            break;
        case 3:
            if (registers[4] != 0)
                i = program[i + 1];
            else
                i += 2;
            break;
        case 4:
            registers[5] = registers[5] ^ registers[6];
            i += 2;
            break;
        case 5:
            cout << registers[program[i + 1]] % 8 << ',';
            i += 2;
            break;
        case 6:
            registers[5] = registers[4] / pow(2, registers[program[i + 1]]);
            i += 2;
            break;
        case 7:
            registers[6] = registers[4] / pow(2, registers[program[i + 1]]);
            i += 2;
            break;

        default:
            break;
        }
    }

    cout << "\b \b\n";
}