/*
 * TileMap.cpp
 *
 *  Created on: 16/set/2016
 *      Author: luca
 */

#include "TileMap.h"
#include <iostream>

TileMap::TileMap(){
	type = "TileMap";

	tiles = nullptr;
	width = -1;
	height = -1;
	sprite = new TileMapSprite();
}


void TileMap::LoadMap(int max_x, int max_y, sf::Vector2i* tile_size, int* map, const TileMapping& legend, const std::string& tile_set) {
	this->width = max_x;
	this->height = max_y;
	this->tile_size = tile_size;
	this->legend = legend;

	if(tiles != nullptr)
		delete tiles;

	this->tiles = map;
	sprite->Load(tile_set,*tile_size, map, width, height);
	sprite->setPosition(0,0);
}

TileMap::~TileMap() {
	world->getWorldTexture()->removeSprite(sprite);
	delete sprite;
	delete tiles;
}

void TileMap::Update() {
}

void TileMap::SetWorldSpace(WorldSpace* w) {
	this->world = w;
	w->getWorldTexture()->addSprite(sprite);
}

TileType TileMap::getTile(int x, int y)
{
    if (x < 0 || x >= width
        || y < 0 || y >= height)
        return BLOCK;

    return legend[tiles[ConvertToMonoC(x,y)]];
}

bool TileMap::isOneWay(int x, int y) {
    if (x < 0 || x >= width
        || y < 0 || y >= height)
        return false;

    return (legend[tiles[ConvertToMonoC(x,y)]] == ONE_WAY);
}

bool TileMap::isGround(int x, int y) {
    if (x < 0 || x >= width
       || y < 0 || y >= height)
        return false;

    return (legend[tiles[ConvertToMonoC(x,y)]] == ONE_WAY || legend[tiles[ConvertToMonoC(x,y)]] == BLOCK);
}

bool TileMap::isObstacle(int x, int y) {
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return true;

	return (legend[tiles[ConvertToMonoC(x,y)]] == BLOCK);
	return false;
}

bool TileMap::isEmpty(int x, int y) {
	if (x < 0 || x >= width
		|| y < 0 || y >= height)
		return false;

	return (legend[tiles[ConvertToMonoC(x,y)]] == EMPTY);
}

int TileMap::ConvertToMonoC(int x, int y) {
	return (int)(x + y*width);
}

sf::Vector2i TileMap::getMapPointAt(const sf::Vector2f& global) {
	return sf::Vector2i((global.x)/tile_size->x,(global.y)/tile_size->y);
}

sf::Vector2f TileMap::getTilePosition(const sf::Vector2i& point) {
	return sf::Vector2f(point.x*tile_size->x, point.y*tile_size->y);
}

sf::Vector2f TileMap::getTilePosition(int x, int y) {
	return sf::Vector2f(x*tile_size->x, y*tile_size->y);
}

sf::Vector2i TileMap::getTileSize() {
	return *tile_size;
}

int TileMap::getTileXIndex(float x) {
	return (x/(float)tile_size->x);
}

int TileMap::getTileYIndex(float y) {
	return (y/(float)tile_size->y);
}

sf::Vector2i TileMap::getMapSize() {
	return sf::Vector2i(width*tile_size->x, height*tile_size->y);
}
