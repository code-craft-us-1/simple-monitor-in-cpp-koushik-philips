#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "./temperature.h"
#include "./pulserate.h"
#include "./spo2.h"

using MessageID = std::wstring;
using LocalizedMessage = std::wstring;
using Table = std::map<MessageID, LocalizedMessage>;

enum class LANG {
    LANG_eng,
    LANG_german,
    LANG_COUNT
};

struct Language {
    explicit Language(LANG language);
    Table& getResourceTable();
    void setLanguage(LANG language);
    std::string getLanguage();
 private:
    std::string sLocalePreference;
    std::string sLocaleResource;
    static Table messageTable;
    std::string getResource();
    void LoadLocalePreference();
    void LoadResourceFile();
};
