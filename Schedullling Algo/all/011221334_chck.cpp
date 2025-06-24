#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int remaining_time;
    int priority;

    Process(int id, int arr, int bur, int pri)
    {
        process_id = id;
        arrival_time = arr;
        burst_time = bur;
        priority = pri;
        remaining_time = burst_time;
        waiting_time = turnaround_time = completion_time = -1;
    }
};

void sjf_preemptive(vector<Process> processes)
{

    ofstream outfile("sjf_output.txt");

    int n = processes.size();
    int current_time = 0;
    int completed = 0;

    // auto cmp = [&](const Process &a, const Process &b)
    // {
    //     return a.remaining_time > b.remaining_time ||
    //            (a.remaining_time == b.remaining_time && a.arrival_time > b.arrival_time);
    // };

    auto cmp = [](Process *a, Process *b)
    {
        // যদি দুইটার remaining_time সমান হয়, তাহলে যেটার arrival_time আগে সে আগে
        if (a->remaining_time == b->remaining_time)
            return a->arrival_time > b->arrival_time;
        return a->remaining_time > b->remaining_time;
    };

    // pq
    priority_queue<Process *, vector<Process *>, decltype(cmp)> pq(cmp);
    vector<bool> inQueue(n, false); // কোন process queue-তে already আছে কিনা

    while (completed < n)
    {

        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                pq.push(&processes[i]);
                inQueue[i] = true;
            }
        }

        if (pq.empty())
        {

            current_time++;
            continue;
        }

        Process *current = pq.top();
        pq.pop();

        current->remaining_time--;
        current_time++;

        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                pq.push(&processes[i]);
                inQueue[i] = true;
            }
        }

        if (current->remaining_time > 0)
        {
            pq.push(current);
        }
        else
        {

            current->completion_time = current_time;
            current->turnaround_time = current_time - current->arrival_time;
            current->waiting_time = current->turnaround_time - current->burst_time;
            completed++;
        }
    }

    // Result file e write
    double total_tat = 0, total_wt = 0;

    for (auto &p : processes)
    {
        total_tat += p.turnaround_time;
        total_wt += p.waiting_time;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.process_id < b.process_id; });
    outfile << fixed << setprecision(5);
    outfile << "Final Completion Time: " << current_time << "\n";
    outfile << "Average Waiting Time: " << total_wt / n << "\n";
    outfile << "Average Turnaround Time: " << total_tat / n << "\n";

    outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
    for (auto &p : processes)
    {
        outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
                << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
    }

    outfile.close();
}

// ------------------------- Round Robin Scheduling -------------------------
void round_robin(vector<Process> processes, int quantum)
{

    ofstream outfile("rr_output.txt");

    int n = processes.size();
    queue<int> q;
    int current_time = 0, completed = 0;
    vector<bool> in_queue(n, false);

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });

    q.push(0);
    in_queue[0] = true;

    while (!q.empty())
    {
        int idx = q.front();
        q.pop();
        Process &p = processes[idx];

        current_time = max(current_time, p.arrival_time);
        int exec_time = min(quantum, p.remaining_time);
        p.remaining_time -= exec_time;
        current_time += exec_time;

        for (int i = 0; i < n; i++)
        {
            if (!in_queue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (p.remaining_time > 0)
        {
            q.push(idx);
        }
        else if (p.completion_time == -1)
        {
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            completed++;
        }

        if (q.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (processes[i].remaining_time > 0)
                {
                    q.push(i);
                    in_queue[i] = true;
                    break;
                }
            }
        }
    }

    double total_tat = 0, total_wt = 0;

    for (auto &p : processes)
    {
        total_tat += p.turnaround_time;
        total_wt += p.waiting_time;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.process_id < b.process_id; });
    outfile << fixed << setprecision(5);
    outfile << "Final Completion Time: " << current_time << "\n";
    outfile << "Average Waiting Time: " << total_wt / n << "\n";
    outfile << "Average Turnaround Time: " << total_tat / n << "\n";

    outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
    for (auto &p : processes)
    {
        outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
                << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
    }

    outfile.close();
}

// ------------------------- Preemptive Priority Scheduling -------------------------
// ------------------------- Preemptive Priority Scheduling -------------------------
void preemptivePriority(vector<Process> processes) {
    ofstream outfile("priority_output.txt");

    int n = processes.size();
    int completed = 0, current_time = 0;

    auto cmp = [](Process* a, Process* b) {
        if (a->priority == b->priority)
            return a->arrival_time > b->arrival_time;
        return a->priority > b->priority; // lower priority = higher actual priority
    };

    priority_queue<Process*, vector<Process*>, decltype(cmp)> pq(cmp);
    vector<bool> added(n, false);

    while (completed < n) {
        // Add newly arrived processes to the queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                processes[i].remaining_time > 0 && 
                !added[i]) {
                pq.push(&processes[i]);
                added[i] = true;
            }
        }

        if (pq.empty()) {
            current_time++;
            continue;
        }

        Process* current = pq.top();
        pq.pop();
        added[current - &processes[0]] = false;

        // Execute the process for 1 time unit
        current->remaining_time--;
        current_time++;

        if (current->remaining_time == 0) {
            current->completion_time = current_time;
            current->turnaround_time = current->completion_time - current->arrival_time;
            current->waiting_time = current->turnaround_time - current->burst_time;
            completed++;
        } else {
            // Re-add to queue if not finished
            pq.push(current);
            added[current - &processes[0]] = true;
        }
    }

    double total_tat = 0, total_wt = 0;

    for (auto &p : processes) {
        total_tat += p.turnaround_time;
        total_wt += p.waiting_time;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.process_id < b.process_id;
    });

    outfile << fixed << setprecision(5);
    outfile << "Final Completion Time: " << current_time << "\n";
    outfile << "Average Waiting Time: " << total_wt / n << "\n";
    outfile << "Average Turnaround Time: " << total_tat / n << "\n";

    outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
    for (auto &p : processes) {
        outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
                << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
    }

    outfile.close();
}


int main()
{
    ifstream infile("input.txt");

    int n, quantum;
    infile >> n >> quantum;
    vector<Process> processes;

    for (int i = 0; i < n; i++)
    {
        int a, b, p;
        infile >> a >> b >> p;
        processes.emplace_back(i + 1, a, b, p);
    }

    infile.close();

    sjf_preemptive(processes);
    round_robin(processes, quantum);
    preemptivePriority(processes); // <- ADD THIS
}

/*//input
//numberofprocess
//quantumtime(forroundrobin)
//arrivaltime,bursttime,priority(forpriorityscheduling)
// Example input file content:

 7
 3
 434
 623
 211
 636
 415
 030
 012
 */