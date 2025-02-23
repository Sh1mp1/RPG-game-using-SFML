#include "stdafx.h"
#include "Game.h"


#include<filesystem>

int main()
{
    srand(static_cast<unsigned>(time(0)));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


   std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    
    Game game;
    game.run();
    //_CrtSetBreakAlloc(171);
    //_CrtDumpMemoryLeaks(); // Check again

    return 0;
}