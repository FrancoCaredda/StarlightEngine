#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include "IBuffers.h"
#include "IVertexArray.h"
#include "IShader.h"

namespace Starlight
{
	enum API
	{
		OPENGL_API = 0,
		VULKAN_API = 1,
		DIRECTX_API = 2
	};

	class STARLIGHT_API Renderer
	{
	public:
		SL_SINGLE_CLASS(Renderer);
	
		static bool Init(API rendererApi);

		static void DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program);

		static inline API GetApi() noexcept { return s_Instance.m_RendererApi; }

		static void Shutdown();

		~Renderer() = default;
	private:
		Renderer() = default;

		static Renderer s_Instance;

		API m_RendererApi;
		bool m_Inited = false;
	};
}

#endif // !RENDERER_H
