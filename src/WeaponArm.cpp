/*
 * WeaponArm.cpp
 *
 *  Created on: 04/ott/2016
 *      Author: luca
 */

#include "WeaponArm.h"


WeaponArm::WeaponArm() : TrackerComponent() {
	type = "WeaponArm";
}

WeaponArm::WeaponArm(TrackerMode mode) : TrackerComponent(mode) {
	type = "WeaponArm";
}

WeaponArm::WeaponArm(TrackerMode mode, Entity* target) : TrackerComponent(mode, target) {
	type = "WeaponArm";
}

WeaponArm::~WeaponArm() {}

void WeaponArm::Update() {
	TrackerComponent::Update();
}



void WeaponArm::SetWorldSpace(WorldSpace* w) {
	TrackerComponent::SetWorldSpace(w);
}

void WeaponArm::Shoot() {
	if(world != nullptr) {
		double angle = getEntity()->transformable->getRotation();

		Entity* bullet = new Entity();
		world->RegisterEntity(bullet);
		bullet->addComponent(new SpriteComponent());
		((SpriteComponent*) (bullet->getComponent("SpriteComponent")))->setTexture(bullet_texture);

		/*auto pos = getEntity()->transformable->getPosition();

		bullet->transformable->setPosition(pos.x / std::cos(angle), pos.y / std::sin(angle));*/

		//RigidBody* bullet_body = (RigidBody*)bullet->addComponent(new RigidBody(0.0));
		//bullet_body->setBullet();
		//bullet_body->setSpeed(sf::Vector2f(std::cos(angle)*speed, std::sin(angle)*speed));
		//std::cout << "Pew Pew\n";
	}
}

std::function<void(void)> WeaponArm::getShootFunction() {
	return [this] () {this->Shoot();};
}


void WeaponArm::setTexture(const sf::Texture& texture) {
	this->bullet_texture = texture;
}

void WeaponArm::setSpeed(double speed) {
	this->speed = speed;
}
