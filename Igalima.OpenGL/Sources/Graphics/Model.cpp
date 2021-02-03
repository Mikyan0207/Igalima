#include <Graphics/Model.h>
#include <stb/stb_image.h>

Model::Model(const std::string& path)
{
	LoadModel(path);
}

void Model::Draw(Shader& shader)
{
	for (auto& mesh : m_Meshes)
		mesh.Draw(shader);
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "[Model] Assimp Error: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_Directory = path.substr(0, path.find_last_of('/'));

	std::cout << "Directory: " << m_Directory << std::endl;

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i += 1)
	{
		auto* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.emplace_back(ProcessMesh(mesh, scene));
	}

	for (uint32_t i = 0; i < node->mNumChildren; i += 1)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<GLTexture> textures;
	std::unordered_map<std::string, GLColor> colors;

	vertices.reserve(mesh->mNumVertices);

	for (uint32_t i = 0; i < mesh->mNumVertices; i += 1)
	{
		glm::vec2 textCoords(0.0f, 0.0f);

		if (mesh->mTextureCoords[0])
		{
			textCoords.x = mesh->mTextureCoords[0][i].x;
			textCoords.y = mesh->mTextureCoords[0][i].y;
		}
		
		vertices.emplace_back(Vertex {
			glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
			glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
			textCoords,
			glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z),
			glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z)
		});
	}

	for (uint32_t i = 0; i < mesh->mNumFaces; i += 1)
	{
		const auto& face = mesh->mFaces[i];

		for (uint32_t j = 0; j < face.mNumIndices; j += 1)
			indices.emplace_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		auto* material = scene->mMaterials[mesh->mMaterialIndex];

		// Materials ???????
		aiColor3D color(0.0f, 0.0f, 0.0f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		colors.insert(std::make_pair("diffuse", GLColor { color.r, color.g, color.b, 1.0f }));

		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
		colors.insert(std::make_pair("specular", GLColor{ color.r, color.g, color.b, 1.0f }));

		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
		colors.insert(std::make_pair("ambient", GLColor{ color.r, color.g, color.b, 1.0f }));

		// Textures
		const auto diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		const auto specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		const auto normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		const auto heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures, colors);
}

std::vector<GLTexture> Model::LoadMaterialTextures(aiMaterial* material, const aiTextureType& type, const std::string& typeName)
{
	std::vector<GLTexture> textures;

	for (uint32_t i = 0; i < material->GetTextureCount(type); i += 1)
	{
		aiString str;

		material->GetTexture(type, i, &str);

		auto skip = false;
		for (auto& j : m_TexturesLoaded)
		{
			if (std::strcmp(j.Path.data(), str.C_Str()) == 0)
			{
				textures.push_back(j);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			GLTexture texture;
			texture.Id = TextureFromFile(str.C_Str(), m_Directory, false);
			texture.Type = typeName;
			texture.Path = str.C_Str();
			textures.push_back(texture);
			m_TexturesLoaded.push_back(texture);
		}
	}

	return textures;
}

uint32_t Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	const auto filename =  directory + '/' + path;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	auto* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
