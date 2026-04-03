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
        int totalRequiredCredits;
        Curriculum();
};
