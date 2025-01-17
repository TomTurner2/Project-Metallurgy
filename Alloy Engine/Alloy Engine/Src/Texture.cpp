#include "Texture.h"
#include "Renderer.h"
#include "WICTextureLoader.h"


wchar_t* CharToWChar(const char* _text)// Stupid windows types.
{
	auto size = strlen(_text) + 1;
	static wchar_t* wa = nullptr;
	if (wa)
	{
		delete[] wa;
		wa = nullptr;
	}
	wa = new wchar_t[size];
	mbstowcs_s(nullptr, wa, size, _text, size);
	return wa;
}


Texture::Texture(Renderer& _renderer, std::string _path)
{
	LoadTexture(_renderer, _path);
}


void Texture::LoadTexture(Renderer & _renderer, std::string _path)
{
	HRESULT result{};

	result = DirectX::CreateWICTextureFromFile(_renderer.GetDevice(), CharToWChar(_path.c_str()),
		&m_texture_resource, &m_texture, 2048);// Could be 4096, but setting to 2048 saves a few mb of memory.

	if (result != MB_OK)
	{
		MessageBox(nullptr, "[Texture](Constructor) Failed to load texture", "Error", MB_OK);
		exit(0);
	}
}


ID3D11ShaderResourceView* Texture::GetTexture() const
{
	return m_texture;
}


ID3D11Resource* Texture::GetTextureResource() const
{
	return m_texture_resource;
}
