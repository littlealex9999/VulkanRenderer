#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <unordered_map>

Mesh Mesh::LoadModel(std::string filepath)
{
	Assimp::Importer importer;

	unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_PreTransformVertices | aiProcess_SortByPType | aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(filepath, flags);

	if (scene == nullptr) {
		throw std::runtime_error("failed to load model");
	}

	for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[0];
		Mesh retMesh;

		std::unordered_map<Vertex, uint32_t> uniqueVertices {};
		for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
			for (uint32_t k = 0; k < mesh->mFaces[j].mNumIndices; k++) {
				Vertex vertex {};
				uint32_t index = mesh->mFaces[j].mIndices[k];

				vertex.pos = glm::vec3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);

				if (mesh->GetNumColorChannels() != 0) {
					vertex.color = glm::vec3(mesh->mColors[index]->r, mesh->mColors[index]->g, mesh->mColors[index]->b);
				} else {
					vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);
				}

				if (mesh->GetNumUVChannels() != 0) {
					vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
				} else {
					vertex.texCoord = glm::vec2(0.0f, 0.0f);
				}

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(retMesh.vertices.size());
					retMesh.vertices.push_back(vertex);
				}

				retMesh.indices.push_back(uniqueVertices[vertex]);
			}
		}

		return retMesh;
	}
}