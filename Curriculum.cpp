#include "Curriculum.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool isCancelInput(const string& input) {
    return input == "0";
}

/*Curriculum::Curriculum() {
    totalRequiredCredits = 62;
    
    // 1. Open the CSV file
    ifstream file("courses.csv");
    string line;

    // Check if the file actually opened successfully
    if (!file.is_open()) {
        cout << "Error: Could not open courses.csv file!" << endl;
        return;
    }

    // 2. Read and throw away the very first line (the header row)
    getline(file, line);

    // 3. Read the rest of the file line-by-line
    while (getline(file, line)) {
        stringstream ss(line);
        
        string name, code, credStr, major, sem2Str, sem3Str, idStr, prereqStr;
        
        // 4. Chop the line up at the commas
        getline(ss, name, ',');
        getline(ss, code, ',');
        getline(ss, credStr, ',');
        getline(ss, major, ',');
        getline(ss, sem2Str, ',');
        getline(ss, sem3Str, ',');
        
        // Grab the 8th piece of data (the prerequisite!)
        getline(ss, prereqStr, ',');

        // 5. Translate the number strings into actual integers
        int credits = stoi(credStr);
        int sem2Year = stoi(sem2Str);
        int sem3Year = stoi(sem3Str);

        // 6. Package it all into a temporary Course object
        Course tempCourse;
        tempCourse.courseName = name;
        tempCourse.courseCode = code;
        tempCourse.credits = credits;
        tempCourse.major = major;
        tempCourse.semester2Year = sem2Year;
        tempCourse.semester3Year = sem3Year;
        
        // If there is a prerequisite, add it to the vector.
        // If the string is empty, we do nothing, leaving the vector empty!
        if (!prereqStr.empty()) {
            tempCourse.prerequisites.push_back(prereqStr);
        }

        // 7. Push the finished course into your main list!
        gisCourses.push_back(tempCourse);
    }
    
    file.close();
}*/

Curriculum::Curriculum() {
    totalRequiredCredits = 62;

    gisCourses.clear();
    cisCourses.clear();
    cntCourses.clear();
    cscCourses.clear();

    loadDegreePlan("data/gis_degree_plan.csv", gisCourses, "GIS");
    loadDegreePlan("data/cis_degree_plan.csv", cisCourses, "CIS");
    loadDegreePlan("data/cnt_degree_plan.csv", cntCourses, "CNT");
    loadDegreePlan("data/csc_degree_plan.csv", cscCourses, "CSC");
}

bool Curriculum::fileExists(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file.close();
        return true;
    }
    return false;
}

void Curriculum::loadDegreePlan(string filename, vector<Course>& courseList, string majorName) {
    courseList.clear();
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);

        string name, code, credStr, major, sem2Str, sem3Str, prereqStr;

        getline(ss, name, ',');
        getline(ss, code, ',');
        getline(ss, credStr, ',');
        getline(ss, major, ',');
        getline(ss, sem2Str, ',');
        getline(ss, sem3Str, ',');
        getline(ss, prereqStr, ',');

        if (name.empty() || code.empty() || credStr.empty() ||
            major.empty() || sem2Str.empty() || sem3Str.empty()) {
            cout << "Skipping invalid row in " << filename << endl;
            continue;
        }

        Course tempCourse;
        tempCourse.courseName = name;
        tempCourse.courseCode = code;
        tempCourse.credits = stoi(credStr);
        tempCourse.major = major;
        tempCourse.semester2Year = stoi(sem2Str);
        tempCourse.semester3Year = stoi(sem3Str);

        if (!prereqStr.empty()) {
            tempCourse.prerequisites.push_back(prereqStr);
        }

        courseList.push_back(tempCourse);
    }

    file.close();
}

