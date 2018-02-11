/*
 * SpriteComponent.cpp
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent() {
	this->type = "SpriteComponent";
	this->sprite = new sf::Sprite();

	this->parent_texture = nullptr;
	world = nullptr;

}

SpriteComponent::SpriteComponent(TextureDrawer* t) {
	this->type = "SpriteComponent";
	this->sprite = new sf::Sprite();

	parent_texture = t;
	parent_texture->addSprite(sprite);
}

SpriteComponent::~SpriteComponent() {
	delete sprite;
}

void SpriteComponent::SetWorldSpace(WorldSpace* w) {
	this->world = w;
	setParentTexture(w->getWorldTexture());
	//if(w != nullptr)
	//	w->world_texture->addSprite(sprite);
}

void SpriteComponent::setParentTexture(TextureDrawer* t) {
	if(parent_texture != nullptr)
		parent_texture->removeSprite(sprite);
	parent_texture = t;
	t->addSprite(sprite);
}

TextureDrawer* SpriteComponent::getParentTexture() {
	return parent_texture;
}

void SpriteComponent::setTexture(const sf::Texture& t) {
	sprite->setTexture(t);
	getEntity()->rect = new sf::FloatRect(getGlobalBounds());
}

void SpriteComponent::setColor(const sf::Color& c) {
	sprite->setColor(c);
}

const sf::Color& SpriteComponent::getColor() {
	return sprite->getColor();
}

const sf::Transform& SpriteComponent::getTransform() {
	return sprite->getTransform();
}

const sf::Vector2f SpriteComponent::getOrigin() {
	return sprite->getOrigin();
}

const sf::Vector2f SpriteComponent::getPosition() {
	return sprite->getPosition();
}

float SpriteComponent::getRotation() {
	return sprite->getRotation();
}

const sf::Vector2f SpriteComponent::getScale() {
	return sprite->getScale();
}

void SpriteComponent::setPosition(float x, float y) {
	sprite->setPosition(x,y);
}

void SpriteComponent::setPosition(const sf::Vector2f& position) {
	sprite->setPosition(position);
}

void SpriteComponent::setRotation(float r) {
	sprite->setRotation(r);
}

void SpriteComponent::setScale(float xscale, float yscale) {
	sprite->setScale(xscale, yscale);
}

void SpriteComponent::setOrigin(float x, float y) {
	sprite->setOrigin(x,y);
}

void SpriteComponent::setOrigin(const sf::Vector2f& o) {
	sprite->setOrigin(o);
}

void SpriteComponent::setScale(const sf::Vector2f& scale) {
	sprite->setScale(scale);
}

void SpriteComponent::Update() {
	setOrigin(this->getEntity()->transformable->getOrigin());
	setPosition(this->getEntity()->transformable->getPosition());
	setScale(this->getEntity()->transformable->getScale());
	setRotation(this->getEntity()->transformable->getRotation());

	delete getEntity()->rect;
	getEntity()->rect = new sf::FloatRect(getGlobalBounds());
}

const sf::FloatRect SpriteComponent::getGlobalBounds() {
	return sprite->getGlobalBounds();
}

sf::FloatRect SpriteComponent::getLocalBounds() {
	return sprite->getLocalBounds();
}
