#pragma once

class Music {
public:
	Music();

	Music(const std::string&);

	~Music();

	void Play(int times = -1);

	void Stop(int msToStop = 1500);

	void Open(const std::string&);

	bool IsOpen();

private:
	std::shared_ptr<Mix_Music> music;
};