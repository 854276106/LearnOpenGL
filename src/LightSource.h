#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//ƽ�й�
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, 
		glm::vec3 _direction, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 direction;
	glm::vec3 color;
};

//���Դ
class LightPoint
{
public:
	LightPoint(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _positon, 
		float _constant, float _linear, float _quadratic, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	glm::vec3 color;
	//˥������
	float constant;  //����
	float linear;   //һ��
	float quadratic;  //����
};

//�۹�
class LightSpot
{
public:
	LightSpot(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _positon, glm::vec3 _direction,
		float _constant, float _linear, float _quadratic, float _cutOff, float _outerCutOff, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();
	void UpdateDirection();
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	//˥������
	float constant;  //����
	float linear;   //һ��
	float quadratic;  //����

	float cutOff;
	float outerCutOff;
public:
};