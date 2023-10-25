#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>

struct UniformBufferObject
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

template <class T>
class UniformBuffer
{
public:
	UniformBuffer(size_t size)
	{
		uniformBuffers.resize(size);
		uniformBuffersMemory.resize(size);
		uniformBuffersMapped.resize(size);
	}

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
};