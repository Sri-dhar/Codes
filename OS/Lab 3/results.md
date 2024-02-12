# CPU Scheduling Simulator

This is a simple CPU scheduling simulator implemented in C, featuring First Come First Served (FCFS), Round Robin, and Shortest Remaining Burst First (SRBF) scheduling algorithms. The simulator reads process information from input files and provides insights into the performance of each scheduling algorithm.

## How to Use

1. **Compilation:**
   - Compile the source code using the provided makefile:
     ```
     make
     ```

2. **Execution:**
   - Run the executable with the desired input file containing process information:
     ```
     ./cpu-scheduler process.txt
     ```
     Replace `process.txt` with the path to your input file.

3. **Scheduling Algorithms:**
   - Choose a scheduling algorithm by entering the corresponding number:
     1. First Come First Served (FCFS)
     2. Round Robin (Specify time quantum when prompted)
     3. Shortest Remaining Burst First (SRBF)
     4. Exit

## Sample Test Cases

The `process.txt` file contains sample process information. The simulator output includes turnaround times, wait times, and averages for each scheduling algorithm.

## Inferences from Test Cases

1. **First Come First Served (FCFS):**
   - FCFS follows the order of process arrival.
   - Results may vary based on the arrival sequence, potentially leading to higher turnaround and wait times.

2. **Round Robin:**
   - Round Robin scheduling with a time quantum of 2 may exhibit higher turnaround and wait times.
   - Negative wait times indicate a potential issue in the implementation.

3. **Shortest Remaining Burst First (SRBF):**
   - SRBF prioritizes processes with the shortest remaining burst time.
   - Generally, SRBF produces lower turnaround and wait times compared to FCFS and Round Robin.


