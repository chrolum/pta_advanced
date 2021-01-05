#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <stdio.h>
using namespace std;

void record(std::map<int, float> &record, string p)
{
    istringstream iss(p);
    double c;
    iss >> c; //skip the first number
    for (int ploy; iss >> ploy; )
    {
        iss >> c;
        record[ploy] += c;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    string p1, p2;
    map<int, float> ploy_record;
    while (getline(cin, p1) && getline(cin, p2))
    {
        ploy_record.clear();
        record(ploy_record, p1);
        record(ploy_record, p2);
        int num = ploy_record.size();
        int zero_num = 0;

        for (auto pair : ploy_record)
        {
            if (pair.second == 0)
            {
                zero_num++;
            }
        }

        cout << num - zero_num;
        for (auto pair = ploy_record.rbegin(); pair != ploy_record.rend(); pair++)
        {
            if (!pair->second)
                continue;
            cout << ' ' << pair->first;
            cout << ' ';
            printf("%.1f", pair->second);
            
        }
        cout << endl;
    }

    return 0;
}

