#pragma once

#include <Util.h>

class Timer {
    public:

        Timer();

        void SetStart(float);

        void Update(float);

        void Restart();

        float Get();

    private:

        float time;
};