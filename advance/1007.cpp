#include <iostream>
#include <queue>
using namespace std;

int getSum(const int a[], int begin_idx, int end_idx) {
    int sum = 0;
    for (int i = begin_idx; i <= end_idx; i++) {
        sum += a[i];
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int* data = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    int win_left = 0, win_right = 0;

    int win_size = n, max_sum = 0;
    bool areAllNagetive = false;
    while (win_size >= 0) {
        int begin_idx = 0, tmp_sum;
        while (begin_idx + win_size < n) {
            tmp_sum = getSum(data, begin_idx, begin_idx + win_size);
            if (tmp_sum > max_sum) {
                max_sum = tmp_sum;
                win_left = begin_idx;
                win_right = begin_idx + win_size;
            }
            begin_idx++;
        }
        win_size--;
    }

    cout << max_sum;
    cout << " " << data[win_left] << " " << data[win_right];

    return 0;
}
