#pragma once
#include <vector>
#include <string>

using namespace std;

struct Course {
    string courseName;
    string courseCode;
    int credits;
    string major;
    int semester2Year;
    int semester3Year;
    vector<string> prerequisites;
};

class Curriculum{
    public:
        vector<Course> gisCourses;
        vector<Course> cisCourses;
        vector<Course> cntCourses;
        vector<Course> cscCourses;
        int totalRequiredCredits;
        Curriculum();
        bool fileExists(string filename);
        void saveDegreePlan(string filename, vector<Course>& courseList);
        void loadDegreePlan(string filename, vector<Course>& courseList, string majorName);
        void addCourseToPlan(string filename, string majorName);
        void editCourseInPlan(string filename, string majorName);
        void removeCourseFromPlan(string filename, string majorName);
        void displayDegreePlan(const vector<Course>& courseList);
        void displayDegreePlanBySemester(const vector<Course>& courseList, int track);
        void displayCourseListCompact(const vector<Course>& courseList);
        vector<Course>& getCoursesForMajor(const string& majorName);
        const vector<Course>& getCoursesForMajor(const string& majorName) const;
};