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
    Language() = delete;
    static Table& getResourceTable();
    static void setLanguage(LANG language);
    static std::string getLanguage();
 private:
    static std::string sLocalePreference;
    static std::string sLocaleResource;
    static Table messageTable;
    static std::string getResource();
    static void LoadLocalePreference();
    static void LoadResourceFile();
};
