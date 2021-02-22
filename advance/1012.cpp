#include <iostream>
#include <unordered_map>
#define MAX_NUM 2000
using namespace std;
//NOTE: rank start from 0
enum class CourseType {C, M, E, A};

struct Student
{
    int C;
    int M;
    int E;
    int A;
    int rank_c;
    int rank_m;
    int rank_e;
    int rank_a;
};

unordered_map<int, Student> student_record;

//bubblesort
void add_bubble_to_end(Student* rank_list[], int end_idx, Student *s1, CourseType c_t)
{
    if (end_idx >= MAX_NUM)
        return;


    int* p_rank = &(s1->C);
    int offset_grade = 0;

    switch (c_t)
    {
    case CourseType::C:
        offset_grade = 0;
        break;
    case CourseType::M:
        offset_grade = 1*sizeof(int);
        break;
    case CourseType::E:
        offset_grade = 2*sizeof(int);
        break;
    case CourseType::A:
        offset_grade = 3*sizeof(int);
        break;
    default:
        break;
    }

    int curr_grade = *(p_rank + offset_grade);
    p_rank += offset_grade + 4*sizeof(int);

    *p_rank = end_idx; //init rank to the end of array
    rank_list[end_idx] = s1;//add element

    if (end_idx == 0)
        return;

    
    //buddle sort
    int curr_idx = end_idx;
    int *p_pre_rank, *p_pre_grade;
    Student* p_pre_s;
    while (curr_idx >= 1)
    {
        p_pre_s = rank_list[curr_idx-1];
        p_pre_grade = &(p_pre_s->C) + offset_grade;
        p_pre_rank = p_pre_grade + 4*sizeof(int);

        if (curr_grade >= *p_pre_grade)
            return;

        if (curr_grade < *p_pre_grade)
        {
            //swap two student position
            rank_list[curr_idx] = p_pre_s;
            rank_list[curr_idx-1] = s1;
            //update rank
            (*p_pre_rank)++;
            (*p_rank) = curr_idx-1;
        }
        curr_idx--;
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
        cin >> s->C >> s->M >> s->E;
        s->A = (s->C + s->E + s->M) / 3;
        student_record[student_id] = *s;
        add_bubble_to_end(rank_c, i, s, CourseType::C);
        add_bubble_to_end(rank_m, i, s, CourseType::M);
        add_bubble_to_end(rank_e, i, s, CourseType::E);
        add_bubble_to_end(rank_a, i, s, CourseType::A);
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
        CourseType output_c = CourseType::A;
        // A > C > M > E
        int tmp_rank = output_s.rank_a;
        if (tmp_rank > output_s.rank_c)
        {
            output_c = CourseType::C;
            tmp_rank = output_s.rank_c;
        }

        if (tmp_rank > output_s.rank_m)
        {
            output_c = CourseType::M;
            tmp_rank = output_s.rank_m;
        }
        
        if (tmp_rank > output_s.rank_e)
        {
            output_c = CourseType::E;
            tmp_rank = output_s.rank_e;
        }

        cout << tmp_rank + 1 << " " << output_str[int(output_c)] << endl;
    }
    return 0;
}
