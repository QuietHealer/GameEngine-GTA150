#pragma once
#include "Mesh.h"

namespace nu
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<Mesh>& mashes) : m_meshes{ mashes }
		{
			CalculateRadius();
		}

		void AddMesh(const Mesh& mesh) { m_meshes.push_back(mesh); }

		void SetMeshes(const std::vector<Mesh>& meshes) { m_meshes = meshes; }
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

		float GetRadius() const { return m_radius; }
		void CalculateRadius();

	private:
		float m_radius = 0.0f;
		std::vector<Mesh> m_meshes;
	};
}
