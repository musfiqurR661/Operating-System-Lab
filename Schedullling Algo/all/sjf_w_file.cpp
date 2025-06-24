
#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int process_id;      // Process ID
    int arrival_time;    // Arrival time
    int burst_time;      // Burst time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    int completion_time; // Completion time
    int remaining_time;  // Remaining time (not used in non-preemptive)
    int priority;        // Priority (not used here)

    // Constructor
    Process(int id, int arr, int bur, int pri)
    {
        process_id = id;
        arrival_time = arr;
        burst_time = bur;
        priority = pri;
        remaining_time = burst_time;

        // These will be calculated later
        // completion_time = -1;
        // waiting_time = -1;
        // turnaround_time = -1;

        turnaround_time = waiting_time = completion_time = -1;
    }
};

// implementation of SJF algorithm
void sjf(vector<Process> &processes)
{
    int n = processes.size();
    int current_time = 0;
    int completed = 0; // Number of completed processes

    while (completed != n)
    {
        int chosen_index = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time < shortestTime &&
                processes[i].arrival_time <= current_time &&
                processes[i].completion_time == -1)
            {
                // If this process has the shortest remaining time and is ready to execute
                    shortestTime = processes[i].remaining_time;
                    chosen_index = i;
                
            }
        }
        // If no process is ready to execute
            if (chosen_index == -1)
            {
                current_time++;
                continue; // No process is ready, increment time
            }
            // Process the chosen process
            processes[chosen_index].remaining_time--;
            current_time++;

            // If the process is completed
            if (processes[chosen_index].remaining_time==0)
            {
                processes[chosen_index].completion_time = current_time;
                processes[chosen_index].turnaround_time = processes[chosen_index].completion_time - processes[chosen_index].arrival_time;
                processes[chosen_index].waiting_time = processes[chosen_index].turnaround_time - processes[chosen_index].burst_time;
                completed++;
            }
        
    }
    // completion time, turnaround time, and waiting time
    int completion_time = current_time;
    double avg_time= 0.0;
    double avg_waiting_time = 0.0;

    for(Process p: processes)
    {
        avg_time+= p.turnaround_time;
        avg_waiting_time+= p.waiting_time;
    }

    //output function 
    cout << "Average Turnaround Time: " << avg_time / n << endl;
    cout << "Average Waiting Time: " << avg_waiting_time / n << endl;
}

int main()
{
    ifstream infile("input.txt"); // Read from input.txt
    int n;
    infile >> n; // Number of processes
    vector<Process> processes;

    for(int i = 0; i < n; i++)
    {
        int a, b, p;
        infile >> a >> b >> p;
        Process pros(i + 1, a, b, p);
        processes.push_back(pros);
    }

    infile.close(); // Close file
    sjf(processes);
}
