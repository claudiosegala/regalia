#include <pch.h>
#include <Game.h>
#include <Number.h>
#include <MenuState.h>
#include <Util.h>

void Setup (int argc, char** argv) {
	UNUSED(argc);
	UNUSED(argv);

	Number::InitRand();
}

int main(int argc, char** argv) {
	Setup(argc, argv);

	auto game = Game::GetInstance();

	game->Push(new MenuState());

	game->Run();

	delete game;

	return 0;
}
