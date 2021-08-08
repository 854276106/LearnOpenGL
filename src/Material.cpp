#include "Material.h"

Material::Material(Shader* _shader, glm::vec3 _ambient, unsigned int _diffues, unsigned int _specular, float _shiness)
	:shader(_shader), ambient(_ambient), diffues(_diffues), specular(_specular), shiness(_shiness)
{

}

Material::~Material()
{
}
