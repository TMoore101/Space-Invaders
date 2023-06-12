#include <vector>
#include <cmath>
#include <cassert>
#include "helper.h"
#include <iostream>

#ifndef GameObject_H
#define GameObject_H
class GameObject {
protected:
	//Parent gameobject
	GameObject* parent;
	//Children gameobjects
	std::vector<GameObject*> children;
	//Transformations | Local & Global
	Matrix3 localTransform = Matrix3::identity;
	Matrix3 globalTransform = Matrix3::identity;;
public:
	//Default Constructor
	GameObject() :
		parent(nullptr), localTransform(1), globalTransform(1)
	{}

	//Deconstructor
	~GameObject()
	{
		//If the gameobject has a parent, remove the object from its parent's children list
		if (parent != nullptr)
		{
			parent->RemoveChild(this);
		}

		//For each child gameobject, set its parent to null
		for (GameObject* child : children)
		{
			child->parent = nullptr;
		}
	}
	//Get local transform
	Matrix3 GetLocalTransformation() const { return localTransform; }
	//Get global transform
	Matrix3 GetGlobalTransformation() const { return globalTransform; }
	//Get parent
	GameObject* GetParent() const { return parent; }
	//Get child count
	int GetChildCount() const { return children.size(); }
	//Get child
	GameObject* GetChild(int index) const { return children[index]; }

	//Add child function
	void AddChild(GameObject* child) {

		child->parent = this;
		children.push_back(child);
	}

	//Remove child function
	void RemoveChild(GameObject* child)
	{
		auto it = std::find(children.begin(), children.end(), child);
		if (it != children.end())
		{
			children.erase(it);
			child->parent = nullptr;
		}
	}

	virtual void OnUpdate(float deltaTime) {}

	virtual void OnDraw() {}

	//Update function
	void Update(float deltaTime)
	{
		OnUpdate(deltaTime);

		for (GameObject* child : children)
		{
			child->Update(deltaTime);
		}
	}

	//Draw function
	void Draw()
	{
		OnDraw();

		for (GameObject* child : children)
		{
			child->Draw();
		}
	}

	//Update transform function
	void UpdateTransform()
	{
		//If the object has a parent, set its globalTransform to its local transform * the parent's transform
		if (parent != nullptr) {
			Matrix3 local = localTransform;
			globalTransform = localTransform * parent->globalTransform;
			//Don't change the localTransform
			localTransform = local;
		}
		//If the parent does not have a parent, set its globalTransform to the its localTransform
		else
			globalTransform = localTransform;

		//Update all children transforms
		for (GameObject* child : children)
		{
			child->UpdateTransform();
		}
	}

	//Set position function
	void SetPosition(float x, float y)
	{
		localTransform.SetTranslation(x, y);
		UpdateTransform();
	}

	//Set rotate function
	void SetRotate(float radians)
	{
		localTransform.SetRotateZ(radians);
		UpdateTransform();
	}

	//Set scale function
	void SetScale(float width, float height)
	{
		localTransform.SetScaled(width, height, 1);
		UpdateTransform();
	}

	//Translate function
	void Translate(float x, float y)
	{
		localTransform.Translate(x, y);
		UpdateTransform();
	}

	//Rotate function
	void Rotate(float radians)
	{
		localTransform.RotateZ(radians);
		UpdateTransform();
	}

	//Scale function
	void Scale(float width, float height)
	{
		localTransform.Scale(width, height, 1);
		UpdateTransform();
	}

	//Get location X function
	float Location_X() const
	{
		return globalTransform.m20;
	}

	//Get location Y function
	float Location_Y() const
	{
		return globalTransform.m21;
	}

	//Set rotation function
	void SetRotation(float radians)
	{
		localTransform.SetRotateZ(radians);
		UpdateTransform();
	}
};
#endif