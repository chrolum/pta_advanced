#include <iostream>
using namespace std;


int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int* data = new int[n];
    bool areAllNagetive = true;
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        if (data[i] >= 0)
            areAllNagetive = false;
    }

    if (areAllNagetive) {
        cout << 0 << " " << data[0] << " " << data[n-1];
        return 0;
    }

    int* dp_sum = new int[n];
    int* begin_idxs = new int[n];
    int end_idx = 0, max_sum = data[0];

    dp_sum[0] = data[0];
    begin_idxs[0] = 0;

    for (int i = 1; i < n; i++) {
        if (dp_sum[i-1] + data[i] < data[i]) {
            dp_sum[i] = data[i];
            begin_idxs[i] = i;
        }
        else {
            dp_sum[i] = dp_sum[i-1] + data[i];
            begin_idxs[i] = begin_idxs[i-1];
        }

        if (max_sum < dp_sum[i]) {
            max_sum = dp_sum[i];
            end_idx = i;
        }
    }

    cout << max_sum;
    cout << " " << data[begin_idxs[end_idx]] << " " << data[end_idx];

    return 0;
}
