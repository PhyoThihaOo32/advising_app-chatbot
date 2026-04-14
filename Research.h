// specification file for Research
#ifndef RESEARCH_H
#define RESEARCH_H

#include <string>
#include <vector>
using namespace std;

struct MajorResearchOpportunities
{
    string major;
    vector<string> opportunities;
};

class Research
{
private:
    vector<MajorResearchOpportunities> researchByMajor;
    string researchFile;

    static string encode(const string &text);
    static string decode(const string &text);
    static bool splitKeyValue(const string &line, string &key, string &value);

    void loadResearchFromFile();
    void saveResearchToFile() const;

    MajorResearchOpportunities *findMajorResearch(const string &major);
    const MajorResearchOpportunities *findMajorResearch(const string &major) const;

public:
    Research();

    void addResearchOpportunity(const string &major, const string &opportunity);
    void showResearchInfo(const string &major) const;
    void showResearchNumbered(const string &major) const;
    bool removeResearchOpportunity(const string &major, int oneBasedIndex);

    // Backward-compatible default display
    void showResearchInfo() const;
};

#endif
