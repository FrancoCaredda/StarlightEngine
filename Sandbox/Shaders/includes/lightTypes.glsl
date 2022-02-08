struct Pointlight
{
    vec3 Position;
    vec3 ColorIntensity;
		
	// Sets the coeficients for quadratic equation ax^(2) + bx + 1, where x is length between objects and light source
	vec2 Params;
};

struct DirectionalLight
{
    vec3 Direction;
	vec3 ColorIntensity;
};

struct Spotlight
{
    vec3 Position;
    vec3 Direction;
		
	// Must be cosine from angle in radians
	float InnerCutoff;
	// Must be cosine from angle in radians
	float OuterCutoff;
};
