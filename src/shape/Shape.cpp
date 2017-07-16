#include "Shape.hpp"

#include <glad/glad.h>

Shape::Shape()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
}

Shape::~Shape()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Shape::use() const
{
	glBindVertexArray(VAO);
}

void Shape::unuse()
{
	glBindVertexArray(0);
}

void Shape::applyVertices(const void *vertices, const unsigned int size)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
