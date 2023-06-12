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
		//Player variables
		float movementSpeed = 400;
		float bulletSpeed = 3000;

		//Tank variables
		GameObject* tankObject = new GameObject();
		SpriteObject* tankSprite = new SpriteObject();
	public:
		//Default constructor
		Game() {}

	//Initialization
	void Init() {
		//Load tank
		tankSprite->Load("Images/Player/Tank.png");
		tankSprite->SetScale(0.35f, 0.35f);
		//Move the tankSprite's pivot to the middle of the tank
		tankSprite->SetPosition((-tankSprite->textureWidth() / 2) * tankSprite->GetGlobalTransformation().m00, -tankSprite->textureHeight() * tankSprite->GetGlobalTransformation().m11);

		//Add children to tank
		tankObject->AddChild(tankSprite);

		//Set the player position
		tankObject->SetPosition(GetScreenWidth() / 2, GetScreenHeight());
	}

	void Update() {
		//Player movement
		//Move to the left
		if (IsKeyDown(KEY_A) && tankObject->GetGlobalTransformation().m20 >= (tankSprite->textureWidth() / 2) * tankSprite->GetGlobalTransformation().m00) {
			//Get the direction the player is facing
			CustomVector3 facing = CustomVector3(
				tankObject->GetLocalTransformation().m00,
				tankObject->GetLocalTransformation().m01,
				0
			);

			//Move player towards the left
			facing *= deltaTime * -movementSpeed;
			tankObject->Translate(facing.x, facing.y);
		}
		//Move to the right
		if (IsKeyDown(KEY_D) && tankObject->GetGlobalTransformation().m20 <= GetScreenWidth() - (tankSprite->textureWidth() / 2) * tankSprite->GetGlobalTransformation().m00) {
			//Get the direction the player is facing
			CustomVector3 facing = CustomVector3(
				tankObject->GetLocalTransformation().m00,
				tankObject->GetLocalTransformation().m01,
				0
			);

			//Move player towards the right
			facing *= deltaTime * movementSpeed;
			tankObject->Translate(facing.x, facing.y);
		}

		//Boost
		if (IsKeyDown(KEY_LEFT_SHIFT))
			movementSpeed = 1000;
		else
			movementSpeed = 400;
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