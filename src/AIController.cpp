/*
 * AIController.cpp
 *
 *  Created on: 27/set/2016
 *      Author: luca
 */

#include "AIController.h"

AIController::AIController() {
	this->chara = nullptr;
	mode = IDLE;

	controller = new bool[NUMBER_OF_KEYS];
	for(int i = 0; i < NUMBER_OF_KEYS; i++)
		controller[i] = false;
}

AIController::~AIController() {
	delete controller;
}

void AIController::Update() {
	switch (mode) {
	case AGGRO: {
		auto dist = getPlayerDist();
		if(dist.x < 0){
			controller[KEY_LEFT] = true;
			controller[KEY_RIGHT] = false;
		} else if (dist.x > 0) {
			controller[KEY_LEFT] = false;
			controller[KEY_RIGHT] = true;
		} else {
			controller[KEY_LEFT] = false;
			controller[KEY_RIGHT] = false;
		}
		break;
	}
	case KEEP_POST:
		break;
	default:
		break;
	}
}

void AIController::SetWorldSpace(WorldSpace* w) {
	this->world = w;
}

void AIController::LinkCharacter(Character* chara) {
	this->chara = chara;
	chara->setController(controller);
}

void AIController::setMode(AIMode mode) {
	this->mode = mode;
}

sf::Vector2f AIController::getPlayerDist() {
	const float epsilon = 0.1f;

	auto dist = world->getPlayer()->transformable->getPosition() - getEntity()->transformable->getPosition();
	dist.x = (std::fabs(dist.x) > epsilon) ? dist.x : 0.0f;
	dist.y = (std::fabs(dist.y) > epsilon) ? dist.y : 0.0f;
	return dist;
}
