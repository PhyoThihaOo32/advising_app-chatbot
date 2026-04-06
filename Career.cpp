// implementation file for Career class
#include "Career.h"
#include <fstream>
#include <iostream>

using namespace std;

Career::Career() : careerFile("career_paths.txt"), alumniFile("alumni.txt")
{
    loadCareerFromFile();
    loadAlumniFromFile();
}

string Career::encode(const string &text)
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

string Career::decode(const string &text)
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

bool Career::splitKeyValue(const string &line, string &key, string &value)
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

void Career::loadCareerFromFile()
{
    careerByMajor.clear();

    ifstream file(careerFile);
    if (!file.is_open())
    {
        return;
    }

    MajorCareerPath currentMajor;
    string line;
    while (getline(file, line))
    {
        if (line == "===")
        {
            if (!currentMajor.major.empty())
            {
                careerByMajor.push_back(currentMajor);
            }
            currentMajor = MajorCareerPath();
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
                careerByMajor.push_back(currentMajor);
            }

            currentMajor = MajorCareerPath();
            currentMajor.major = value;
        }
        else if (key == "career" && !currentMajor.major.empty())
        {
            currentMajor.careers.push_back(value);
        }
    }

    if (!currentMajor.major.empty())
    {
        careerByMajor.push_back(currentMajor);
    }
}

void Career::saveCareerToFile() const
{
    ofstream file(careerFile);
    for (const MajorCareerPath &majorEntry : careerByMajor)
    {
        file << "major\t" << encode(majorEntry.major) << '\n';
        for (const string &careerPath : majorEntry.careers)
        {
            file << "career\t" << encode(careerPath) << '\n';
        }
        file << "===\n";
    }
}

