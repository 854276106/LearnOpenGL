#include "Model.h"

Model::Model(std::string const& path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(const Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string const& path)
{
	Assimp::Importer importer;
	std::cout << path << std::endl;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | aiProcess_GenSmoothNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of("\\"));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	std::cout << "mNumMeshes:" << node->mNumMeshes << std::endl;
	std::cout << "mNumChildren:" << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		std::cout << "mNumMeshes->i:" << i << std::endl;
		aiMesh* currMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.emplace_back(processMesh(currMesh,scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		std::cout << "mNumChildren->i:" << i << std::endl;
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> tempTextures;

	glm::vec3 temVec;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex;

		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			tempVertex.Normal.x = mesh->mNormals[i].x;
			tempVertex.Normal.y = mesh->mNormals[i].y;
			tempVertex.Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0] != nullptr)
		{
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		tempVertices.emplace_back(tempVertex);
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			{
				tempIndices.emplace_back(mesh->mFaces[i].mIndices[j]);
			}
		}

	}
	return Mesh(tempVertices,tempIndices,tempTextures);
}

