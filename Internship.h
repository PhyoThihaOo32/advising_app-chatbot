// specification file for Internship
#ifndef INTERNSHIP_H
#define INTERNSHIP_H

#include <string>
#include <vector>
using namespace std;

struct MajorInternshipOpportunities
{
    string major;
    vector<string> opportunities;
};

class Internship
{
private:
    vector<MajorInternshipOpportunities> internshipByMajor;
    string internshipFile;

    static string encode(const string &text);
    static string decode(const string &text);
    static bool splitKeyValue(const string &line, string &key, string &value);

    void loadInternshipFromFile();
    void saveInternshipToFile() const;

    MajorInternshipOpportunities *findMajorInternship(const string &major);
    const MajorInternshipOpportunities *findMajorInternship(const string &major) const;

public:
    Internship();

    void addInternshipOpportunity(const string &major, const string &opportunity);
    void showInternshipInfo(const string &major) const;
    void showInternshipNumbered(const string &major) const;
    bool removeInternshipOpportunity(const string &major, int oneBasedIndex);

    // Backward-compatible default display
    void showInternshipInfo() const;
};

#endif
