#pragma once

#include <Interfaces.h>
#include <SpriteSheetData.h>
#include <Vec2.h>
#include "BackgroundAnimationData.h"

namespace Constants {

// TODO: This is the size of the components array on a GameObject optimal size will be the exact number of components type we have
const int NumberOfComponentsTypes = 32;

enum class PersonaType {
	MISTER_N_RED = 0,
	MISTER_N_BLUE,
	GOTICA_PURPLE,
	GOTICA_GREEN,
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
	const int Sets = 9;
	const bool FriendlyFire = false;
	const float Gravity = 600.0f;
	const float LongJumpGravity = 420.0f;
	const int MillisecondsPerRound = 35000;
	const int MinNumPlayers = 2; // TODO: change to 2
	const int MaxNumPlayers = 4;
	const int VictoriesToWin = 3;
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
	const std::string Sound = "assets/audio/Mudança de opção no menu (Regalia).ogg";
	const std::string ConfirmSound = "assets/audio/Clique em menu (regalia).ogg";
	const std::string Background = "assets/img/menu/livro_fundo.png";

	const SpriteSheetData BackgroundInitial(
	    "assets/img/menu/background_initial.png",
	    5760,
	    264,
	    100,
	    1,
	    { 
			{ 0, 12 }, 
		});

	const SpriteSheetData Credits(
	    "assets/img/menu/botao_creditos_spritesheet.png",
	    222,
	    36,
	    100,
	    2,
	    {
	        { 0, 1 },
	        { 1, 1 },
	    });

	const SpriteSheetData History(
	    "assets/img/menu/botao_historia_spritesheet.png",
	    222,
	    36,
	    100,
	    2,
	    {
	        { 0, 1 },
	        { 1, 1 },
	    });

	const SpriteSheetData Exit(
	    "assets/img/menu/botao_sair_spritesheet.png",
	    222,
	    36,
	    100,
	    2,
	    {
	        { 0, 1 },
	        { 1, 1 },
	    });

	const SpriteSheetData Play(
	    "assets/img/menu/botao_jogar_spritesheet.png",
	    236,
	    148,
	    100,
	    2,
	    {
	        { 0, 1 },
	        { 1, 1 },
	    });

}

namespace Book {
	const Vec2 CardPositions[4] = {
		{ 528, 70 },
		{ 652, 70 },
		{ 528, 246 },
		{ 652, 246 }
	};

	const Vec2 PlayerLabelPositions[4] = {
		{ 564, 82 },
		{ 688, 82 },
		{ 564, 258 },
		{ 688, 258 }
	};

	const Vec2 PersonasPositions[4] = {
		{ 536, 90 },
		{ 660, 90 },
		{ 536, 266 },
		{ 660, 266 }
	};

	const Vec2 VictoriesPositions[4] = {
		{ 540, 198 },
		{ 664, 198 },
		{ 540, 374 },
		{ 664, 374 }
	};
}

namespace SelectPersona {
	const std::string Title = "assets/img/select/select_title.png";
}

namespace Countdown {
	const bool Enabled = true; // Change this to enable or disable the countdown
	const std::string Sound = "assets/audio/Som de batalha (Regalia).ogg";
	const int TextSize = 180;
	const int StartValue = 3;
}

namespace Score {
	const std::string Background = "assets/img/score/score_menu_bg.png";
	const std::string Chapter = "assets/img/score/chapter_title.png";
	const std::string End = "assets/img/score/end_title.png";
	const std::string Music = "assets/audio/score_song.ogg";
	const int VictoriesSize = 75;
	const int OptionSize = 45;
	const SpriteSheetData Nums(
	    "assets/img/score/numbers_spritesheet.png",
	    220,
	    36,
	    100,
	    10,
	    {
	        { 0, 1 },
	        { 1, 1 },
	        { 2, 1 },
	        { 3, 1 },
	        { 4, 1 },
	        { 5, 1 },
	        { 6, 1 },
	        { 7, 1 },
	        { 8, 1 },
	        { 9, 1 },
	    });

	const SpriteSheetData Cards(
	    "assets/img/score/card_spritesheet.png",
	    168,
	    82,
	    100,
	    3,
	    {
	        { 0, 1 },
	        { 1, 1 },
	        { 2, 1 },
	    });

	const SpriteSheetData PlayerLabel(
	    "assets/img/score/player_label_spritesheet.png",
	    100,
	    4,
	    100,
	    5,
	    {
	        { 0, 1 },
	        { 1, 1 },
	        { 2, 1 },
	        { 3, 1 },
	        { 4, 1 },
	    });

	const SpriteSheetData Victories(
	    "assets/img/score/points_spritesheet.png",
	    176,
	    10,
	    100,
	    4,
	    {
	        { 0, 1 },
	        { 1, 1 },
	        { 2, 1 },
	        { 3, 1 },
	    });

	const SpriteSheetData NavBar(
	    "assets/img/score/nav_prompts_spritesheet.png",
	    310,
	    11,
	    100,
	    2,
	    {
	        { 0, 1 },
	        { 1, 1 },
	    });
}

namespace Story {
	const std::string Background = "assets/img/historia.png";
}

namespace Credit {
	const std::string Background = "assets/img/credito.png";
}

namespace Play {
	const std::string Music = "assets/audio/Batalha I Loop.ogg";

