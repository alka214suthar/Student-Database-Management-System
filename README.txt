Student DBMS Project (C++ + SQLite)

Description:
-------------
A console-based Student Database Management System using C++ and SQLite.

Features:
---------
✔ Insert Student
✔ View All Students
✔ Search Student by ID
✔ Delete Student by ID
✔ Update Student by ID
✔ Reset (Delete & Recreate) Table
✔ Export data to CSV (students.csv)

How to Compile:
---------------
g++ -c student.cpp -fpermissive
g++ -c main.cpp -fpermissive
gcc -c sqlite3.c
g++ student.o main.o sqlite3.o -o student_db.exe

How to Run:
-----------
.\student_db.exe

Output:
-------
students.csv → generated when "Export to CSV" is used.

Project Files:
--------------
main.cpp, student.cpp, student.h, sqlite3.c, sqlite3.h, README.txt
