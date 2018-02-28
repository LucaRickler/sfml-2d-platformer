#ifndef SRC_COMPONENT_H_
#define SRC_COMPONENT_H_

#include <string>
class Component;
class WorldSpace;

#include "Entity.h"

class Component {
public:
	Component();
	virtual ~Component();
	virtual void Update() = 0;

	virtual void SetWorldSpace(WorldSpace*) = 0;

	const std::string getType();
	Entity* getEntity();

	friend class Entity;

protected:
	std::string type;
	WorldSpace* world;

private:
	Entity* owner;

};

#include "WorldSpace.h"

#endif /* SRC_COMPONENT_H_ */
