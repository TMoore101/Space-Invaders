#include <raylib.h>
#include <cmath>
#include "GameObject.h"

class SpriteObject : public GameObject {
	//2D sprite texture
	Texture2D texture;

public:
	//Get texture width
	float textureWidth() const { return static_cast<float>(texture.width); }
	//Get texture height
	float textureHeight() const { return static_cast<float>(texture.height); }

	//Default constructor
	SpriteObject() {}

	//Load image and texture
	void Load(const std::string& fileName) {
		Image img = LoadImage(fileName.c_str());
		texture = LoadTextureFromImage(img);
	}

	//OnDraw override
	void OnDraw() override {
		//Draw texture
		DrawTextureEx(texture, { globalTransform.m20, globalTransform.m21 }, GetRotation() * (static_cast<float>(180) / static_cast<float>(M_PI)), localTransform.m00, WHITE);
	}

	//Get rotation
	float GetRotation() const {
		return std::atan2(globalTransform.m01, globalTransform.m00);
	}
};