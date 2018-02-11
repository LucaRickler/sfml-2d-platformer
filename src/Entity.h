#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

class Entity;

#include <vector>
#include <string>
#include <algorithm>
#include "Component.h"
#include <SFML/Graphics/Transformable.hpp>

class WorldSpace;

class Entity {
public:
	Entity();
	Entity(Entity&);
	virtual ~Entity();

	Component* getComponent(const std::string&);
	Component* addComponent(Component*);

	void addChild(Entity*, sf::Vector2f offset);

	void Update();

	friend class WorldSpace;

	sf::Transformable* transformable;
	sf::FloatRect* rect;

	//sf::Vector2f getPosition();

private:
	WorldSpace* world;
	std::vector<Component*> components;

	std::vector<Entity*> children;
	Entity* parent;

	sf::Vector2f parent_offset;

	sf::Transformable* getParentTrasformable();
};

#endif /* SRC_ENTITY_H_ */
