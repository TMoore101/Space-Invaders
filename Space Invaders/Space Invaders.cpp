#include "raylib.h"
#include "Game.cpp"

int main(int argc, char* argv[]) {
	//Create game
	Game* game = new Game();

	//Create application window
	InitWindow(1920 * 0.9, 1080 * 0.9, "Space Invaders");

	//Set target frame rate
	SetTargetFPS(60);

	//Initialize game
	game->Init();

	//Run game
	while (!WindowShouldClose()) {
		game->Update();
		game->Draw();
	}

	//Close window on end
	CloseWindow();
}