# 🎓 Student Database Management System

A **console-based application** built in **C++** with **SQLite** to manage student records efficiently.  
This project demonstrates strong fundamentals in **Object-Oriented Programming**, **file/database handling**, and **modular software design**.

---

## ✨ Why I Built This Project

As part of my academic and career preparation , I developed this DBMS to:
- Practice **C++ and database integration**
- Learn **SQLite embedded systems**
- Simulate real-world **CRUD operations** in a structured system

---

## 🚀 Features

- 🔐 Unique Student ID validation (no duplicates)
- 📥 Add student with manual ID, name, marks
- 🧾 View all student records
- 🔍 Search students by ID
- ✏️ Update student details
- ❌ Delete student by ID
- 🧹 Delete and recreate entire table
- 📤 Export data to `students.csv`
- 🚫 Handles invalid input and empty database scenarios gracefully

---

## 🛠️ Tech Stack

| Language | Database | Compiler | Environment |
|----------|----------|----------|-------------|
| C++      | SQLite   | MinGW    | Visual Studio Code (Windows)

---

## 🧪 How to Compile & Run

```bash
g++ -c main.cpp -fpermissive
g++ -c student.cpp -fpermissive
gcc -c sqlite3.c
g++ main.o student.o sqlite3.o -o student_db.exe
.\student_db.exe
