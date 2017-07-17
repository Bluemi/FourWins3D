#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include <debug/Debug.hpp>

ShaderProgram::ShaderProgram()
{}

void ShaderProgram::load(const std::string vertexPath, const std::string fragmentPath)
{
	bool works = true;

	unsigned int vertex, fragment;

	// vertex
	std::string vertexCode;
	if (loadFromFile(vertexPath, &vertexCode))
	{
		int success;
		char infoLog[INFO_LOG_SIZE];
		vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* vc = vertexCode.c_str();
		glShaderSource(vertex, 1, &vc, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, INFO_LOG_SIZE, NULL, infoLog);
			Debug::out << Debug::error << "ShaderProgram::ShaderProgram: failed to create vertex Shader. infoLog: " << infoLog << Debug::endl;
			works = false;
		}
	} else {
		works = false;
	}

	// fragment
	std::string fragmentCode;
	if (loadFromFile(fragmentPath, &fragmentCode))
	{
		int success;
		char infoLog[INFO_LOG_SIZE];
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fc = fragmentCode.c_str();
		glShaderSource(fragment, 1, &fc, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, INFO_LOG_SIZE, NULL, infoLog);
			Debug::out << Debug::error << "ShaderProgram::ShaderProgram: failed to create fragment Shader. infoLog: " << infoLog << Debug::endl;
			works = false;
		}
	} else {
		works = false;
	}

	// linking
	if (works)
	{
		programID = glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);

		int success;
		char infoLog[INFO_LOG_SIZE];
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programID, INFO_LOG_SIZE, NULL, infoLog);
			Debug::out << Debug::error << "couldnt link program with vertexPath: \"" << vertexPath << "\"" << " fragmentPath: \"" << fragmentPath << "\"" << Debug::endl;
			Debug::out << "infoLog:\n" << infoLog << Debug::endl;
			works = false;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
}

void ShaderProgram::use() const
{
	glUseProgram(programID);
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

int ShaderProgram::getID() const
{
	return programID;
}

bool ShaderProgram::loadFromFile(const std::string path, std::string *text) const
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		*text = stream.str();
	} catch (std::ifstream::failure e) {
		Debug::out << Debug::error << "couldnt read file \"" << path << "\"" << Debug::endl;
		return false;
	}
	return true;
}
