#include "NoteFileStorage.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

NoteFileStorage::NoteFileStorage()
{
    if (!std::filesystem::exists(fileName) || std::filesystem::is_empty(fileName))
    {
        Initialize();
    }
}

void NoteFileStorage::Initialize() const
{
    std::ofstream file(fileName);

    if (!file.is_open())
        throw std::runtime_error("Не удалось создать файл: " + fileName);

    json notes;
    notes["notes"] = json::array();

    file << notes.dump(2);

    file.close();

    if (!file)
        throw std::runtime_error("Ошибка записи: " + fileName);
}

void NoteFileStorage::Read(std::vector<Note>& list) const
{
    std::ifstream input(fileName);

    if (!input.is_open())
        throw std::runtime_error("Не удалось открыть файл: " + fileName);

    auto document = nlohmann::json::parse(input);

    if (!document.contains("notes")) {
        throw std::runtime_error("В файле заметок нет ключа 'notes'");
    }

    if (!document.at("notes").is_array()) {
        throw std::runtime_error("В файле заметок нет массива для заметок");
    }

    for (const auto& note : document.at("notes")) {
     
        list.emplace_back(note.at("id"), note.at("text"));
    }
}

void NoteFileStorage::Write(const std::vector<Note>& list)
{
    
     //CheckEmpty();
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

