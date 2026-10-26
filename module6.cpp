
#include <iostream>
#include <queue>
#include <string>
#include "ui.h"
using namespace std;

class Notice {
public:
    int id;
    string title;
    string category;
    int priority;

    Notice(int i, string t, string c, int p) {
        id = i;
        title = t;
        category = c;
        priority = p;
    }
};

// Highest priority notice comes first
struct Compare {
    bool operator()(Notice a, Notice b) {
        return a.priority < b.priority;
    }
};

class NoticeBoard {
private:
    priority_queue<Notice, vector<Notice>, Compare> notices;
    int nextID = 1;

public:
    // Add a new notice
    void addNotice(string title, string category, int priority) {
        notices.push(Notice(nextID++, title, category, priority));
        cout << "Notice added successfully!\n";
    }

    // Display the most important notice first
    void showNotices() {
        if (notices.empty()) {
            cout << "No notices available.\n";
            return;
        }

        priority_queue<Notice, vector<Notice>, Compare> temp = notices;

        cout << "\n===== NOTICE BOARD =====\n";

        while (!temp.empty()) {
            Notice n = temp.top();
            temp.pop();

            cout << "\nNotice ID: " << n.id << endl;
            cout << "Title: " << n.title << endl;
            cout << "Category: " << n.category << endl;
            cout << "Priority: " << n.priority << endl;
        }
    }

    // Show top K important notices
    void showTopK(int k) {
        if (k <= 0) {
            cout << "Enter a positive number.\n";
            return;
        }

        priority_queue<Notice, vector<Notice>, Compare> temp = notices;

        cout << "\n===== TOP " << k << " NOTICES =====\n";

        if (temp.empty()) {
            cout << "No notices available.\n";
            return;
        }

        int count = 0;

        while (!temp.empty() && count < k) {
            Notice n = temp.top();
            temp.pop();

            cout << n.title
                 << " | Priority: " << n.priority << endl;

            count++;
        }
    }
};

int runModule6() {
    NoticeBoard board;
    int choice;

    do {
        cout << "\n===== CAMPUSCONNECT NOTICE BOARD =====\n";
        cout << "1. Add Notice\n";
        cout << "2. Show All Notices by Priority\n";
        cout << "3. Show Top-K Important Notices\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, category;
            int priority;

            cout << "Enter notice title: ";
            getline(cin >> ws, title);

            cout << "Enter category (Exam/Emergency/General): ";
            getline(cin, category);

            cout << "Enter priority (1-10): ";
            cin >> priority;

            if (priority < 1 || priority > 10) {
                cout << "Priority must be between 1 and 10.\n";
            } else {
                board.addNotice(title, category, priority);
            }
        }
        else if (choice == 2) {
            board.showNotices();
        }
        else if (choice == 3) {
            int k;
            cout << "How many top notices? ";
            cin >> k;

            board.showTopK(k);
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
