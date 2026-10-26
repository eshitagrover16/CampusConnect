
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// =====================================================
// MODULE 3: DEPARTMENT & COURSE HIERARCHY
// =====================================================

// ---------------- STUDENT STRUCTURE ----------------

struct Module3Student {
    string rollNo;
    string name;
    float cgpa;
};

// Sample CGPA values for project demonstration
Module3Student module3Students[] = {
    {"251030001", "UPARJIT SHARMA", 9.1},
    {"251030002", "AKANKSHA", 8.2},
    {"251030004", "KRISH KUNAL", 8.5},
    {"251030005", "KAPISH SOOD", 7.8},
    {"251030006", "SHRESTH THAKUR", 7.5},
    {"251030007", "ARPIT RATHORE", 8.7},
    {"251030009", "ARYAN SHARMA", 8.0},
    {"251030010", "HRITVIK SOOD", 7.9},
    {"251030011", "BHASKAR PANDEY", 8.4},
    {"251030012", "SURBHI KUMARI", 9.2},
    {"251030013", "RAJANNYA MISHRA", 8.8},
    {"251030014", "SHRISHTI NIRWAL", 9.0},
    {"251030015", "SOMYA AGARWAL", 8.6},
    {"251030016", "SAMRIDDHI ROUT", 9.3},
    {"251030017", "ADITYA SATI", 7.7},
    {"251030018", "VIDDYOTIMA SINGH", 8.9},
    {"251030019", "HARSHIT SRIVASTAVA", 8.1},
    {"251030021", "DEEPALI VERMA", 9.1},
    {"251030022", "YASH TIWARI", 7.6},
    {"251030023", "MANYA UPPAL", 9.0},
    {"251030024", "TARUN SHARMA", 8.3},
    {"251030025", "DIVYANSHU KUMAR JHA", 7.8},
    {"251030026", "ESHITA GROVER", 9.0},
    {"251030027", "SIDHANT KATOCH", 9.1},
    {"251030028", "NEETI SINGH", 8.7},
    {"251030029", "SHRIYUL SHARMA", 8.0},
    {"251030030", "HARSHITH", 7.9},
    {"251030031", "YASH KUMAR", 8.5}
};

const int STUDENT_COUNT =
    sizeof(module3Students) / sizeof(module3Students[0]);

// ---------------- DEPARTMENT HIERARCHY ----------------

void showDepartmentHierarchy() {
    int choice;

    while (true) {
        cout << "\n====================================\n";
        cout << "       DEPARTMENT SELECTION\n";
        cout << "====================================\n";
        cout << "1. Computer Science\n";
        cout << "2. Data Science\n";
        cout << "0. Return to Module 3 Menu\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 0) {
            return;
        }

        if (choice == 1) {
            cout << "\n--- COMPUTER SCIENCE ---\n";
            cout << "Department: Computer Science\n";
            cout << "Course: B.Tech CSE\n";
            cout << "Subjects:\n";
            cout << "  1. Python Programming\n";
            cout << "  2. Data Structures\n";
        }
        else if (choice == 2) {
            cout << "\n--- DATA SCIENCE ---\n";
            cout << "Department: Data Science\n";
            cout << "Course: B.Tech Data Science\n";
            cout << "Subjects:\n";
            cout << "  1. Machine Learning\n";
            cout << "  2. Statistics\n";
        }
        else {
            cout << "Invalid choice. Select 0, 1, or 2.\n";
        }
    }
}

// ---------------- BINARY SEARCH TREE ----------------

class StudentBST {
private:
    struct Node {
        Module3Student data;
        Node* left;
        Node* right;

        Node(Module3Student s) {
            data = s;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;

    void insertNode(Node*& node, Module3Student s) {
        if (node == nullptr) {
            node = new Node(s);
            return;
        }

        if (s.cgpa < node->data.cgpa) {
            insertNode(node->left, s);
        }
        else {
            insertNode(node->right, s);
        }
    }

    // In-order traversal displays students in CGPA order
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);

        cout << node->data.rollNo << " | "
             << node->data.name << " | "
             << node->data.cgpa << "\n";

        inorder(node->right);
    }

    void rangeSearch(Node* node, float low, float high,
                     bool& found) {
        if (node == nullptr) {
            return;
        }

        if (node->data.cgpa > low) {
            rangeSearch(node->left, low, high, found);
        }

        if (node->data.cgpa >= low &&
            node->data.cgpa <= high) {
            cout << node->data.rollNo << " | "
                 << node->data.name << " | "
                 << node->data.cgpa << "\n";
            found = true;
        }

        if (node->data.cgpa <= high) {
            rangeSearch(node->right, low, high, found);
        }
    }

    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    StudentBST() {
        for (int i = 0; i < STUDENT_COUNT; i++) {
            insertNode(root, module3Students[i]);
        }
    }

    ~StudentBST() {
        deleteTree(root);
    }

    void displaySorted() {
        cout << "\n--- Students SORTED BY CGPA ---\n";
        cout << "Roll Number | Name | CGPA\n";
        cout << "-----------------------------------------------\n";

        inorder(root);
    }

    void searchRange(float low, float high) {
        bool found = false;

        cout << "\n--- STUDENTS IN CGPA RANGE ---\n";
        cout << "Roll Number | Name | CGPA\n";
        cout << "-----------------------------------------------\n";

        rangeSearch(root, low, high, found);


        if (!found) {
            cout << "No students found in this CGPA range.\n";
        }
    }
};

// ---------------- TRIE FOR AUTOCOMPLETE ----------------

