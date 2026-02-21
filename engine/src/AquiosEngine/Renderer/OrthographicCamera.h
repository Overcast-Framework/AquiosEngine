#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <AquiosEngine/Renderer/Camera.h>

namespace Aquios
{
	class OrthographicCamera : public Camera
	{
	public:
		glm::vec3 Up = { 0,1,0 };

		OrthographicCamera(glm::vec3 pos, glm::vec3 up, glm::vec2 screenDims)
			: Up(up)
		{
			Position = pos;
			m_ScreenDimensions = screenDims;
		}

		void UpdateMatrices() override;
	};
}