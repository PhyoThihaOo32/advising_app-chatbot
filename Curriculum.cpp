#include "Curriculum.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Curriculum::Curriculum() {
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
}
