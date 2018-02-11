/*
 * Character.h
 *
 *  Created on: 16/set/2016
 *      Author: luca
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "RigidBody.h"
#include <functional>

enum KeysBindings {
	KEY_LEFT = 0,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_JUMP,
	KEY_RUN,
	KEY_SHOOT,
	NUMBER_OF_KEYS
};

class Character: public RigidBody {
public:
	enum CharState {
		STAND,
		JUMP,
		RUN,
		WALK,
		GRAB_LEDGE,
		NUMBER_OF_STATES
	};

	Character(float, float, float);
	virtual ~Character();

	virtual void Update ();

	virtual void SetWorldSpace(WorldSpace* w);

	void setController(bool*);

	void Teleport(float, float);

	void Shoot();
	void AssignShootFunction(const std::function<void(void)>&);

private:
	CharState state;

	float move_speed;
	float run_speed;
	float jump_speed;

	bool* controller;

	std::function<void(void)> shoot_function;
};

#endif /* SRC_CHARACTER_H_ */
