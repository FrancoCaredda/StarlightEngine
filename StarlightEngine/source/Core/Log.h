#ifndef LOG_H
#define LOG_H

#include "defines.h"

#include <cstddef>
#include <iostream>

#ifdef SL_PLATFORM_WINDOWS
#include <Windows.h>

#define STD_COLOR 7

#define SL_INFO(MSG)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);\
					  std::cout << "[INFO]: " << MSG << std::endl; \
					  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STD_COLOR)

#define SL_WARN(MSG)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);\
					  std::cout << "[WARNING] " <<  __FUNCTION__ << ":" << __LINE__  << ": " << MSG << std::endl;\
					  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STD_COLOR)

#define SL_ERROR(MSG) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);\
					  std::cerr << "[ERROR] " << __FUNCTION__  << ":" << __LINE__ << ": " << MSG << std::endl;\
					  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STD_COLOR)

#define SL_FATAL(MSG) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);\
					  std::cerr << "[FATAL] " << __FUNCTION__  << ":" << __LINE__ << ": " << MSG << std::endl;\
					  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STD_COLOR)

#else
#error Other platform is not implemented!
#endif // SL_PLATFORM_WINDOWS

#endif // !LOG_H