void Curriculum::saveDegreePlan(string filename, vector<Course>& courseList) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << " for saving.\n";
        return;
    }

    file << "course_name,code,credits,major,semester_in_2_year_track,semester_in_3_year_track,prerequisite\n";

    for (int i = 0; i < courseList.size(); i++) {
        file << courseList[i].courseName << ","
            << courseList[i].courseCode << ","
            << courseList[i].credits << ","
            << courseList[i].major << ","
            << courseList[i].semester2Year << ","
            << courseList[i].semester3Year << ",";

        if (!courseList[i].prerequisites.empty()) {
            file << courseList[i].prerequisites[0];
        }

        file << "\n";
    }

    file.close();
}

void Curriculum::displayDegreePlan(const vector<Course>& courseList) {
    if (courseList.empty()) {
        cout << "No courses found in this degree plan.\n";
        return;
    }

    for (int i = 0; i < courseList.size(); i++) {
        cout << "\nCourse #" << i + 1 << endl;
        cout << "Name: " << courseList[i].courseName << endl;
        cout << "Code: " << courseList[i].courseCode << endl;
        cout << "Credits: " << courseList[i].credits << endl;
        cout << "2-Year Semester: " << courseList[i].semester2Year << endl;
        cout << "3-Year Semester: " << courseList[i].semester3Year << endl;

        if (!courseList[i].prerequisites.empty()) {
            cout << "Prerequisite: " << courseList[i].prerequisites[0] << endl;
        }
        else {
            cout << "Prerequisite: None" << endl;
        }
    }
}

void Curriculum::displayDegreePlanBySemester(const vector<Course>& courseList, int track) {
    if (courseList.empty()) {
        cout << "No courses found in this degree plan.\n";
        return;
    }

    // Determine max semester (usually 4, but this makes it flexible)
    int maxSemester = 0;
    for (int i = 0; i < courseList.size(); i++) {
        int sem = (track == 1) ? courseList[i].semester2Year : courseList[i].semester3Year;
        if (sem > maxSemester) {
            maxSemester = sem;
        }
    }

    // Loop through semesters
    for (int sem = 1; sem <= maxSemester; sem++) {
        cout << "\nSEMESTER #" << sem << "\n";
        cout << "======================================================\n";

        bool hasCourses = false;

        for (int i = 0; i < courseList.size(); i++) {
            int courseSem = (track == 1) ? courseList[i].semester2Year : courseList[i].semester3Year;

            if (courseSem == sem) {
                cout << " * " << courseList[i].courseCode
                    << " - " << courseList[i].courseName
                    << " (" << courseList[i].credits << " credits)\n";
                hasCourses = true;
            }
        }

        if (!hasCourses) {
            cout << " (No courses)\n";
        }

        cout << "======================================================\n";
    }
}

void Curriculum::addCourseToPlan(string filename, string majorName) {
    vector<Course>& courseList = getCoursesForMajor(majorName);
    loadDegreePlan(filename, courseList, majorName);

    Course newCourse;
    string input;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Name
    cout << "Enter course name (0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    newCourse.courseName = input;

    // Code
    cout << "Enter course code (0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    newCourse.courseCode = input;

    // Credits
    cout << "Enter credits (0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    newCourse.credits = stoi(input);

    // 2-Year Semester
    cout << "Enter 2-Year semester (0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    newCourse.semester2Year = stoi(input);

    // 3-Year Semester
    cout << "Enter 3-Year semester (0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    newCourse.semester3Year = stoi(input);

    // Prerequisite
    cout << "Enter prerequisite (leave blank for none, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;

    if (!input.empty()) {
        newCourse.prerequisites.push_back(input);
    }

    newCourse.major = majorName;

    courseList.push_back(newCourse);
    saveDegreePlan(filename, courseList);

    cout << "\nCourse added successfully.\n";
}

