#include <iostream>
#include <cmath>
#include <iomanip>
#include "src/SpriteComponent.h"
#include "src/WeaponArm.h"
#include "src/Entity.h"
#include "src/Character.h"
#include "src/TileMap.h"
#include "src/AIController.h"

int main() {
	WorldSpace world = WorldSpace();

	int level_c[] = {
		63,63,63,63,63,63,63,63,63,63,63,63,
		57,57,57,57,57,57,57,57,57,57,57,63,
		57,57,57,57,57,57,63,57,57,57,57,57,
		57,57,57,57,57,57,57,57,57,57,57,57,
		63,63,63,57,57,57,57,57,57,57,57,57,
		57,57,57,57,57,57,57,57,57,57,57,57,
		57,57,57,57,57,57,63,63,63,63,63,63,
		57,57,57,57,57,57,57,57,57,57,57,57,
		57,57,57,57,57,57,57,57,57,57,57,57
	};

	int* level = new int[12*9];

	std::copy(level_c, level_c +12*9, &level[0]);

	Entity* map = new Entity();
	world.RegisterEntity(map);
	map->addComponent(new TileMap());
	TileMapping legend;
	legend.insert(TileMappingPair(63, BLOCK));
	legend.insert(TileMappingPair(57, EMPTY));

	((TileMap*)map->getComponent("TileMap"))->LoadMap(12,9,new sf::Vector2i(64,64),level, legend, "bin/Tiles_64x64.png");
	world.RegisterMap((TileMap*)map->getComponent("TileMap"));

	sf::RenderTexture prt;
	if (!prt.create(50, 50)) {}
	prt.clear(sf::Color::Blue);
	prt.display();
	const sf::Texture& pt = prt.getTexture();

	Entity* player = new Entity();
	world.RegisterPlayer(player);
	player->addComponent(new SpriteComponent());
	((SpriteComponent*) (player->getComponent("SpriteComponent")))->setTexture(pt);
	player->transformable->setPosition(200,0);
	Character* player_body = (Character*)player->addComponent(new Character(1.0,160,400));

	sf::RenderTexture art;
	if (!art.create(30, 20)) {}
	art.clear(sf::Color::White);
	art.display();
	const sf::Texture& arm_t = art.getTexture();

	//sf::Sprite* spt = new sf::Sprite(arm_t);

	Entity* player_arm = new Entity();
	//world.RegisterEntity(player_arm);
	player->addChild(player_arm, sf::Vector2f(15,25));
	player_arm->transformable->setPosition(0,0);
	player_arm->addComponent(new SpriteComponent());
	((SpriteComponent*) (player_arm->getComponent("SpriteComponent")))->setTexture(arm_t);

	sf::RenderTexture bullet;
	if (!bullet.create(2, 2)) {}
	bullet.clear(sf::Color::Yellow);
	bullet.display();
	const sf::Texture& bullet_t = sf::Texture(bullet.getTexture());

	player_body->AssignShootFunction(((WeaponArm*)player_arm->addComponent(new WeaponArm()))->getShootFunction());
	((WeaponArm*)player_arm->getComponent("WeaponArm"))->setTexture(bullet_t);
	((WeaponArm*)player_arm->getComponent("WeaponArm"))->setSpeed(1000);

	//sf::Vector2i mouse_position;

	/*sf::RenderTexture enm;
	if (!enm.create(50,50)) {}
	enm.clear(sf::Color::Red);
	enm.display();
	const sf::Texture& enm_t = enm.getTexture();

	//sf::Sprite* spt = new sf::Sprite(arm_t);

	Entity* enemy = new Entity();
	world.RegisterEntity(enemy);
	enemy->transformable->setPosition(700,0);
	enemy->addComponent(new SpriteComponent());
	((SpriteComponent*) (enemy->getComponent("SpriteComponent")))->setTexture(enm_t);
	enemy->addComponent(new Character(1.0,160,400));
	AIController* ai = (AIController*)enemy->addComponent(new AIController());
	ai->setMode(AIController::AGGRO);
	ai->LinkCharacter((Character*)enemy->getComponent("Character"));*/

	world.CreateRBObject(sf::Vector2f(100,0));

	bool* key_state = new bool[NUMBER_OF_KEYS];
	for(int i = 0; i < NUMBER_OF_KEYS; i++)
		key_state[i] = false;

	player_body->setController(key_state);

	while (world.getWindow()->isOpen()) {
		sf::Event event;
		while (world.getWindow()->pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				world.getWindow()->close();

			if (event.type == sf::Event::KeyPressed){
				switch(event.key.code){
				case sf::Keyboard::W:{
					if(!world.isSlowTime())
						key_state[KEY_UP] = true;
					break;
				}
				case sf::Keyboard::A:{
					if(!world.isSlowTime())
						key_state[KEY_LEFT] = true;
					break;
				}
				case sf::Keyboard::D:{
					if(!world.isSlowTime())
						key_state[KEY_RIGHT] = true;
					break;
				}
				case sf::Keyboard::Space: {
					if(!world.isSlowTime())
						key_state[KEY_JUMP] = true;
					break;
				}
				case sf::Keyboard::LShift:
				case sf::Keyboard::RShift:{
					if(!world.isSlowTime())
						key_state[KEY_RUN] = true;
					break;
				}
				case sf::Keyboard::E: {
					world.SlowTime();
					break;
				}
				default:
					break;

				}
			}

			if (event.type == sf::Event::KeyReleased) {
				switch(event.key.code){
				case sf::Keyboard::W:{
					//if(!world.isSlowTime())
						key_state[KEY_UP] = false;
					break;
				}
				case sf::Keyboard::A:{
					//if(!world.isSlowTime())
						key_state[KEY_LEFT] = false;
					break;
				}
				case sf::Keyboard::D:{
					//if(!world.isSlowTime())
						key_state[KEY_RIGHT] = false;
					break;
				}
				case sf::Keyboard::LShift:
				case sf::Keyboard::RShift:{
					//if(!world.isSlowTime())
						key_state[KEY_RUN] = false;
					break;
				}
				case sf::Keyboard::Space: {
					//if(!world.isSlowTime())
						key_state[KEY_JUMP] = false;
					break;
				}
				default:
					break;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				switch(event.mouseButton.button) {
				case sf::Mouse::Left:
					if(world.isSlowTime()){
						auto m_pos_w = sf::Mouse::getPosition(*world.getWindow());
						auto m_pos = world.getWindow()->mapCoordsToPixel(sf::Vector2f(m_pos_w.x, world.getWindow()->getSize().y - m_pos_w.y));
						if(!world.getMap()->isObstacle(m_pos.x/world.getMap()->getTileSize().x, m_pos.y/world.getMap()->getTileSize().y)){
							if(m_pos.x > 0.0f && m_pos.y > 0.0f && m_pos.x < world.getWindow()->getSize().x
									&& m_pos.y < world.getWindow()->getSize().y){
								player_body->Teleport(m_pos.x, m_pos.y);
								world.SlowTime();
							}
						}
					} else {
						//key_state[KEY_SHOOT] = true;
					}
					break;
				case sf::Mouse::Right:
					world.SlowTime();
					break;
				default:
					break;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				switch(event.mouseButton.button) {
				case sf::Mouse::Left:
					if(!world.isSlowTime())
						key_state[KEY_SHOOT] = false;
					break;
				default:
					break;
				}
			}
		}


		world.Step();
	}

	return 0;
}
