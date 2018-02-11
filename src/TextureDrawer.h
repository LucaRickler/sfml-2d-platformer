#ifndef SRC_TEXTUREDRAWER_H_
#define SRC_TEXTUREDRAWER_H_

#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

class TextureDrawer {
public:
	TextureDrawer();
	TextureDrawer(int x, int y);
	virtual ~TextureDrawer();

	const sf::Texture& Draw();

	void addSprite(sf::Drawable*);
	void removeSprite(sf::Drawable*);

	void setBackground(const sf::Color&);
	const sf::Color& getBackground();

private:
	std::vector<sf::Drawable*> sprites;
	sf::RenderTexture texture;
	sf::Color background;
	sf::Vector2i size;
};

#endif /* SRC_TEXTUREDRAWER_H_ */
