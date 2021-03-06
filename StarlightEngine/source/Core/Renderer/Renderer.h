#ifndef RENDERER_H
#define RENDERER_H

#include "defines.h"

#include "IBuffers.h"
#include "IVertexArray.h"
#include "IShader.h"
#include "Camera.h"
#include "IFrameBuffer.h"

#include "Core/enums.h"

#include "Components/Mesh/Mesh.h"

namespace Starlight
{
	class STARLIGHT_API Renderer
	{
	public:
		SL_SINGLE_CLASS(Renderer);
	
		static bool Init(API rendererApi, int width, int height);

		static void Enable(Test test) noexcept;
		static void Disable(Test test) noexcept;

		static void Clear(int buffers) noexcept;
		static void ClearColor(const glm::vec4& color) noexcept;
		// Draws object by selected vertex buffer data
		static void DrawArrays(int first, int count) noexcept;
		// Draws object by selected index buffer data
		static void DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program);
		static void DrawPoints(uint32_t count) noexcept;

		// Draws static mesh. Uses Renderer::DrawArrays method inside
		static void DrawStaticMesh(StaticMesh* mesh, IShaderProgram* program);
		// Draws static mesh normals. Uses Renderer::DrawArrays method inside
		static void DrawNormals(StaticMesh* mesh, IShaderProgram* program);
		// Draws std frame
		// TODO(Franco): Make posibility to draw users frame buffers.
		static void DrawFrame() noexcept;

		static void DrawDynamicMesh(DynamicMesh* mesh, IShaderProgram* program);

		// Returns texture of std frame buffer
		static ITexture2D* GetFrameColor() noexcept;

		static void SetMainCamera(Camera* camera) noexcept;
		static void SetProjection(const glm::mat4& projection) noexcept;

		static inline API GetApi() noexcept { return s_Instance.m_RendererApi; }

		static void Shutdown();

		~Renderer() = default;
	private:
		Renderer() = default;

		static Renderer s_Instance;

		// --------------------View/Projection--------------------
		Camera* m_Camera;
		glm::mat4 m_Projection;
		// -------------------------------------------------------

		// -------------------STD Frame Buffer--------------------
		IFrameBuffer* m_FrameBuffer;
		IRenderBuffer* m_RenderBuffer;
		ITexture2D* m_ColorBuffer;
		IVertexArray* m_FrameVAO;
		IVertexBuffer* m_FrameVBO;
		IIndexBuffer* m_FrameIBO;
		IShaderProgram* m_FrameShader;
		// -------------------------------------------------------


		// -------------------STD Uniform Buffers-----------------
		IUniformBuffer* m_ViewProjection;
		// -------------------------------------------------------



		// ------------------Renderer data------------------------
		API m_RendererApi;
		bool m_Inited = false;
		// -------------------------------------------------------
	};
}

#endif // !RENDERER_H
