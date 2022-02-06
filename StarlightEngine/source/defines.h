#ifndef DEFINES_H
#define DEFINES_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <exception>
#include <cstdint>

#define SL_OPENGL

#ifdef STARLIGHT_EXPORTS
#define STARLIGHT_API __declspec(dllexport)
#else
#define STARLIGHT_API __declspec(dllimport)
#endif // STARLIGHTENGINE_DYNAMIC

// This macro allows us to create singletons by deleting copy constructor and move constructor
#define SL_SINGLE_CLASS(CLASS) CLASS(const CLASS&) = delete;\
							   CLASS(CLASS&&) = delete;\
							   CLASS& operator=(const CLASS&) = delete

#define SL_STD_EXCEPTION(CONDITION, MESSAGE) if (CONDITION) throw std::exception(MESSAGE)
#define SL_CODE_EXCEPTION(CONDITION, VALUE) if (CONDITION) throw VALUE
#define SL_EXCEPTION(CONDITION, MESSAGE, TYPE) if (CONDITION) throw TYPE(MESSAGE)

#define BUFFER_SIZE 256

#define GL_MACRO(NAME) NAME = GL_##NAME

#endif