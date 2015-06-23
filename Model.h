#ifndef _BOP_MODEL_H_
#define _BOP_MODEL_H_

#include "cocos2d.h"

enum Team;
class CollisionContainer;

/**
 * A class that represents a physical model.
 */
class Model : public cocos2d::Ref
{
protected:
	CollisionContainer* _collisionContainer;
	cocos2d::Vec3 _modelPosition;
	cocos2d::Vec3 _modelVelocity;
	float _modelDampeningFactor;
	float _modelHealth;
	Team _modelTeam;
protected:
	virtual bool init();
public:
	CREATE_FUNC(Model);

	// Gets the model's position.
	cocos2d::Vec3 getModelPosition() const { return _modelPosition; }
	// Sets the model's position.
	void setModelPosition(cocos2d::Vec3 modelPosition) { _modelPosition = modelPosition; }

	// Gets the model's velocity.
	cocos2d::Vec3 getModelVelocity() const { return _modelVelocity; }
	// Sets the model's velocity.
	void setModelVelocity(cocos2d::Vec3 modelVelocity) { _modelVelocity = modelVelocity; }
	// Adds to the model's velocity.
	void addToModelVelocity(cocos2d::Vec3 velocity) { _modelVelocity += velocity; }

	// Gets the model's dampening factor.
	float getModelDampeningFactor() const { return _modelDampeningFactor; }
	// Sets the model's dampening factor.
	void setModelDampeningFactor(float dampeningFactor) { _modelDampeningFactor = dampeningFactor; }

	// Gets the model's health.
	float getModelHealth() const { return _modelHealth; }
	// Sets the model's health.
	void setModelHealth(float health) { _modelHealth = health; }

	Team getModelTeam() const { return _modelTeam; }
	void setModelTeam(Team team) { _modelTeam = team; }

	const CollisionContainer* getCollisionContainer() const { return _collisionContainer; }
	void setCollisionContainer(CollisionContainer* collisionContainer);

	// Updates the model.
	virtual void update(float deltaTime);
};

#endif