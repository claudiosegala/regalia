#pragma once

class Music {
public:
	Music();

	Music(const std::string& file);

	~Music();

	void Play(int times = -1);

	void Stop(int msToStop = 1500);

	void Open(const std::string& file);

	bool IsOpen();

private:
	std::shared_ptr<Mix_Music> music;
};