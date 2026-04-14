// implementation file for Research class
#include "Research.h"
#include <fstream>
#include <iostream>

using namespace std;

Research::Research() : researchFile("data/research_opportunities.txt")
{
    loadResearchFromFile();
}

string Research::encode(const string &text)
{
    string encoded;
    for (char c : text)
    {
        if (c == '\\')
        {
            encoded += "\\\\";
        }
        else if (c == '\n')
        {
            encoded += "\\n";
        }
        else
        {
            encoded += c;
        }
    }
    return encoded;
}

string Research::decode(const string &text)
{
    string decoded;
    bool escapeMode = false;

    for (char c : text)
    {
        if (escapeMode)
        {
            if (c == 'n')
            {
                decoded += '\n';
            }
            else
            {
                decoded += c;
            }
            escapeMode = false;
        }
        else if (c == '\\')
        {
            escapeMode = true;
        }
        else
        {
            decoded += c;
        }
    }

    if (escapeMode)
    {
        decoded += '\\';
    }

    return decoded;
}

bool Research::splitKeyValue(const string &line, string &key, string &value)
{
    size_t delimiter = line.find('\t');
    size_t offset = 1;

    if (delimiter == string::npos)
    {
        delimiter = line.find("\\t");
        offset = 2;
    }

    if (delimiter == string::npos)
    {
        delimiter = line.find('|');
        offset = 1;
    }

    if (delimiter == string::npos)
    {
        return false;
    }

    key = line.substr(0, delimiter);
    value = decode(line.substr(delimiter + offset));
    return true;
}

void Research::loadResearchFromFile()
{
    researchByMajor.clear();

    ifstream file(researchFile);
    if (!file.is_open())
    {
        return;
    }

    MajorResearchOpportunities currentMajor;
    string line;

    while (getline(file, line))
    {
        if (line == "===")
        {
            if (!currentMajor.major.empty())
            {
                researchByMajor.push_back(currentMajor);
            }
            currentMajor = MajorResearchOpportunities();
            continue;
        }

        if (line.empty())
        {
            continue;
        }

        string key;
        string value;
        if (!splitKeyValue(line, key, value))
        {
            continue;
        }

        if (key == "major")
        {
            if (!currentMajor.major.empty())
            {
                researchByMajor.push_back(currentMajor);
            }

            currentMajor = MajorResearchOpportunities();
            currentMajor.major = value;
        }
        else if ((key == "opportunity" || key == "research") && !currentMajor.major.empty())
        {
            currentMajor.opportunities.push_back(value);
        }
    }

    if (!currentMajor.major.empty())
    {
        researchByMajor.push_back(currentMajor);
    }
}

void Research::saveResearchToFile() const
{
    ofstream file(researchFile);
    for (const MajorResearchOpportunities &majorEntry : researchByMajor)
    {
        file << "major\t" << encode(majorEntry.major) << '\n';
        for (const string &opportunity : majorEntry.opportunities)
        {
            file << "opportunity\t" << encode(opportunity) << '\n';
        }
        file << "===\n";
    }
}

MajorResearchOpportunities *Research::findMajorResearch(const string &major)
{
    for (MajorResearchOpportunities &entry : researchByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

const MajorResearchOpportunities *Research::findMajorResearch(const string &major) const
{
    for (const MajorResearchOpportunities &entry : researchByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

void Research::addResearchOpportunity(const string &major, const string &opportunity)
{
    MajorResearchOpportunities *majorEntry = findMajorResearch(major);
    if (majorEntry == nullptr)
    {
        MajorResearchOpportunities newEntry;
        newEntry.major = major;
        newEntry.opportunities.push_back(opportunity);
        researchByMajor.push_back(newEntry);
    }
    else
    {
        majorEntry->opportunities.push_back(opportunity);
    }

    saveResearchToFile();
}

void Research::showResearchInfo() const
{
    showResearchInfo("Geographic Information Science (GIS)");
}

void Research::showResearchInfo(const string &major) const
{
    cout << "\n============================================\n";
    cout << " RESEARCH OPPORTUNITIES\n";
    cout << "============================================\n\n";
    cout << "Major/Program: " << major << "\n\n";

    const MajorResearchOpportunities *majorEntry = findMajorResearch(major);
    if (majorEntry == nullptr || majorEntry->opportunities.empty())
    {
        cout << "No research data is available for this major yet.\n\n";
        return;
    }

    for (const string &opportunity : majorEntry->opportunities)
    {
        cout << "- " << opportunity << endl;
    }

    cout << endl;
}

void Research::showResearchNumbered(const string &major) const
{
    cout << "\n============================================\n";
    cout << " RESEARCH LIST (ADMIN)\n";
    cout << "============================================\n\n";
    cout << "Major/Program: " << major << "\n\n";

    const MajorResearchOpportunities *majorEntry = findMajorResearch(major);
    if (majorEntry == nullptr || majorEntry->opportunities.empty())
    {
        cout << "No research data is available for this major yet.\n\n";
        return;
    }

    for (size_t i = 0; i < majorEntry->opportunities.size(); i++)
    {
        cout << i + 1 << ". " << majorEntry->opportunities[i] << endl;
    }

    cout << endl;
}

bool Research::removeResearchOpportunity(const string &major, int oneBasedIndex)
{
    if (oneBasedIndex <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < researchByMajor.size(); i++)
    {
        if (researchByMajor[i].major == major)
        {
            vector<string> &opportunities = researchByMajor[i].opportunities;
            if (oneBasedIndex > static_cast<int>(opportunities.size()))
            {
                return false;
            }

            opportunities.erase(opportunities.begin() + (oneBasedIndex - 1));

            if (opportunities.empty())
            {
                researchByMajor.erase(researchByMajor.begin() + i);
            }

            saveResearchToFile();
            return true;
        }
    }

    return false;
}
