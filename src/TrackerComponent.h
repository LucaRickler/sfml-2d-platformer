#ifndef SRC_TRACKERCOMPONENT_H_
#define SRC_TRACKERCOMPONENT_H_

#include "Component.h"

class TrackerComponent: public Component {
public:
	enum TrackerMode{
		MODE_MOUSE,
		MODE_PLAYER,
		MODE_TARGET
	};

	TrackerComponent();
	TrackerComponent(TrackerMode);
	TrackerComponent(TrackerMode, Entity*);
	virtual ~TrackerComponent();

	virtual void Update();

	virtual void SetWorldSpace(WorldSpace*);

	void setTarget(Entity*);
private:
	TrackerMode mode;
	Entity* target;
};

#endif /* SRC_TRACKERCOMPONENT_H_ */
