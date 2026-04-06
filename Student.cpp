#include "Student.h"
#include <iostream>

Student::Student() {
    currentMajor = "GIS";
}

//void Student::setMajor(int major) {
//    if(major == 1) {
//        currentMajor = "GIS";
//    }
//}

void Student::setMajor(int major) {
    if (major == 1) currentMajor = "GIS";
    else if (major == 2) currentMajor = "CIS";
    else if (major == 3) currentMajor = "CSC";
    else if (major == 4) currentMajor = "CNT";
}
void Student::setTrack(int track) {
    // Store exactly what the user picked (1 or 2)
    // so it matches the logic in Advising.cpp
    if(track == 1 || track == 2) {
        chosenTrack = track;
    } else {
        cout << "Invalid Track\n";
    }
}
void Student::setSemester(int semester) {
    currentSemester = semester;
}

string Student::getMajor() const {
    return currentMajor;
}

int Student::getTrack() const {
    return chosenTrack;
}

int Student::getSemester() const {
    return currentSemester;
}

CourseHistory& Student::getCourseHistory() {
    return history;
};

int Student::getCredits() const {
    return completedCredits;
}

