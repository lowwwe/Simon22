#include "main.h"
#include "Game.h"

/// <summary>
/// @brief starting point for all c programs.
/// 
/// create a game object and run it.
/// </summary>
/// <param name=""></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int, char* argv[])
{
	Game game;
	game.run();
}