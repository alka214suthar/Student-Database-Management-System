// main.cpp
#include <iostream>
#include "student.h"

int main() {
    int choice;
    int exit = sqlite3_open("student.db", &DB);

    if (exit != SQLITE_OK) {
        cout << " Can't open DB: " << sqlite3_errmsg(DB) << endl;
        return -1;
    }

    createTable();

    do {
        cout << "\n===== Student DBMS Menu =====\n";
        cout << "1. Insert Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Delete Student by ID\n";
        cout << "5. Update Student by ID\n";
        cout << "6. Reset (Delete & Recreate) Table\n";
        cout << "7. Export Student Data to CSV\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: resetTable(); break;
            case 7: exportToCSV(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    sqlite3_close(DB);
    return 0;
}
