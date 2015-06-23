// CollisionContainer.h
// Defines some collision containers and functions

#ifndef _COLLISION_CONTAINER_H_
#define _COLLISION_CONTAINER_H_

#include "cocos2d.h"

class CollisionContainer : public cocos2d::Ref
{
protected:
	cocos2d::Vec3 _position;

	virtual bool init()
	{
		_position = cocos2d::Vec3(0, 0, 0);
		return true;
	}
public:
	CREATE_FUNC(CollisionContainer);
	
	virtual bool intersects(const CollisionContainer* other) const
	{
		return false;
	}

	void setPosition(cocos2d::Vec3 position) { _position = position; }
	cocos2d::Vec3 getPosition() const { return _position; }
};

class SphericalCollisionContainer : public CollisionContainer
{
protected:
	float _radius;

	bool init() override
	{
		_radius = 0;
		return true;
	}
public:
	CREATE_FUNC(SphericalCollisionContainer);

	bool intersects(const CollisionContainer* other) const
	{
		if (other != nullptr)
		{
			const SphericalCollisionContainer* otherAsSphere = (const SphericalCollisionContainer*)other;
			return (this->_position).distanceSquared(otherAsSphere->_position) < pow(this->_radius + otherAsSphere->_radius, 2);
		}
	}

	void setRadius(float radius) { _radius = radius; }
	float getRadius() const { return _radius; }
};

#endif