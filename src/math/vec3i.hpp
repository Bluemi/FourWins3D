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
		void set(const int index, const int value);
		vec3i operator+(const vec3i &vec) const;
		vec3i operator-(const vec3i &vec) const;
		vec3i operator*(const vec3i &vec) const;
		vec3i operator/(const vec3i &vec) const;

		vec3i operator+(const int value) const;
		vec3i operator-(const int value) const;
		vec3i operator*(const int value) const;
		vec3i operator/(const int value) const;

		bool operator<(const vec3i &vec) const;
		bool operator>(const vec3i &vec) const;
		bool operator<=(const vec3i &vec) const;
		bool operator>=(const vec3i &vec) const;
		bool operator==(const vec3i &vec) const;
		vec3i min(const vec3i &vec) const;
		vec3i max(const vec3i &vec) const;
		std::string toString() const;
		glm::vec3 toVec3() const;

		static const int X;
		static const int Y;
		static const int Z;
		static const int SIZE;

		int x;
		int y;
		int z;
};

#endif
