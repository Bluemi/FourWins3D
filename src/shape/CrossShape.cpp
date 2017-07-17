#include "CrossShape.hpp"

#include <glad/glad.h>

CrossShape::CrossShape()
{}

void CrossShape::load()
{
	float vertices[] = {
		-0.002f,  0.04f,
		-0.002f, -0.04f,
		 0.002f, -0.04f,
		 0.002f, -0.04f,
		-0.002f,  0.04f,
		 0.002f,  0.04f,

		-0.03f,  0.002f,
		-0.03f, -0.002f,
		 0.03f, -0.002f,
		 0.03f, -0.002f,
		-0.03f,  0.002f,
		 0.03f,  0.002f
        };
	applyVertices(vertices, sizeof(vertices));
	defineVertexAttribPointer();
}

void CrossShape::defineVertexAttribPointer() const
{
	const unsigned int stripe = 2*sizeof(float);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stripe, 0);
	glEnableVertexAttribArray(0);
}
