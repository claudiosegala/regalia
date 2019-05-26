#include <pch.h>
#include <Constants.h>
#include <Game.h>
#include <Logger.h>
#include <MenuState.h>

int main(int argc, char** argv) {
	UNUSED(argc);
	UNUSED(argv);

	srand((unsigned int)time(NULL));

	auto game = Game::GetInstance();

	game->Push(new MenuState());

	game->Run();

	game->~Game();

	return 0;
}
