/*
 * AIController.h
 *
 *  Created on: 27/set/2016
 *      Author: luca
 */

#ifndef SRC_AICONTROLLER_H_
#define SRC_AICONTROLLER_H_

#include "Component.h"
#include "Character.h"

class AIController: public Component {
public:
	enum AIMode {
		AGGRO,
		KEEP_POST,
		IDLE
	};
	AIController();
	//AIController();
	virtual ~AIController();

	virtual void Update();

	virtual void SetWorldSpace(WorldSpace*);

	void LinkCharacter(Character*);

	void setMode(AIMode mode);

	sf::Vector2f getPlayerDist();

private:
	Character* chara;

	sf::Vector2i post;

	AIMode mode;

	bool* controller;
};

#endif /* SRC_AICONTROLLER_H_ */
