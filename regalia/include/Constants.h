#pragma once

#include <Interfaces.h>
#include <SpriteSheetData.h>
#include <Vec2.h>

namespace Constants {

// TODO: This is the size of the components array on a GameObject optimal size will be the exact number of components type we have
const int NumberOfComponentsTypes = 32;

namespace Window {
	const int Width = 960;
	const int Height = 528;
	const std::string Name = "Regalia";
	const Vec2 Center = {
		float(Width) / 2.0f,
		float(Height) / 2.0f
	};
}

namespace Game {
	const int Sets = 5;
	const int Players = 2;
	const bool FriendlyFire = false;
	const float SetLength = 45.0f;
	const Vec2 MaxVelocity = { 100.0f, 1000.0f };
	const float Gravity = 500.0f;
	const int MillisecondsPerRound = 10000;
	const std::string Font = "assets/font/Dark Crystal.ttf";
}

namespace Camera {
	const int Pace = 1500;
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
	const int TextSize = 48;

	const std::string Music = "assets/audio/opening.ogg";
	const std::string Background = "assets/img/tileSet_01.png";
}

namespace Countdown {
	const bool Enabled = true; // Change this to enable or disable the countdown
	const int TextSize = 180;
	const int StartValue = 3;
}

namespace Score {
	const std::string Background = "assets/img/black.jpeg";
	const int VictoriesSize = 75;
	const int OptionSize = 45;
}

namespace Story {
	const int TextSize = 15;

	const std::string Story = "Here, on the other hand, I've gone crazy \
				and really let the literal span several lines, \
				without bothering with quoting each line's \
				content. This works, but you can't indent.";
	const std::string Background = "assets/img/tileSet_01.png";
}

namespace Credit {
	const int TextSize = 15;

	const std::string Background = "assets/img/tileSet_01.png";
}

namespace Play {
	const std::string Music = "assets/audio/Batalha dos Magos MP3-RSE.ogg";

	const std::vector<BackgroundData> Backgrounds = {
		{ "assets/img/backgrounds/play_state_01.png" },
		{ "assets/img/backgrounds/catacombs_01.png" },
		{ "assets/img/backgrounds/catacombs_02.png" },
	};

	const std::vector<TileSetData> TileSets = {
		{ 24, 24, "assets/img/tile_sets/01.png" }
	};

	const std::vector<TileMapData> TileMaps = {
		//{ "assets/map/01.txt" },
		//{ "assets/map/02.txt" },
		//{ "assets/map/03.txt" },
		//{ "assets/map/04.txt" },
		//{ "assets/map/05.txt" }
		//{ "assets/map/06.txt" }
		{ "assets/map/07.txt" }
	};
}

namespace Bullet {
	const int DefaultDamage = 50;

	const float DefaultSpeed = 200.0f;

	const float DefaultMaxDistance = 400.0f;

	const SpriteSheetData DefaultSpriteSheet(
	    "assets/img/penguinbullet.png",
	    120,
	    29,
	    100,
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
	const int P = SDLK_p;
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
	const SDL_Color Black = { 0, 0, 0, 0 };
	const SDL_Color White = { 255, 255, 255, 0 };
	const SDL_Color Red = { 255, 0, 0, 0 };
}

namespace Player {
	enum State {
		Idle = 0,
		Running,
		Jumping,
		Falling,
		Sliding,
		Loading,
		ShootingUp,
		ShootingDiagUp,
		ShootingHorizontal,
		ShootingDiagDown,
		ShootingDown,
		Dying,
		TOTAL_STATES
	};

	const float LateralForce = 450.0f;

	const float SpeedMultiplier = 100.0f;

	const float JumpSpeed = -300.0f;

	const float WallJumpSpeed = -450.0f;

	const int Hp = 50;

	const Vec2 ArrowDistance = Vec2(50, 0);

	const SpriteSheetData MisterN(
	    "assets/img/mister_n_spritesheet.png",
	    2112,
	    48,
	    100,
	    TOTAL_STATES,
	    {
	        { Idle, 6 },
	        { Running, 6 },
	        { Jumping, 2 },
	        { Falling, 3 },
	        { Sliding, 2 },
	        { Loading, 2 },
	    	{ ShootingUp, 3 },
	        { ShootingDiagUp, 3 },
	        { ShootingHorizontal, 3 },
	        { ShootingDiagDown, 3 },
	        { ShootingDown, 3 },
	        { Dying, 8 },
	    });
}

}