void Curriculum::editCourseInPlan(string filename, string majorName) {
    vector<Course>& courseList = getCoursesForMajor(majorName);
    loadDegreePlan(filename, courseList, majorName);

    displayCourseListCompact(courseList);

    if (courseList.empty()) return;

    int choice;
    cout << "\nEnter course number to edit (0 to cancel): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Edit canceled.\n";
        return;
    }

    if (choice < 1 || choice > courseList.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    Course& course = courseList[choice - 1];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;

    // Name
    cout << "\nCurrent name: " << course.courseName << endl;
    cout << "Enter new name (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    if (!input.empty()) course.courseName = input;

    // Code
    cout << "\nCurrent code: " << course.courseCode << endl;
    cout << "Enter new code (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    if (!input.empty()) course.courseCode = input;

    // Credits
    cout << "\nCurrent credits: " << course.credits << endl;
    cout << "Enter new credits (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    if (!input.empty()) course.credits = stoi(input);

    // 2-Year Semester
    cout << "\nCurrent 2-Year semester: " << course.semester2Year << endl;
    cout << "Enter new value (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    if (!input.empty()) course.semester2Year = stoi(input);

    // 3-Year Semester
    cout << "\nCurrent 3-Year semester: " << course.semester3Year << endl;
    cout << "Enter new value (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;
    if (!input.empty()) course.semester3Year = stoi(input);

    // Prerequisite
    cout << "\nCurrent prerequisite: ";
    if (!course.prerequisites.empty()) cout << course.prerequisites[0];
    else cout << "None";
    cout << endl;

    cout << "Enter new prerequisite (Enter to keep current, 0 to cancel): ";
    getline(cin, input);
    if (isCancelInput(input)) return;

    if (!input.empty()) {
        course.prerequisites.clear();
        course.prerequisites.push_back(input);
    }

    course.major = majorName;

    saveDegreePlan(filename, courseList);
    cout << "\nCourse updated successfully.\n";
}

void Curriculum::removeCourseFromPlan(string filename, string majorName) {
    vector<Course>& courseList = getCoursesForMajor(majorName);
    loadDegreePlan(filename, courseList, majorName);

    //displayDegreePlan(courseList);
    displayCourseListCompact(courseList);

    if (courseList.empty()) {
        return;
    }

    int choice;
    cout << "\nEnter course number to delete (0 to cancel): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Delete canceled.\n";
        return;
    }

    if (choice < 1 || choice > courseList.size()) {
        cout << "Invalid selection.\n";
        return;
    }

    courseList.erase(courseList.begin() + (choice - 1));
    saveDegreePlan(filename, courseList);

    cout << "Course deleted successfully.\n";
}

void Curriculum::displayCourseListCompact(const vector<Course>& courseList) {
    if (courseList.empty()) {
        cout << "No courses found in this degree plan.\n";
        return;
    }

    for (int i = 0; i < courseList.size(); i++) {
        cout << "[" << i + 1 << "] "
            << courseList[i].courseCode << " - "
            << courseList[i].courseName
            << " (" << courseList[i].credits << " Credits)\n";

        cout << "     2-Year: Semester #" << courseList[i].semester2Year
            << " | 3-Year: Semester #" << courseList[i].semester3Year
            << " | Prerequisite: ";

        if (!courseList[i].prerequisites.empty()) {
            cout << courseList[i].prerequisites[0];
        }
        else {
            cout << "None";
        }

        cout << "\n\n";
    }
}

vector<Course>& Curriculum::getCoursesForMajor(const string& majorName) {
    if (majorName == "GIS") return gisCourses;
    if (majorName == "CIS") return cisCourses;
    if (majorName == "CNT") return cntCourses;
    if (majorName == "CSC") return cscCourses;

    throw invalid_argument("Unknown major: " + majorName);
}

const vector<Course>& Curriculum::getCoursesForMajor(const string& majorName) const {
    if (majorName == "GIS") return gisCourses;
    if (majorName == "CIS") return cisCourses;
    if (majorName == "CNT") return cntCourses;
    if (majorName == "CSC") return cscCourses;

    throw invalid_argument("Unknown major: " + majorName);
}