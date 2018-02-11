#include <iostream>
#include <cmath>
#include <iomanip>

#include "../RigidBody.h"
#include "src/SpriteComponent.h"
#include "src/Entity.h"

int main() {
	WorldSpace world = WorldSpace(b2Vec2(0.0f, -1.0f));

	float x = 0.0f;
	float v = 0.1f;

	sf::RenderTexture grt;
	if (!grt.create(800, 50)) {
		// error...
	}
	grt.clear(sf::Color::Green);
	grt.display();
	const sf::Texture& gt = grt.getTexture();

	Entity* ground = new Entity();
	world.RegisterEntity(ground);
	ground->addComponent(new SpriteComponent());
	((SpriteComponent*) (ground->getComponent("SpriteComponent")))->setTexture(gt);
	ground->transformable->setPosition(0,0);
	ground->addComponent(new RigidBody(0.0f, GROUND));

	sf::RenderTexture prt;
	if (!prt.create(100, 100)) {
		// error...
	}
	prt.clear(sf::Color::Blue);
	prt.display();
	const sf::Texture& pt = prt.getTexture();

	Entity* player = new Entity();
	world.RegisterEntity(player);
	player->addComponent(new SpriteComponent());
	((SpriteComponent*) (player->getComponent("SpriteComponent")))->setTexture(pt);
	player->transformable->setPosition(200,200);
	player->addComponent(new RigidBody(1.0f, DYNAMIC));
	RigidBody* player_body = (RigidBody*)player->getComponent("PhysicsComponent");



	while (world.getWindow()->isOpen()) {
		sf::Event event;
		while (world.getWindow()->pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				world.getWindow()->close();
			if (event.type == sf::Event::KeyPressed){
				switch(event.key.code){
				case sf::Keyboard::Up:{
					player_body->ApplyImpulseToCenter(b2Vec2(0.0f,1.0f),true);
					break;
				}
				case sf::Keyboard::Left:{
					player_body->ApplyImpulseToCenter(b2Vec2(-1.0f,0.0f),true);
					break;
				}
				case sf::Keyboard::Right:{
					player_body->ApplyImpulseToCenter(b2Vec2(1.0f,0.0f),true);
					break;
				}
				case sf::Keyboard::Q:{
					player_body->ApplyTorque(1.0f,true);
					break;
				}
				default:
					break;

				}
			}
		}


		//player->transformable->setPosition(x, 200);
		//x= (x + v) > world.getWindow()->getSize().x ? 0.0f : x + v;

		world.Step();
	}

	return 0;
}
