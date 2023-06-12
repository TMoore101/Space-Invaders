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

		//Enemy variables
		std::vector<GameObject*>* enemyObjects = new std::vector<GameObject*>();
		std::vector<SpriteObject*>* enemySprites = new std::vector<SpriteObject*>();
		int movingLeft = 200;
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

		//Amount of rows & objects
		int numObjectsPerRow = GetScreenWidth() / tankSprite->textureWidth() * 2;
		int numRows = 4;
		//Create rows of enemies
		for (int row = 0; row < numRows; row++) {
			for (int col = 0; col < numObjectsPerRow; col++) {
				//Create enemy object
				GameObject* enemyObject = new GameObject();
				SpriteObject* enemySprite = new SpriteObject();

				//Load enemy sprite
				enemySprite->Load("Images/Enemy/Enemy.png");

				//Set the enemy sprite transformations
				enemySprite->SetScale(0.35f, 0.35f);
				enemySprite->SetPosition(0 * enemySprite->GetGlobalTransformation().m00, 0 * enemySprite->GetGlobalTransformation().m11);

				//Parent the enemySprite to the enemyObject
				enemyObject->AddChild(enemySprite);

				//Set the position of the enemyObject
				enemyObject->SetPosition((enemySprite->textureWidth() * col / 3) + 18 * col, (enemySprite->textureHeight() * row / 3) + 18 * row);

				//Add the enemy object to the enemyObjects list
				enemyObjects->push_back(enemyObject);
				enemySprites->push_back(enemySprite);
			}
		}
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

		//Enemy movement
		for (int i = 0; i < enemyObjects->size(); i++) {
			//Get enemy at location i
			GameObject* currentEnemy = enemyObjects->at(i);
			SpriteObject* enemySprite = enemySprites->at(i);

			//Get enemy direction
			CustomVector3 facing = CustomVector3(
				currentEnemy->GetLocalTransformation().m00,
				currentEnemy->GetLocalTransformation().m01,
				0
			);

			//Move left or right once 1 enemy reaches the end of the screen
			if (currentEnemy->GetGlobalTransformation().m20 >= GetScreenWidth() - (enemySprite->textureWidth()) * enemySprite->GetGlobalTransformation().m00)
				movingLeft = -200;
			else if (currentEnemy->GetGlobalTransformation().m20 <= 0)
				movingLeft = 200;

			//Move the enemy
			facing *= deltaTime * movingLeft;
			enemyObjects->at(i)->Translate(facing.x, facing.y);
		}

		if (enemyObjects->size() <= 0) {

			//Amount of rows & objects
			int numObjectsPerRow = GetScreenWidth() / tankSprite->textureWidth() * 2;
			int numRows = 4;
			//Create rows of enemies
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numObjectsPerRow; col++) {
					//Create enemy object
					GameObject* enemyObject = new GameObject();
					SpriteObject* enemySprite = new SpriteObject();

					//Load enemy sprite
					enemySprite->Load("Images/Enemy/Enemy.png");

					//Set the enemy sprite transformations
					enemySprite->SetScale(0.35f, 0.35f);
					enemySprite->SetPosition(0 * enemySprite->GetGlobalTransformation().m00, 0 * enemySprite->GetGlobalTransformation().m11);

					//Parent the enemySprite to the enemyObject
					enemyObject->AddChild(enemySprite);

					//Set the position of the enemyObject
					enemyObject->SetPosition((enemySprite->textureWidth() * col / 3) + 18 * col, (enemySprite->textureHeight() * row / 3) + 18 * row);

					//Add the enemy object to the enemyObjects list
					enemyObjects->push_back(enemyObject);
					enemySprites->push_back(enemySprite);
				}
			}
		}
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