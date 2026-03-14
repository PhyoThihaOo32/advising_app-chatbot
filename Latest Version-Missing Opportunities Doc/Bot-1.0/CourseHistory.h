#pragma once
#include "Curriculum.h"

class CourseHistory {
    private:
        string filename;
        vector<string> completedCourses;
    public:
        CourseHistory();
        bool fileExists();
        void loadCourses();
        void promptEnterCourses(Curriculum& curriculum);
        void enterCourses(Curriculum& curriculum);
        bool validateCourse(string course);
        void saveCourses();
        bool hasCompleted(string course);
        vector<string> getCourses();
};
