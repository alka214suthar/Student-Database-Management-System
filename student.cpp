// student.cpp
#include "student.h"
#include <iostream>
#include <fstream>
using namespace std;

sqlite3* DB;
char* messageError;

int rowCounter(void* data, int argc, char** argv, char** colNames) {
    int* counter = (int*)data;
    (*counter)++;
    for (int i = 0; i < argc; i++) {
        cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

int exportCallback(void* filePtr, int argc, char** argv, char** azColName) {
    ofstream* out = (ofstream*)filePtr;
    for (int i = 0; i < argc; i++) {
        *out << (argv[i] ? argv[i] : "") << (i < argc - 1 ? "," : "\n");
    }
    return 0;
}

void createTable() {
    string sql = "CREATE TABLE IF NOT EXISTS STUDENTS ("
                 "ID INTEGER PRIMARY KEY, "
                 "NAME TEXT NOT NULL, "
                 "AGE INT NOT NULL, "
                 "COURSE TEXT NOT NULL);";

    int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << " Table creation error: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << " STUDENTS table ready.\n";
    }
}

void insertStudent() {
    int id, age;
    string name, course;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    getline(cin >> ws, name);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Course: ";
    getline(cin >> ws, course);
if (name.empty() || age <= 0 || course.empty()) {
    cout << " Invalid input. Please try again.\n";
    return;
}

    string sql = "INSERT INTO STUDENTS (ID, NAME, AGE, COURSE) VALUES("
                 + to_string(id) + ", '" + name + "', " + to_string(age) + ", '" + course + "');";

    int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        if (string(messageError).find("UNIQUE constraint failed") != string::npos) {
            cout << " Cannot insert: Student with ID " << id << " already exists.\n";
        } else {
            cout << " Insert error: " << messageError << endl;
        }
        sqlite3_free(messageError);
    } else {
        cout << " Student inserted successfully!\n";
    }
}

void viewStudents() {
    string sql = "SELECT * FROM STUDENTS;";
    int count = 0;

    int exit = sqlite3_exec(DB, sql.c_str(), rowCounter, &count, &messageError);
    if (exit != SQLITE_OK) {
        cout << " View error: " << messageError << endl;
        sqlite3_free(messageError);
    } else if (count == 0) {
        cout << " No student records found.\n";
    }
}

void searchStudent() {
    int id;
    cout << "Enter Student ID to search: ";
    cin >> id;

    int found = 0;
    string sql = "SELECT * FROM STUDENTS WHERE ID = " + to_string(id) + ";";
    int exit = sqlite3_exec(DB, sql.c_str(), rowCounter, &found, &messageError);

    if (exit != SQLITE_OK) {
        cout << " Search error: " << messageError << endl;
        sqlite3_free(messageError);
    } else if (found == 0) {
        cout << " No student found with ID " << id << ".\n";
    }
}

void deleteStudent() {
    int id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    string sql = "DELETE FROM STUDENTS WHERE ID = " + to_string(id) + ";";
    int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cout << " Delete error: " << messageError << endl;
        sqlite3_free(messageError);
    } else if (sqlite3_changes(DB) == 0) {
        cout << " No student found with ID " << id << ". Nothing deleted.\n";
    } else {
        cout << " Student deleted successfully.\n";
    }
}

void updateStudent() {
    int id, age;
    string name, course;

    cout << "Enter ID of student to update: ";
    cin >> id;
    cout << "Enter new Name: ";
    getline(cin >> ws, name);
    cout << "Enter new Age: ";
    cin >> age;
    cout << "Enter new Course: ";
    getline(cin >> ws, course);
if (name.empty() || age <= 0 || course.empty()) {
    cout << " Invalid input. Please try again.\n";
    return;
}

    string sql = "UPDATE STUDENTS SET "
                 "NAME = '" + name + "', "
                 "AGE = " + to_string(age) + ", "
                 "COURSE = '" + course + "' "
                 "WHERE ID = " + to_string(id) + ";";

    int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << " Update error: " << messageError << endl;
        sqlite3_free(messageError);
    } else if (sqlite3_changes(DB) == 0) {
        cout << " No student found with ID " << id << ". Nothing updated.\n";
    } else {
        cout << " Student updated successfully.\n";
    }
}

void resetTable() {
    string drop = "DROP TABLE IF EXISTS STUDENTS;";
    sqlite3_exec(DB, drop.c_str(), NULL, 0, &messageError);

    string create = "CREATE TABLE STUDENTS ("
                    "ID INTEGER PRIMARY KEY, "
                    "NAME TEXT NOT NULL, "
                    "AGE INT NOT NULL, "
                    "COURSE TEXT NOT NULL);";

    int exit = sqlite3_exec(DB, create.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cout << " Reset error: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << " STUDENTS table has been reset.\n";
    }
}

void exportToCSV() {
    ofstream outFile("students.csv");
    if (!outFile.is_open()) {
        cout << " Could not open file to write.\n";
        return;
    }

    outFile << "ID,Name,Age,Course\n";

    string sql = "SELECT * FROM STUDENTS;";
    int exit = sqlite3_exec(DB, sql.c_str(), exportCallback, &outFile, &messageError);

    outFile.close();

    if (exit != SQLITE_OK) {
        cout << " Export error: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << " Exported to students.csv successfully!\n";
    }
}
