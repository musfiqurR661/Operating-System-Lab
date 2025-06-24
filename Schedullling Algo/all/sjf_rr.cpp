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

    auto cmp = [&](const Process &a, const Process &b)
    {
        return a.remaining_time > b.remaining_time ||
               (a.remaining_time == b.remaining_time && a.arrival_time > b.arrival_time);
    };

    while (completed < n)
    {
        int idx = -1, min_time = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_time)
            {
                min_time = processes[i].remaining_time;
                idx = i;
            }
        }

        if (idx == -1)
        {
            current_time++;
            continue;
        }

        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0)
        {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
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

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.process_id < b.process_id;
    });
    outfile << fixed << setprecision(2);
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

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.process_id < b.process_id;
    });
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
// void preemptivePriority(vector<Process> processes)
// {

//     ofstream outfile("priority_output.txt");

//     int n = processes.size();
//     int completed = 0, current_time = 0;

//     auto cmp = [](Process *a, Process *b)
//     {
//         if (a->priority == b->priority)
//             return a->arrival_time > b->arrival_time;
//         return a->priority > b->priority; // lower priority = higher actual priority
//     };

//     priority_queue<Process *, vector<Process *>, decltype(cmp)> pq(cmp);
//     vector<bool> inQueue(n, false);

//     while (completed < n)
//     {
//         for (int i = 0; i < n; i++)
//         {
//             if (processes[i].arrival_time <= current_time &&
//                 !inQueue[i] &&
//                 processes[i].remaining_time > 0)
//             {
//                 pq.push(&processes[i]);
//                 inQueue[i] = true;
//             }
//         }

//         if (pq.empty())
//         {
//             current_time++;
//             continue;
//         }

//         Process *current = pq.top();
//         pq.pop();
//         current->remaining_time--;
//         current_time++;

//         // Add new processes that arrived during execution
//         for (int i = 0; i < n; i++)
//         {
//             if (processes[i].arrival_time <= current_time &&
//                 !inQueue[i] &&
//                 processes[i].remaining_time > 0)
//             {
//                 pq.push(&processes[i]);
//                 inQueue[i] = true;
//             }
//         }

//         if (current->remaining_time > 0)
//         {
//             pq.push(current); 
//         }
//         else
//         {
//             current->completion_time = current_time;
//             current->turnaround_time = current->completion_time - current->arrival_time;
//             current->waiting_time = current->turnaround_time - current->burst_time;
//             completed++;
//         }
//     }

  
// //result

//     double total_tat = 0, total_wt = 0;
    
//    for (auto &p : processes)
//     {
//         total_tat += p.turnaround_time;
//         total_wt += p.waiting_time;
//     }

//     sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
//         return a.process_id < b.process_id;
//     });
//     outfile << fixed << setprecision(2);
//     outfile << "Final Completion Time: " << current_time << "\n";
//     outfile << "Average Waiting Time: " << total_wt / n << "\n";
//     outfile << "Average Turnaround Time: " << total_tat / n << "\n";

//     outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
//     for (auto &p : processes)
//     {
//         outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
//                 << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
//     }

//     outfile.close();
// }


// void preemptivePriority(vector<Process> processes)
// {
//     ofstream outfile("priority_output.txt");

//     int n = processes.size();
//     int completed = 0, current_time = 0;

//     auto cmp = [](Process *a, Process *b)
//     {
//         if (a->priority == b->priority)
//             return a->arrival_time > b->arrival_time;
//         return a->priority > b->priority; // lower priority = higher actual priority
//     };

//     priority_queue<Process *, vector<Process *>, decltype(cmp)> pq(cmp);
//     vector<bool> inQueue(n, false);

//     while (completed < n)
//     {
//         // Only check for arrivals at current time (not <=)
//         for (int i = 0; i < n; i++)
//         {
//             if (processes[i].arrival_time == current_time &&
//                 !inQueue[i] &&
//                 processes[i].remaining_time > 0)
//             {
//                 pq.push(&processes[i]);
//                 inQueue[i] = true;
//             }
//         }

//         if (pq.empty())
//         {
//             current_time++;
//             continue;
//         }

//         Process *current = pq.top();
//         pq.pop();

//         current->remaining_time--;

//         // Process finished
//         if (current->remaining_time == 0)
//         {
//             current->completion_time = current_time + 1; // +1 because it finishes at the end of this unit
//             current->turnaround_time = current->completion_time - current->arrival_time;
//             current->waiting_time = current->turnaround_time - current->burst_time;
//             completed++;
//         }
//         else
//         {
//             pq.push(current); // Push back if not done
//         }

//         current_time++; // Move time forward after execution
//     }

//     // result calculation
//     double total_tat = 0, total_wt = 0;

//     for (auto &p : processes)
//     {
//         total_tat += p.turnaround_time;
//         total_wt += p.waiting_time;
//     }

//     sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
//          { return a.process_id < b.process_id; });

//     outfile << fixed << setprecision(2);
//     outfile << "Final Completion Time: " << current_time << "\n";
//     outfile << "Average Waiting Time: " << total_wt / n << "\n";
//     outfile << "Average Turnaround Time: " << total_tat / n << "\n";

//     outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
//     for (auto &p : processes)
//     {
//         outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
//                 << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
//     }

//     outfile.close();
// }

void preemptivePriority(vector<Process> processes)
{
    ofstream outfile("priority_output.txt");

    int n = processes.size();
    int completed = 0, current_time = 0;

    auto cmp = [](Process* a, Process* b) {
        if (a->priority == b->priority)
            return a->arrival_time > b->arrival_time;
        return a->priority > b->priority;
    };

    priority_queue<Process*, vector<Process*>, decltype(cmp)> pq(cmp);

    while (completed < n)
    {
        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0)
            {
                pq.push(&processes[i]);
            }
        }

        if (pq.empty())
        {
            current_time++;
            continue;
        }

        Process* current = pq.top();
        pq.pop();

        // Execute for 1 unit time
        current->remaining_time--;
        current_time++;

        // Clear the queue to avoid duplicate processes
        while (!pq.empty()) pq.pop();

        // If finished
        if (current->remaining_time == 0)
        {
            current->completion_time = current_time;
            current->turnaround_time = current->completion_time - current->arrival_time;
            current->waiting_time = current->turnaround_time - current->burst_time;
            completed++;
        }
    }

    // Calculate and write result
    double total_tat = 0, total_wt = 0;
    for (auto& p : processes)
    {
        total_tat += p.turnaround_time;
        total_wt += p.waiting_time;
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.process_id < b.process_id;
    });

    outfile << fixed << setprecision(2);
    outfile << "Final Completion Time: " << current_time << "\n";
    outfile << "Average Waiting Time: " << total_wt / n << "\n";
    outfile << "Average Turnaround Time: " << total_tat / n << "\n";
    outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
    for (auto& p : processes)
    {
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


    vector<Process> copy1 = processes;
    vector<Process> copy2 = processes;
    vector<Process> copy3 = processes;

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