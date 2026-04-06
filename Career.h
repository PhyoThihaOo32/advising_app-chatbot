// specification file for careerPath

#ifndef CAREER_H
#define CAREER_H

#include <vector>
#include <string>

using namespace std;

struct Alumni
{
    string name;
    string background;
    string update;
    string linkedin;
    string advice;
};

struct MajorCareerPath
{
    string major;
    vector<string> careers;
};

struct MajorAlumniProfile
{
    string major;
    vector<Alumni> alumni;
};

class Career
{
private:
    vector<MajorCareerPath> careerByMajor;
    vector<MajorAlumniProfile> alumniByMajor;
    string careerFile;
    string alumniFile;

    void loadCareerFromFile();
    void loadAlumniFromFile();
    void saveCareerToFile() const;
    void saveAlumniToFile() const;

    static string encode(const string &text);
    static string decode(const string &text);
    static bool splitKeyValue(const string &line, string &key, string &value);
    MajorCareerPath *findMajorCareer(const string &major);
    const MajorCareerPath *findMajorCareer(const string &major) const;
    MajorAlumniProfile *findMajorAlumni(const string &major);
    const MajorAlumniProfile *findMajorAlumni(const string &major) const;

public:
    // default constructor loads career and alumni information from data files
    Career();

    // add a new career path under GIS and persist it
    void setCareer(string);

    // add a career path for a specific major and persist it
    void setCareer(const string &major, const string &careerPath);

    // show GIS career paths
    void showCareer() const;

    // show career paths for a specific major
    void showCareer(const string &major) const;
    void showCareerNumbered(const string &major) const;
    bool removeCareer(const string &major, int oneBasedIndex);

    // add a new alumni profile and persist it to file
    void setAlumni();

    // add a new alumni profile for a specific major and persist it to file
    void setAlumni(const string &major);

    // show current alumni working in GIS
    void showAlumni() const;

    // show alumni for a specific major
    void showAlumni(const string &major) const;
    void showAlumniNumbered(const string &major) const;
    bool removeAlumni(const string &major, int oneBasedIndex);
};

#endif
