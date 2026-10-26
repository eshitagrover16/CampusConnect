
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "ui.h"
using namespace std;

class Library {
private:
    string books[5] = {
        "Python Basics",
        "Advanced Python",
        "C++ Basics",
        "Data Science",
        "Machine Learning"
    };

    // Graph: {book ID, similarity score}
    vector<pair<int, int>> graph[5];

public:
    // Add connection between two similar books
    void addEdge(int u, int v, int weight) {
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    // Display all books
    void showBooks() {
        cout << "\nAvailable Books:\n";

        for (int i = 0; i < 5; i++) {
            cout << i << ". " << books[i] << endl;
        }
    }

    // Recommend the most similar books
    void recommend(int id) {
        if (id < 0 || id >= 5) {
            cout << "Invalid book ID!\n";
            return;
        }

        // Max Heap: highest similarity comes first
        priority_queue<pair<int, int>> pq;

        for (auto edge : graph[id]) {
            int bookID = edge.first;
            int score = edge.second;

            pq.push({score, bookID});
        }

        cout << "\nRecommendations for: "
             << books[id] << endl;

        if (pq.empty()) {
            cout << "No recommendations available.\n";
            return;
        }

        while (!pq.empty()) {
            int score = pq.top().first;
            int bookID = pq.top().second;
            pq.pop();

            cout << books[bookID]
                 << " | Similarity Score: "
                 << score << "/10\n";
        }
    }
};

int  runModule4() {
    Library lib;

    // Connect books with similarity scores
    lib.addEdge(0, 1, 9);  // Python Basics - Advanced Python
    lib.addEdge(0, 3, 7);  // Python Basics - Data Science
    lib.addEdge(1, 3, 8);  // Advanced Python - Data Science
    lib.addEdge(3, 4, 9);  // Data Science - Machine Learning
    lib.addEdge(2, 0, 4);  // C++ Basics - Python Basics

    int choice;

    do {
        cout << "\n===== CAMPUSCONNECT LIBRARY =====\n";
        cout << "1. Show Books\n";
        cout << "2. Get Recommendations\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            lib.showBooks();
        }
        else if (choice == 2) {
            lib.showBooks();

            int id;
            cout << "Enter Book ID: ";
            cin >> id;

            lib.recommend(id);
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
