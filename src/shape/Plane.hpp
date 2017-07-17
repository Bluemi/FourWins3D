#ifndef __PLANE_CLASS__
#define __PLANE_CLASS__

#include <glm/glm.hpp>

class Plane
{
	public:
		Plane(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third);
		void transform(const glm::mat4 &trans);
		glm::vec4 first;
		glm::vec4 second;
		glm::vec4 third;
};

#endif
