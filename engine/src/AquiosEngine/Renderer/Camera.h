#pragma once
#include <glm/glm.hpp>

namespace Aquios
{
	class Camera
	{
	public:
		glm::vec3 Position;

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		void SetScreenDimensions(glm::vec2 dims) { m_ScreenDimensions = dims; }

		virtual void UpdateMatrices() = 0;
	protected:
		glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
		glm::vec2 m_ScreenDimensions;
	};
}