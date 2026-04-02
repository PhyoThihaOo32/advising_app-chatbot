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
        void promptEnterCourses(Curriculum& curriculum, string major);
        void enterCourses(Curriculum& curriculum, string major);
        bool validateCourse(string course);
        bool validateInput(int& input, int min, int max);
        void saveCourses();
        bool hasCompleted(string course);
        vector<string> getCourses();
};
