#pragma once
#include <vulkan/vulkan.h>

class Texture
{
public:
	VkImage image;
	VkDeviceMemory imageMemory;
	VkImageView imageView;
	VkFormat format;

	void Cleanup(VkDevice device);
};