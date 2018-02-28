#ifndef SRC_SPRITECOMPONENT_H_
#define SRC_SPRITECOMPONENT_H_

#include "Component.h"
#include <SFML/Graphics.hpp>
#include "TextureDrawer.h"

class SpriteComponent: public Component {
public:
	SpriteComponent();
	SpriteComponent(TextureDrawer*);
	virtual ~SpriteComponent();

	virtual void Update();

	virtual void SetWorldSpace(WorldSpace*);

	void setTexture(const sf::Texture&);

	void setParentTexture(TextureDrawer*);
	TextureDrawer* getParentTexture();

	void setColor(const sf::Color&);
	const sf::Color& getColor();

	const sf::Transform& getTransform();

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f&);
	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f&);
	void setRotation(float);
	void setScale(float, float);
	void setScale(const sf::Vector2f&);

	const sf::Vector2f getOrigin();
	const sf::Vector2f getPosition();
	float getRotation();
	const sf::Vector2f getScale();

	const sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();



private:

	sf::Sprite* sprite;

	TextureDrawer* parent_texture;
};

#endif /* SRC_SPRITECOMPONENT_H_ */
