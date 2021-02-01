#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define SAFE_RELEASE(RESOURCE) \
	if ((RESOURCE) != nullptr) { delete RESOURCE; RESOURCE = nullptr; }

#define UNINITIALIZED Count
#define FROM_DATA(DATA) (DATA), sizeof((DATA))