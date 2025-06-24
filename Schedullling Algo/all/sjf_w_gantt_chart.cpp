// // #include <iostream>
// // #include <vector>
// // using namespace std;

// #include <bits/stdc++.h>
// using namespace std;

// struct Process
// {
//     int process_id;      // Process ID
//     int arrival_time;    // Arrival time
//     int burst_time;      // Burst time
//     int waiting_time;    // Waiting time
//     int turnaround_time; // Turnaround time
//     int completion_time; // Completion time
//     int remaining_time;  // Remaining time (not used in non-preemptive)
//     int priority;        // Priority (not used here)

//     // Constructor
//     Process(int id, int arr, int bur, int pri)
//     {
//         process_id = id;
//         arrival_time = arr;
//         burst_time = bur;
//         priority = pri;
//         remaining_time = burst_time;

//         // These will be calculated later
//         // completion_time = -1;
//         // waiting_time = -1;
//         // turnaround_time = -1;

//         turnaround_time = waiting_time = completion_time = -1;
//     }
// };

// // implementation of SJF algorithm
// void sjf(vector<Process> &processes)
// {
//     int n = processes.size();
//     int current_time = 0;
//     int completed = 0;
//     vector<int> gantt_chart; // To store process_id execution history

//     while (completed != n)
//     {
//         int chosen_index = -1;
//         int shortestTime = INT_MAX;

//         for (int i = 0; i < n; i++)
//         {
//             if (processes[i].remaining_time < shortestTime &&
//                 processes[i].arrival_time <= current_time &&
//                 processes[i].completion_time == -1)
//             {
//                 shortestTime = processes[i].remaining_time;
//                 chosen_index = i;
//             }
//         }

//         if (chosen_index == -1)
//         {
//             gantt_chart.push_back(0); // 0 means idle
//             current_time++;
//             continue;
//         }

//         gantt_chart.push_back(processes[chosen_index].process_id);
//         processes[chosen_index].remaining_time--;
//         current_time++;

//         if (processes[chosen_index].remaining_time == 0)
//         {
//             processes[chosen_index].completion_time = current_time;
//             processes[chosen_index].turnaround_time = current_time - processes[chosen_index].arrival_time;
//             processes[chosen_index].waiting_time = processes[chosen_index].turnaround_time - processes[chosen_index].burst_time;
//             completed++;
//         }
//     }

//     // Print Gantt Chart
//     cout << "\nGantt Chart:\n";
//     vector<int> timeline;
//     vector<string> chart;

//     int prev = -1;
//     for (int i = 0; i < gantt_chart.size(); i++)
//     {
//         if (gantt_chart[i] != prev)
//         {
//             timeline.push_back(i);
//             if (gantt_chart[i] == 0)
//                 chart.push_back("Idle");
//             else
//                 chart.push_back("P" + to_string(gantt_chart[i]));
//             prev = gantt_chart[i];
//         }
//     }
//     timeline.push_back(gantt_chart.size()); // Last time

//     // Print process IDs
//     for (string p : chart)
//         cout << p << " ";
//     cout << endl;

//     // Print time points
//     for (int t : timeline)
//         cout << t << " ";
//     cout << endl;

//     // Calculate average times
//     double avg_turnaround = 0, avg_waiting = 0;
//     for (auto &p : processes)
//     {
//         avg_turnaround += p.turnaround_time;
//         avg_waiting += p.waiting_time;
//     }

//     cout << "Average Turnaround Time: " << avg_turnaround / n << endl;
//     cout << "Average Waiting Time: " << avg_waiting / n << endl;
// }
// int main()
// {
//     int n;
//     cin >> n; // Number of processes
//     vector<Process> processes;

//     for(int i = 0; i < n; i++)
//     {
//         int a, b, p;
//         cin >> a >> b >> p; // Arrival time, Burst time, Priority
//         Process pros(i + 1, a, b, p); // Process ID starts from 1
//         processes.push_back(pros);
//     }
//     sjf(processes);
// }


#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;

    Process(int id, int a, int b) {
        pid = id;
        arrival = a;
        burst = b;
        remaining = b;
    }
};

// Comparator for priority_queue (min-heap)
struct Compare {
    bool operator()(Process* a, Process* b) {
        if (a->remaining == b->remaining)
            return a->arrival > b->arrival; // break tie by arrival
        return a->remaining > b->remaining; // smaller remaining time first
    }
};

void sjf_preemptive(vector<Process> &processes) {
    int n = processes.size();
    int current_time = 0, completed = 0;
    vector<int> gantt_chart;

    auto cmp = Compare();
    priority_queue<Process*, vector<Process*>, Compare> pq;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int i = 0; // pointer to push processes when they arrive

    while (completed < n) {
        // Push all processes that have arrived by current_time
        while (i < n && processes[i].arrival <= current_time) {
            pq.push(&processes[i]);
            i++;
        }

        if (!pq.empty()) {
            Process* current = pq.top();
            pq.pop();

            gantt_chart.push_back(current->pid);

            current->remaining--;
            current_time++;

            // If completed
            if (current->remaining == 0) {
                current->completion = current_time;
                current->turnaround = current->completion - current->arrival;
                current->waiting = current->turnaround - current->burst;
                completed++;
            } else {
                pq.push(current); // still needs to run
            }
        } else {
            gantt_chart.push_back(-1); // idle
            current_time++;
        }
    }

    // Print Gantt Chart
    cout << "Gantt Chart:\n";
    int last_pid = -2;
    for (int t = 0; t < gantt_chart.size(); ++t) {
        if (gantt_chart[t] != last_pid) {
            if (last_pid != -2) cout << t << " ";
            if (gantt_chart[t] == -1) cout << "| idle ";
            else cout << "| P" << gantt_chart[t] << " ";
            last_pid = gantt_chart[t];
        }
    }
    cout << gantt_chart.size() << " |\n\n";

    // Calculate and print average
    double avg_wait = 0, avg_turn = 0;
    for (auto p : processes) {
        avg_wait += p.waiting;
        avg_turn += p.turnaround;
        cout << "P" << p.pid << " - Arrival: " << p.arrival
             << ", Burst: " << p.burst
             << ", Completion: " << p.completion
             << ", Waiting: " << p.waiting
             << ", Turnaround: " << p.turnaround << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_wait / n << endl;
    cout << "Average Turnaround Time: " << avg_turn / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes;
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        processes.emplace_back(i, a, b);
    }

    sjf_preemptive(processes);
    return 0;
}
