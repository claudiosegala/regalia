#pragma once

#include <Interfaces.h>
#include <SpriteSheetData.h>
#include <Vec2.h>

namespace Constants {

// TODO: This is the size of the components array on a GameObject optimal size will be the exact number of components type we have
const int NumberOfComponentsTypes = 32;

enum class PersonaType {
	MISTER_N = 0,
	GOTICA,
	MONGE,
	ALQUIMISTA,
	MAX_VALUE
};

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
	const float LongJumpGravity = 350.0f;
	const int MillisecondsPerRound = 10000;
	const std::string Font = "assets/font/Dark Crystal.ttf";
}

namespace Camera {
	const int Pace = 1500;
}

namespace SharedAssets {
	namespace Sounds {
		const std::string Shot = "assets/audio/Tiro Gótica.ogg";
	}

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

	const std::string Music = "assets/audio/Menu.ogg";
	const std::string Background = "assets/img/menu_livro_aberto.png";
	const std::string Sound = "assets/audio/Mudança de opção no menu (Regalia).ogg";
	const std::string ConfirmSound = "assets/audio/Clique em menu (regalia).ogg";
}

namespace Countdown {
	const bool Enabled = true; // Change this to enable or disable the countdown
	const std::string Sound = "assets/audio/Som de batalha (Regalia).ogg";
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
	const std::string Music = "assets/audio/Batalha I Loop.ogg";

	const std::vector<BackgroundData> Backgrounds = {
		{ "assets/img/backgrounds/catacombs_01.png" },
		{ "assets/img/backgrounds/catacombs_02.png" },
	};

	const std::vector<TileSetData> TileSets = {
		{ 24, 24, "assets/img/tile_sets/01.png" }
	};

	const std::vector<TileMapData> TileMaps = {
		{ "assets/map/map1.csv" },
		{ "assets/map/map2.csv" },
		{ "assets/map/map3.csv" },
		{ "assets/map/map4.csv" },
		{ "assets/map/map5.csv" },
		{ "assets/map/map6.csv" },
	};
}

namespace Bullet {
	const float LevelSpeed[] = { 100, 200, 300 };

	const int DefaultDamage = 50;

	const float DefaultSpeed = 350.0f;

	const float DefaultMaxDistance = 400.0f;

	const SpriteSheetData MisterN(
	    "assets/img/mister_n_bullet_spritesheet.png",
	    64,
	    16,
	    100,
	    1,
	    {
	        { 0, 4 },
	    });

	const SpriteSheetData Gotica(
	    "assets/img/gotica_bullet_spritesheet.png",
	    128,
	    16,
	    100,
	    1,
	    {
	        { 0, 8 },
	    });

	const SpriteSheetData Alquimista(
	    "assets/img/alquimista_bullet_spritesheet.png",
	    64,
	    16,
	    100,
	    1,
	    {
	        { 0, 4 },
	    });

	const SpriteSheetData Monge(
	    "assets/img/monge_bullet_spritesheet.png",
	    64,
	    16,
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

namespace Colors {
	const SDL_Color Black = { 0, 0, 0, 0 };
	const SDL_Color White = { 255, 255, 255, 0 };
	const SDL_Color Red = { 255, 0, 0, 0 };
}

namespace Player {

	enum AnimationState {
		IdleAnimation = 0,
		RunningAnimation,
		JumpingAnimation,
		StartFallingAnimation,
		FallingAnimation,
		SlidingAnimation,
		ShootingUpAnimation,
		ShootingDiagUpAnimation,
		ShootingHorizontalAnimation,
		ShootingDiagDownAnimation,
		ShootingDownAnimation,
		DyingAnimation,
		TOTAL_ANIMATION_STATES
	};

	const SpriteSheetData Charge (
	    "assets/img/charge.png",
	    1776,
	    48,
	    80,
	    4,
	    {
	        { 0, 1 },
	        { 1, 12 },
	        { 2, 12 },
	        { 3, 12 }
	    }
	);

	const unsigned ChargeTimeLevelOne = 1000u;

	const unsigned ChargeTimeLevelTwo = 1000u;

	const unsigned ChargeTimeLevelThree = 1000u;

	const unsigned ChargeTimeMax = ChargeTimeLevelOne + ChargeTimeLevelTwo + ChargeTimeLevelThree;

	const unsigned ShootingCoolDown = 500u;

	const float LateralForce = 450.0f;

	const float SpeedMultiplier = 100.0f;

	const float JumpSpeed = -300.0f;

	const float WallJumpSpeed = -450.0f;

	const int Hp = 50;

	const Vec2 ArrowDistance = Vec2(50, 0);

	const SpriteSheetData MisterN(
	    "assets/img/mister_n_spritesheet.png",
	    2448,
	    48,
	    100,
	    TOTAL_ANIMATION_STATES,
	    {
	        { IdleAnimation, 6 },
	        { RunningAnimation, 6 },
	        { JumpingAnimation, 2 },
	        { StartFallingAnimation, 1 },
	        { FallingAnimation, 2 },
	        { SlidingAnimation, 2 },
	        { ShootingUpAnimation, 4 },
	        { ShootingDiagUpAnimation, 4 },
	        { ShootingHorizontalAnimation, 4 },
	        { ShootingDiagDownAnimation, 4 },
	        { ShootingDownAnimation, 4 },
	        { DyingAnimation, 12 },
	    });

	const SpriteSheetData Gotica(
	    "assets/img/gotica_spritesheet.png",
	    2640,
	    48,
	    100,
	    TOTAL_ANIMATION_STATES,
	    {
	        { IdleAnimation, 6 },
	        { RunningAnimation, 6 },
	        { JumpingAnimation, 2 },
	        { StartFallingAnimation, 1 },
	        { FallingAnimation, 2 },
	        { SlidingAnimation, 2 },
	        { ShootingUpAnimation, 5 },
	        { ShootingDiagUpAnimation, 5 },
	        { ShootingHorizontalAnimation, 5 },
	        { ShootingDiagDownAnimation, 5 },
	        { ShootingDownAnimation, 5 },
	        { DyingAnimation, 11 },
	    });

	const SpriteSheetData Monge(
	    "assets/img/monge_spritesheet.png",
	    2448,
	    48,
	    100,
	    TOTAL_ANIMATION_STATES,
	    {
	        { IdleAnimation, 6 },
	        { RunningAnimation, 6 },
	        { JumpingAnimation, 2 },
	        { StartFallingAnimation, 1 },
	        { FallingAnimation, 2 },
	        { SlidingAnimation, 2 },
	        { ShootingUpAnimation, 4 },
	        { ShootingDiagUpAnimation, 4 },
	        { ShootingHorizontalAnimation, 4 },
	        { ShootingDiagDownAnimation, 4 },
	        { ShootingDownAnimation, 4 },
	        { DyingAnimation, 12 },
	    });

	const SpriteSheetData Alquimista(
	    "assets/img/alquimista_spritesheet.png",
	    2448,
	    48,
	    100,
	    TOTAL_ANIMATION_STATES,
	    {
	        { IdleAnimation, 6 },
	        { RunningAnimation, 6 },
	        { JumpingAnimation, 2 },
	        { StartFallingAnimation, 1 },
	        { FallingAnimation, 2 },
	        { SlidingAnimation, 2 },
	        { ShootingUpAnimation, 4 },
	        { ShootingDiagUpAnimation, 4 },
	        { ShootingHorizontalAnimation, 4 },
	        { ShootingDiagDownAnimation, 4 },
	        { ShootingDownAnimation, 4 },
	        { DyingAnimation, 12 },
	    });

}

}