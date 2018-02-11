/*
 * Entity.cpp
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#include "Entity.h"

Entity::Entity() {
	transformable = new sf::Transformable();
	world = nullptr;

	children = std::vector<Entity*> ();
	parent = nullptr;
}

Entity::Entity(Entity&) {
}

Entity::~Entity() {
	std::for_each(components.begin(), components.end(), [] (Component* c) {delete c;});
	std::for_each(children.begin(), children.end(), [] (Entity* e) {delete e;});

}

Component* Entity::getComponent(const std::string& type) {
	Component* output = nullptr;
	/*std::for_each(components.begin(), components.end(), [output, &type] (Component* c) {
		if(c->getType() == type) {
			output = c;
		}
	});*/
	for(unsigned int i = 0; i < components.size(); i++){
		if(components[i]->getType() == type){
			output = components[i];
			break;
		}
	}

	return output;
}

Component* Entity::addComponent(Component* c) {
	Component* old = getComponent(c->getType());
	if(old != nullptr){
		components.erase(std::remove(components.begin(), components.end(), old), components.end());
		delete old;
	}
	components.push_back(c);
	c->owner = this;
	c->SetWorldSpace(world);

	return c;
}

void Entity::addChild(Entity* child, sf::Vector2f offset) {
	children.push_back(child);
	world->RegisterEntity(child);
	child->parent = this;
	child->parent_offset = offset;
}

sf::Transformable* Entity::getParentTrasformable() {
	if(parent != nullptr)
		return parent->transformable;
	else
		return nullptr;
}

void Entity::Update() {
	std::for_each(components.begin(), components.end(), [] (Component* c) {
		c->Update();
	});
	std::for_each(children.begin(), children.end(), [this] (Entity* child) {
		child->transformable->setPosition(this->transformable->getPosition() + child->parent_offset);
	});
}
