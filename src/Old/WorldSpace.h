#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "TextureDrawer.h"


class WorldSpace {
public:
	WorldSpace(const b2Vec2& gravity);
	virtual ~WorldSpace();

	void Init();

	void Step();

	void RegisterEntity(Entity*);

	TextureDrawer* getWorldTexture();
	sf::RenderWindow* getWindow();

	b2World* getB2World();


private:
	std::vector<Entity*> game_objects;
	sf::RenderWindow* window;

	TextureDrawer* world_texture;
	sf::Sprite* world_sprite;

	b2World* world;

};

#endif /* WORLDSPACE_H_ */
