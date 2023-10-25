#pragma once
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::string MODEL_PATH = "models/MonkeyBrain.fbx";
const std::string BASECOLOR_TEXTURE_PATH = "textures/MonkeyBrain_BaseColor.png";
const std::string EMISSIVE_TEXTURE_PATH = "textures/MonkeyBrain_Emissive.png";
const std::string HEIGHT_TEXTURE_PATH = "textures/MonkeyBrain_Height.png";
const std::string METALLIC_TEXTURE_PATH = "textures/MonkeyBrain_Metallic.png";
const std::string NORMAL_TEXTURE_PATH = "textures/MonkeyBrain_Normal.png";
const std::string ROUGHNESS_TEXTURE_PATH = "textures/MonkeyBrain_Roughness.png";

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif