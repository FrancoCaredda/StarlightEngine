#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core/Renderer/ITexture.h"

#include "glm/glm.hpp"

namespace Starlight
{
	typedef struct Material
	{
		glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
		ITexture2D* Diffuse = nullptr;
		ITexture2D* Specular = nullptr;
		
		float Shininess = 2.0;
	} Material;
}

#endif