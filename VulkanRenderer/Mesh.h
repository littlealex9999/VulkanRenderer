#pragma once
#include <string>
#include <vector>
#include "Vertex.h"
#include <vulkan/vulkan.h>

class Mesh
{
public:
	static Mesh LoadModel(std::string);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
};