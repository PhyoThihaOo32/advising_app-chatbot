// implementation file for Course History class

#include "CourseHistory.h"
#include <iostream>
#include <fstream>

using namespace std;

CourseHistory::CourseHistory() {
	filename = "completed_courses.txt";
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

void CourseHistory::promptEnterCourses() {

    cout << "======================================================\n";

    if (!fileExists()) {
        cout << "No saved course history found.\n";
        cout << "Would you like to enter your completed courses?\n";
        cout << "[1] Yes\n";
        cout << "[2] No\n";

        int choice;
        cin >> choice;

        if (choice == 1) {
            enterCourses();
        }

        return;
    }

    // File exists — check if empty
    ifstream file(filename);
    file.seekg(0, ios::end);

    if (file.tellg() == 0) {
        cout << "Course history file is empty.\n";
        cout << "Please enter your completed courses.\n";

        enterCourses();
        return;
    }

    file.close();

    cout << "Saved course history detected.\n";
    cout << "[1] Use saved courses\n";
    cout << "[2] Update course history\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        loadCourses();
    }
    else if (choice == 2) {
        completedCourses.clear();
        enterCourses();
    }
}

bool CourseHistory::validateCourse(string course) {
    bool valid = true;
    if (course.length() != 7)
        valid = false;

    return valid;
}

void CourseHistory::enterCourses() {
    int count;
    string course;

    cout << "How many courses have you completed? ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "Enter course " << i + 1 << ": ";
        cin >> course;

        completedCourses.push_back(course);
    }

    saveCourses();
};

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