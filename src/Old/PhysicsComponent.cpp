/*
 * PhysicsComponent.cpp
 *
 *  Created on: 14/set/2016
 *      Author: luca
 */

#include "PhysicsComponent.h"

RigidBody::RigidBody(float density, BodyType btype) {
	type = "PhysicsComponent";
	this->density = density;
	this->btype = btype;

	def = new b2BodyDef();

	switch(btype){
	case DYNAMIC:{
		def->type = b2_dynamicBody;
		break;
	}
	default:
		break;
	}
	world = nullptr;
	def->bullet = true;

}

RigidBody::~RigidBody() {
	delete def;
	world->getB2World()->DestroyBody(body);
}

void RigidBody::SetWorldSpace(WorldSpace* w) {
	this->world = w;
	def->position.Set(getEntity()->transformable->getPosition().x/UNIT_SCALE + 0.5*getEntity()->rect->width/UNIT_SCALE, getEntity()->transformable->getPosition().y/UNIT_SCALE + 0.5*getEntity()->rect->height/UNIT_SCALE);
	//def->position.Set(getEntity()->transformable->getPosition().x/UNIT_SCALE, getEntity()->transformable->getPosition().y/UNIT_SCALE);
	body = w->getB2World()->CreateBody(def);

	b2PolygonShape shape;
	//b2Vec2 verts[4];
	/*verts[0].Set(-0.5*getEntity()->rect->width/UNIT_SCALE, -0.5*getEntity()->rect->height/UNIT_SCALE);
	verts[1].Set(-0.5*getEntity()->rect->width/UNIT_SCALE, +0.5*getEntity()->rect->height/UNIT_SCALE);
	verts[2].Set(+0.5*getEntity()->rect->width/UNIT_SCALE, +0.5*getEntity()->rect->height/UNIT_SCALE);
	verts[3].Set(+0.5*getEntity()->rect->width/UNIT_SCALE, -0.5*getEntity()->rect->height/UNIT_SCALE);*/
	shape.SetAsBox(0.5*getEntity()->rect->width/UNIT_SCALE, 0.5*getEntity()->rect->height/UNIT_SCALE);
	//shape.Set(verts, 4);
	b2FixtureDef fix;
	fix.shape = &shape;
	fix.density = density;
	fix.friction = 0.3f;

	body->CreateFixture(&fix);

}

void RigidBody::FixInSpace() {
}

bool RigidBody::isFixedInSpace() {
}

void RigidBody::setBounds(const sf::FloatRect& rect) {
}

const sf::FloatRect& RigidBody::getBounds() {
}

void RigidBody::Update() {
	getEntity()->transformable->setPosition(body->GetPosition().x*UNIT_SCALE - 0.5*getEntity()->rect->width, body->GetPosition().y*UNIT_SCALE - 0.5*getEntity()->rect->height);
	//getEntity()->transformable->setPosition(body->GetPosition().x*UNIT_SCALE, body->GetPosition().y*UNIT_SCALE);
	getEntity()->transformable->setRotation(body->GetAngle()*180.0f/3.14);
}

void RigidBody::ApplyForceToCenter(const b2Vec2& f, bool wake) {
	body->ApplyForceToCenter(f, wake);
}

void RigidBody::ApplyForce() {
}

void RigidBody::ApplyTorque(float t, bool wake) {
	body->ApplyTorque(t, wake);
}

void RigidBody::ApplyImpulseToCenter(const b2Vec2& p, bool wake) {
	body->ApplyLinearImpulseToCenter(p,wake);
}
