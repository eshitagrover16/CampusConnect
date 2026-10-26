
#include <iostream>
#include <string>
#include <limits>
#include "ui.h"

using namespace std;

// MODULE 1: STUDENT AND RESOURCE DIRECTORY

// Student structure
struct Student {
    int roll;
    string name;
    string department;
};

// Array to store students
Student s[100];
int n = 0;

// Queue for help-desk requests
string requests[100];
int front = 0, rear = -1;

// Prevent loading the initial students more than once
bool studentsLoaded = false;


// Load the initial 28 student records
void loadStudents() {
    if (studentsLoaded)
        return;

    s[0]  = {251030001, "UPARJIT SHARMA", "CSE"};
    s[1]  = {251030002, "AKANKSHA", "CSE"};
    s[2]  = {251030004, "KRISH KUNAL", "CSE"};
    s[3]  = {251030005, "KAPISH SOOD", "CSE"};
    s[4]  = {251030006, "SHRESTH THAKUR", "CSE"};
    s[5]  = {251030007, "ARPIT RATHORE", "CSE"};
    s[6]  = {251030009, "ARYAN SHARMA", "CSE"};
    s[7]  = {251030010, "HRITVIK SOOD", "CSE"};
    s[8]  = {251030011, "BHASKAR PANDEY", "CSE"};
    s[9]  = {251030012, "SURBHI KUMARI", "CSE"};
    s[10] = {251030013, "RAJANNYA MISHRA", "CSE"};
    s[11] = {251030014, "SHRISHTI NIRWAL", "CSE"};
    s[12] = {251030015, "SOMYA AGARWAL", "CSE"};
    s[13] = {251030016, "SAMRIDDHI ROUT", "CSE"};
    s[14] = {251030017, "ADITYA SATI", "CSE"};
    s[15] = {251030018, "VIDDYOTIMA SINGH", "CSE"};
    s[16] = {251030019, "HARSHIT SRIVASTAVA", "CSE"};
    s[17] = {251030021, "DEEPALI VERMA", "CSE"};
    s[18] = {251030022, "YASH TIWARI", "CSE"};
    s[19] = {251030023, "MANYA UPPAL", "CSE"};
    s[20] = {251030024, "TARUN SHARMA", "CSE"};
    s[21] = {251030025, "DIVYANSHU KUMAR JHA", "CSE"};
    s[22] = {251030026, "ESHITA GROVER", "CSE"};
    s[23] = {251030027, "SIDHANT KATOCH", "CSE"};
    s[24] = {251030028, "NEETI SINGH", "CSE"};
    s[25] = {251030029, "SHRIYUL SHARMA", "CSE"};
    s[26] = {251030030, "HARSHITH", "CSE"};
    s[27] = {251030031, "YASH KUMAR", "CSE"};

    n = 28;
    studentsLoaded = true;
}


