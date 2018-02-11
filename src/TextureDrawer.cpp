/*
 * TextureDrawer.cpp
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#include "TextureDrawer.h"

TextureDrawer::TextureDrawer() {
	sprites = std::vector<sf::Drawable*>();
}

TextureDrawer::TextureDrawer(int x, int y) {
	sprites = std::vector<sf::Drawable*>();
	this->size = sf::Vector2i(x,y);
	this->texture.create(x,y);
}

TextureDrawer::~TextureDrawer() {
	// TODO Auto-generated destructor stub
}

const sf::Texture& TextureDrawer::Draw() {
	texture.clear(background);
	std::for_each(sprites.begin(),sprites.end(), [this] (sf::Drawable* c){
		this->texture.draw(*c);
	});
	return texture.getTexture();
}

void TextureDrawer::addSprite(sf::Drawable* c) {
	this->sprites.push_back(c);
}

void TextureDrawer::removeSprite(sf::Drawable* c) {
	sprites.erase(std::remove(sprites.begin(),sprites.end(), c), sprites.end());
}

void TextureDrawer::setBackground(const sf::Color& color) {
	this->background = color;
}

const sf::Color& TextureDrawer::getBackground() {
	return this->background;
}

