#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//平行光
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
	void UpdateDirection();
public:
	glm::vec3 position;
	glm::vec3 angles;  //旋转角度
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
};

//点光源
class LightPoint
{
public:
	LightPoint(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

public:
	glm::vec3 position;
	glm::vec3 angles;  //旋转角度
	glm::vec3 color;

public:
	//衰减参数
	float constant;  //常数
	float linear;   //一次
	float quadratic;  //二次
};

//聚光
class LightSpot
{
public:
	LightSpot(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();
	void UpdateDirection();
public:
	glm::vec3 position;
	glm::vec3 angles;  //旋转角度
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

public:
	float cosPhy = 0.9f;
};