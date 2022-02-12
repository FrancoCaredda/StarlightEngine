#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

namespace Starlight
{
	typedef struct Pointlight
	{
		glm::vec3 Position;
		glm::vec3 ColorIntensity;
		
		// Sets the coeficients for quadratic equation ax^(2) + bx + 1, where x is length between objects and light source
		glm::vec2 Params;
	} Pointlight;

	typedef struct DirectionalLight
	{
		glm::vec3 Direction;
		glm::vec3 ColorIntensity;
	} DirectionalLight;

	typedef struct Spotlight
	{
		glm::vec3 Position;
		glm::vec3 Direction;
		
		// Must be cosine from angle in radians
		float InnerCutoff;
		// Must be cosine from angle in radians
		float OuterCutoff;
	} Spotlight;
}

#endif // !LIGHT_H
