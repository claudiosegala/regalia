#pragma once

#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>

#include <memory>
#include <iostream>
#include <string>

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