#include "Renderer.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {
		std::cout << "fuckshit\n";
	}
}

bool GLLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError())
	{
		std::cout << "[GLCall Error]" << error << ", Function: " << func << ", File: " << file << ", on line: " << line << "\n";
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
