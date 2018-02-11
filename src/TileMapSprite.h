/*
 * TileMapSprite.h
 *
 *  Created on: 16/set/2016
 *      Author: luca
 */

#ifndef SRC_TILEMAPSPRITE_H_
#define SRC_TILEMAPSPRITE_H_

#include <SFML/Graphics.hpp>

class TileMapSprite: public sf::Drawable, public sf::Transformable {
public:
	TileMapSprite();
	virtual ~TileMapSprite();

	bool Load(const std::string& tileset, sf::Vector2i& tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};


#endif /* SRC_TILEMAPSPRITE_H_ */