	const std::vector<BackgroundAnimationData> CityBackground = {
		{ // Background
		    new SpriteSheetData(
		        "assets/img/backgrounds/cidade_pisca_300ms.png",
		        3840,
		        528,
		        300,
		        1,
		        {
		            { 0, 4 },
		        }),
		    { 0, 0 },
		    {} },
		{ // Subway
		    new SpriteSheetData(
		        "assets/img/backgrounds/cidade_metro_100ms_252_371.png",
		        2442,
		        16,
		        150,
		        1,
		        { { 0, 22 } }),
		    { 252, 371 },
		    {} },
		{ // Crane
		    new SpriteSheetData(
		        "assets/img/backgrounds/cidade_gindaste_200ms_305_161.png",
		        360,
		        27,
		        200,
		        1,
		        {
		            { 0, 10 },
		        }),
		    { 305, 161 },
		    {} },
		{ // Cars 1
		    new SpriteSheetData(
		        "assets/img/backgrounds/cidade_carros1_150ms_162_270.png",
		        623,
		        4,
		        150,
		        1,
		        {
		            { 0, 7 },
		        }),
		    { 162, 270 },
		    {} },
		{ // Cars 2
		    new SpriteSheetData(
		        "assets/img/backgrounds/cidade_carros2_150ms_162_270.png",
		        979,
		        4,
		        150,
		        1,
		        {
		            { 0, 11 },
		        }),
		    { 162, 270 },
		    {} }
	};

	const std::vector<BackgroundAnimationData> CatacombsBackground = {
		{ // Background
		    new SpriteSheetData(
		        "assets/img/backgrounds/catacumba_4frames_200ms.png",
		        3840,
		        528,
		        200,
		        1,
		        {
		            { 0, 4 },
		        }),
		    { 0, 0 },
		    {} },
	};

	const int TileSetSize = 24;

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
	const float LevelSpeed[] = { 200, 400, 600 };

	const int DefaultDamage = 50;

	const float DefaultMaxDistance = 400.0f;

	const float Size = 16.0f;

	const SpriteSheetData MisterNRed(
	    "assets/img/spritesheets/wand_red.png",
	    128,
	    16,
	    75,
	    1,
	    {
	        { 0, 8 },
	    });

	const SpriteSheetData MisterNBlue(
	    "assets/img/spritesheets/wand_blue.png",
	    128,
	    16,
	    75,
	    1,
	    {
	        { 0, 8 },
	    });

	const SpriteSheetData GoticaPurple(
	    "assets/img/spritesheets/goth_bullet_spritesheet_purple.png",
	    192,
	    16,
	    100,
	    1,
	    {
	        { 0, 8 },
	    });

	const SpriteSheetData GoticaGreen(
	    "assets/img/spritesheets/goth_bullet_spritesheet_green.png",
	    192,
	    16,
	    100,
	    1,
	    {
	        { 0, 8 },
	    });

	// Explosions
	const SpriteSheetData MisterNRedExplosion(
	    "assets/img/spritesheets/wand_explosion_red.png",
	    144,
	    16,
	    100,
	    1,
	    {
	        { 0, 9 },
	    },
	    true);

	const SpriteSheetData MisterNBlueExplosion(
	    "assets/img/spritesheets/wand_explosion_blue.png",
	    144,
	    16,
	    100,
	    1,
	    {
	        { 0, 9 },
	    },
	    true);

	const SpriteSheetData GoticaPurpleExplosion(
	    "assets/img/spritesheets/gotica_explosao_roxo.png",
	    128,
	    16,
	    100,
	    1,
	    {
	        { 0, 8 },
	    },
	    true);

	const SpriteSheetData GoticaGreenExplosion(
	    "assets/img/spritesheets/gotica_explosao_verde.png",
	    128,
	    16,
	    100,
	    1,
	    {
	        { 0, 8 },
	    },
	    true);
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

	const SpriteSheetData Charge(
	    "assets/img/spritesheets/charge_spritesheet.png",
	    2368,
	    64,
	    80,
	    4,
	    {
	        { 0, 1 },
	        { 1, 12 },
	        { 2, 12 },
	        { 3, 12 },
	    });

	const unsigned ChargeTimeLevelOne = 1000u;

	const unsigned ChargeTimeLevelTwo = 1000u;

	const unsigned ChargeTimeLevelThree = 1000u;

	const unsigned ChargeTimeMax = ChargeTimeLevelOne + ChargeTimeLevelTwo + ChargeTimeLevelThree;

	const unsigned ShootingCoolDown = 500u;

	const float LateralForce = 600.0f;

	const float SpeedMultiplier = 160.0f;

	const Vec2 MaxVelocity = { SpeedMultiplier, 1000.0f };

	const float JumpSpeed = -300.0f;

	const float WallJumpSpeed = -450.0f;

	const int Hp = 50;

	const Vec2 ArrowDistance = Vec2(50, 0);

	const SpriteSheetData MisterNRed(
	    "assets/img/spritesheets/mister_n_spritesheet_red.png",
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

	const SpriteSheetData MisterNBlue(
	    "assets/img/spritesheets/mister_n_spritesheet_blue.png",
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

	const SpriteSheetData GoticaPurple(
	    "assets/img/spritesheets/goth_spritesheet_purple.png",
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

	const SpriteSheetData GoticaGreen(
	    "assets/img/spritesheets/goth_spritesheet_green.png",
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

}
}
