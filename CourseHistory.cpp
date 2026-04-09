// implementation file for Course History class

#include "CourseHistory.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

CourseHistory::CourseHistory() {
	filename = "data/completed_courses.txt";
};

bool CourseHistory::validateInput(int& input, int min, int max) {
    bool valid = false;
    while (!valid) {

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number between ("
                << min << "-" << max << "): ";

            cin >> input;  // force new input here
            continue;
        }

        if (input >= min && input <= max) {
            valid = true;
        }
        else {
            cout << "Invalid input. Please enter a number between ("
                << min << "-" << max << "): ";
            cin >> input;
        }
    }
    return valid;
}

bool CourseHistory::fileExists() {
    ifstream file(filename);

    if (file.is_open()) {
        file.close();
        return true;
    }

    return false;
};

void CourseHistory::loadCourses() {
    ifstream file(filename);
    string course;

    while (file >> course) {
        completedCourses.push_back(course);
    }
    file.close();

    cout << "Loaded your saved courses.\n";
};

void CourseHistory::promptEnterCourses(Curriculum& curriculum, string major) {
    cout << "======================================================\n";

    if (!fileExists()) {
        cout << "No saved course history found.\n";
        cout << "Would you like to enter your completed courses?\n\n";
        cout << "[1] Yes\n";
        cout << "[2] No\n";
        cout << "\nEnter your choice: ";

        int choice;
        cin >> choice;
        validateInput(choice, 1, 2);

        if (choice == 1) {
            enterCourses(curriculum, major);
        }

        return;
    }

    ifstream file(filename);
    file.seekg(0, ios::end);

    if (file.tellg() == 0) {
        file.close();

        cout << "Your saved course history file is empty, ";
        cout << "would you like to enter your completed courses?\n\n";
        cout << "[1] Yes\n";
        cout << "[2] No\n";
        cout << "\nEnter your choice: ";

        int choice;
        cin >> choice;
        validateInput(choice, 1, 2);

        if (choice == 1) {
            enterCourses(curriculum, major);
        }

        return;
    }

    file.close();

    cout << "Saved course history detected.\n\n";
    cout << "[1] Use saved courses\n";
    cout << "[2] Update course history\n";
    cout << "[3] Ignore saved history\n";
    cout << "\nEnter your choice: ";

    int choice;
    cin >> choice;
    validateInput(choice, 1, 3);

    if (choice == 1) {
        loadCourses();
    }
    else if (choice == 2) {
        completedCourses.clear();
        enterCourses(curriculum, major);
    }
    else if (choice == 3) {
        cout << "Ignoring saved course history.\n";
    }
}

bool CourseHistory::validateCourse(string course) {
    bool valid = true;
    if (course.length() != 7)
        valid = false;

    return valid;
}

// Update the function signature in .h and .cpp to include 'string major'
void CourseHistory::enterCourses(Curriculum& curriculum, string major) {
    cout << "\n--- Quick History Setup ---\n";
    for (int i = 0; i < curriculum.gisCourses.size(); i++) {
        // ONLY ask if the course belongs to the student's major
        if (curriculum.gisCourses[i].major == major) {
            int response;
            cout << "Did you finish " << curriculum.gisCourses[i].courseCode
                << " - [" << curriculum.gisCourses[i].courseName << "]? [1=Yes, 0=No]: ";
            
            cin >> response;
            validateInput(response, 0, 1);

            if (response == 1) {
                completedCourses.push_back(curriculum.gisCourses[i].courseCode);
            }
        }
    }
    saveCourses();
}

void CourseHistory::saveCourses() {
    ofstream file(filename);

    for (int i = 0; i < completedCourses.size(); i++) {
        file << completedCourses[i] << endl;
    }

    file.close();
    cout << "Course history saved.\n";
};

bool CourseHistory::hasCompleted(string course) {
    for (int i = 0; i < completedCourses.size(); i++) {
        if (completedCourses[i] == course) {
            return true;
        }
    }
    return false;
};

vector<string> CourseHistory::getCourses() {
    return completedCourses;
};

