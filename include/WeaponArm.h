/*
 * WeaponArm.h
 *
 *  Created on: 04/ott/2016
 *      Author: luca
 */

#ifndef SRC_WEAPONARM_H_
#define SRC_WEAPONARM_H_

#include "TrackerComponent.h"
#include "RigidBody.h"
#include "SpriteComponent.h"
#include <functional>
#include <cmath>

class WeaponArm: public TrackerComponent {
public:
	WeaponArm();
	WeaponArm(TrackerMode);
	WeaponArm(TrackerMode, Entity*);
	virtual ~WeaponArm();

	virtual void Update();

	virtual void SetWorldSpace(WorldSpace*);

	void Shoot();

	void setTexture(const sf::Texture&);
	void setSpeed(double);

	std::function<void(void)> getShootFunction();
private:


	double speed;
	sf::Texture bullet_texture;
};

#endif /* SRC_WEAPONARM_H_ */
