#pragma once

#include"vec3.h"

class camera
{
public:
	vec3 eyePos = vec3(0, 0, 0);
	vec3 lookAt = vec3(0, 0, -1);
	vec3 lookUp = vec3(0, 1, 0);
	float vfov = 90;
};