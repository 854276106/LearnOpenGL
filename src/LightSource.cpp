#include "LightSource.h"

LightDirectional::LightDirectional(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color)
	:position(_positon), angles(_angles), color(_color)
{
	this->UpdateDirection();
}

LightDirectional::~LightDirectional()
{
}

void LightDirectional::UpdateDirection()
{
	this->direction = glm::vec3(0, 0, 1.0f);
	this->direction = glm::rotateX(direction, angles.x);
	this->direction = glm::rotateY(direction, angles.y);
	this->direction = glm::rotateZ(direction, angles.z);
}

LightPoint::LightPoint(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color)
	:position(_positon), angles(_angles), color(_color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

LightPoint::~LightPoint()
{
}

LightSpot::LightSpot(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color)
	:position(_positon), angles(_angles), color(_color)
{
	this->UpdateDirection();
}

LightSpot::~LightSpot()
{
}

void LightSpot::UpdateDirection()
{
	this->direction = glm::vec3(0, 0, 1.0f);
	this->direction = glm::rotateX(direction, angles.x);
	this->direction = glm::rotateY(direction, angles.y);
	this->direction = glm::rotateZ(direction, angles.z);
}
