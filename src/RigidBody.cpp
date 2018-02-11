/*
 * PhysicsComponent.cpp
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(float mass) {
	this->mass = mass;

	onGround = false;
	pushesLeftWall = false;
	pushesRightWall = false;
	atCeiling = false;

	has_moved = false;

	hit_detection = new bool[NUMBER_OF_DIRECTIONS];
	for(int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
		hit_detection[i] = false;

	bullet = false;
//	bullet_bounds = nullptr;

}

RigidBody::~RigidBody() {
	world->deleteRigidBody(this);

}

void RigidBody::SetWorldSpace(WorldSpace* w) {
	this->world = w;

	position = getEntity()->transformable->getPosition();
	setSpeed(sf::Vector2f(0,0));
	setBounds(getEntity()->rect);

	world->addRigidBody(this);
}

void RigidBody::setBounds(sf::FloatRect* rect) {
	bounds = rect;
}

sf::FloatRect* RigidBody::getBounds() {
	if(!bullet)
		return bounds;
	else {
		if(bullet_bounds != nullptr)
			delete bullet_bounds;
		auto size = sf::Vector2f(std::fabs(old_position.x - position.x) + bounds->width,
								 std::fabs(old_position.y - position.y) + bounds->height);
		auto origin = sf::Vector2f((old_position.x < position.x) ? old_position.x : position.x,
								   (old_position.y < position.y) ? old_position.y : position.y);
		bullet_bounds = new sf::FloatRect(origin, size);
		return bullet_bounds;
		//return bounds;
	}
	return bounds;
}

bool RigidBody::hasMoved() {
	return has_moved;
}

void RigidBody::RecordHit(HitDirection direct) {
	hit_detection[direct] = true;
}

void RigidBody::setBullet() {
	bullet = true;
}

bool RigidBody::isBullet() {
	return bullet;
}

bool RigidBody::RetriveHit(HitDirection direct) {
	bool out = hit_detection[direct];
	hit_detection[direct] = false;
	return out;
}

void RigidBody::setSpeed(const sf::Vector2f& v) {
	speed = v;
}

void RigidBody::addSpeed(const sf::Vector2f& v) {
	speed += v;
}

void RigidBody::setXSpeed(float vx) {
	speed.x = vx;
}

void RigidBody::setYSpeed(float vy) {
	speed.y = vy;
}

void RigidBody::Update() {
	old_position = position;
	old_speed = speed;

	wasOnGround = onGround;
	pushedRightWall = pushesRightWall;
	pushedLeftWall = pushesLeftWall;
	wasAtCeiling = atCeiling;

	float t = world->getTimeStep();

	position += speed*t;

	if(position.x < 0.0f)
		position.x = 0.0f;
	else if (position.x >= world->getMap()->getMapSize().x - getBounds()->width)
		position.x = world->getMap()->getMapSize().x - getBounds()->width;
	if(position.y < 0.0f)
		position.y = 0.0f;
	else if (position.y >= world->getMap()->getMapSize().y - getBounds()->height)
		position.y = world->getMap()->getMapSize().y  - getBounds()->height;

	float groundY = 0.0f, ceilingY = 0.0f;
	float rightWallX = 0.0f, leftWallX = 0.0f;

	if(speed.y <= 0 && HasGround(old_position, position, speed, groundY)){
		//std::cout<<"on ground\n";
		position.y = groundY + world->getMap()->getTileSize().y;
		speed.y = 0.0f;
		onGround = true;
	} else if(speed.y <= 0 && RetriveHit(DOWN)) {
		speed.y = 0.0f;
		onGround = true;
	} else
		onGround = false;

	//std::cout<<"Pushing?\n";

	if (speed.x <= 0.0f && CollidesWithLeftWall(old_position, position, leftWallX))
	{
	    if (old_position.x >= leftWallX)
	    {
	    	//std::cout<<"pushes left\n";
	    	position.x = leftWallX;
	        pushesLeftWall = true;
	    }
	    speed.x = (speed.x > 0.0f) ? speed.x : 0.0f;
	}
	else if (speed.x <= 0.0f && RetriveHit(LEFT)) {
		if (old_position.x >= position.x)
		{
			pushesLeftWall = true;
		}
		speed.x = (speed.x > 0.0f) ? speed.x : 0.0f;
	}
	else
		pushesLeftWall = false;



	if (speed.x >= 0.0f && CollidesWithRightWall(old_position, position, rightWallX)) {
	    if (old_position.x + getBounds()->width <= rightWallX)
	    {
	    	//std::cout<<"pushes right\n";
	    	position.x = rightWallX - getBounds()->width;
	    	pushesRightWall = true;
	    }

	    speed.x = (speed.x < 0.0f) ? speed.x : 0.0f;
	}
	else if (speed.x <= 0.0f && RetriveHit(RIGHT)) {
		if (old_position.x <= position.x)
		{
			pushesRightWall = true;
		}
		speed.x = (speed.x < 0.0f) ? speed.x : 0.0f;
	}
	else
		pushesRightWall = false;


	if (speed.y > 0.0f
	    && HasCeiling(old_position, position, ceilingY))
	{
		//std::cout<<"head hit\n";
		position.y = ceilingY - getBounds()->height;
	    speed.y = 0.0f;
	    atCeiling = true;
	}
	else if (speed.y > 0.0f && RetriveHit(UP)) {
			//std::cout<<"head hit\n";
			speed.y = 0.0f;
		    atCeiling = true;
		}
		else
		    atCeiling = false;

	if(old_position != position) {
		has_moved = true;
		world->CheckCollisions(this);
		getEntity()->transformable->setPosition(position);
		setBounds(getEntity()->rect);
	} else
		has_moved = false;

/*	if(speed.x > 0) {
		hit_detection[LEFT] = false;
	} else if (speed.x < 0)
		hit_detection[RIGHT] = false;
	if(speed.y > 0) {
		hit_detection[DOWN] = false;
	} else if (speed.y < 0)
		hit_detection[UP] = false;*/

}

