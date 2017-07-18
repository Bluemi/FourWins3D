#ifndef __VEC3I_CLASS__
#define __VEC3I_CLASS__

#include <glm/glm.hpp>

#include <string>

class vec3i
{
	public:
		vec3i();
		vec3i(const int x, const int y, const int z);
		int operator[](const unsigned int index) const;
		vec3i operator+(const vec3i &vec) const;
		vec3i operator-(const vec3i &vec) const;
		vec3i operator*(const vec3i &vec) const;
		vec3i operator/(const vec3i &vec) const;
		bool operator<(const vec3i &vec) const;
		bool operator>(const vec3i &vec) const;
		bool operator<=(const vec3i &vec) const;
		bool operator>=(const vec3i &vec) const;
		bool operator==(const vec3i &vec) const;
		vec3i min(const vec3i &vec) const;
		vec3i max(const vec3i &vec) const;
		std::string toString() const;
		glm::vec3 toVec3() const;

		int x;
		int y;
		int z;
};

#endif
