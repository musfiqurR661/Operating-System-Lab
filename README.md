# Operating Systems Lab - Spring 2025

This repository contains all the lab work, assignments, and projects for the Operating Systems course (10th Semester) at UIU.

## 📁 Repository Structure

### 🎯 Assignments
- **Assignment_1/** - First assignment implementation
  - `011221334.cpp` - Main C++ source code
  - `011221334.exe` - Compiled executable
  - `input.txt` - Input data file

- **Assignment_2/** - Second assignment focusing on IPC and threading
  - `01122134.cpp` - Main C++ implementation
  - `01122134.exe` - Compiled executable
  - `prod_cons_with_mutex.cpp` - Producer-Consumer with mutex implementation
  - `prod_cons_with_mutex.exe` - Compiled executable
  - `thread_counter.cpp` - Thread counter implementation
  - `simple_thread.c` - Basic thread example in C

### ⚡ Scheduling Algorithms
- **Schedullling Algo/all/** - Comprehensive scheduling algorithm implementations
  - `sjf_rr.cpp` - Shortest Job First and Round Robin implementation
  - `sjf_w_gantt_chart.cpp` - SJF with Gantt chart visualization
  - `sjf_w_file.cpp` - SJF with file I/O
  - `sjf_demo_mine.cpp` - SJF demonstration
  - `class_sjf.cpp` - SJF class-based implementation
  - `011221334_chck.cpp` - Additional scheduling implementation
  - `input.txt` - Test input data
  - `sjf_output.txt` - SJF algorithm output
  - `rr_output.txt` - Round Robin algorithm output

- **Schedullling Algo/psa/** - Priority Scheduling Algorithm
  - `rpsa.cpp` - Round Robin Priority Scheduling Algorithm
  - `input.txt` - Priority scheduling input
  - `priority_output.txt` - Priority scheduling output

### 🔄 Inter-Process Communication (IPC)
- **IPC/IPC resources/** - IPC implementations and resources
  - `prod_cons_with_mutex.cpp` - Producer-Consumer with mutex
  - `thread_counter.cpp` - Thread counter implementation
  - `simple_thread.c` - Basic thread example
  - `PThread.pdf` - PThread documentation
  - `IPC.pdf` - IPC concepts and examples

### 🐧 Linux Shell Scripting
- **Code/** - Shell scripting examples and practice
  - `basicPractics.sh` - Basic shell scripting practice
  - `script.sh` - General shell script examples
  - `for.sh` - For loop examples
  - `while.sh` - While loop examples
  - `director.sh` - Directory manipulation scripts
  - `basic_file.txt`, `m1.txt` - Test files

### 📚 Course Materials
- **from Class/** - Class materials and examples
  - `Scheduling.pdf` - Scheduling algorithms documentation
  - `scheduling_assignment.pdf` - Scheduling assignment details
  - `Scheduling examples.pdf` - Scheduling examples

- **MID/** - Midterm materials
  - `Linux_Shell_Midterm_Question_Sets.pdf` - Midterm question sets
  - `mid.txt` - Midterm notes

- **CT/** - Class Test materials
  - `OS_CT/` - Class test implementations
  - `Section_C.pdf` - Section C materials
  - `virus.sh` - Virus simulation script
  - `virus.txt` - Virus simulation data

- **Final Qn/** - Final examination materials
  - `Final QN OS.jpg` - Final question paper

### 📖 Documentation
- `OS Lab Lecture.pdf` - Complete lab lecture notes
- `Basic Linux Commands.pdf` - Linux command reference
- `MorePracticeProblems.pdf` - Additional practice problems
- `Practice1.zip`, `Practice2.zip` - Practice problem archives

## 🚀 Getting Started

### Prerequisites
- C/C++ compiler (GCC/G++)
- Linux environment or WSL for shell scripts
- PDF viewer for documentation

### Compilation
Most C++ programs can be compiled using:
```bash
g++ -o program_name program_name.cpp
```

### Running Programs
```bash
# For C++ executables
./program_name.exe

# For shell scripts
chmod +x script.sh
./script.sh
```

## 📋 Topics Covered

1. **Process Management**
   - Process creation and management
   - Inter-Process Communication (IPC)
   - Threading and synchronization

2. **Scheduling Algorithms**
   - First Come First Serve (FCFS)
   - Shortest Job First (SJF)
   - Round Robin (RR)
   - Priority Scheduling
   - Gantt chart visualization

3. **Linux Shell Scripting**
   - Basic shell commands
   - Control structures (if, for, while)
   - File and directory operations
   - Script automation

4. **Synchronization**
   - Mutex implementation
   - Producer-Consumer problem
   - Thread synchronization

## 👨‍💻 Student Information
- **Student ID**: 011221334
- **Course**: Operating Systems Lab
- **Semester**: 10th Semester
- **Institution**: UIU

## 📝 Notes
- All executables are compiled for Windows environment
- Source code is cross-platform compatible
- Input files are provided for testing algorithms
- Output files show expected results for verification

## 🔗 Related Resources
- Course materials and lecture notes are included in PDF format
- Practice problems and additional resources are available in zip archives
- Class test and midterm materials are organized in respective folders

---
*This repository serves as a comprehensive collection of Operating Systems lab work and serves as a reference for understanding core OS concepts through practical implementation.* 