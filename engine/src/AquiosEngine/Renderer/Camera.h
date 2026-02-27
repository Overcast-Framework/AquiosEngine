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

		glm::vec3 ScreenToWorldSpace(glm::vec3 screenPos)
		{
			return glm::inverse(m_ViewMatrix) * glm::vec4(screenPos, 1);
		}

		glm::vec3 WorldToScreenSpace(glm::vec3 worldPos)
		{
			return m_ViewMatrix * glm::vec4(worldPos, 1);
		}

		void SetScreenDimensions(glm::vec2 dims) { m_ScreenDimensions = dims; }

		virtual void UpdateMatrices() = 0;
	protected:
		glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
		glm::vec2 m_ScreenDimensions;
	};
}