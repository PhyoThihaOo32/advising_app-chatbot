#include "Advising.h"
#include <iostream>
#include <string>
#include "CourseHistory.h"

using namespace std;

Advising::Advising(){
    
}

void Advising::conversationController() {
    int command;
    cout
    << "======================================================\n"
    << "Hello! I am your virtual advisor. I can help you stay on track for your 62-credit GIS degree.\n"
    << "What can I help you with today?\n" << endl
    << "[1] What classes do I need to take next semester?\n"
    << "[2] How many credits do I still need to graduate?\n"
//    << "[0] Exit program\n"
    << "Enter your choice (1-3)\n";
    cin >> command;

    askForMajor();
    askForTrack();
    askForCourseHistory();
    askForSemester();

    if(command == 1) {
        loadSchedule(command);
    } else if (command == 2) {
        creditsRemaining();
    } else if (command == 3) {
        cout << "Goodbye\n";
    }
}

int Advising::creditsRemaining() {
    cout << "======================================================\n";
    int totalCreditsRemaining = 0;
    
    for (int i = 0; i < curriculum.gisCourses.size(); i++) {
        // ONLY count credits if the course is NOT in the history
        if (!student.getCourseHistory().hasCompleted(curriculum.gisCourses[i].courseCode)) {
            totalCreditsRemaining += curriculum.gisCourses[i].credits;
        }
    }
    cout << "Credits Remaining to Graduate: " << totalCreditsRemaining << endl;
    return 0;
}

void Advising::loadSchedule(int command) {
    cout << "======================================================\n";
    int chosenTrack = student.getTrack();
    int currentSemester = student.getSemester();
    for (int i = 0; i < curriculum.gisCourses.size(); i++) {
        int courseSemester;
        if (chosenTrack == 2) {
            courseSemester = curriculum.gisCourses[i].semester2Year;
        } else {
            courseSemester = curriculum.gisCourses[i].semester3Year;
        }

        if (courseSemester == currentSemester + 1 && !student.getCourseHistory().hasCompleted(curriculum.gisCourses[i].courseCode)) {
            cout << " * " << curriculum.gisCourses[i].courseCode << " " << curriculum.gisCourses[i].courseName
                << " (" << curriculum.gisCourses[i].credits << " credits)" << endl;
        }
    }
}
void Advising::askForMajor() {
    int major;
    cout
    << "======================================================\n"
    << "Select your major:\n"
    << "[1] GIS\n"
    << "[2] CIS (Not Working)\n"
    << "[3] CSC (Not Working)\n"
    << "[4] CIN (Not Working)\n";
    cin >> major;
    student.setMajor(major);
}

void Advising::askForTrack() {
    int track;
    cout
    << "======================================================\n"
    << "To give you the right results, I need to know your current degree plan\n"
    << "Are you following the accelerated 2-year track or the standard 3-year track?\n"
    
    << "[1] 2-Year Track (4 Semesters)\n"
    << "[2] 3-Year Track (5 Semesters)\n";
    cin >> track;
    student.setTrack(track);
}

void Advising::askForCourseHistory() {
    cout << "======================================================\n";
    CourseHistory& history = student.getCourseHistory();
    history.promptEnterCourses(curriculum);
//    CourseHistory history = student.getCourseHistory();
//    if (history.fileExists()) {
//        cout << "A saved course history was found.\n";
//        cout << "[1] Use saved course history\n";
//        cout << "[2] Update course history\n";
//
//        int choice;
//        cin >> choice;
//
//        if (choice == 1) {
//            history.loadCourses();
//        }
//        else if (choice == 2) {
//            history.enterCourses(curriculum);
//        }
//        else {
//            cout << "No course history found.\n";
//            cout << "Would you like to enter the courses you have completed?\n";
//            cout << "[1] Yes\n";
//            cout << "[2] Skip\n";
//
//            int choice;
//            cin >> choice;
//            if (choice == 1) {
//                history.enterCourses(curriculum);
//            }
//        }
//    }
}

void Advising::askForSemester() {
    int semester;
    cout << "======================================================\n"
    << "Got it. Which semester are you currently in?\n";
    cout
    << "[1] Semester 1\n"
    << "[2] Semester 2\n"
    << "[3] Semester 3\n"
    << "[4] Semester 4\n";
    cin >> semester;
    student.setSemester(semester);
}










