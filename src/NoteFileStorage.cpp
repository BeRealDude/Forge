#include "NoteFileStorage.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <cstdint>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using Clock = std::chrono::system_clock;

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

        const int id = note.at("id").get<int>();
        const auto text = note.at("text").get<std::string>();

        const std::chrono::milliseconds sinceEpoch{
            note.at("created_at_ms").get<std::int64_t>()
        };

        const Clock::time_point createdAt{
            std::chrono::duration_cast<Clock::duration>(sinceEpoch)
        };
     
        list.emplace_back(id, text, createdAt);
    }
}

void NoteFileStorage::Write(const std::vector<Note>& list) const
{
    std::ofstream file(tempPath);

    if (!file.is_open())
        throw std::runtime_error("Не удалось создать временный файл для записи: " + tempPath);

    json notes;
    json note;
    notes["notes"] = json::array();

    for (const Note& item : list)
    {
        note["created_at_ms"] = std::chrono::duration_cast<std::chrono::milliseconds>(item.GetCreatedAt().time_since_epoch()).count();
        note["id"] = item.GetId();
        note["text"] = item.GetText();
        notes.at("notes").emplace_back(note);
    }

    file << notes.dump();

    file.close();

    if (!file)
        throw std::runtime_error("Ошибка записи во временный файл: " + tempPath);

    std::filesystem::rename(tempPath, fileName);
}