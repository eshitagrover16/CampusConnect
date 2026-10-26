
#include <iostream>
#include <limits>
#include "ui.h"

using namespace std;

// Function declarations from the module files
int runModule1();
int runModule2();
int runModule3();
int runModule4();
int runModule5();
int runModule6();  // Notice Board is stored in module6.cpp


int main() {
    int choice = -1;

    do {
        

        cout << "\n";
        cout << UI::BOLD << "  MAIN MENU\n\n" << UI::RESET;

        cout << UI::CYAN << "  [1] " << UI::RESET
             << "Student & Resource Directory\n";

        cout << UI::CYAN << "  [2] " << UI::RESET
             << "Login & Fast Access System\n";

        cout << UI::CYAN << "  [3] " << UI::RESET
             << "Department & Course Hierarchy\n";

        cout << UI::CYAN << "  [4] " << UI::RESET
             << "Library Book Recommendation\n";

        cout << UI::CYAN << "  [5] " << UI::RESET
             << "Campus Navigation\n";

        cout << UI::CYAN << "  [6] " << UI::RESET
             << "Notice Board Priority System\n";

        cout << UI::RED << "  [0] " << UI::RESET
             << "Exit CampusConnect\n";

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
                runModule1();
                break;

            case 2:
                runModule2();
                break;

            case 3:
                runModule3();
                break;

            case 4:
                runModule4();
                break;

            case 5:
                runModule5();
                break;

            case 6:
                runModule6();
                break;

            case 0:
                cout << "\n";
                UI::success("Thank you for using CampusConnect!");
                cout << "Goodbye!\n";
                break;

            default:
                UI::error("Invalid choice. Please select an available option.");
                UI::pause();
        }

    } while (choice != 0);

    return 0;
}
