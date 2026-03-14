#include <vector>
#include <iostream>
#include "Student.h"
#include "Advising.h"
#include "career.h"
#include "transferOption.h"
#include <fstream>

using namespace std;

int main() {
    Advising advisor;
    Career career;
    TransferOption options;

    //1. Welcome Message
    cout << "======================================================\n";
    cout << "Welcome to the BMCC Advising Bot!\n";
    cout << "Geographic Information Science\n";
    cout << "======================================================\n";

    //2. The Main Hub Menu
    int command;
    cout << "[1] Curriculum Advising\n"
         << "[2] Career Pathway \n"
         << "[3] Transfer opportunity\n"
         << "[4] Internship/Research opportunity\n"
         << "[5] Resources and News\n"
         << "[0] Exit program\n"
         << "Selection: ";
    cin >> command;
    
    //3. Selection feature-
    switch (command) {
        case 1:
            advisor.conversationController();
            break;
        case 2:
            int option;
            cout
            << "[1] Show Careers\n"
            << "[2] Show Alumni\n";
            cin >> option;
            if(option == 1) {
                career.showCareer();
            } else if(option == 2) {
                career.showAlumni();
            }
            break;
        case 3:
            cout << "Transfer opportunity\n"
            << "[1] Show Transfer Options\n";
            int select;
            cin >> select;
            if(select == 1) {
                options.displayTransferOption();
            }
            break;
;       case 4:
            cout << "Resources and News\n code";
            break;
        case 0:
            cout << "Exitting program... \n";
            break;
        default:
            break;
    }
    return 0;
}

