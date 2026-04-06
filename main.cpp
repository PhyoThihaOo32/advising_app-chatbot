#include <vector>
#include <iostream>
#include <limits>
#include <string>
#include "Student.h"
#include "Advising.h"
#include "Career.h"
#include "TransferOption.h"
#include "Internship.h"
#include "Research.h"
#include <fstream>

using namespace std;

namespace
{
    const string ADMIN_PASSWORD = "csc211Hadvisingchatbot";

    string majorFromChoice(int choice)
    {
        switch (choice)
        {
        case 1:
            return "Computer Information Systems";
        case 2:
            return "Computer Network Technology";
        case 3:
            return "Computer Science";
        case 4:
            return "Geographic Information Science (GIS)";
        case 5:
            return "Cybersecurity Certificate";
        default:
            return "Geographic Information Science (GIS)";
        }
    }

    int promptMajorChoice(Advising &advisor)
    {
        int majorChoice;

        cout << "\nSelect major/program:\n"
             << "[1] Computer Information Systems\n"
             << "[2] Computer Network Technology\n"
             << "[3] Computer Science\n"
             << "[4] Geographic Information Science (GIS)\n"
             << "[5] Cybersecurity Certificate\n\n"
             << "Enter your choice: ";

        cin >> majorChoice;
        advisor.validateInput(majorChoice, 1, 5);

        return majorChoice;
    }

    void clearLine()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void showCareerPathway(Advising &advisor, Career &career)
    {
        int majorChoice = promptMajorChoice(advisor);
        string selectedMajor = majorFromChoice(majorChoice);

        bool hasAlumniSection =
            (selectedMajor == "Geographic Information Science (GIS)" ||
             selectedMajor == "Computer Science");

        if (hasAlumniSection)
        {
            int option;
            cout << "\n[1] Show Career Paths\n"
                 << "[2] Show BMCC Alumni\n\n"
                 << "Enter your choice: ";

            cin >> option;
            advisor.validateInput(option, 1, 2);

            if (option == 1)
            {
                career.showCareer(selectedMajor);
            }
            else
            {
                career.showAlumni(selectedMajor);
            }
        }
        else
        {
            career.showCareer(selectedMajor);
        }
    }

    void showTransferOption(Advising &advisor, TransferOption &options)
    {
        int majorChoice = promptMajorChoice(advisor);
        string selectedMajor = majorFromChoice(majorChoice);
        options.displayTransferOption(selectedMajor);
    }

    void showInternshipOrResearch(Advising &advisor, Internship &internship, Research &research)
    {
        int select;

        cout << "\nOpportunities\n";
        cout << "1. Internship Opportunity\n";
        cout << "2. Research Opportunity\n";

        cin >> select;
        advisor.validateInput(select, 1, 2);

        if (select == 1)
        {
            internship.showInternshipInfo();
        }
        else
        {
            research.showResearchInfo();
        }
    }

    void runUserMenu(Advising &advisor, Career &career, TransferOption &options, Internship &internship, Research &research)
    {
        char repeat;

        do
        {
            int command;

            cout << "\nUSER MENU\n";
            cout << "[1] Curriculum Advising\n"
                 << "[2] Career Pathway\n"
                 << "[3] Transfer Options\n"
                 << "[4] Internship/Research Opportunity\n"
                 << "[0] Back\n\n"
                 << "Enter your choice: ";

            cin >> command;
            advisor.validateInput(command, 0, 4);

            switch (command)
            {
            case 1:
                advisor.conversationController();
                break;
            case 2:
                showCareerPathway(advisor, career);
                break;
            case 3:
                showTransferOption(advisor, options);
                break;
            case 4:
                showInternshipOrResearch(advisor, internship, research);
                break;
            case 0:
                cout << "Returning to role selection...\n";
                return;
            default:
                break;
            }

            cout << "\nTo continue in User mode press 'y'. To go back press 'n': ";
            cin >> repeat;
        } while (repeat == 'y' || repeat == 'Y');
    }

    bool authenticateAdmin()
    {
        string enteredPassword;

        cout << "\nEnter admin password: ";
        cin >> enteredPassword;

        if (enteredPassword != ADMIN_PASSWORD)
        {
            cout << "Invalid password. Access denied.\n";
            return false;
        }

        cout << "Admin login successful.\n";
        return true;
    }

