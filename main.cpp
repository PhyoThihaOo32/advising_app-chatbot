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
            return "Computer Information Systems (CIS)";
        case 2:
            return "Computer Network Technology (CNT)";
        case 3:
            return "Computer Science (CSC)";
        case 4:
            return "Geographic Information Science (GIS)";
        case 5:
            return "Cybersecurity Certificate (CYB)";
        default:
            return "Geographic Information Science (GIS)";
        }
    }

    int promptMajorChoice(Advising &advisor)
    {
        int majorChoice;

        cout << "\nSelect major/program:\n"
             << "[1] Computer Information Systems (CIS)\n"
             << "[2] Computer Network Technology (CNT)\n"
             << "[3] Computer Science (CSC)\n"
             << "[4] Geographic Information Science (GIS)\n"
             << "[5] Cybersecurity Certificate (CYB)\n\n"
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
        cout << "Enter admin password: ";
        cin >> enteredPassword;

        if (enteredPassword != ADMIN_PASSWORD)
        {
            cout << "Invalid password. Access denied.\n";
            return false;
        }

        cout << "Admin login successful.\n";
        return true;
    }

    bool selectDegreePlan(Advising& advisor, Curriculum& curriculum, string& filename, string& majorName) {
        vector<string> availablePlans;
        vector<string> displayNames;
        vector<string> majorCodes;

        if (curriculum.fileExists("data/gis_degree_plan.csv")) {
            availablePlans.push_back("data/gis_degree_plan.csv");
            displayNames.push_back("Geographic Information Science (GIS)");
            majorCodes.push_back("GIS");
        }
        if (curriculum.fileExists("data/cis_degree_plan.csv")) {
            availablePlans.push_back("data/cis_degree_plan.csv");
            displayNames.push_back("Computer Information Systems (CIS)");
            majorCodes.push_back("CIS");
        }
        if (curriculum.fileExists("data/csc_degree_plan.csv")) {
            availablePlans.push_back("data/csc_degree_plan.csv");
            displayNames.push_back("Computer Science (CSC)");
            majorCodes.push_back("CSC");
        }
        if (curriculum.fileExists("data/cnt_degree_plan.csv")) {
            availablePlans.push_back("data/cnt_degree_plan.csv");
            displayNames.push_back("Computer Network Technology (CNT)");
            majorCodes.push_back("CNT");
        }

        if (availablePlans.empty()) {
            cout << "No degree plan files found.\n";
            return false;
        }

        cout << "\nAVAILABLE DEGREE PLANS\n";
        for (int i = 0; i < availablePlans.size(); i++) {
            cout << "[" << i + 1 << "] " << displayNames[i] << " - Degree Map" << endl;
        }
        cout << "[0] Cancel\n\nEnter your choice: ";

        int choice;
        cin >> choice;
        advisor.validateInput(choice, 0, availablePlans.size());

        if (choice == 0) {
            cout << "Selection canceled.\n";
            return false;
        }

        filename = availablePlans[choice - 1];
        majorName = majorCodes[choice - 1];
        return true;
    }
    
    void runCurriculumEditor(Advising& advisor) {
        Curriculum& curriculum = advisor.getCurriculum();
        bool editingCurriculum = true;

        while (editingCurriculum) {
            int command;

            cout << "\nCURRICULUM EDITOR\n"
                << "[1] View Degree Maps\n"
                << "[2] Add Course to Degree Map\n"
                << "[3] Edit Course in Degree Map\n"
                << "[4] Delete Course in Degree Map\n"
                << "[0] Exit Curriculum Editor\n\n"
                << "Enter your choice: ";

            cin >> command;
            advisor.validateInput(command, 0, 4);

            switch (command) {
            case 1:
            {
                string filename, majorName;
                if (selectDegreePlan(advisor, curriculum, filename, majorName)) {
                    vector<Course> courseList;
                    curriculum.loadDegreePlan(filename, courseList, majorName);

                    int track;
                    cout << "\nSelect track:\n"
                        << "[1] 2-Year Track\n"
                        << "[2] 3-Year Track\n\n"
                        << "Enter your choice: ";

                    cin >> track;
                    advisor.validateInput(track, 1, 2);

                    curriculum.displayDegreePlanBySemester(courseList, track);
                }
                break;
            }
            case 2:
            {
                string filename, majorName;
                if (selectDegreePlan(advisor, curriculum, filename, majorName)) {
                    curriculum.addCourseToPlan(filename, majorName);
                }
                break;
            }
            case 3:
            {
                string filename, majorName;
                if (selectDegreePlan(advisor, curriculum, filename, majorName)) {
                    curriculum.editCourseInPlan(filename, majorName);
                }
                break;
            }
            case 4:
            {
                string filename, majorName;
                if (selectDegreePlan(advisor, curriculum, filename, majorName)) {
                    curriculum.removeCourseFromPlan(filename, majorName);
                }
                break;
            }
            case 0:
            {
                cout << "Returning to Admin Menu.\n";
                editingCurriculum = false;
                break;
            }
            default:
                break;
            }
        }
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
                 << "[1] Open Curriculum Editor (writes to file & edits the courses the users can see)\n"
                 << "[2] Add Career Pathway (writes to file)\n"
                 << "[3] Add Transfer Option (writes to file)\n"
                 << "[4] Add Alumni Profile (writes to file)\n"
                 << "[5] Delete Career Pathway (writes to file)\n"
                 << "[6] Delete Transfer Option (writes to file)\n"
                 << "[7] Delete Alumni Profile (writes to file)\n"
                 << "[8] Open User Menu (read-only)\n"
                 << "[0] Logout\n\n"
                 << "Enter your choice: ";

            cin >> command;
            advisor.validateInput(command, 0, 8);

            switch (command)
            {
            case 1:
            {
                // Curriculum advising edits go here.
                runCurriculumEditor(advisor);
                break;
            }
            case 2:
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
            case 3:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);
                options.setTransfer(selectedMajor);
                options.addTransferOption();
                cout << "Transfer option saved successfully.\n";
                break;
            }
            case 4:
            {
                int majorChoice = promptMajorChoice(advisor);
                string selectedMajor = majorFromChoice(majorChoice);
                career.setAlumni(selectedMajor);
                cout << "Alumni profile saved successfully.\n";
                break;
            }
            case 5:
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
            case 6:
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
            case 7:
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
            case 8:
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

    cout << "\nThank you for using the BMCC Advising App." << endl
         << "Wishing you success in your academic journey and future career." << endl
         << "Cheer!" << endl;

    return 0;
}
