/*
 * PhysicsComponent.h
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#ifndef SRC_RIGIDBODY_H_
#define SRC_RIGIDBODY_H_

class RigidBody;

#include "Component.h"
#include <SFML/Graphics.hpp>
#include "WorldSpace.h"

const float gravity = -400.0f;
const sf::Vector2f gravV = sf::Vector2f(0.0f, gravity);
const float max_falling_speed = -400.0f;
const float min_jump_speed = 200.0f;

class RigidBody: public Component {
public:
	enum HitDirection {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NUMBER_OF_DIRECTIONS
	};

	RigidBody(float);
	virtual ~RigidBody();

	void FixInSpace();
	bool isFixedInSpace();

	void setBounds(sf::FloatRect*);
	sf::FloatRect* getBounds();

	virtual void SetWorldSpace(WorldSpace* w);

	virtual void Update();

	void setSpeed(const sf::Vector2f&);
	void addSpeed(const sf::Vector2f&);
	void setXSpeed(float vx);
	void setYSpeed(float vy);

	bool HasGround(sf::Vector2f oldPosition, sf::Vector2f position, sf::Vector2f speed, float& groundY);
	bool HasCeiling(sf::Vector2f oldPosition, sf::Vector2f position, float& ceilingY);
	bool CollidesWithLeftWall(sf::Vector2f oldPosition, sf::Vector2f position, float& wallX);
	bool CollidesWithRightWall(sf::Vector2f oldPosition, sf::Vector2f position, float& wallX);

	const float getYSpeed();
	const float getXSpeed();

	sf::Vector2f getPosition();
	void setPosition(float, float);

	bool hasMoved();

	void RecordHit(HitDirection);

	void setBullet();
	bool isBullet();

protected:
	bool pushedRightWall;
	bool pushesRightWall;

	bool pushedLeftWall;
	bool pushesLeftWall;

	bool wasOnGround;
	bool onGround;

	bool wasAtCeiling;
	bool atCeiling;

private:
	float mass;
	sf::Vector2f position;
	sf::Vector2f old_position;

	sf::Vector2f speed;
	sf::Vector2f old_speed;

	bool fixed_in_space;

	sf::FloatRect* bounds;
	sf::FloatRect* bullet_bounds;
	bool bullet;

	sf::Vector2f round_vector(const sf::Vector2f&);

	bool has_moved;

	bool *hit_detection;
	bool RetriveHit(HitDirection);
};

#endif /* SRC_RIGIDBODY_H_ */
