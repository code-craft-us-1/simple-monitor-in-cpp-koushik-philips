#include <codecvt>
#include <filesystem>
#include "./localization.h"

LANG Language::choice = LANG::LANG_eng;
Table Language::messageTable;

void Language::setLanguage( int lang ) {
    Language::choice = static_cast<LANG>(lang);
    LoadResourceFile();
}
LANG Language::getLanguage() {
    return Language::choice;
}

void Language::LoadResourceFile() {
    messageTable.clear();
    std::locale loc;
    std::wstring sLine;
    std::wstring sKey;
    std::wstring sValue;
    std::string filename;

    if (Language::getLanguage() == static_cast<LANG>(1)) {
        loc = std::locale(std::locale("De_DE"), new std::codecvt_utf8<wchar_t>);
        std::setlocale(LC_ALL, loc.name().c_str());
        filename = std::string("resource_ger.lang");
    } else {
        loc = std::locale(std::locale("en_US.UTF-8"), new std::codecvt_utf8<wchar_t>);
        std::setlocale(LC_ALL, loc.name().c_str());
        filename = std::string("resource_eng.lang");
    }

    std::filesystem::path filePath(filename);
    std::filesystem::path folderPath = std::filesystem::path(__FILE__).remove_filename();
    std::filesystem::path absoluteFilePath = std::filesystem::absolute(folderPath / filePath);

    std::wifstream file(absoluteFilePath,std::ios::in);
    file.imbue(loc);
    if (file.is_open()) {
        while (!file.eof()) {
            std::getline(file, sLine);

            std::wstringstream strStream(sLine);
            std::getline(strStream, sKey, L'=');
            std::getline(strStream, sValue);
            messageTable.insert(std::make_pair(sKey, sValue));

            if (Language::getLanguage() == static_cast<LANG>(1)) {
                std::locale newLocale(std::locale("De_DE"));
                std::setlocale(LC_ALL, newLocale.name().c_str());
                std::locale::global(newLocale);
                std::wcout.imbue(newLocale);
            } else {
                std::locale newLocale(std::locale("en_US.UTF-8"));
                std::setlocale(LC_ALL, newLocale.name().c_str());
                std::locale::global(newLocale);
                std::wcout.imbue(newLocale);
            }
        }
    }
    file.close();
}

Table& Language::getResourceTable() {
    return messageTable;
}

