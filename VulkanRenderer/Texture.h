#pragma once
#include <vulkan/vulkan.h>

class Texture
{
public:

private:
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
};