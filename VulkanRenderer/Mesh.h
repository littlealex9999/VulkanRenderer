#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

class Mesh
{
public:
	static Mesh LoadModel(std::string);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};