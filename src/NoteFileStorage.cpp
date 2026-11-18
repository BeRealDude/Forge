#include "NoteFileStorage.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

NoteFileStorage::NoteFileStorage()
{
    if (!CheckExist())
    {
        file.open(fileName, std::ios::out);

        std::cout << "Файл создан!" << std::endl;

        file.close();
    }   
}

bool NoteFileStorage::CheckExist()
{
    if (std::filesystem::exists(fileName)) {
        std::cout << "Файл существует." << std::endl;

        return true;
    }
    else {
        std::cout << "Файл не существует." << std::endl;

        return false;
    }
}

bool NoteFileStorage::CheckEmpty()
{

    if (std::filesystem::is_empty(fileName)) {
        std::cout << "Файл пуст." << std::endl;

        return true;
    }
    else {
        std::cout << "В файле есть данные." << std::endl;
        return false;
    }
}

void NoteFileStorage::Write(std::vector<Note>& list)
{

    CheckEmpty();
    //json array();

    /*json notes;
    json data;

    notes["notes"] = json::array();


    data["id"] = id;
    data["text"] = text;

    notes["notes"].emplace_back(data);

    std::string jsonString = notes.dump(2);

    std::cout << "notes:\t" << notes << std::endl;
    std::cout << "data:\t" << data << std::endl;
   


    file << jsonString;*/
}

void NoteFileStorage::Read(std::vector<Note>& list)
{
    if (CheckEmpty())
    {
        return;
    }

    file.open(fileName, std::ios::in);

    if (file.is_open())
    {
        std::cout << "Файл открыт!" << std::endl;

        auto document = nlohmann::json::parse(file);

        for (const auto& note : document["notes"]) {
            //std::cout << note << "\tnote ";

            list.emplace_back(note["id"], note["text"]);
        }
    }

    else
    {
        std::cerr << "Не удалось открыть файл!" << std::endl;
    }

    file.clear();

    file.close();
}

std::string NoteFileStorage::CreateJson()
{
    std::string a{};
    return a;
}