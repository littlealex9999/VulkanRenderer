#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "Vertex.h"

class Mesh
{
public:
	Mesh(VkDevice* device);
	Mesh(const Mesh& other) = default;
	Mesh& operator=(Mesh const& other) = delete;
	~Mesh() = default;

	static std::vector<Mesh> LoadMesh(VkDevice* device, std::string filepath);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

private:
	VkDevice* device;
};