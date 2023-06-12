#include <raylib.h>
#include <cmath>
#include "GameObject.h"
#include "SpriteObject.h"
#include "helper.h"
#include <iostream>

class Game {
	private:
		//Game variables
		int fps = 1;
		float deltaTime = 0.005f;
	public:
		//Default constructor
		Game() {}

	//Initialization
	void Init() {

	}

	//Draw game
	void Draw() {
		//Start drawing canvas
		BeginDrawing();

		//Set background color
		ClearBackground(BLACK);



		//End drawing canvas
		EndDrawing();
	}
};