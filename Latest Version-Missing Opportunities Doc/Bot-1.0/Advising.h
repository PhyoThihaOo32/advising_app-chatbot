#pragma once
#include "Student.h"
#include "Curriculum.h"
#include "CourseHistory.h"

class Advising {
    private:
        Student student;
        Curriculum curriculum;
    public:
        void conversationController();
        void askForMajor();
        void askForTrack();
        void askForCourseHistory();
        void askForSemester();
        void adviseOnClasses();
        void calculateCredits();
        void showcareerPathway();
        void showinterResearchopp();
        void loadSchedule(int command);
        int creditsRemaining();
        Advising();
};
