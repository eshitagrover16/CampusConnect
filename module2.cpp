
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <limits>
#include "ui.h"

using namespace std;

// MODULE 2: LOGIN & FAST ACCESS SYSTEM

// Student details
struct Student {
    string rollNo;
    string name;
    string department;
};

// Same 28 students as Module 1
Student students[] = {
    {"251030001", "UPARJIT SHARMA", "CSE"},
    {"251030002", "AKANKSHA", "CSE"},
    {"251030004", "KRISH KUNAL", "CSE"},
    {"251030005", "KAPISH SOOD", "CSE"},
    {"251030006", "SHRESTH THAKUR", "CSE"},
    {"251030007", "ARPIT RATHORE", "CSE"},
    {"251030009", "ARYAN SHARMA", "CSE"},
    {"251030010", "HRITVIK SOOD", "CSE"},
    {"251030011", "BHASKAR PANDEY", "CSE"},
    {"251030012", "SURBHI KUMARI", "CSE"},
    {"251030013", "RAJANNYA MISHRA", "CSE"},
    {"251030014", "SHRISHTI NIRWAL", "CSE"},
    {"251030015", "SOMYA AGARWAL", "CSE"},
    {"251030016", "SAMRIDDHI ROUT", "CSE"},
    {"251030017", "ADITYA SATI", "CSE"},
    {"251030018", "VIDDYOTIMA SINGH", "CSE"},
    {"251030019", "HARSHIT SRIVASTAVA", "CSE"},
    {"251030021", "DEEPALI VERMA", "CSE"},
    {"251030022", "YASH TIWARI", "CSE"},
    {"251030023", "MANYA UPPAL", "CSE"},
    {"251030024", "TARUN SHARMA", "CSE"},
    {"251030025", "DIVYANSHU KUMAR JHA", "CSE"},
    {"251030026", "ESHITA GROVER", "CSE"},
    {"251030027", "SIDHANT KATOCH", "CSE"},
    {"251030028", "NEETI SINGH", "CSE"},
    {"251030029", "SHRIYUL SHARMA", "CSE"},
    {"251030030", "HARSHITH", "CSE"},
    {"251030031", "YASH KUMAR", "CSE"}
};

const int STUDENT_COUNT = sizeof(students) / sizeof(students[0]);
const string DEFAULT_PASSWORD = "Campus@123";

// Custom Hash Map using Chaining
class CustomHashMap {
private:
    vector<list<pair<string, string>>> table;
    int tableSize;

    int hashFunction(string key) {
        int hash = 0;

        for (char ch : key) {
            hash = (hash * 31 + ch) % tableSize;
        }

        return hash;
    }

public:
    CustomHashMap(int size = 101) {
        tableSize = size;
        table.resize(tableSize);
    }

    void insert(string rollNo, string password) {
        int index = hashFunction(rollNo);

        for (auto &entry : table[index]) {
            if (entry.first == rollNo) {
                entry.second = password;
                return;
            }
        }

        table[index].push_back({rollNo, password});
    }

    bool login(string rollNo, string password) {
        int index = hashFunction(rollNo);

        for (auto entry : table[index]) {
            if (entry.first == rollNo &&
                entry.second == password) {
                return true;
            }
        }

        return false;
    }
};

// LRU-style recent book access tracker
class LRUCache {
private:
    list<string> recentBooks;
    int capacity;

public:
    LRUCache(int cap = 5) {
        capacity = cap;
    }

    void accessBook(string bookName) {
        recentBooks.remove(bookName);
        recentBooks.push_front(bookName);

        if (recentBooks.size() > capacity) {
            recentBooks.pop_back();
        }
    }

    void displayRecentBooks() {
        if (recentBooks.empty()) {
            cout << "\nNo books accessed yet.\n";
            return;
        }

        cout << "\n--- Recently Accessed Books ---\n";

        int number = 1;

        for (string book : recentBooks) {
            cout << number++ << ". " << book << "\n";
        }
    }
};

// Global objects
CustomHashMap studentLogin;
LRUCache recentBooks;

bool dataLoaded = false;
bool loggedIn = false;

string currentRollNo = "";
string currentStudentName = "";

// Find a student's name using roll number
string getStudentName(string rollNo) {
    for (int i = 0; i < STUDENT_COUNT; i++) {
        if (students[i].rollNo == rollNo) {
            return students[i].name;
        }
    }

    return "";
}

// Load student IDs and passwords into the hash map
void loadLoginData() {
    if (dataLoaded) {
        return;
    }

    for (int i = 0; i < STUDENT_COUNT; i++) {
        studentLogin.insert(students[i].rollNo, DEFAULT_PASSWORD);
    }

    dataLoaded = true;
}

// Student login
void studentLoginMenu() {
    string rollNo, password;

    cout << "\nEnter Student Roll Number: ";
    cin >> rollNo;

    cout << "Enter Password: ";
    cin >> password;

    if (studentLogin.login(rollNo, password)) {
        loggedIn = true;
        currentRollNo = rollNo;
        currentStudentName = getStudentName(rollNo);

        UI::success("Login successful!");

        cout << "\nWelcome, " << currentStudentName << "!\n";
        cout << "Roll Number: " << currentRollNo << "\n";
        cout << "Department: CSE\n";
    } else {
        UI::error("Invalid roll number or password.");
    }
}

// Book access
void accessBook() {
    if (!loggedIn) {
        UI::error("Please log in before accessing books.");
        return;
    }

    string books[] = {
        "Data Structures and Algorithms",
        "Database Management Systems",
        "Operating Systems",
        "Computer Networks",
        "Artificial Intelligence"
    };

    cout << "\n--- Library Books ---\n";

    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << books[i] << "\n";
    }

    int choice;

    cout << "\nSelect a book number (1-5): ";
    cin >> choice;

    if (choice < 1 || choice > 5) {
        UI::error("Invalid book selection.");
        return;
    }

    recentBooks.accessBook(books[choice - 1]);

    UI::success("Book accessed successfully!");

    cout << "Student: " << currentStudentName << "\n";
    cout << "Book: " << books[choice - 1] << "\n";
}

// Main function called by CampusConnect
int runModule2() {
    loadLoginData();

    int choice;

    while (true) {
        UI::header("MODULE 2: LOGIN & FAST ACCESS SYSTEM");

        if (loggedIn) {
            cout << "Logged in as: " << currentStudentName
                 << " (" << currentRollNo << ")\n";
        } else {
            cout << "Status: Not logged in\n";
        }

        cout << "\n1. Student Login\n";
        cout << "2. Access Library Book\n";
        cout << "3. View Recently Accessed Books\n";
        cout << "4. Logout\n";
        cout << "0. Return to Main Menu\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            UI::error("Please enter a valid number.");
            continue;
        }

        switch (choice) {
            case 1:
                studentLoginMenu();
                break;

            case 2:
                accessBook();
                break;

            case 3:
                if (!loggedIn) {
                    UI::error("Please log in first.");
                } else {
                    recentBooks.displayRecentBooks();
                }
                break;

            case 4:
                if (loggedIn) {
                    loggedIn = false;
                    currentRollNo = "";
                    currentStudentName = "";
                    UI::success("Logged out successfully.");
                } else {
                    cout << "\nYou are not logged in.\n";
                }
                break;

            case 0:
                return 0;

            default:
                UI::error("Invalid choice. Please try again.");
        }

        UI::pause();
    }

    return 0;
}
