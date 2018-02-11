/*
 * WorldSpace.cpp
 *
 *  Created on: 15/set/2016
 *      Author: luca
 */

#include "WorldSpace.h"

WorldSpace::WorldSpace(){
	window = new sf::RenderWindow(sf::VideoMode(768, 576), "My window");

	world_texture = new TextureDrawer(window->getSize().x, window->getSize().y);
	world_sprite = new sf::Sprite();

	window->setFramerateLimit(60);

	slow_time_factor = 3.0f;
	slow_time = false;

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

void WorldSpace::RegisterMap(TileMap* map) {
	//RegisterEntity(map->getEntity());
	this->map = map;
}

void WorldSpace::RegisterPlayer(Entity* e) {
	game_objects.push_back(e);
	e->world = this;
	this->player = e;
}

void WorldSpace::Step() {
	window->clear(sf::Color::Black);

	std::for_each(game_objects.begin(), game_objects.end(), [] (Entity* e) {
		e->Update();
	});

	world_sprite->setTexture(world_texture->Draw());

	window->draw(*world_sprite);
	window->display();

	//CheckCollisions();

}

TextureDrawer* WorldSpace::getWorldTexture() {
	return world_texture;
}

sf::RenderWindow* WorldSpace::getWindow() {
	return window;
}

TileMap* WorldSpace::getMap() {
	return map;
}

Entity* WorldSpace::getPlayer() {
	return player;
}

float WorldSpace::getTimeStep() {
	static sf::Clock clock;
	return 1.0f/(slow_time ? slow_time_factor : 1.0f)/45.0f;
}

bool WorldSpace::isSlowTime() {
	return slow_time;
}

void WorldSpace::SlowTime() {
	if(slow_time){
		slow_time = false;
	} else {
		slow_time = true;
	}
}

void WorldSpace::CreateRBObject(const sf::Vector2f& position) {
	sf::RenderTexture rT;
	if (!rT.create(50,50)) {}
	rT.clear(sf::Color::Yellow);
	rT.display();
	const sf::Texture& enm_t = rT.getTexture();

	Entity* obj = new Entity();
	RegisterEntity(obj);
	obj->transformable->setPosition(position);
	obj->addComponent(new SpriteComponent());
	((SpriteComponent*) (obj->getComponent("SpriteComponent")))->setTexture(enm_t);
	obj->addComponent(new RigidBody(1.0f));
}

void WorldSpace::addRigidBody(RigidBody* body) {
	rigid_bodies.push_back(body);
}

void WorldSpace::deleteRigidBody(RigidBody* body) {
	rigid_bodies.erase(std::remove(rigid_bodies.begin(), rigid_bodies.end(), body), rigid_bodies.end());
}

void WorldSpace::CheckCollisions(RigidBody* body) {
	auto bounds = body->getBounds();
	std::for_each(rigid_bodies.begin(), rigid_bodies.end(), [&] (RigidBody* other) {
		sf::FloatRect intersect;
		if(body == other)
			return;
		if(!bounds->intersects(*other->getBounds(), intersect))
			return;
		//std::cout << "Collision!\n";
		auto dist = body->getPosition() - other->getPosition();
		if(intersect.height > intersect.width) {
			if(dist.x < 0) {
				auto pos = body->getPosition();
				body->setPosition(pos.x - intersect.width, pos.y);
				body->setXSpeed(0.0f);
				body->RecordHit(RigidBody::RIGHT);
			} else if (dist.x > 0) {
				auto pos = body->getPosition();
				body->setPosition(pos.x + intersect.width, pos.y);
				body->setXSpeed(0.0f);
				body->RecordHit(RigidBody::LEFT);
			}
		} else {
			if(dist.y < 0) {
				auto pos = body->getPosition();
				body->setPosition(pos.x, pos.y - intersect.height);
				body->setYSpeed(0.0f);
				body->RecordHit(RigidBody::UP);
			} else if (dist.y > 0){
				auto pos = body->getPosition();
				body->setPosition(pos.x, pos.y + intersect.height);
				body->setYSpeed(0.0f);
				body->RecordHit(RigidBody::DOWN);
			}
		}
	});
}
