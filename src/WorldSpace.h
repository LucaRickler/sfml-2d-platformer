#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_

class WorldSpace;

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "TextureDrawer.h"
#include "RigidBody.h"
#include "SpriteComponent.h"
#include <iostream>

class WorldSpace {
public:
	WorldSpace();
	virtual ~WorldSpace();

	void Init();

	void Step();

	void RegisterEntity(Entity*);
	void RegisterMap(TileMap*);
	void RegisterPlayer(Entity*);

	TextureDrawer* getWorldTexture();
	sf::RenderWindow* getWindow();
	TileMap* getMap();
	Entity* getPlayer();

	float getTimeStep();

	bool isSlowTime();
	void SlowTime();

	void CreateRBObject(const sf::Vector2f&);

	void addRigidBody(RigidBody*);
	void deleteRigidBody(RigidBody*);

	void CheckCollisions(RigidBody*);

private:

	std::vector<Entity*> game_objects;
	sf::RenderWindow* window;

	TextureDrawer* world_texture;
	sf::Sprite* world_sprite;

	TileMap* map;

	Entity* player;

	bool slow_time;

	float slow_time_factor;

	std::vector<RigidBody*> rigid_bodies;
};

#endif /* WORLDSPACE_H_ */
