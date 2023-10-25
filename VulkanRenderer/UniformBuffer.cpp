#include "UniformBuffer.h"

void UniformBuffer::Resize(size_t size)
{
	uniformBuffers.resize(size);
	uniformBuffersMemory.resize(size);
	uniformBuffersMapped.resize(size);
}

void UniformBuffer::Cleanup(VkDevice device, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		vkDestroyBuffer(device, uniformBuffers[i], nullptr);
		vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
	}
}