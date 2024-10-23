#include <codecvt>
#include <string>
#include <utility>
#include <iostream>
#include "./localization.h"

Table Language::messageTable;

Language::Language(LANG language):
    sLocalePreference(),
    sLocaleResource() {
    setLanguage(language);
}
void Language::setLanguage(LANG language) {
    switch (language) {
        case LANG::ENGLISH: {
            sLocalePreference = "en_US.UTF-8";
            sLocaleResource = "resource_eng.lang";
            break;
        }
        case LANG::GERMAN: {
            //  sLocalePreference = "De_DE";
            sLocalePreference = "de_DE.UTF-8";
            sLocaleResource = "resource_ger.lang";
            break;
        }
        default: {
            LoadLocalePreference();
            break;
        }
    }
    LoadResourceFile();
}

std::string Language::getLanguage() {
    return sLocalePreference;
}

std::string Language::getResource() {
    return sLocaleResource;
}

void Language::LoadLocalePreference() {
    std::string sIndex;
    std::string sPreferredLocale;
    std::ifstream file("localization.cfg");
    if (file.is_open()) {
        std::getline(file, sPreferredLocale);
        std::stringstream strStream(sPreferredLocale);
        strStream >> sIndex;
        if (sIndex == "PREFFERED") {
            strStream >> sLocalePreference >> sLocaleResource;
        } else {
            sLocalePreference = "en_US.UTF-8";
            sLocaleResource = "resource_eng.lang";
        }
    }
    file.close();
    return;
}

void Language::LoadResourceFile() {
    messageTable.clear();
    std::locale loc;
    std::wstring sLine;
    std::wstring sKey;
    std::wstring sValue;
    std::string filename;

    //  use this for std::wifstream
    std::string slocale = Language::getLanguage();
    loc = std::locale(std::locale(slocale), new std::codecvt_utf8<wchar_t>);
    std::setlocale(LC_ALL, loc.name().c_str());
    filename = Language::getResource();

    //  use this for std::wcout
    std::locale nLoc = std::locale(slocale);
    std::setlocale(LC_ALL, nLoc.name().c_str());
    std::wcout.imbue(loc);

    std::wifstream file(filename, std::ios::in);
    file.imbue(loc);
    if (file.is_open()) {
        while (!file.eof()) {
            std::getline(file, sLine);

            std::wstringstream strStream(sLine);
            std::getline(strStream, sKey, L'=');
            std::getline(strStream, sValue);
            messageTable.insert(std::make_pair(sKey, sValue));
        }
    }
    file.close();
}

Table& Language::getResourceTable() {
    return messageTable;
}
