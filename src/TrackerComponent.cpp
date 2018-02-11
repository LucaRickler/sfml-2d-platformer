/*
 * TrackerComponent.cpp
 *
 *  Created on: 17/set/2016
 *      Author: luca
 */

#include "TrackerComponent.h"

TrackerComponent::TrackerComponent() {
	mode = MODE_MOUSE;
	target = nullptr;
}

TrackerComponent::TrackerComponent(TrackerMode mode) {
	this->mode = mode;
	target  = nullptr;
}

TrackerComponent::TrackerComponent(TrackerMode mode, Entity* target) {
	this->mode = mode;
	setTarget(target);
}

TrackerComponent::~TrackerComponent() {}

void TrackerComponent::setTarget(Entity* target) {
	this->target = target;
}

void TrackerComponent::Update() {
	sf::Vector2i target_pos;
	static sf::Vector2i old_target_pos = sf::Vector2i(0,0);
	static sf::Vector2f old_my_pos = sf::Vector2f(0,0);
	auto my_pos = getEntity()->transformable->getPosition();


	switch(mode){
	case MODE_MOUSE:
		target_pos = sf::Mouse::getPosition(*world->getWindow());
		target_pos = world->getWindow()->mapCoordsToPixel(sf::Vector2f(target_pos.x, world->getWindow()->getSize().y - target_pos.y));
		break;
	case MODE_PLAYER:
		target_pos = (sf::Vector2i)world->getPlayer()->transformable->getPosition();
		break;
	case MODE_TARGET:
		target_pos = (sf::Vector2i)target->transformable->getPosition();
		break;
	}


	if(std::fabs(target_pos.x - old_target_pos.x) > 0.01 || std::fabs(target_pos.y - old_target_pos.y) > 0.01 ||
			std::fabs(my_pos.x - old_my_pos.x) > 0.01 || std::fabs(my_pos.y - old_my_pos.y) > 0.01) {
		auto origin = getEntity()->transformable->getPosition();
		float angle = -std::atan2((origin.x-target_pos.x),(origin.y-target_pos.y))*180/3.14 - 90.0f;
		getEntity()->transformable->setRotation(angle);
	}

	old_target_pos = target_pos;
	old_my_pos = getEntity()->transformable->getPosition();
}

void TrackerComponent::SetWorldSpace(WorldSpace* w) {
	this->world = w;
}
