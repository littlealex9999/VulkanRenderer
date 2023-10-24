#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <iostream>

Mesh::Mesh(VkDevice* device)
{
	this->device = device;
}

std::vector<Mesh> Mesh::LoadMesh(VkDevice* device, std::string filepath)
{
	Assimp::Importer importer;

	unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_PreTransformVertices | aiProcess_SortByPType | aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(filepath, flags);

	if (scene == nullptr) {
		throw std::runtime_error("failed to load model");
	}

	std::vector<Mesh> meshes;

	for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
		Mesh meshObject { device };

		aiMesh* mesh = scene->mMeshes[i];

		size_t numV = mesh->mNumVertices;
		meshObject.vertices.resize(numV);
		for (uint32_t j = 0; j < numV; j++) {
			meshObject.vertices[j].pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

			if (mesh->GetNumColorChannels() != 0) {
				meshObject.vertices[j].color = glm::vec3(mesh->mColors[j]->r, mesh->mColors[j]->g, mesh->mColors[j]->b);
			}

			if (mesh->GetNumUVChannels() != 0) {
				meshObject.vertices[j].texCoord = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			}

			std::cout << j << std::endl;
			std::cout << meshObject.vertices[j].pos.x << ", " << meshObject.vertices[j].pos.y << ", " << meshObject.vertices[j].pos.z << std::endl;
			//std::cout << meshObject.vertices[j].color.r << ", " << meshObject.vertices[j].color.g << ", " << meshObject.vertices[j].color.b << std::endl;
			//std::cout << meshObject.vertices[j].texCoord.x << ", " << meshObject.vertices[j].texCoord.y << std::endl;
		}

		meshObject.indices.resize(mesh->mNumFaces * 3);
		for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
			meshObject.indices[j * 3] = mesh->mFaces[j].mIndices[0];
			meshObject.indices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
			meshObject.indices[j * 3 + 2] = mesh->mFaces[j].mIndices[2];

			std::cout << meshObject.indices[j * 3] << ", " << meshObject.indices[j * 3 + 1] << ", " << meshObject.indices[j * 3 + 2] << std::endl;
		}

		//std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		//for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
		//	for (uint32_t k = 0; k < mesh->mFaces[j].mNumIndices; k++) {
		//		Vertex vertex{};
		//		uint32_t index = mesh->mFaces[j].mIndices[k];
		//		vertex.pos = glm::vec3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);

		//		if (mesh->GetNumColorChannels() != 0) {
		//			vertex.color = glm::vec3(mesh->mColors[index]->r, mesh->mColors[index]->g, mesh->mColors[index]->b);
		//		}

		//		if (mesh->GetNumUVChannels() != 0) {
		//			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
		//		}

		//		if (uniqueVertices.count(vertex) == 0) {
		//			uniqueVertices[vertex] = static_cast<uint32_t>(meshObject.vertices.size());
		//			meshObject.vertices.push_back(vertex);
		//		}

		//		meshObject.indices.push_back(uniqueVertices[vertex]);
		//	}
		//}

		meshes.push_back(meshObject);
	}

    return meshes;
}
