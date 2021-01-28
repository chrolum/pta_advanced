#include <iostream>
using namespace std;

#define UP_TIME 6
#define DOWN_TIME 4
#define STOP_TIME 5

int getRunningTime(int currFloor, int targetFloor) {

    bool isUp = currFloor < targetFloor ? true : false;
    int movingTime, floor_num;
    if (isUp) {
        floor_num = targetFloor - currFloor;
        movingTime = floor_num * UP_TIME;
    }
    else {
        floor_num = currFloor - targetFloor;
        movingTime = floor_num * DOWN_TIME;
    }

    return STOP_TIME + movingTime;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int* req = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> req[i];
    }

    int totalTime = 0;

    totalTime += getRunningTime(0, req[0]);
    for (int i = 1; i < n; i++) {
        totalTime += getRunningTime(req[i-1], req[i]);
    }

    cout << totalTime;

    return 0;
}
