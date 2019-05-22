#include <pch.h>
#include <Resources.h>
#include <Game.h>
#include <Logger.h>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;

std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;

std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;

std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::textTable;

void Resources::Prune () {
    Resources::PruneImages();
    Resources::PruneMusics();
    Resources::PruneSounds();
    Resources::PruneTexts();
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if (Resources::imageTable.find(file) == Resources::imageTable.end()) {
        Logger::Info("Loading image in path: " + file);

        auto game = Game::GetInstance();
        auto renderer = game->GetRenderer();
        auto image = IMG_LoadTexture(renderer, file.c_str());
        
        if (image == nullptr) {
            auto msg = "ImgError: " + std::string(IMG_GetError()) + "\n";
            throw std::runtime_error(msg);
        }

        std::shared_ptr<SDL_Texture> image_ptr(image, [=](SDL_Texture* texture) { SDL_DestroyTexture(texture); });

        Resources::imageTable[file] = image_ptr;
    }

    return Resources::imageTable[file];
}

std::tuple<int, int> Resources::QueryImage (SDL_Texture *texture) {
    auto width = 0;
    auto height = 0;
    auto err = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    if (err < 0) {
        auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
        throw std::runtime_error(msg);
    }

    return std::make_tuple(width, height);
}

void Resources::PruneImages() {
    Logger::Info("Pruning images");

    auto it = begin(Resources::imageTable);

    while (it != end(Resources::imageTable)) {
        if (it->second.unique()) {
            it = Resources::imageTable.erase(it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    if (Resources::musicTable.find(file) == Resources::musicTable.end()) {
        Logger::Info("Loading music in path: " + file);

        auto music = Mix_LoadMUS(file.c_str());

        if (music == nullptr) {
            auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
            throw std::runtime_error(msg);
        }

        std::shared_ptr<Mix_Music> music_ptr(music, [=](Mix_Music* music) { Mix_FreeMusic(music); });

        Resources::musicTable[file] = music_ptr;
    }

    return Resources::musicTable[file];
}

void Resources::PruneMusics() {
    Logger::Info("Pruning musics");

    auto it = begin(Resources::musicTable);

    while (it != end(Resources::musicTable)) {
        if (it->second.unique()) {
            it = Resources::musicTable.erase(it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    if (Resources::soundTable.find(file) == Resources::soundTable.end()) {
        Logger::Info("Loading sound in path: " + file);

        auto sound = Mix_LoadWAV(file.c_str());

        if (sound == nullptr) {
            auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
            throw std::runtime_error(msg);
        }

        std::shared_ptr<Mix_Chunk> sound_ptr(sound, [=](Mix_Chunk* sound) { Mix_FreeChunk(sound); });

        Resources::soundTable[file] = sound_ptr;
    }

    return Resources::soundTable[file];
}

void Resources::PruneSounds() {
    Logger::Info("Pruning sounds");

    auto it = begin(Resources::soundTable);

    while (it != end(Resources::soundTable)) {
        if (it->second.unique()) {
            it = Resources::soundTable.erase(it);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<TTF_Font> Resources::GetText(std::string file, int size) {
    auto key = std::to_string(size) + "pt-" + file;

    if (Resources::textTable.find(key) == Resources::textTable.end()) {
        Logger::Info("Loading text in path: " + file);

        auto text = TTF_OpenFont(file.c_str(), size);

        if (text == nullptr) {
            auto msg = "TTFError: " + std::string(TTF_GetError()) + "\n";
            throw std::runtime_error(msg);
        }

        std::shared_ptr<TTF_Font> text_ptr(text, [=](TTF_Font* text) { TTF_CloseFont(text); });

        Resources::textTable[key] = text_ptr;
    }

    return Resources::textTable[key];
}

void Resources::PruneTexts() {
    Logger::Info("Pruning texts");

    auto it = begin(Resources::textTable);

    while (it != end(Resources::textTable)) {
        if (it->second.unique()) {
            it = Resources::textTable.erase(it);
        } else {
            ++it;
        }
    }
}
