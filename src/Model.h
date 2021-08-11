#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"

class Model
{
public:
	Model(std::string const &path);
	~Model();
	void Draw(const Shader& shader);
public:
	std::vector<Mesh> meshes;
	std::string directory;
private:
	void loadModel(std::string const &path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

