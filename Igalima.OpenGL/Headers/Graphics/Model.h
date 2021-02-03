#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include <OpenGL/GLColor.h>

class Model
{
public:
	explicit Model(const std::string& path);
	Model(const Model&) = default;
	Model(Model&&) noexcept = default;
	~Model() = default;

public:
	Model& operator=(const Model&) = default;
	Model& operator=(Model&&) noexcept = default;

public:
	void Draw(Shader& shader);

private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<GLTexture> LoadMaterialTextures(aiMaterial* material, const aiTextureType& type, const std::string& typeName);
	static uint32_t TextureFromFile(const char* path, const std::string& directory, bool gamma);
private:
	std::vector<Mesh> m_Meshes;
	std::vector<GLTexture> m_TexturesLoaded;
	std::string m_Directory;
};
