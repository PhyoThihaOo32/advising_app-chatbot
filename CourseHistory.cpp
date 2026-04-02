// implementation file for Course History class

#include "CourseHistory.h"
#include <iostream>
#include <fstream>

using namespace std;

CourseHistory::CourseHistory() {
    filename = "completed_courses.txt";
};

bool CourseHistory::validateInput(int& input, int min, int max) {
    bool valid = false;
    while (!valid) {
        // Check if the input is within the valid range
        if (input >= min and input <= max) {
            valid = true;
        }
        else {
            cout << "Invalid input. Please enter a number between ("
                << min << "-" << max << "): ";
            cin >> input;
        }
    }
    return valid;
};

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
        cout << "Would you like to enter your completed courses?\n";
        cout << "[1] Yes\n" << "[2] No\n";
        
        int choice;
        cin >> choice;
        validateInput(choice, 1, 2);

        if (choice == 1) {
            enterCourses(curriculum, major); // Hand off the major here
        }
        return;
    }

    ifstream file(filename);
    file.seekg(0, ios::end);

    if (file.tellg() == 0) {
        cout << "Course history file is empty. Please enter your completed courses.\n";
        enterCourses(curriculum, major); // Hand off the major here
        return;
    }
    file.close();

    cout << "Saved course history detected.\n" << endl;
    cout << "[1] Use saved courses\n" << "[2] Update course history\n\nChoice: ";

    int choice;
    cin >> choice;
    validateInput(choice, 1, 2);

    if (choice == 1) {
        loadCourses();
    }
    else if (choice == 2) {
        completedCourses.clear();
        enterCourses(curriculum, major); // Hand off the major here
    }
}

bool CourseHistory::validateCourse(string course) {
    bool valid = true;
    if (course.length() != 7)
        valid = false;

    return valid;
}

//void CourseHistory::enterCourses(Curriculum& curriculum) {
//    cout << "\n--- Quick History Setup ---\n";
//    cout << "Type '1' for Yes (Completed) or '0' for No (Not Taken)\n\n";
//
//    for (int i = 0; i < curriculum.gisCourses.size(); i++) {
//        int response;
//        cout << "Did you finish " << curriculum.gisCourses[i].courseCode
//            << " - [" << curriculum.gisCourses[i].courseName << "]? [1=Yes, 0=No]: ";
//
//        cin >> response;
//        validateInput(response, 0, 1); // input, smallest choice, largest choice
//
//        if (response == 1) {
//            completedCourses.push_back(curriculum.gisCourses[i].courseCode);
//            cout << ">> Recorded.\n";
//        }
//        else {
//            cout << "Invalid input. Please enter '1' for Yes or '0' for No.\n";
//        }
//    }
//
//    saveCourses();
//    cout << "\nAll done! Your history is saved.\n";
//}
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

