#include "Texture.hpp"

#include <images/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <debug/Debug.hpp>

Texture::Texture()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
	//glDeleteTexture(id);
}

void Texture::load(const std::string &path) const
{
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		Debug::out << Debug::error << "couldnt load " << path << Debug::endl;
	}

	stbi_image_free(data);
}

void Texture::use() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
