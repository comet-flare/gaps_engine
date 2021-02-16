#pragma once

#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_map>

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define SAFE_RELEASE(RESOURCE) \
	if ((RESOURCE) != nullptr) { delete RESOURCE; RESOURCE = nullptr; }

#define UNINITIALIZED Count
#define FROM_DATA(DATA) (DATA), sizeof((DATA))

typedef uint64_t id_t;