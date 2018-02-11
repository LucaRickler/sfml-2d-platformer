/*
 * Character.cpp
 *
 *  Created on: 16/set/2016
 *      Author: luca
 */

#include "Character.h"

Character::Character(float mass, float move_speed, float jump_speed) :
		RigidBody(mass) {
	type = "Character";
	this->move_speed = move_speed;
	this->run_speed = 2.0 * move_speed;
	this->jump_speed = jump_speed;

	state = JUMP;

	controller = nullptr;
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

void Character::setController(bool* controller) {
	this->controller = controller;
}

void Character::Update() {
	RigidBody::Update();
	switch (state) {
		case STAND:{
			setSpeed(sf::Vector2f(0, 0));

			if (!onGround) {
				state = JUMP;
				break;
			}

			if (controller[KEY_LEFT] != controller[KEY_RIGHT]) {
				state = WALK;
				break;
			}

			if (controller[KEY_JUMP]) {
				setYSpeed(jump_speed);
				state = JUMP;
				//onGround = false;
				break;
			}

			break;
		}
		case WALK: {
			if (controller[KEY_LEFT] == controller[KEY_RIGHT]) {
				state = STAND;
				setSpeed(sf::Vector2f(0, 0));
				break;
			} else if (controller[KEY_RIGHT]) {
				if (pushesRightWall)
					setXSpeed(0.0f);
				else
					setXSpeed(move_speed);
				//break;
			} else if (controller[KEY_LEFT]) {
				if (pushesLeftWall)
					setXSpeed(0.0f);
				else
					setXSpeed(-move_speed);
				//break;
			}
			if (controller[KEY_JUMP]) {
				setYSpeed(jump_speed);
				state = JUMP;
				break;
			} else if (!onGround) {
				state = JUMP;
				break;
			}
			/*case RUN: {
			 if(direct == LEFT)
			 if(pushesLeftWall)
			 setXSpeed(0);
			 else
			 setXSpeed(-run_speed);
			 else if (direct == RIGHT)
			 if(pushesRightWall)
			 setXSpeed(0);
			 else
			 setXSpeed(run_speed);
			 if(!onGround) {
			 state = JUMP;
			 break;
			 }*/
			break;
		}
		case JUMP: {
			addSpeed(sf::Vector2f(0.0f, gravity * world->getTimeStep()));

			setYSpeed((getYSpeed() > max_falling_speed) ? getYSpeed() : max_falling_speed);

			if (!controller[KEY_JUMP] && getYSpeed() > 0.0f){
				setYSpeed((getYSpeed() < min_jump_speed) ? getYSpeed() : min_jump_speed);
				break;
			}

			if (controller[KEY_LEFT] == controller[KEY_RIGHT]) {
				setXSpeed(0.0f);
				break;
			} else if (controller[KEY_RIGHT]) {
				if (pushesRightWall)
					setXSpeed(0.0f);
				else
					setXSpeed(move_speed);
			} else if (controller[KEY_LEFT]) {
				if (pushesLeftWall)
					setXSpeed(0.0f);
				else
					setXSpeed(-move_speed);
			}

			if (onGround) {
				if (controller[KEY_LEFT] == controller[KEY_RIGHT]) {
					state = STAND;
					setSpeed(sf::Vector2f(0, 0));
				} else {
					state = WALK;
					setYSpeed(0.0f);
				}
				//state = STAND;
				break;
			}

			break;
		}
		default:
			break;
	}

	if(controller[KEY_SHOOT])
		Shoot();
}

void Character::SetWorldSpace(WorldSpace* w) {
	RigidBody::SetWorldSpace(w);
}

void Character::Teleport(float x, float y) {
	//this->setPosition(x - 0.5f*getBounds()->width, y + 0.5f*getBounds()->height);
	this->setPosition(x, y);
}

void Character::Shoot() {
	if(shoot_function)
		shoot_function();
}

void Character::AssignShootFunction(const std::function<void(void)>& shootf) {
	if(shootf)
		shoot_function = shootf;
}