// Add a new student
void addStudent() {
    if (n >= 100) {
        UI::error("Student directory is full.");
        return;
    }

    Student st;

    cout << "\nEnter roll number: ";

    if (!(cin >> st.roll) || st.roll <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        UI::error("Please enter a valid positive roll number.");
        return;
    }

    // Check for duplicate roll number
    for (int i = 0; i < n; i++) {
        if (s[i].roll == st.roll) {
            UI::error("A student with this roll number already exists.");
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter student name: ";
    getline(cin, st.name);

    if (st.name.empty()) {
        UI::error("Student name cannot be empty.");
        return;
    }

    cout << "Enter department: ";
    getline(cin, st.department);

    if (st.department.empty()) {
        UI::error("Department cannot be empty.");
        return;
    }

    s[n] = st;
    n++;

    UI::success("Student added successfully.");
}


// Display all students
void display() {
    if (n == 0) {
        UI::error("No student records found.");
        return;
    }

    UI::header("STUDENT DIRECTORY");

    cout << "\n";
    cout << "Roll Number\tName\t\t\tDepartment\n";
    UI::line();

    for (int i = 0; i < n; i++) {
        cout << s[i].roll << "\t"
             << s[i].name << "\t\t"
             << s[i].department << "\n";
    }

    UI::line();
    cout << "Total students: " << n << "\n";
}


// Merge function for merge sort
void merge(int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;

    Student temp[100];

    while (i <= mid && j <= right) {
        if (s[i].roll <= s[j].roll) {
            temp[k++] = s[i++];
        } else {
            temp[k++] = s[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = s[i++];
    }

    while (j <= right) {
        temp[k++] = s[j++];
    }

    for (int x = 0; x < k; x++) {
        s[left + x] = temp[x];
    }
}


// Merge sort students by roll number
void mergeSort(int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    merge(left, mid, right);
}


// Search for a student using binary search
void searchStudent() {
    if (n == 0) {
        UI::error("No student records available.");
        return;
    }

    // Binary search requires sorted data
    mergeSort(0, n - 1);

    int roll;
    cout << "\nEnter roll number to search: ";

    if (!(cin >> roll)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        UI::error("Please enter a valid roll number.");
        return;
    }

    int low = 0;
    int high = n - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (s[mid].roll == roll) {
            UI::success("Student found!");

            cout << "\nRoll Number: " << s[mid].roll;
            cout << "\nName: " << s[mid].name;
            cout << "\nDepartment: " << s[mid].department << "\n";

            found = true;
            break;
        }
        else if (s[mid].roll < roll) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    if (!found) {
        UI::error("Student with this roll number was not found.");
    }
}


// Add a help-desk request to the queue
void addRequest() {
    if (rear == 99) {
        UI::error("Help-desk request queue is full.");
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string request;

    cout << "\nEnter your help-desk request: ";
    getline(cin, request);

    if (request.empty()) {
        UI::error("Request cannot be empty.");
        return;
    }

    requests[++rear] = request;

    UI::success("Help-desk request added to the queue.");
}


// Process the oldest help-desk request
void processRequest() {
    if (front > rear) {
        UI::error("No pending help-desk requests.");
        return;
    }

    cout << "\nProcessing request: "
         << requests[front] << "\n";

    front++;

    UI::success("Request processed successfully.");
}


// MODULE 1 MENU
int runModule1() {
    loadStudents();

    int choice;

    do {
        UI::header("STUDENT & RESOURCE DIRECTORY");

        cout << "\n";
        cout << "[1] Add Student\n";
        cout << "[2] Display All Students\n";
        cout << "[3] Search Student by Roll Number\n";
        cout << "[4] Sort Students by Roll Number\n";
        cout << "[5] Add Help-Desk Request\n";
        cout << "[6] Process Help-Desk Request\n";
        cout << "[7] Return to Main Menu\n";

        UI::line();
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            UI::error("Please enter a valid number.");
            UI::pause();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                UI::pause();
                break;

            case 2:
                display();
                UI::pause();
                break;

            case 3:
                searchStudent();
                UI::pause();
                break;

            case 4: {
                mergeSort(0, n - 1);

                UI::success("Students sorted by roll number.");

                char answer;

                cout << "\nDo you want to see the students sorted "
                     << "by roll number? (Y/N): ";

                cin >> answer;

                if (answer == 'Y' || answer == 'y') {
                    display();
                }
                else if (answer == 'N' || answer == 'n') {
                    cout << "\nSorted successfully. "
                         << "Returning to the Module 1 menu.\n";
                }
                else {
                    UI::error("Invalid choice. Please enter Y or N.");
                }

                UI::pause();
                break;
            }

            case 5:
                addRequest();
                UI::pause();
                break;

            case 6:
                processRequest();
                UI::pause();
                break;

            case 7:
                cout << "\nReturning to the Main Menu...\n";
                break;

            default:
                UI::error("Invalid choice. Please select 1 to 7.");
                UI::pause();
        }

    } while (choice != 7);

    return 0;
}
