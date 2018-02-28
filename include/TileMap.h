#ifndef SRC_TILEMAP_H_
#define SRC_TILEMAP_H_

class TileMap;

#include <unordered_map>
#include "Component.h"
#include "TileMapSprite.h"

enum TileType{
	BLOCK,
	EMPTY,
	GROUND,
	ONE_WAY
};

typedef std::pair<int, TileType> TileMappingPair;
typedef std::unordered_map<int, TileType> TileMapping;

class TileMap: public Component {
public:
	TileMap();
	virtual ~TileMap();

	void LoadMap(int, int, sf::Vector2i*, int*, const TileMapping&, const std::string&);

	virtual void Update();

	virtual void SetWorldSpace(WorldSpace*);

	TileType getTile(int x, int y);

	bool isOneWay(int x, int y);
	bool isGround(int x, int y);
	bool isObstacle(int x, int y);
	bool isEmpty(int x, int y);

	sf::Vector2i getMapPointAt(const sf::Vector2f&);
	sf::Vector2f getTilePosition(const sf::Vector2i&);
	sf::Vector2f getTilePosition(int x, int y);
	sf::Vector2i getTileSize();
	int getTileXIndex(float x);
	int getTileYIndex(float y);

	sf::Vector2i getMapSize();

private:

	int ConvertToMonoC(int x, int y);

	std::unordered_map<int, TileType> legend;

	int* tiles;
	sf::Vector2i* tile_size;
	int width;
	int height;

	TileMapSprite* sprite;

};

#endif /* SRC_TILEMAP_H_ */
