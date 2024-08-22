
#define OLC_PGE_APPLICATION
#include "AsteroidsGame.h"

int main()
{
    AsteroidsGame game;
    if (game.Construct(640, 480, 2, 2))
        game.Start();
    return 0;
}