bool RigidBody::HasGround(sf::Vector2f oldPosition, sf::Vector2f position, sf::Vector2f speed, float& groundY) {
	auto newBottomRight = position + sf::Vector2f(getBounds()->width -2.0f, -1.0f);
	oldPosition += sf::Vector2f(2.0f, -1.0f);
	position += sf::Vector2f(2.0f, -1.0f);

	int endY = world->getMap()->getTileYIndex(position.y);
	int begY = (world->getMap()->getTileYIndex(oldPosition.y) - 1 > endY) ? world->getMap()->getTileYIndex(oldPosition.y) - 1 : endY;
	int dist = (std::abs(endY - begY) > 1) ? std::abs(endY - begY) : 1;

	int tileIndexX;

	for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
	{
		float t = (float)std::abs(endY - tileIndexY) / dist;
		auto bottomLeft = position + sf::Vector2f(t*(oldPosition.x - position.x), t*(oldPosition.y - position.y));
		auto bottomRight = sf::Vector2f(bottomLeft.x + getBounds()->width, bottomLeft.y);

		for (auto checkedTile = bottomLeft; ; checkedTile.x += world->getMap()->getTileSize().x)
		{
			checkedTile.x = (checkedTile.x < bottomRight.x) ? checkedTile.x : bottomRight.x;

			tileIndexX = world->getMap()->getTileXIndex(checkedTile.x);

			groundY = (float)tileIndexY * world->getMap()->getTileSize().y;

			if (world->getMap()->isObstacle(tileIndexX, tileIndexY))
				return true;

			if (checkedTile.x >= bottomRight.x)
				break;
		}
	}

	return false;
}

bool RigidBody::HasCeiling(sf::Vector2f oldPosition, sf::Vector2f position, float& ceilingY)
{
    ceilingY = 0.0f;

    auto oldTopRight = oldPosition + sf::Vector2f(getBounds()->width -2.0f, getBounds()->height +1.0f);
    auto newTopRight = position + sf::Vector2f(getBounds()->width -2.0f, getBounds()->height +1.0f);
    auto newTopLeft = position + sf::Vector2f(2.0f, getBounds()->height +1.0f);

    int endY = world->getMap()->getTileYIndex(newTopRight.y);
    int begY = (world->getMap()->getTileYIndex(oldPosition.y) + 1 < endY) ? world->getMap()->getTileYIndex(oldPosition.y) + 1 : endY;
    int dist = (std::abs(endY - begY) > 1) ? std::abs(endY - begY) : 1;

    int tileIndexX;

    for (int tileIndexY = begY; tileIndexY <= endY; ++tileIndexY)
    {
    	float t = (float)std::abs(endY - tileIndexY) / dist;
    	auto topRight = newTopRight + sf::Vector2f(t*(oldTopRight.x - newTopRight.x), t*(oldTopRight.y - newTopRight.y));
        auto topLeft = sf::Vector2f(topRight.x - getBounds()->width, topRight.y);

        for (auto checkedTile = topLeft; ; checkedTile.x += world->getMap()->getTileSize().x)
        {
            checkedTile.x = (checkedTile.x < topRight.x) ? checkedTile.x : topRight.x;

            tileIndexX = world->getMap()->getTileXIndex(checkedTile.x);

            if (world->getMap()->isObstacle(tileIndexX, tileIndexY))
            {
                ceilingY = (float)tileIndexY * world->getMap()->getTileSize().y;
                return true;
            }

            if (checkedTile.x >= topRight.x)
                break;
        }
    }

    return false;
}

