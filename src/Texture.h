#pragma once

#include "Renderer.h"

class Texture
{

private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Height, m_Width, m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetHeight() const { return m_Height; }
	inline int GetWidth() const { return m_Width; }
};

