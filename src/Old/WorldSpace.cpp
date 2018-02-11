/*
 * WorldSpace.cpp
 *
 *  Created on: 15/set/2016
 *      Author: luca
 */

#include "WorldSpace.h"

WorldSpace::WorldSpace(const b2Vec2& gravity){
	world = new b2World(gravity);

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");

	world_texture = new TextureDrawer(window->getSize().x, window->getSize().y);
	world_sprite = new sf::Sprite();

	window->setFramerateLimit(60);

}

WorldSpace::~WorldSpace() {
	delete world_sprite;
	delete world_texture;
	delete window;
}

void WorldSpace::Init() {
}

void WorldSpace::RegisterEntity(Entity* e) {
	game_objects.push_back(e);
	e->world = this;
}


void WorldSpace::Step() {
	window->clear(sf::Color::Black);

	world->Step(1/120.f,8,3);
	world->Step(1/120.f,8,3);


	std::for_each(game_objects.begin(), game_objects.end(), [] (Entity* e) {
		e->Update();
	});

	world_sprite->setTexture(world_texture->Draw());

	window->draw(*world_sprite);
	window->display();

}

TextureDrawer* WorldSpace::getWorldTexture() {
	return world_texture;
}

sf::RenderWindow* WorldSpace::getWindow() {
	return window;
}

b2World* WorldSpace::getB2World() {
	return world;
}