bool RigidBody::CollidesWithLeftWall(sf::Vector2f oldPosition, sf::Vector2f position, float& wallX)
{
    wallX = 0.0f;

    auto newTopLeft = position + sf::Vector2f(-1.0f, getBounds()->height);
    position += sf::Vector2f(-1.0f, 0.0f);
    oldPosition += sf::Vector2f(-1.0f, 0.0f);

    int tileIndexY;

    int endX = world->getMap()->getTileXIndex(position.x);
    int begX = (world->getMap()->getTileXIndex(oldPosition.x) - 1 > endX) ? world->getMap()->getTileXIndex(oldPosition.x) - 1 : endX;
    int dist = (std::abs(endX - begX) > 1) ? std::abs(endX - begX) : 1;

    for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
    {
    	//std::cout<<tileIndexX<<std::endl;
    	float t = (float)std::abs(endX - tileIndexX) / dist;
    	auto bottomLeft = position + sf::Vector2f(t*(oldPosition.x - position.x), t*(oldPosition.y - position.y));
        auto topLeft = bottomLeft + sf::Vector2f(0.0f, getBounds()->height);

        for (auto checkedTile = bottomLeft; ; checkedTile.y += world->getMap()->getTileSize().y)
        {
        	//std::cout<<checkedTile.x<<std::endl;
            checkedTile.y = (checkedTile.y < topLeft.y) ? checkedTile.y : topLeft.y;

            tileIndexY = world->getMap()->getTileYIndex(checkedTile.y);

            //std::cout<<tileIndexY<<"\n";
            if (world->getMap()->isObstacle(tileIndexX, tileIndexY))
            {
                wallX = (float)(tileIndexX +1) * world->getMap()->getTileSize().x;
                if(wallX < 0.0f)
                	wallX = 0.0f;
                return true;
            }

            if (checkedTile.y >= topLeft.y)
                break;
        }
    }

    return false;
}

bool RigidBody::CollidesWithRightWall(sf::Vector2f oldPosition, sf::Vector2f position, float& wallX)
{
    wallX = 0.0f;

    auto oldBottomRight = oldPosition + sf::Vector2f(getBounds()->width +2.0f, 0);
    auto newBottomRight = position + sf::Vector2f(getBounds()->width +2.0f, 0);
    auto newTopRight = newBottomRight + sf::Vector2f(2.0f, getBounds()->height);

    int endX = world->getMap()->getTileXIndex(newBottomRight.x);
    int begX = (world->getMap()->getTileXIndex(oldBottomRight.x) - 1 > endX) ? world->getMap()->getTileXIndex(oldBottomRight.x) - 1 : endX;
    int dist = (std::abs(endX - begX) > 1) ? std::abs(endX - begX) : 1;

    int tileIndexY;

    for (int tileIndexX = begX; tileIndexX <= endX; ++tileIndexX)
    {
    	float t = (float)std::abs(endX - tileIndexX) / dist;
    	auto bottomRight = newBottomRight + sf::Vector2f(t*(oldBottomRight.x - newBottomRight.x), t*(oldBottomRight.y - newBottomRight.y));
        auto topRight = bottomRight + sf::Vector2f(0.0f, getBounds()->height);

        for (auto checkedTile = bottomRight; ; checkedTile.y += world->getMap()->getTileSize().y)
        {
            checkedTile.y = (checkedTile.y < topRight.y) ? checkedTile.y : topRight.y;

            tileIndexY = world->getMap()->getTileYIndex(checkedTile.y);

            if (world->getMap()->isObstacle(tileIndexX, tileIndexY))
            {
                wallX = (float)tileIndexX * world->getMap()->getTileSize().x;
                return true;
            }

            if (checkedTile.y >= topRight.y)
                break;
        }
    }

    return false;
}

const float RigidBody::getYSpeed() {
	return speed.y;
}

const float RigidBody::getXSpeed() {
	return speed.y;
}

sf::Vector2f RigidBody::round_vector(const sf::Vector2f& vec){
	return sf::Vector2f(std::round(vec.x), std::round(vec.y));
}

sf::Vector2f RigidBody::getPosition() {
	return position;
}

void RigidBody::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}
