#include "stdafx.h"
#include "Game.h"




int main()
{
    srand(static_cast<unsigned>(time(0)));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Game game;
    game.run();
    //_CrtSetBreakAlloc(171);
    //_CrtDumpMemoryLeaks(); // Check again

    return 0;
}