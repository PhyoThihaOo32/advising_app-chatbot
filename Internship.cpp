// implementation file for Internship class
#include "Internship.h"
#include <fstream>
#include <iostream>

using namespace std;

Internship::Internship() : internshipFile("data/internship_opportunities.txt")
{
    loadInternshipFromFile();
}

string Internship::encode(const string &text)
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

string Internship::decode(const string &text)
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

bool Internship::splitKeyValue(const string &line, string &key, string &value)
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

void Internship::loadInternshipFromFile()
{
    internshipByMajor.clear();

    ifstream file(internshipFile);
    if (!file.is_open())
    {
        return;
    }

    MajorInternshipOpportunities currentMajor;
    string line;

    while (getline(file, line))
    {
        if (line == "===")
        {
            if (!currentMajor.major.empty())
            {
                internshipByMajor.push_back(currentMajor);
            }
            currentMajor = MajorInternshipOpportunities();
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
                internshipByMajor.push_back(currentMajor);
            }

            currentMajor = MajorInternshipOpportunities();
            currentMajor.major = value;
        }
        else if ((key == "opportunity" || key == "internship") && !currentMajor.major.empty())
        {
            currentMajor.opportunities.push_back(value);
        }
    }

    if (!currentMajor.major.empty())
    {
        internshipByMajor.push_back(currentMajor);
    }
}

void Internship::saveInternshipToFile() const
{
    ofstream file(internshipFile);
    for (const MajorInternshipOpportunities &majorEntry : internshipByMajor)
    {
        file << "major\t" << encode(majorEntry.major) << '\n';
        for (const string &opportunity : majorEntry.opportunities)
        {
            file << "opportunity\t" << encode(opportunity) << '\n';
        }
        file << "===\n";
    }
}

MajorInternshipOpportunities *Internship::findMajorInternship(const string &major)
{
    for (MajorInternshipOpportunities &entry : internshipByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

const MajorInternshipOpportunities *Internship::findMajorInternship(const string &major) const
{
    for (const MajorInternshipOpportunities &entry : internshipByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

void Internship::addInternshipOpportunity(const string &major, const string &opportunity)
{
    MajorInternshipOpportunities *majorEntry = findMajorInternship(major);
    if (majorEntry == nullptr)
    {
        MajorInternshipOpportunities newEntry;
        newEntry.major = major;
        newEntry.opportunities.push_back(opportunity);
        internshipByMajor.push_back(newEntry);
    }
    else
    {
        majorEntry->opportunities.push_back(opportunity);
    }

    saveInternshipToFile();
}

void Internship::showInternshipInfo() const
{
    showInternshipInfo("Geographic Information Science (GIS)");
}

void Internship::showInternshipInfo(const string &major) const
{
    cout << "\n============================================\n";
    cout << " INTERNSHIP OPPORTUNITIES\n";
    cout << "============================================\n\n";
    cout << "Major/Program: " << major << "\n\n";

    const MajorInternshipOpportunities *majorEntry = findMajorInternship(major);
    if (majorEntry == nullptr || majorEntry->opportunities.empty())
    {
        cout << "No internship data is available for this major yet.\n\n";
        return;
    }

    for (const string &opportunity : majorEntry->opportunities)
    {
        cout << "- " << opportunity << endl;
    }

    cout << endl;
}

void Internship::showInternshipNumbered(const string &major) const
{
    cout << "\n============================================\n";
    cout << " INTERNSHIP LIST (ADMIN)\n";
    cout << "============================================\n\n";
    cout << "Major/Program: " << major << "\n\n";

    const MajorInternshipOpportunities *majorEntry = findMajorInternship(major);
    if (majorEntry == nullptr || majorEntry->opportunities.empty())
    {
        cout << "No internship data is available for this major yet.\n\n";
        return;
    }

    for (size_t i = 0; i < majorEntry->opportunities.size(); i++)
    {
        cout << i + 1 << ". " << majorEntry->opportunities[i] << endl;
    }

    cout << endl;
}

bool Internship::removeInternshipOpportunity(const string &major, int oneBasedIndex)
{
    if (oneBasedIndex <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < internshipByMajor.size(); i++)
    {
        if (internshipByMajor[i].major == major)
        {
            vector<string> &opportunities = internshipByMajor[i].opportunities;
            if (oneBasedIndex > static_cast<int>(opportunities.size()))
            {
                return false;
            }

            opportunities.erase(opportunities.begin() + (oneBasedIndex - 1));

            if (opportunities.empty())
            {
                internshipByMajor.erase(internshipByMajor.begin() + i);
            }

            saveInternshipToFile();
            return true;
        }
    }

    return false;
}
