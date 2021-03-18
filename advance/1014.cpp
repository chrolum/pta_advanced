#include <iostream>
#include <queue>
#include <unordered_map>
#include <stdio.h>

#define END_HOUR 17
#define RUNNING_TIME (17-8)*60
#define BEGIN_HOUR 8
using namespace std;

unordered_map<int, int> end_time_record; //-1 mean sorry

struct Customer
{
	int id;
	int job_time;
	Customer(int n, int j) { id = n; job_time = j; }
};

struct Window
{
	queue<Customer*> q;
	int curr_time = 0;
	int id = 0;
};

auto cmp = [](Window* q1, Window* q2)
{
	if ((q1->q.front()->job_time + q1->curr_time) == (q2->q.front()->job_time + q2->curr_time))
	{
		return q1->id > q2->id;
	}
	return (q1->q.front()->job_time + q1->curr_time) > (q2->q.front()->job_time + q2->curr_time);
};

priority_queue<Window*, std::vector<Window*>, decltype(cmp)> next_free_window(cmp);
vector<Window*> all_windows;

int num_win, num_wait_capacity, num_customers, num_queries;

void print_end_time(int q_idx)
{
	if (end_time_record[q_idx] == -1)
	{
		cout << "Sorry" << endl;
		return;
	}

	int total_time_by_min = end_time_record[q_idx];
	int hour = total_time_by_min / 60 + BEGIN_HOUR;
	int min = total_time_by_min % 60;

	//if (total_time_by_min >= (RUNNING_TIME + 59))
	//	printf("17:59\n");

	printf("%.2d:%.2d\n", hour, min);
}

int main(int argc, char const* argv[])
{
	cin >> num_win >> num_wait_capacity >> num_customers >> num_queries;

	all_windows.resize(num_win);
	for (int i = 1; i <= num_win; i++)
	{
		all_windows[i-1] = new Window();
		all_windows[i-1]->id = i;
	}

	int job_time;
	// while the waitting area is not full, just pull custumer in window idx order
	//inital the priority_queue
	int customer_cnt = 1;
	for (int win_idx = 1; customer_cnt <= num_customers && win_idx <= num_win; win_idx++, customer_cnt++)
	{
		cin >> job_time;
		Customer* c = new Customer(customer_cnt, job_time);
		Window* curr_win = all_windows[win_idx - 1];
		curr_win->q.push(c);
		next_free_window.push(curr_win);
	}

	// all window has one customer, not need to update the priority_queue
	for (; customer_cnt <= num_win * num_wait_capacity
		&& customer_cnt <= num_customers; customer_cnt++)
	{
		cin >> job_time;
		Customer* c = new Customer(customer_cnt, job_time);
		int win_idx = (customer_cnt - 1) % num_win;
		all_windows[win_idx]->q.push(c);
	}

	// waiting area is full, should pop the min job finish time queue and add new customer
	// if all customer has been waiting, the loop will skip
	for (; customer_cnt <= num_customers; customer_cnt++)
	{
		cin >> job_time;
		Customer* c = new Customer(customer_cnt, job_time);
		Window* w = next_free_window.top();
		// the first customer has finish his jobs
		int end_time = w->q.front()->job_time + w->curr_time;
		int curr_time = w->curr_time;
		int curr_customer_idx = w->q.front()->id;

		if (curr_time > RUNNING_TIME)
		{
			end_time_record[curr_customer_idx] = -1;
			w->curr_time = RUNNING_TIME;
		}
		else
		{
			end_time_record[curr_customer_idx] = end_time;
			next_free_window.pop();
			w->curr_time = end_time;
			w->q.pop();
			w->q.push(c);
			next_free_window.push(w);
		}
	}

	// process waiting area customer
	for (int i = 0; i < num_win; i++)
	{
		auto wq = all_windows[i];
		int curr_time = wq->curr_time;
		auto& q = wq->q;

		while (!q.empty())
		{
			if (curr_time >= RUNNING_TIME)
				curr_time = -1;

			if (curr_time != -1)
				curr_time += q.front()->job_time;

			end_time_record[q.front()->id] = curr_time;
			q.pop();
		}

	}

	//queue
	int queue_idx;
	for (int i = 1; i <= num_queries; i++)
	{
		cin >> queue_idx;
		print_end_time(queue_idx);
	}

	return 0;
}
