#include "NoteFileStorage.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

NoteFileStorage::NoteFileStorage()
{
    if (CheckExist())
    {
        file.open(fileName, std::ios::in | std::ios::out | std::ios::app);

        if (file.is_open())
        {
            std::cout << "Файл открыт!" << std::endl;

            Read();
        }
        else
        {
            std::cout << "Не удалось открыть файл!" << std::endl;
        }
    }
    else
    {
        file.open(fileName, std::ios::out);

        std::cout << "Файл создан!" << std::endl;
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

        return false;
    }
    else {
        std::cout << "В файле есть данные." << std::endl;
        return true;
    }
}

void NoteFileStorage::Write(int id, std::string text)
{

    CheckEmpty();
    //json array();

    json notes;
    json data;

    notes["notes"] = json::array();


    data["id"] = id;
    data["text"] = text;

    notes["notes"].emplace_back(data);

    std::string jsonString = notes.dump(2);

    std::cout << "notes:\t" << notes << std::endl;
    std::cout << "data:\t" << data << std::endl;
    /*std::cout << "jsonString:\t" << data << std::endl;*/
    //std::cout << "jsonString parse:\t" << data.parse(jsonString)["id"] << std::endl;


    file << jsonString;
}

void NoteFileStorage::Read()
{
    std::string notes;

    file.clear();
    file.seekg(0, std::ios::beg);

    while(std::getline(file, notes))
    { 
        std::cout << notes << '\n';
    }

    file.clear();

    /*file >> notes*/;

    /*std::cout << notes << '\n';*/
}