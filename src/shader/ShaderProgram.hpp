#ifndef __SHADERPROGRAM_CLASS__
#define __SHADERPROGRAM_CLASS__

#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
	public:
		ShaderProgram(const std::string vertexPath, const std::string fragmentPath);
		void use();
		void setBool(const std::string &name, bool value) const;
		void setFloat(const std::string &name, float value) const;
		void setInt(const std::string &name, int value) const;
		void setMat4(const std::string &name, const glm::mat4 value) const;

		int getID() const;
	private:
		bool loadFromFile(const std::string path, std::string *text) const;

		unsigned int programID;
		unsigned const int INFO_LOG_SIZE = 512;
};

#endif
