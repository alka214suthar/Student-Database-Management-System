// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "sqlite3.h"
#include <string>
using namespace std;

extern sqlite3* DB;
extern char* messageError;

void createTable();
void insertStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void resetTable();
void exportToCSV();

#endif
