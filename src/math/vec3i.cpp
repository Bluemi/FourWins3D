#include "vec3i.hpp"

#include <misc/Debug.hpp>

vec3i::vec3i()
	: x(0), y(0), z(0)
{}

vec3i::vec3i(const int x, const int y, const int z)
	: x(x), y(y), z(z)
{}

int vec3i::operator[](const unsigned int index) const
{
	int res;
	switch (index)
	{
		case 0:
			res = x;
			break;
		case 1:
			res = y;
			break;
		case 2:
			res = z;
			break;
		default:
			Debug::out << Debug::error << "vec3i::operator[]: index = " << (int)index << Debug::endl;
			res = 0;
			break;
	}
	return res;
}

vec3i vec3i::operator+(const vec3i &vec) const
{
	return vec3i(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

vec3i vec3i::operator-(const vec3i &vec) const
{
	return vec3i(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

vec3i vec3i::operator*(const vec3i &vec) const
{
	return vec3i(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vec3i vec3i::operator/(const vec3i &vec) const
{
	return vec3i(this->x / vec.x, this->y / vec.y, this->z / vec.z);
}

bool vec3i::operator<(const vec3i &vec) const
{
	for (int i = 0; i < 3; i++)
	{
		if ((*this)[i] >= vec[i])
			return false;
	}
	return true;
}

bool vec3i::operator>(const vec3i &vec) const
{
	for (int i = 0; i < 3; i++)
	{
		if ((*this)[i] <= vec[i])
			return false;
	}
	return true;
}

bool vec3i::operator<=(const vec3i &vec) const
{
	for (int i = 0; i < 3; i++)
	{
		if ((*this)[i] > vec[i])
			return false;
	}
	return true;
}

bool vec3i::operator>=(const vec3i &vec) const
{
	for (int i = 0; i < 3; i++)
	{
		if ((*this)[i] < vec[i])
			return false;
	}
	return true;
}

bool vec3i::operator==(const vec3i &vec) const
{
	for (int i = 0; i < 3; i++)
	{
		if ((*this)[i] != vec[i])
			return false;
	}
	return true;
}

vec3i vec3i::min(const vec3i &vec) const
{
	return vec3i(std::min(this->x, vec.x), std::min(this->y, vec.y), std::min(this->z, vec.z));
}

vec3i vec3i::max(const vec3i &vec) const
{
	return vec3i(std::max(this->x, vec.x), std::max(this->y, vec.y), std::max(this->z, vec.z));
}

std::string vec3i::toString() const
{
	return "x: " + std::to_string(x) + "y: " + std::to_string(y) + "z: " + std::to_string(z);
}

glm::vec3 vec3i::toVec3() const
{
	return glm::vec3(x, y, z);
}
