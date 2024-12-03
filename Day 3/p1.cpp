#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <regex>
#define ll long long int
using namespace std;

int main(){
    ifstream f;
    f.open("input.txt");
    string buffer;
    regex e("mul\\((\\d+),(\\d+)\\)");
    smatch m;
    long long int sum = 0;

    while(getline(f, buffer)){
        for(auto i = sregex_iterator(buffer.begin(), buffer.end(), e); i != sregex_iterator(); i++){
            sum += stoi((*i)[1].str()) * stoi((*i)[2].str());
        }
    }
    cout << sum;
}