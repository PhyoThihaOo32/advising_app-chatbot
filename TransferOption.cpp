#include "TransferOption.h"
#include <fstream>
#include <iostream>

using namespace std;

TransferOption::TransferOption() : pendingMajor("Geographic Information Science (GIS)"), transferFile("transfer_options.txt")
{
    loadTransferOptionsFromFile();
}

string TransferOption::encode(const string &text)
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

string TransferOption::decode(const string &text)
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

bool TransferOption::splitKeyValue(const string &line, string &key, string &value)
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

void TransferOption::loadTransferOptionsFromFile()
{
    transferByMajor.clear();

    ifstream file(transferFile);
    if (!file.is_open())
    {
        return;
    }

    MajorTransferOption currentMajor;
    Transfer current;
    string line;

    while (getline(file, line))
    {
        if (line == "===")
        {
            if (!current.college.empty())
            {
                currentMajor.options.push_back(current);
                current = Transfer();
            }

            if (!currentMajor.major.empty())
            {
                transferByMajor.push_back(currentMajor);
            }
            currentMajor = MajorTransferOption();
            continue;
        }

        if (line == "---")
        {
            if (!currentMajor.major.empty() && !current.college.empty())
            {
                currentMajor.options.push_back(current);
            }
            current = Transfer();
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

        if (key == "college")
        {
            if (!current.college.empty())
            {
                currentMajor.options.push_back(current);
                current = Transfer();
            }

            current.college = value;
        }
        else if (key == "major")
        {
            if (!currentMajor.major.empty() && currentMajor.major != value)
            {
                if (!current.college.empty())
                {
                    currentMajor.options.push_back(current);
                    current = Transfer();
                }
                transferByMajor.push_back(currentMajor);
                currentMajor = MajorTransferOption();
            }
            currentMajor.major = value;
        }
        else if (key == "degree")
        {
            current.degree.push_back(value);
        }
        else if (key == "activity")
        {
            current.activities.push_back(value);
        }
    }

    if (!current.college.empty())
    {
        currentMajor.options.push_back(current);
    }

    if (!currentMajor.major.empty())
    {
        transferByMajor.push_back(currentMajor);
    }
}

void TransferOption::saveTransferOptionsToFile() const
{
    ofstream file(transferFile);
    for (const MajorTransferOption &majorEntry : transferByMajor)
    {
        file << "major\t" << encode(majorEntry.major) << '\n';

        for (const Transfer &t : majorEntry.options)
        {
            file << "college\t" << encode(t.college) << '\n';

            for (const string &d : t.degree)
            {
                file << "degree\t" << encode(d) << '\n';
            }

            for (const string &a : t.activities)
            {
                file << "activity\t" << encode(a) << '\n';
            }

            file << "---\n";
        }

        file << "===\n";
    }
}

void TransferOption::setTransfer()
{
    setTransfer("Geographic Information Science (GIS)");
}

void TransferOption::setTransfer(const string &major)
{
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    pendingMajor = major;

    cout << "Enter College Name: ";
    getline(cin, transfer.college);

    int n;

    cout << "How many degree programs? ";
    cin >> n;
    cin.ignore();

    transfer.degree.clear();

    for (int i = 0; i < n; i++)
    {
        string d;
        cout << "Degree " << i + 1 << ": ";
        getline(cin, d);
        transfer.degree.push_back(d);
    }

    cout << "How many activities? ";
    cin >> n;
    cin.ignore();

    transfer.activities.clear();

    for (int i = 0; i < n; i++)
    {
        string a;
        cout << "Activity " << i + 1 << ": ";
        getline(cin, a);
        transfer.activities.push_back(a);
    }
}

MajorTransferOption *TransferOption::findMajorTransfer(const string &major)
{
    for (MajorTransferOption &entry : transferByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

const MajorTransferOption *TransferOption::findMajorTransfer(const string &major) const
{
    for (const MajorTransferOption &entry : transferByMajor)
    {
        if (entry.major == major)
        {
            return &entry;
        }
    }
    return nullptr;
}

void TransferOption::addTransferOption()
{
    MajorTransferOption *majorEntry = findMajorTransfer(pendingMajor);
    if (majorEntry == nullptr)
    {
        MajorTransferOption newEntry;
        newEntry.major = pendingMajor;
        newEntry.options.push_back(transfer);
        transferByMajor.push_back(newEntry);
    }
    else
    {
        majorEntry->options.push_back(transfer);
    }

    saveTransferOptionsToFile();
}

void TransferOption::displayTransferOption() const
{
    displayTransferOption("Geographic Information Science (GIS)");
}

void TransferOption::displayTransferOption(const string &major) const
{
    cout << "\n================================\n";
    cout << "Transfer Options: " << major << endl;
    cout << "================================\n";

    const MajorTransferOption *majorEntry = findMajorTransfer(major);
    if (majorEntry == nullptr || majorEntry->options.empty())
    {
        cout << "\nNo transfer option data is available for this major yet.\n\n";
        return;
    }

    for (const Transfer &t : majorEntry->options)
    {
        cout << "\nTransfer College: " << t.college << endl;

        cout << "\nAvailable Degrees:\n";
        for (const string &d : t.degree)
        {
            cout << "- " << d << endl;
        }

        cout << "\nStudent Activities:\n";
        for (const string &a : t.activities)
        {
            cout << "- " << a << endl;
        }

        cout << endl;
    }
}

void TransferOption::showTransferOptionNumbered(const string &major) const
{
    cout << "\n=========================================\n";
    cout << "TRANSFER OPTION LIST (ADMIN): " << major << endl;
    cout << "=========================================\n\n";

    const MajorTransferOption *majorEntry = findMajorTransfer(major);
    if (majorEntry == nullptr || majorEntry->options.empty())
    {
        cout << "No transfer option data is available for this major yet.\n\n";
        return;
    }

    for (size_t i = 0; i < majorEntry->options.size(); i++)
    {
        cout << i + 1 << ". " << majorEntry->options[i].college << endl;
    }

    cout << endl;
}

bool TransferOption::removeTransferOption(const string &major, int oneBasedIndex)
{
    if (oneBasedIndex <= 0)
    {
        return false;
    }

    for (size_t i = 0; i < transferByMajor.size(); i++)
    {
        if (transferByMajor[i].major == major)
        {
            vector<Transfer> &options = transferByMajor[i].options;
            if (oneBasedIndex > static_cast<int>(options.size()))
            {
                return false;
            }

            options.erase(options.begin() + (oneBasedIndex - 1));

            if (options.empty())
            {
                transferByMajor.erase(transferByMajor.begin() + i);
            }

            saveTransferOptionsToFile();
            return true;
        }
    }

    return false;
}
