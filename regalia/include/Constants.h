#pragma once

#include <Interfaces.h>
#include <SpriteSheetData.h>
#include <Vec2.h>

namespace Constants {

// TODO: This is the size of the components array on a GameObject optimal size will be the exact number of components type we have
const int NumberOfComponentsTypes = 32;

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
	const float MaxVelocity = 1000.0f;
	const float Gravity = 500.0f;
}

namespace Camera {
	const int Pace = 1500.0f;
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
	const std::string Music = "assets/audio/Batalha dos Magos MP3-RSE.mp3";

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

	const SpriteSheetData DefaultSpriteSheet(
	    "assets/img/penguinbullet.png",
	    120,
	    29,
	    0.1f,
	    1,
	    {
	        { 0, 4 },
	    });
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
	const int StickDeadZone = 8000;
	const int TriggerDeadZone = 8000;
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

namespace Colors {
	const SDL_Color Red = { 255, 0, 0, 0 };
}

namespace Player {
	enum State {
		Idle = 0,
		Running,
		Jumping,
		Falling,
		TOTAL_STATES
	};

	const float SpeedMultiplier = 100.0f;

	const float JumpSpeed = -300.0f;

	const int Hp = 50;

	const Vec2 ArrowDistance = Vec2(50, 0);

	const SpriteSheetData MisterN(
	    "assets/img/mister_n_spritesheet.png",
	    432,
	    48,
	    0.1f,
	    TOTAL_STATES,
	    {
	        { Idle, 1 },
	        { Running, 6 },
	        { Jumping, 1 },
	        { Falling, 1 },
	    });
}

}