MajorCareerPath *Career::findMajorCareer(const string &major)
{
    for (MajorCareerPath &entry : careerByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

const MajorCareerPath *Career::findMajorCareer(const string &major) const
{
    for (const MajorCareerPath &entry : careerByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

MajorAlumniProfile *Career::findMajorAlumni(const string &major)
{
    for (MajorAlumniProfile &entry : alumniByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

const MajorAlumniProfile *Career::findMajorAlumni(const string &major) const
{
    for (const MajorAlumniProfile &entry : alumniByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

void Career::loadAlumniFromFile()
{
    alumniByMajor.clear();

    ifstream file(alumniFile);
    if (!file.is_open())
    {
        return;
    }

    MajorAlumniProfile currentMajor;
    Alumni current;
    bool hasAlumniData = false;
    string line;

    while (getline(file, line))
    {
        if (line == "===")
        {
            if (hasAlumniData && !currentMajor.major.empty())
            {
                currentMajor.alumni.push_back(current);
                current = Alumni();
                hasAlumniData = false;
            }

            if (!currentMajor.major.empty())
            {
                alumniByMajor.push_back(currentMajor);
            }
            currentMajor = MajorAlumniProfile();
            continue;
        }

        if (line == "---")
        {
            if (hasAlumniData && !currentMajor.major.empty())
            {
                currentMajor.alumni.push_back(current);
            }
            current = Alumni();
            hasAlumniData = false;
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

        if (key == "name")
        {
            current.name = value;
            hasAlumniData = true;
        }
        else if (key == "major")
        {
            if (hasAlumniData && !currentMajor.major.empty())
            {
                currentMajor.alumni.push_back(current);
                current = Alumni();
                hasAlumniData = false;
            }

            if (!currentMajor.major.empty() && currentMajor.major != value)
            {
                alumniByMajor.push_back(currentMajor);
                currentMajor = MajorAlumniProfile();
            }

            currentMajor.major = value;
        }
        else if (key == "background")
        {
            current.background = value;
            hasAlumniData = true;
        }
        else if (key == "update")
        {
            current.update = value;
            hasAlumniData = true;
        }
        else if (key == "linkedin")
        {
            current.linkedin = value;
            hasAlumniData = true;
        }
        else if (key == "advice")
        {
            current.advice = value;
            hasAlumniData = true;
        }
    }

    if (hasAlumniData && !currentMajor.major.empty())
    {
        currentMajor.alumni.push_back(current);
    }

    if (!currentMajor.major.empty())
    {
        alumniByMajor.push_back(currentMajor);
    }
}

void Career::saveAlumniToFile() const
{
    ofstream file(alumniFile);
    for (const MajorAlumniProfile &majorEntry : alumniByMajor)
    {
        file << "major\t" << encode(majorEntry.major) << '\n';

        for (const Alumni &a : majorEntry.alumni)
        {
            file << "name\t" << encode(a.name) << '\n';
            file << "background\t" << encode(a.background) << '\n';
            file << "update\t" << encode(a.update) << '\n';
            file << "linkedin\t" << encode(a.linkedin) << '\n';
            file << "advice\t" << encode(a.advice) << '\n';
            file << "---\n";
        }

        file << "===\n";
    }
}

// add new career pathway
void Career::setCareer(string c)
{
    setCareer("Geographic Information Science (GIS)", c);
}

void Career::setCareer(const string &major, const string &careerPath)
{
    MajorCareerPath *majorEntry = findMajorCareer(major);
    if (majorEntry == nullptr)
    {
        MajorCareerPath newMajor;
        newMajor.major = major;
        newMajor.careers.push_back(careerPath);
        careerByMajor.push_back(newMajor);
    }
    else
    {
        majorEntry->careers.push_back(careerPath);
    }

    saveCareerToFile();
}

// display GIS career paths
void Career::showCareer() const
{
    showCareer("Geographic Information Science (GIS)");
}

// display career paths by major
void Career::showCareer(const string &major) const
{
    cout << "\n========================\n";
    cout << "     CAREER PATHWAYS\n";
    cout << "========================\n\n";

    cout << "Major/Program: " << major << "\n\n";

    const MajorCareerPath *majorEntry = findMajorCareer(major);
    if (majorEntry == nullptr || majorEntry->careers.empty())
    {
        cout << "No career pathway data is available for this major yet.\n\n";
        return;
    }

    for (const string &careerPath : majorEntry->careers)
    {
        cout << "- " << careerPath << endl;
    }

    cout << endl;
}

void Career::showCareerNumbered(const string &major) const
{
    cout << "\n========================\n";
    cout << " CAREER PATHWAYS (ADMIN)\n";
    cout << "========================\n\n";

    cout << "Major/Program: " << major << "\n\n";

    const MajorCareerPath *majorEntry = findMajorCareer(major);
    if (majorEntry == nullptr || majorEntry->careers.empty())
    {
        cout << "No career pathway data is available for this major yet.\n\n";
        return;
    }

    for (size_t i = 0; i < majorEntry->careers.size(); i++)
    {
        cout << i + 1 << ". " << majorEntry->careers[i] << endl;
    }

    cout << endl;
}

bool Career::removeCareer(const string &major, int oneBasedIndex)
{
    if (oneBasedIndex <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < careerByMajor.size(); i++)
    {
        if (careerByMajor[i].major == major)
        {
            vector<string> &careers = careerByMajor[i].careers;
            if (oneBasedIndex > static_cast<int>(careers.size()))
            {
                return false;
            }

            careers.erase(careers.begin() + (oneBasedIndex - 1));

            if (careers.empty())
            {
                careerByMajor.erase(careerByMajor.begin() + i);
            }

            saveCareerToFile();
            return true;
        }
    }

    return false;
}

// add alumni interactively
void Career::setAlumni()
{
    setAlumni("Geographic Information Science (GIS)");
}

void Career::setAlumni(const string &major)
{
    Alumni alumnus;
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    cout << "Name: ";
    getline(cin, alumnus.name);

    cout << "Academic Background: ";
    getline(cin, alumnus.background);

    cout << "Update: ";
    getline(cin, alumnus.update);

    cout << "LinkedIn: ";
    getline(cin, alumnus.linkedin);

    cout << "Advice: ";
    getline(cin, alumnus.advice);

    MajorAlumniProfile *majorEntry = findMajorAlumni(major);
    if (majorEntry == nullptr)
    {
        MajorAlumniProfile newEntry;
        newEntry.major = major;
        newEntry.alumni.push_back(alumnus);
        alumniByMajor.push_back(newEntry);
    }
    else
    {
        majorEntry->alumni.push_back(alumnus);
    }

    saveAlumniToFile();
}

// display GIS alumni
void Career::showAlumni() const
{
    showAlumni("Geographic Information Science (GIS)");
}

// display alumni by major
void Career::showAlumni(const string &major) const
{
    cout << "\n==============================\n";
    cout << "         BMCC ALUMNI\n";
    cout << "==============================\n\n";

    cout << "Major/Program: " << major << "\n\n";

    const MajorAlumniProfile *majorEntry = findMajorAlumni(major);
    if (majorEntry == nullptr || majorEntry->alumni.empty())
    {
        cout << "No alumni data is available for this major yet.\n\n";
        return;
    }

    for (const Alumni &a : majorEntry->alumni)
    {
        cout << "---------------------------------\n";
        cout << "Name: " << a.name << endl;
        cout << "Academic Background:\n"
             << a.background << endl;
        cout << "Current Role:\n"
             << a.update << endl;
        cout << "LinkedIn: " << a.linkedin << endl;
        cout << "Advice: " << a.advice << endl;
        cout << endl;
    }
}

void Career::showAlumniNumbered(const string &major) const
{
    cout << "\n========================\n";
    cout << "   ALUMNI LIST (ADMIN)\n";
    cout << "========================\n\n";

    cout << "Major/Program: " << major << "\n\n";

    const MajorAlumniProfile *majorEntry = findMajorAlumni(major);
    if (majorEntry == nullptr || majorEntry->alumni.empty())
    {
        cout << "No alumni data is available for this major yet.\n\n";
        return;
    }

    for (size_t i = 0; i < majorEntry->alumni.size(); i++)
    {
        cout << i + 1 << ". " << majorEntry->alumni[i].name << endl;
    }

    cout << endl;
}

bool Career::removeAlumni(const string &major, int oneBasedIndex)
{
    if (oneBasedIndex <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < alumniByMajor.size(); i++)
    {
        if (alumniByMajor[i].major == major)
        {
            vector<Alumni> &alumni = alumniByMajor[i].alumni;
            if (oneBasedIndex > static_cast<int>(alumni.size()))
            {
                return false;
            }

            alumni.erase(alumni.begin() + (oneBasedIndex - 1));

            if (alumni.empty())
            {
                alumniByMajor.erase(alumniByMajor.begin() + i);
            }

            saveAlumniToFile();
            return true;
        }
    }

    return false;
}
