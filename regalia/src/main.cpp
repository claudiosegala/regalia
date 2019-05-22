#include <pch.h>
#include <Game.h>
#include <MenuState.h>
#include <Constants.h>
#include <Logger.h>

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    try {
        srand((unsigned int)time(NULL));

        Logger::GetInstance();    
    
        auto game = Game::GetInstance();

        game->Push(new MenuState());

        game->Run();

        game->~Game();
    } catch (std::runtime_error e) {
        Logger::Error(e.what());
    }

    return 0;
}
