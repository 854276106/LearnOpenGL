#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//ƽ�й�
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
	void UpdateDirection();
public:
	glm::vec3 position;
	glm::vec3 angles;  //��ת�Ƕ�
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
};

//���Դ
class LightPoint
{
public:
	LightPoint(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

public:
	glm::vec3 position;
	glm::vec3 angles;  //��ת�Ƕ�
	glm::vec3 color;

public:
	//˥������
	float constant;  //����
	float linear;   //һ��
	float quadratic;  //����
};

//�۹�
class LightSpot
{
public:
	LightSpot(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();
	void UpdateDirection();
public:
	glm::vec3 position;
	glm::vec3 angles;  //��ת�Ƕ�
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

public:
	float cosPhy = 0.9f;
};