#pragma once

class Resources {
public:
	static void Prune();

	static std::shared_ptr<SDL_Texture> GetImage(const std::string&);

	static std::tuple<int, int> QueryImage(SDL_Texture*);

	static void PruneImages();

	static std::shared_ptr<Mix_Music> GetMusic(const std::string&);

	static void PruneMusics();

	static std::shared_ptr<Mix_Chunk> GetSound(const std::string&);

	static void PruneSounds();

	static std::shared_ptr<TTF_Font> GetText(const std::string&, int);

	static void PruneTexts();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;

	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;

	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;

	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> textTable;
};