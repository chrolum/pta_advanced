#include <iostream>
#include <unordered_map>
#define MAX_NUM 2000
#define C 0
#define M 1
#define E 2
#define A 3
using namespace std;

struct Student
{
    int grade[4];
    int rank[4];
};

unordered_map<int, Student> student_record;

//bubblesort
void add_bubble_to_end(Student* rank_list[], int end_idx, Student *s1, int course_type)
{
    if (end_idx >= MAX_NUM)
        return;

    //inital student rank and update rank list
    s1->rank[course_type] = end_idx;
    rank_list[end_idx] = s1;
    int curr_idx = end_idx;

    if (curr_idx == 0)
        return; //not need to bubble up

    //bubble sort

    int pre_grade;
    const int curr_grade = s1->grade[course_type];
    int last_grade = curr_grade;
    int same_cnt = 0;
    while (curr_idx >= 1)
    {
        pre_grade = rank_list[curr_idx-1]->grade[course_type];
        
        if (curr_grade < pre_grade) //swap two student and update their rank
        {
            //update the older record
            rank_list[curr_idx] = rank_list[curr_idx-1];
            rank_list[curr_idx]->rank[course_type] = curr_idx;

            //update the new student record
            --curr_idx;
            rank_list[curr_idx] = s1;
            s1->rank[course_type] = curr_idx;
            continue;
        }

        if (curr_grade == pre_grade)
        {
            s1->rank[course_type] = rank_list[curr_idx-1]->rank[course_type];
            return; //just copy the front student rank
        }

        if (curr_grade > pre_grade)
            return; // the rank infomation has been initaled
    }

    

}

Student* rank_c[2000];
Student* rank_m[2000];
Student* rank_e[2000];
Student* rank_a[2000];

int main(int argc, char const *argv[])
{
    int record_num, query_num;
    cin >> record_num >> query_num;

    //update rank list
    int student_id;
    char output_str[] = {'C', 'M', 'E', 'A'};
    for(int i = 0; i < record_num; i++)
    {
        cin >> student_id;
        Student* s = new Student();
        cin >> s->grade[C] >> s->grade[M] >> s->grade[E];
        s->grade[A] = (s->grade[C] + s->grade[M] + s->grade[E]) / 3;
        student_record[student_id] = *s;
        add_bubble_to_end(rank_c, i, s, C);
        add_bubble_to_end(rank_m, i, s, M);
        add_bubble_to_end(rank_e, i, s, E);
        add_bubble_to_end(rank_a, i, s, A);
    }
    
    //query
    Student output_s;
    for (int j = 0; j < query_num; j++)
    {
        cin >> student_id;
        
        if (student_record.count(student_id) == 0)
        {
            cout << "N/A" << endl;
            continue;
        }

        output_s = student_record[student_id];
        // A > C > M > E


        // cout << student_id << " " << output_s.rank_a << " " << output_s.A << endl;

        // cout << tmp_rank + 1 << " " << output_str[int(output_c)] << endl;
    }
    return 0;
}
