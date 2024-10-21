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
        case LANG::LANG_eng: {
            sLocalePreference = "en_US.UTF-8";
            sLocaleResource = "resource_eng.lang";
            break;
        }
        case LANG::LANG_german: {
            sLocalePreference = "De_DE";
            sLocaleResource = "resource_ger.lang";
            break;
        }
        default: {
            sLocalePreference = "en_US.UTF-8";
            sLocaleResource = "resource_eng.lang";
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
    std::ifstream file("localization.cfg");
    std::getline(file, sLocalePreference);
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

    std::string slocale = Language::getLanguage();
    loc = std::locale(std::locale(slocale), new std::codecvt_utf8<wchar_t>);
    std::setlocale(LC_ALL, loc.name().c_str());
    filename = Language::getResource();

   /* std::filesystem::path filePath(filename);
    std::filesystem::path folderPath = std::filesystem::path(__FILE__).remove_filename();
    std::filesystem::path absoluteFilePath = std::filesystem::absolute(folderPath / filePath);*/

    std::wifstream file(filename/*absoluteFilePath*/, std::ios::in);
    file.imbue(loc);
    if (file.is_open()) {
        while (!file.eof()) {
            std::getline(file, sLine);

            std::wstringstream strStream(sLine);
            std::getline(strStream, sKey, L'=');
            std::getline(strStream, sValue);
            messageTable.insert(std::make_pair(sKey, sValue));

            std::locale nLoc = std::locale(slocale);
            std::setlocale(LC_ALL, nLoc.name().c_str());
            std::locale::global(nLoc);
            std::wcout.imbue(nLoc);
        }
    }
    file.close();
}

Table& Language::getResourceTable() {
    return messageTable;
}
