#include <iostream>
#include <stdio.h>
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    int buy_records[3] = {0,0,0};
    char buy_record_output[3] = {'W', 'T', 'L'};

    float curr_odd, max_odd, curr_buy;
    float profit = 1.0;
    for (int game_idx=0; game_idx < 3; game_idx++)
    {
        max_odd = 0.0;
        curr_buy = 0;
        for (int res_idx=0; res_idx < 3; res_idx++)
        {
            cin >> curr_odd;
            if (max_odd < curr_odd)
            {
                max_odd = curr_odd;
                curr_buy = res_idx;
            }
        }
        profit *= max_odd;
        buy_records[game_idx] = curr_buy;
    }

    float output_profit = (profit * 0.65 - 1) * 2;

    for (int i = 0; i < 3; i++)
        cout << buy_record_output[buy_records[i]] << " ";

    printf("%.2f", output_profit);

    return 0;
}
