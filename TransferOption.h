#ifndef TRANSFEROPTION_H
#define TRANSFEROPTION_H

#include <vector>
#include <string>

using namespace std;

struct Transfer
{
    string college;
    vector<string> degree;
    vector<string> activities;
};

struct MajorTransferOption
{
    string major;
    vector<Transfer> options;
};

class TransferOption
{
private:
    Transfer transfer;
    string pendingMajor;
    vector<MajorTransferOption> transferByMajor;
    string transferFile;

    void loadTransferOptionsFromFile();
    void saveTransferOptionsToFile() const;

    static string encode(const string &text);
    static string decode(const string &text);
    static bool splitKeyValue(const string &line, string &key, string &value);
    MajorTransferOption *findMajorTransfer(const string &major);
    const MajorTransferOption *findMajorTransfer(const string &major) const;

public:
    TransferOption();

    // default: create a GIS transfer option interactively
    void setTransfer();

    // create a transfer option for a specific major interactively
    void setTransfer(const string &major);
    void addTransferOption();

    // default: show GIS transfer options
    void displayTransferOption() const;

    // show transfer options for the selected major
    void displayTransferOption(const string &major) const;
    void showTransferOptionNumbered(const string &major) const;
    bool removeTransferOption(const string &major, int oneBasedIndex);
};

#endif
