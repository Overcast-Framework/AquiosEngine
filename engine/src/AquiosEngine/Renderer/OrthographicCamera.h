#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Aquios
{
	class OrthographicCamera
	{
	public:
		glm::vec3 Position;
		glm::vec3 Up = { 0,1,0 };
		glm::vec3 Target = { 0,0,1 };
		glm::vec2 ScreenDimensions;

		OrthographicCamera(glm::vec3 pos, glm::vec3 up, glm::vec3 target, glm::vec2 screenDims)
			: Position(pos), Up(up), Target(target), ScreenDimensions(screenDims)
		{
		}

		void Update();

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjMatrix; }
	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjMatrix = glm::mat4(1.0f);
	};
}