class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;

        TrieNode() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }

            isEnd = false;
        }
    };

    TrieNode* root;

    string toLowerCase(string word) {
        for (char& ch : word) {
            ch = static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }

        return word;
    }

    void collectWords(TrieNode* node, string current,
                      vector<string>& results) {
        if (node == nullptr) {
            return;
        }

        if (node->isEnd) {
            results.push_back(current);
        }

        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                char ch = static_cast<char>('a' + i);

                collectWords(
                    node->children[i],
                    current + ch,
                    results
                );
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

    void insert(string word) {
        word = toLowerCase(word);

        TrieNode* current = root;

        for (char ch : word) {
            // This Trie stores alphabetic names and words
            if (ch < 'a' || ch > 'z') {
                continue;
            }

            int index = ch - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEnd = true;
    }

    vector<string> autocomplete(string prefix) {
        prefix = toLowerCase(prefix);

        // Normalize the prefix by removing spaces and punctuation.
        // The Trie stores only letters, so "python p" becomes "pythonp".
        string cleanPrefix;
        for (char ch : prefix) {
            if (ch >= 'a' && ch <= 'z') {
                cleanPrefix += ch;
            }
        }

        TrieNode* current = root;

        for (char ch : cleanPrefix) {
            int index = ch - 'a';

            if (current->children[index] == nullptr) {
                return {};
            }

            current = current->children[index];
        }

        vector<string> results;
        collectWords(current, cleanPrefix, results);

        return results;
    }
};

// ---------------- AUTOCOMPLETE DATA ----------------

void loadAutocompleteData(Trie& trie) {
    // Student names
    for (int i = 0; i < STUDENT_COUNT; i++) {
        trie.insert(module3Students[i].name);
    }

    // Book names
    trie.insert("Python Programming");
    trie.insert("Data Structures");
    trie.insert("Machine Learning");
    trie.insert("Statistics");
    trie.insert("Database Management Systems");
    trie.insert("Operating Systems");
    trie.insert("Computer Networks");
    trie.insert("Artificial Intelligence");
}

// ---------------- AUTOCOMPLETE MENU ----------------

void autocompleteMenu(Trie& trie) {
    int choice;
    string prefix;

    while (true) {
        cout << "\n--- AUTOCOMPLETE SEARCH ---\n";
        cout << "1. Search Student Names\n";
        cout << "2. Search Book/Subject Names\n";
        cout << "0. Return to Module 3 Menu\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 0) {
            return;
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter the starting letters: ";
        getline(cin, prefix);

        if (prefix.empty()) {
            cout << "Please enter a search prefix.\n";
            continue;
        }

        Trie searchTrie;
        loadAutocompleteData(searchTrie);

        vector<string> results = searchTrie.autocomplete(prefix);

        // Filter results by the selected category
        vector<string> filteredResults;

        if (choice == 1) {
            for (string result : results) {
                for (int i = 0; i < STUDENT_COUNT; i++) {
                    string studentName = module3Students[i].name;

                    for (char& ch : studentName) {
                        ch = static_cast<char>(
                            tolower(static_cast<unsigned char>(ch))
                        );
                    }
                    studentName.erase(
                        remove_if(studentName.begin(), studentName.end(),
                                  [](unsigned char ch) { return !isalpha(ch); }),
                        studentName.end()
                    );

                    if (result == studentName) {
                        filteredResults.push_back(module3Students[i].name);
                        break;
                    }
                }
            }
        }
        else {
            vector<string> books = {
                "Python Programming",
                "Data Structures",
                "Machine Learning",
                "Statistics",
                "Database Management Systems",
                "Operating Systems",
                "Computer Networks",
                "Artificial Intelligence"
            };

            for (string result : results) {
                for (string book : books) {
                    string lowerBook = book;

                    for (char& ch : lowerBook) {
                        ch = static_cast<char>(
                            tolower(static_cast<unsigned char>(ch))
                        );
                    }
                    lowerBook.erase(
                        remove_if(lowerBook.begin(), lowerBook.end(),
                                  [](unsigned char ch) { return !isalpha(ch); }),
                        lowerBook.end()
                    );

                    if (result == lowerBook) {
                        filteredResults.push_back(book);
                        break;
                    }
                }
            }
        }

        if (filteredResults.empty()) {
            cout << "No matching names found.\n";
        }
        else {
            cout << "\nSuggestions:\n";

            for (string result : filteredResults) {
                cout << " - " << result << "\n";
            }
        }
    }
}

// ---------------- MODULE 3 MENU ----------------

void runModule3() {
    int choice;

    while (true) {
        cout << "\n====================================\n";
        cout << "      CAMPUSCONNECT MODULE 3\n";
        cout << "====================================\n";
        cout << "1. Show Department and Course Hierarchy\n";
        cout << "2. Show Students Sorted by CGPA\n";
        cout << "3. Search Students by CGPA Range\n";
        cout << "4. Autocomplete Student/Book Names\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                showDepartmentHierarchy();
                break;

            case 2: {
                // Build the BST only when this option is selected.
                StudentBST studentBST;
                studentBST.displaySorted();
                break;
            }

            case 3: {
                float low, high;

                cout << "Enter minimum CGPA: ";
                if (!(cin >> low)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid CGPA.\n";
                    break;
                }

                cout << "Enter maximum CGPA: ";
                if (!(cin >> high)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid CGPA.\n";
                    break;
                }

                if (low < 0 || high > 10 || low > high) {
                    cout << "Enter a valid range between 0 and 10.\n";
                    break;
                }

                // Build the BST only when a CGPA search is requested.
                StudentBST studentBST;
                studentBST.searchRange(low, high);
                break;
            }

            case 4: {
                // Build and load the Trie only when autocomplete is selected.
                Trie trie;
                loadAutocompleteData(trie);
                autocompleteMenu(trie);
                break;
            }

            case 0:
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
