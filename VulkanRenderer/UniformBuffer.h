#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

class UniformBuffer
{
public:
	void Resize(size_t size);
	void Cleanup(VkDevice device, size_t size);

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
};