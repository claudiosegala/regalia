#pragma once

#include <Interfaces.h>
#include <Vec2.h>

namespace Constants {

namespace Window {
	const int Width = 480;
	const int Height = 336;
	const std::string Name = "Regalia";
	const Vec2 Center = {
		float(Width) / 2.0f,
		float(Height) / 2.0f
	};
}

namespace Game {
	const int Sets = 5;
	const int Players = 2;
	const float SetLenght = 45.0f;
	const float Gravity = 10.0f;
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
	const std::string Music = "assets/audio/stageState.ogg";

	const std::vector<BackgroundData> Backgrounds = {
		{ "assets/img/ocean.jpg" }
	};

	const std::vector<TileSetData> TileSets = {
		{ 24, 24, "assets/img/tileSetSample.png" }
	};

	const std::vector<TileMapData> TileMaps = {
		{ "assets/map/00.txt" },
		/*{ "assets/map/01.txt" },
		{ "assets/map/02.txt" },
		{ "assets/map/03.txt" },
		{ "assets/map/04.txt" },
		{ "assets/map/05.txt" }*/
	};
}

namespace Bullet {
	const int DefaultDamage = 10;

	const float DefaultSpeed = 100.0f;

	const float DefaultMaxDistance = 400.0f;
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

namespace Gamepad {
	// TODO: replace
	const int ArrowLeft = SDLK_LEFT;
	const int ArrowRight = SDLK_RIGHT;
	const int ArrowUp = SDLK_UP;
	const int ArrowDown = SDLK_DOWN;

	const int Select = SDLK_ESCAPE;
	const int Start = SDLK_SPACE;

	const int Cross = SDLK_a;
	const int Ball = SDLK_d;
	const int Square = SDLK_w;
	const int Triangle = SDLK_s;

	const int R1 = SDLK_LEFT;
	const int R2 = SDLK_RIGHT;
	const int L1 = SDLK_UP;
	const int L2 = SDLK_DOWN;

	const int StickDeadZone = 8000;
	const int TriggerDeadZone = 8000;
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

namespace Player {
	const float SpeedMultiplier = 100.0f;
}

}

#define W(x) std::cerr << "\033[31m" << #x << "=" << x << "\033[0m" \
	                   << "\n";
#define UNUSED(x) (void)x
#define EQUAL(x, y) fabs(x - y) < Constants::Math::EPS
#define RAND static_cast<float>(rand()) / static_cast<float>(RAND_MAX) // 0.0 to 1.0