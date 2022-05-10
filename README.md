## mpi-parallel-processing

Given a file contains ids and grades of students.

**Master Process:**
1. Read data from file
2. Divide the students list by the number of processes you have then send it to them.
3. Print the summation of the number of passed students received from each process.
4. For each process, receive part of students data, check if they passed or not and print message for each student:
    - StudentID Passed The Exam, or
    - StudentID Failed. Please Repeat The Exam.
5. Calculate number of passed student then send it to master process.
