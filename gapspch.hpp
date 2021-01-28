#pragma once

#include <iostream>

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#define SAFE_RELEASE(RESOURCE) if ((RESOURCE) != nullptr) { delete RESOURCE; RESOURCE = nullptr; }