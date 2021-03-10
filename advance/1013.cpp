#include <iostream>
#include <set>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
#define CITY_MAX_NUM 2000

struct City
{
    set<int> neighour;
    /* data */
};

//TO-DO timeout in checkpoint 4
City map[CITY_MAX_NUM+1];
bool hasVisted[CITY_MAX_NUM];

void level_travel(int c, int check_city)
{
    if (hasVisted[c] || c == check_city)
        return;
    queue<int> q;
    q.push(c);

    int tmp_c;
    while (!q.empty())
    {
        tmp_c = q.front(); 
        hasVisted[tmp_c] = true;
        for (int n : map[tmp_c].neighour)
        {
            if (hasVisted[n] || n == check_city) // the check_city has been destroied
                continue;
            q.push(n);
        }
        q.pop();
    }
}

int main(int argc, char const *argv[])
{ 
    // ios::sync_with_stdio(false);
    int city_num, highways_num, check_num;
    cin >> city_num >> highways_num >> check_num;

    int c1, c2;
    for (int i = 0; i < highways_num; i++)
    {
        scanf("%d %d", &c1, &c2);
        map[c1].neighour.insert(c2);
        map[c2].neighour.insert(c1);
    }

    // broken the city
    int check_city;
    int cc_cnt = 0; // connected compent counter
    for (int i = 1; i <= check_num; i++)
    {
        scanf("%d", &check_city);
        // broken the road
        // find out all connected component
        cc_cnt = 0;
        for (int curr_idx = 1; curr_idx <= city_num; curr_idx++)
        {
            if (hasVisted[curr_idx] || curr_idx == check_city)
                continue;
            
            level_travel(curr_idx, check_city);
            cc_cnt++;
        }
        printf("%d\n", cc_cnt-1);

        memset(hasVisted, 0, sizeof(bool)*CITY_MAX_NUM);
    }
    
    return 0;

}