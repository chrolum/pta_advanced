#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;

class CityInfo
{
public:
    int** road;
    int* rescue_team;
    int city_num = 0;
    int road_num = 0;
    int c1 = 0, c2 = 0;
    int shortest__num = 0, max_rescue = 0;
public:
    int* distTo;
    vector<int>* pre_city;
    bool* hasVisited;
    priority_queue<pair<int, int>> pq;//pair<vex, weight>
public:
    CityInfo()
    {
        cin >> city_num >> road_num >> c1 >> c2;
        rescue_team = new int[city_num];
        distTo = new int[city_num];
        // init the distTo array for dfs
        road = new int*[city_num];
        hasVisited = new bool[city_num];
        for (int i = 0; i < city_num; i++)
        {
            distTo[i] = INT32_MAX;
            cin >> rescue_team[i];
            pre_city = new vector<int>[city_num];
            road[i] = new int[city_num];
            hasVisited[i] = false;
        }
        distTo[c1] = 0;

        int c1_tmp, c2_tmp, w;
        for (int i = 0; i < road_num; i++)
        {
            cin >> c1_tmp >> c2_tmp >> w;
            road[c1_tmp][c2_tmp] = w;
            road[c2_tmp][c1_tmp] = w;
        }
    }

    void print_res()
    {
        cout << shortest__num << ' ' << max_rescue << endl;
    }

    void dijstra()
    {
        
    }

private:
    void relax(int v)
    {
        for (int i = 0; i < city_num; i++)
        {
            if (road[v][i] == 0)//not road here
                continue;
            if (distTo[i] > distTo[v] + road[v][i])
            {
                distTo[i] = distTo[v] + road[v][i];
                pre_city[i].push_back(v);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    CityInfo cities = CityInfo();
    cities.print_res();
    
    return 0;
}
