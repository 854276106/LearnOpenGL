#pragma once
#include"Shader.h"

class Material
{
public:
	Material(Shader * _shader, glm::vec3 _ambient, unsigned int _diffues, unsigned int _specular, float _shiness);
	~Material();
public:
	Shader* shader;
	glm::vec3 ambient;
	unsigned int diffues;
	unsigned int specular;
	float shiness;
};