    void runAdminMenu(Advising &advisor, Career &career, TransferOption &options, Internship &internship, Research &research)
    {
        if (!authenticateAdmin())
        {
            return;
        }

        bool adminActive = true;
        while (adminActive)
        {
            int command;
            cout << "\nADMIN MENU\n"
                 << "[1] Add Career Pathway (writes to file)\n"
                 << "[2] Add Transfer Option (writes to file)\n"
                 << "[3] Add Alumni Profile (writes to file)\n"
                 << "[4] Delete Career Pathway (writes to file)\n"
                 << "[5] Delete Transfer Option (writes to file)\n"
                 << "[6] Delete Alumni Profile (writes to file)\n"
                 << "[7] Open User Menu (read-only)\n"
                 << "[0] Logout\n\n"
                 << "Enter your choice: ";

            cin >> command;
            advisor.validateInput(command, 0, 7);

            switch (command)
            {
            case 1:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);
                clearLine();

                string careerPath;
                cout << "Enter new career pathway: ";
                getline(cin, careerPath);

                if (careerPath.empty())
                {
                    cout << "No data saved. Career pathway cannot be empty.\n";
                }
                else
                {
                    career.setCareer(selectedMajor, careerPath);
                    cout << "Career pathway saved successfully.\n";
                }
                break;
            }
            case 2:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);
                options.setTransfer(selectedMajor);
                options.addTransferOption();
                cout << "Transfer option saved successfully.\n";
                break;
            }
            case 3:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);
                career.setAlumni(selectedMajor);
                cout << "Alumni profile saved successfully.\n";
                break;
            }
            case 4:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);

                career.showCareerNumbered(selectedMajor);

                int indexToDelete;
                cout << "Enter career number to delete (0 to cancel): ";
                cin >> indexToDelete;

                if (indexToDelete == 0)
                {
                    cout << "Delete canceled.\n";
                }
                else if (career.removeCareer(selectedMajor, indexToDelete))
                {
                    cout << "Career pathway deleted successfully.\n";
                }
                else
                {
                    cout << "Invalid selection. Nothing was deleted.\n";
                }
                break;
            }
            case 5:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);

                options.showTransferOptionNumbered(selectedMajor);

                int indexToDelete;
                cout << "Enter transfer option number to delete (0 to cancel): ";
                cin >> indexToDelete;

                if (indexToDelete == 0)
                {
                    cout << "Delete canceled.\n";
                }
                else if (options.removeTransferOption(selectedMajor, indexToDelete))
                {
                    cout << "Transfer option deleted successfully.\n";
                }
                else
                {
                    cout << "Invalid selection. Nothing was deleted.\n";
                }
                break;
            }
            case 6:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);

                career.showAlumniNumbered(selectedMajor);

                int indexToDelete;
                cout << "Enter alumni number to delete (0 to cancel): ";
                cin >> indexToDelete;

                if (indexToDelete == 0)
                {
                    cout << "Delete canceled.\n";
                }
                else if (career.removeAlumni(selectedMajor, indexToDelete))
                {
                    cout << "Alumni profile deleted successfully.\n";
                }
                else
                {
                    cout << "Invalid selection. Nothing was deleted.\n";
                }
                break;
            }
            case 7:
                runUserMenu(advisor, career, options, internship, research);
                break;
            case 0:
                cout << "Admin logout completed.\n";
                adminActive = false;
                break;
            default:
                break;
            }
        }
    }

    int promptRole(Advising &advisor)
    {
        int roleChoice;

        cout << "\nSelect mode:\n"
             << "[1] User (Read Only)\n"
             << "[2] Admin (Password Required)\n"
             << "[0] Exit Program\n\n"
             << "Enter your choice: ";

        cin >> roleChoice;
        advisor.validateInput(roleChoice, 0, 2);
        return roleChoice;
    }
}

int main()
{
    // Create objects for different advising modules
    Advising advisor;       // Handles curriculum advising and course planning
    Career career;          // Stores major-based career pathways and GIS alumni information
    TransferOption options; // Stores major-based transfer schools and their programs
    Internship internship;  // Displays internship opportunities
    Research research;      // Displays research opportunities

    cout << "======================================================\n";
    cout << "Welcome to the BMCC Advising Bot!\n";
    cout << "CIS Department Programs\n";
    cout << "======================================================\n";

    bool appRunning = true;
    while (appRunning)
    {
        int roleChoice = promptRole(advisor);

        switch (roleChoice)
        {
        case 1:
            runUserMenu(advisor, career, options, internship, research);
            break;
        case 2:
            runAdminMenu(advisor, career, options, internship, research);
            break;
        case 0:
            appRunning = false;
            break;
        default:
            break;
        }
    }

    cout << "Thank you for using the BMCC Advising App." << endl
         << "Wishing you success in your academic journey and future career." << endl
         << "Cheer!" << endl;

    return 0;
}
