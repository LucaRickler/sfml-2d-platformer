#include "Component.h"

Component::Component() {
}

Component::~Component() {
}

const std::string Component::getType() {
	return type;
}

Entity* Component::getEntity() {
	return owner;
}

