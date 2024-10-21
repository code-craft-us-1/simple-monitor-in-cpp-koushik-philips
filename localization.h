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
    static LANG choice;
    Language() = delete;
    static void setLanguage(int lang);
    static LANG getLanguage();
    static Table& getResourceTable();
 private:
    static Table messageTable;
    static void LoadResourceFile();
    
};
