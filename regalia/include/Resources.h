#pragma once

#include <Logger.h>
#include <SDL_Include.h>
#include <Constants.h>

#include <unordered_map>
#include <memory>
#include <string>
#include <tuple>

class Resources {
    public:

        static void Prune();

        static std::shared_ptr<SDL_Texture> GetImage(std::string);

        static std::tuple<int, int> QueryImage(SDL_Texture*);

        static void PruneImages();

        static std::shared_ptr<Mix_Music> GetMusic(std::string);

        static void PruneMusics();

        static std::shared_ptr<Mix_Chunk> GetSound(std::string);

        static void PruneSounds();

        static std::shared_ptr<TTF_Font> GetText(std::string, int);

        static void PruneTexts();

    private:

        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;

        static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;

        static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;

        static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> textTable;

};