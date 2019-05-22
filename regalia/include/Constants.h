#pragma once

#include <SDL_Include.h>
#include <iostream>
#include <string>
#include <cmath>

namespace Constants {

    namespace Window {
        const int Width = 1024;
        const int Height = 600;
    }

    namespace SharedAssets {
        namespace Music {
            
        }

        namespace Text {

        }

        namespace Image {
            
        }

        namespace Map {
            
        }
    }

    namespace Menu {
        const int TextSize = 20;

        const std::string Music = "assets/audio/opening.ogg";
        const std::string Background = "assets/img/ocean.jpg";
    }

    namespace Story {
        const int TextSize = 15;

        const std::string Story = "Here, on the other hand, I've gone crazy \
            and really let the literal span several lines, \
            without bothering with quoting each line's \
            content. This works, but you can't indent.";
        const std::string Background = "assets/img/ocean.jpg";
    }

    namespace Credit {
        const int TextSize = 15;

        const std::string Background = "assets/img/ocean.jpg";
    }

    namespace Play {
        const float SetTime = 45.0f;
        const int NumSets = 5;

        const std::string Music = "assets/audio/gameon.ogg";
        const std::string Background = "assets/img/menubackground.png";
    }

    namespace Key {
        const int ArrowLeft = SDLK_LEFT;
        const int ArrowRight = SDLK_RIGHT;
        const int ArrowUp = SDLK_UP;
        const int ArrowDown = SDLK_DOWN;

        const int Escape = SDLK_ESCAPE;
        const int Space = SDLK_SPACE;
        const int Return = SDLK_RETURN;

        const int A = SDLK_a;
        const int D = SDLK_d;
        const int W = SDLK_w;
        const int S = SDLK_s;
    }

    namespace Mouse {
        const int Left = SDL_BUTTON_LEFT;
        const int Right = SDL_BUTTON_RIGHT;
    }

    namespace Math {
        const float PI = 3.141592653589793f;
        const float TAO = 2.0f * PI;
        const float EPS = 0.00001f;
    }

    namespace StdColor {
        const std::string Red = "\x1b[31m";
        const std::string Green = "\x1b[32m";
        const std::string Yellow = "\x1b[33m";
        const std::string Blue = "\x1b[34m";
        const std::string Magenta = "\x1b[35m";
        const std::string Cyan = "\x1b[36m";
        const std::string Reset = "\x1b[0m";
    }
    
    // namespace Persona {
    //     // Pode ser feito usando o valor do enum como índice para array.
    //     // Será usado para carregar os assets de cada persona.
    //     const enum {
    //         PERSONA1 = "PERSONA1",
    //         PERSONA2 = "PERSONA2",
    //         PERSONA3 = "PERSONA3",
    //         PERSONA4 = "PERSONA4"
    //     }
    // }
    
}

#define W(x)        std::cerr << "\033[31m" << #x << "=" << x << "\033[0m" << "\n";
#define UNUSED(x)   (void)x
#define EQUAL(x, y) fabs(x - y) < Constants::Math::EPS
#define RAND        static_cast <float> (rand()) / static_cast <float> (RAND_MAX) // 0.0 to 1.0