#include "core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    GameEngine* game = new GameEngine();

    game->initEngine();
    game->play();
}