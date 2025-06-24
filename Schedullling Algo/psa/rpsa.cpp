#include <bits/stdc++.h>
using namespace std;

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int remaining_time;
    int priority;

    Process(int id, int arr, int bur, int pri) {
        process_id = id;
        arrival_time = arr;
        burst_time = bur;
        priority = pri;
        remaining_time = burst_time;
        waiting_time = turnaround_time = completion_time = -1;
    }
};

void preemptivePriority(vector<Process> &processes) {
    ofstream outfile("priority_output.txt");

    int n = processes.size();
    int completed = 0, current_time = 0;

    auto cmp = [](Process* a, Process* b) {
        if (a->priority == b->priority)
            return a->arrival_time > b->arrival_time;
        return a->priority > b->priority;
    };

    priority_queue<Process*, vector<Process*>, decltype(cmp)> pq(cmp);

    vector<pair<int, int>> gantt; // {time, process_id}

    while (completed < n) {
        // Push all processes that have arrived and are not finished
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                pq.push(&processes[i]);
            }
        }

        if (pq.empty()) {
            current_time++;
            continue;
        }

        Process* current = nullptr;

        // Pop until find valid process with remaining_time > 0
        while (!pq.empty()) {
            Process* top = pq.top();
            pq.pop();
            if (top->remaining_time > 0) {
                current = top;
                break;
            }
        }

        if (!current) {
            current_time++;
            continue;
        }

        gantt.push_back({current_time, current->process_id});
        current->remaining_time--;
        current_time++;

        if (current->remaining_time == 0) {
            current->completion_time = current_time;
            current->turnaround_time = current->completion_time - current->arrival_time;
            current->waiting_time = current->turnaround_time - current->burst_time;
            completed++;
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

    outfile << fixed << setprecision(2);
    outfile << "Final Completion Time: " << current_time << "\n";
    outfile << "Average Waiting Time: " << total_wt / n << "\n";
    outfile << "Average Turnaround Time: " << total_tat / n << "\n";

    outfile << "\nID,Arrival,Burst,Completion,Turnaround,Waiting\n";
    for (auto &p : processes) {
        outfile << p.process_id << "," << p.arrival_time << "," << p.burst_time << ","
                << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
    }

    // Gantt Chart
    outfile << "\nGantt Chart:\n|";
    for (size_t i = 0; i < gantt.size(); i++) {
        outfile << " P" << gantt[i].second << " |";
    }
    outfile << "\n0";
    for (size_t i = 1; i <= gantt.size(); i++) {
        outfile << setw(4) << i;
    }

    outfile.close();
}

int main() {
    ifstream infile("input.txt");
    int n, quantum; // quantum unused here
    infile >> n >> quantum;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int a, b, p;
        infile >> a >> b >> p;
        processes.emplace_back(i + 1, a, b, p);
    }
    infile.close();

    preemptivePriority(processes);
}
