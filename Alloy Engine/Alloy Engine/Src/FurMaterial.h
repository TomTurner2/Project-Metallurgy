#pragma once
#include "Material.h"
#include "FurParameters.h"
#include "FurTexture.h"

class Texture;

class FurMaterial : public Material
{
public:
	void LoadFurTextures(Renderer& _renderer, std::string _fur_mask_path, std::string _fur_alpha_path);
	void SetFurParameters(FurParameters _fur_params);
	void SetFurTextures(Texture* _fur_alpha, Texture* _fur_mask);

protected:
	void CreateBuffers(Renderer& _renderer) override;
	void UpdateAndAddCustomBuffers(Renderer& _renderer) override;

	bool m_buffer_is_dirty = true;
	Texture* m_fur_alpha{ nullptr };
	Texture* m_fur_mask{ nullptr };
	ID3D11Buffer* m_fur_param_buffer{ nullptr };
	FurParameters m_fur_params;
};
