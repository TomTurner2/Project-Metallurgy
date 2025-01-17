#pragma once
#include <d3d11.h>
#include "Matrix.h"
#include "Vector3.h"
#include "Light.h"
#include "PBRMaterialParams.h"
#include <vector>
#include "Texture.h"

class Renderer;

// Class should be inherited from.
class Material
{
public:
	Material();
	virtual ~Material();
	
	void CreateShaders(std::string _vertex_shader, std::string _pixel_shader, Renderer& _renderer, std::string _geometry_shader = "");
	void LoadStandardTextures(std::string _albedo_path, std::string _roughness_path, std::string _specular_path, Renderer& _renderer);
	virtual void UpdateBuffers(Renderer& _renderer);

	ID3D11VertexShader* GetVertexShader() const;
	ID3D11PixelShader* GetPixelShader() const;
	ID3D11GeometryShader* GetGeometryShader() const;
	ID3D11InputLayout* GetInputLayout() const;

	void SetStandardTextures(Texture* _albedo, Texture* _roughness, Texture* _specular);
	void SetTransformMatrix(Matrix _transform);
	void SetView(Matrix _view);
	void SetProjection(Matrix _projection);
	void SetCameraPosition(Vector3 _pos);
	void SetLight(Light _light);
	void SetMaterialParams(PBRMaterialParams _pbr_params);

private:
	void SetBuffers(Renderer& _renderer);

	void MapVSObjectBuffer(Renderer& _renderer);
	void MapVSFrameBuffer(Renderer& _renderer);

	void MapPSObjectBuffer(Renderer& _renderer);
	void MapPSFrameBuffer(Renderer& _renderer);
	void MapPSSceneBuffer(Renderer& _renderer);

	void RegisterAllBuffers();
	void RegisterVertexBuffers();
	void RegisterPixelBuffers();
	void RegisterGeometryBuffers();
	void RegisterResources();


	ID3D11VertexShader* m_vertex_shader { nullptr };
	ID3D11PixelShader* m_pixel_shader { nullptr };
	ID3D11GeometryShader* m_geometry_shader { nullptr };
	ID3D11InputLayout* m_input_layout { nullptr };

	// Vertex buffers.
	ID3D11Buffer* m_vs_per_object_buffer { nullptr };
	ID3D11Buffer* m_vs_per_frame_buffer { nullptr };

	// Pixel buffers.
	ID3D11Buffer* m_ps_per_frame_buffer { nullptr };
	ID3D11Buffer* m_ps_per_scene_buffer { nullptr };
	ID3D11Buffer* m_ps_per_object_buffer { nullptr };

	// Shader resources.
	ID3D11SamplerState* m_sample_state;
	Texture* m_albedo_texture { nullptr };
	Texture* m_specular_texture { nullptr };
	Texture* m_rougness_texture { nullptr };

	struct VSPerFrameBuffer
	{
		Matrix view;
		Matrix proj;
	};

	struct VSPerObjectBuffer
	{
		Matrix transform;
	};

	struct PSPerFrameBuffer
	{
		Vector3 camera_position;
		float extra;//buffer size must be a multiple of 16
	};

	struct __declspec(align(32)) PSPerSceneBuffer
	{
		Light light;
	};

	struct __declspec(align(32)) PSPerObjectBuffer
	{
		PBRMaterialParams material_params;
	};

	// Data to be passed to buffer (dirtyable pattern).
	std::pair<bool, VSPerObjectBuffer> m_vs_per_object;
	std::pair<bool, VSPerFrameBuffer> m_vs_per_frame;
	std::pair<bool, PSPerFrameBuffer> m_ps_per_frame;
	std::pair<bool, PSPerSceneBuffer> m_ps_per_scene;
	std::pair<bool, PSPerObjectBuffer> m_ps_per_object;

protected:
	virtual void CreateBuffers(Renderer& _renderer);
	virtual void CreateSamplerState(Renderer& _renderer);
	virtual void UpdateAndAddCustomBuffers(Renderer& _renderer);
	
	// Inherited materials add buffers to these lists.
	std::vector<ID3D11Buffer*> m_vs_buffers;
	std::vector<ID3D11Buffer*> m_ps_buffers;
	std::vector<ID3D11Buffer*> m_gs_buffers;

	std::vector<ID3D11ShaderResourceView*> m_ps_resources;
	std::vector<ID3D11ShaderResourceView*> m_gs_resources;
};
