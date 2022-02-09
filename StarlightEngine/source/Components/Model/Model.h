#ifndef MODEL_H
#define MODEL_H

#include "defines.h"

#include "glm/glm.hpp"

#include "Core/Renderer/IBuffers.h"
#include "Core/Renderer/IVertexArray.h"

#include "Components/Graphics/Material.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Starlight
{
	typedef struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TextureCoord;
	} Vertex;

	class STARLIGHT_API Mesh
	{
	public:
		Mesh();

		void SetVertecies(const std::vector<Vertex>& vertecies) noexcept;
		void SetIndecies(const std::vector<uint32_t>& indecies) noexcept;

		// Writes data to GPU buffers
		void WriteData() noexcept;

		inline const std::vector<Vertex>& GetVertecies() const noexcept { return m_Vertecies; }
		inline const std::vector<uint32_t>& GetIndecies() const noexcept { return m_Indecies; }

		inline IVertexBuffer* GetVertexBuffer() const noexcept { return m_VertexBuffer; }
		inline IIndexBuffer* GetIndexBuffer() const noexcept { return m_IndexBuffer; }
		inline IVertexArray* GetVertexArray() const noexcept { return m_VertexArray; }

		void Bind() const noexcept;
		void Unbind() const noexcept;

		friend class Model;
		~Mesh();
	private:
		std::vector<Vertex> m_Vertecies;
		std::vector<uint32_t> m_Indecies;
		uint32_t m_MaterialID;

		IVertexBuffer* m_VertexBuffer = nullptr;
		IIndexBuffer* m_IndexBuffer = nullptr;
		IVertexArray* m_VertexArray = nullptr;
	};


	// TODO(Franco): Rewrite class model
	class STARLIGHT_API Model
	{
	public:
		Model() = default;

		bool Load(const std::string& filename) noexcept;

		friend class Renderer;
		~Model();
	private:
		void ProcessScene();
		void ProcessNode(const aiNode* node);
		void ReadSingleMesh(aiMesh* mesh, Mesh* outMesh);
		void ReadSingleMaterial(aiMesh* mesh);
	private:
		std::vector<Mesh*> m_Meshes;
		Material* m_Material;
		std::string m_NativePath;

		const aiScene* m_Scene;
	};
}

#endif // !MODEL_H

