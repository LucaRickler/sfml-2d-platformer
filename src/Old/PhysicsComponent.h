/*
 * PhysicsComponent.h
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#ifndef SRC_PHYSICSCOMPONENT_H_
#define SRC_PHYSICSCOMPONENT_H_

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define UNIT_SCALE (75.0f)

enum BodyType {
	GROUND,
	STATIC,
	DYNAMIC,
	BULLLET
};

class RigidBody: public Component {
public:
	RigidBody(float, BodyType);
	virtual ~RigidBody();

	void FixInSpace();
	bool isFixedInSpace();

	void setBounds(const sf::FloatRect&);
	const sf::FloatRect& getBounds();

	virtual void SetWorldSpace(WorldSpace* w);

	virtual void Update();

	void ApplyForceToCenter(const b2Vec2&, bool);
	void ApplyForce();
	void ApplyTorque(float, bool);
	void ApplyImpulseToCenter(const b2Vec2&, bool);

private:
	float density;
	sf::Vector2f speed;

	b2Body* body;
	b2BodyDef* def;

	bool fixed_in_space;

	sf::FloatRect bounds;
	BodyType btype;
};

#endif /* SRC_PHYSICSCOMPONENT_H_ */
