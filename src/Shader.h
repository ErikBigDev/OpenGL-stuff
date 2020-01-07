#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
private:
	std::string m_FilepathVert;
	std::string m_FilepathFrag;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& fileVert, const std::string& fileFrag);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform1f(const std::string& name, float v0);

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform2i(const std::string& name, int v0, int v1);
	void SetUniform3i(const std::string& name, int v0, int v1, int v2);
	void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3);

	//void SetUniformMat2f(const std::string& name, float v0, float v1);
	//void SetUniformMat3f(const std::string& name, float v0, float v1, float v2);
	//void SetUniformMat4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

