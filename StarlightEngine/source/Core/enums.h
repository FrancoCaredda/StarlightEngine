#ifndef ENUMS_H
#define ENUMS_H

enum API
{
	OPENGL_API = 0,
	VULKAN_API = 1,
	DIRECTX_API = 2
};

enum Buffers
{
#ifdef SL_OPENGL
	GL_MACRO(COLOR_BUFFER_BIT),
	GL_MACRO(DEPTH_BUFFER_BIT),
	GL_MACRO(STENCIL_BUFFER_BIT)
#else
#error Starlight supports only OpenGL now
#endif // SL_OPENGL
};

enum Test
{
#ifdef SL_OPENGL
	GL_MACRO(DEPTH_TEST),
	GL_MACRO(STENCIL_TEST),
	GL_MACRO(BLEND)
#else
#error Starlight supports only OpenGL now
#endif // SL_OPENGL
};

enum Attachments
{
#ifdef SL_OPENGL
	GL_MACRO(COLOR_ATTACHMENT0),
	GL_MACRO(COLOR_ATTACHMENT1),
	GL_MACRO(COLOR_ATTACHMENT2),
	GL_MACRO(COLOR_ATTACHMENT3),
	GL_MACRO(COLOR_ATTACHMENT4),
	GL_MACRO(COLOR_ATTACHMENT5),
	GL_MACRO(COLOR_ATTACHMENT6),
	GL_MACRO(COLOR_ATTACHMENT7),
	GL_MACRO(COLOR_ATTACHMENT8),
	GL_MACRO(COLOR_ATTACHMENT9),
	GL_MACRO(COLOR_ATTACHMENT10),
	GL_MACRO(COLOR_ATTACHMENT11),
	GL_MACRO(COLOR_ATTACHMENT12),
	GL_MACRO(COLOR_ATTACHMENT13),
	GL_MACRO(COLOR_ATTACHMENT14),
	GL_MACRO(DEPTH_ATTACHMENT),
	GL_MACRO(DEPTH_STENCIL_ATTACHMENT)
#else
#error Starlight supports only OpenGL now
#endif // SL_OPENGL
};

enum Formats
{
#ifdef SL_OPENGL
	GL_MACRO(DEPTH24_STENCIL8),
	GL_MACRO(DEPTH32F_STENCIL8),
	GL_MACRO(RGB),
	GL_MACRO(RGBA)
#else
#error Starlight supports only OpenGL now
#endif // SL_OPENGL
};

#endif // !ENUMS_H
