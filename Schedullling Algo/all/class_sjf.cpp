#include <iostream>
#include <vector>
using namespace std;

/*
arrival time
burst time
priority
quantum time

turnaround time (completion time - arrival time)
waiting time (turnaround time - burst time)
*/

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int turnaroundTime;
    int waitingTime;
    int completionTime;
    int remainingTime;

    Process(int id, int arr, int bur, int pri)
    {
        this->id = id;
        arrivalTime = arr;
        burstTime = bur;
        priority = pri;
        remainingTime = burstTime;
        turnaroundTime = waitingTime = completionTime = -1;
    }
};

// implementation of shortest job first (SJF)
void sjf(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;

    while (completed != n)
    {
        int chosen = -1;
        int shortestTime = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remainingTime < shortestTime && 
                processes[i].arrivalTime <= currentTime && 
                processes[i].completionTime == -1)
            {
                shortestTime = processes[i].remainingTime;
                chosen = i;
            }
        }

        /*
        start -> 0
        P1 -> 2, P2 -> 4.....
        */
        if (chosen == -1)
        {
            currentTime++;
            continue;
        }

        processes[chosen].remainingTime--;
        currentTime++;

        if (processes[chosen].remainingTime == 0)
        {
            processes[chosen].completionTime = currentTime;
            processes[chosen].turnaroundTime = processes[chosen].completionTime - processes[chosen].arrivalTime;
            processes[chosen].waitingTime = processes[chosen].turnaroundTime - processes[chosen].burstTime;
            completed++;
            // cout << completed << endl;
        }
        // cout << currentTime << endl;
    }
  

    // completion time, turnaround time, waiting time
    int completionTime = currentTime;

    double avg_tt = 0;
    double avg_wt = 0;

    for (Process p : processes)
    {
        avg_tt += p.turnaroundTime;
        avg_wt += p.waitingTime;
    }

    cout << "turnaround time " << avg_tt / n << endl;
    cout << "waiting time " << avg_wt / n << endl;
}

void round_robin(vector<Process> &processes, int quantum)
{
}

void priority_scheduling(vector<Process> &processes)
{
}

int main()
{
    int n;
    cin >> n;
    vector<Process> processes;

    for (int i = 0; i < n; i++)
    {
        int a, b, p;
        cin >> a >> b >> p;
        Process pro(i + 1, a, b, p);
        processes.push_back(pro);
    }

    sjf(processes);
}