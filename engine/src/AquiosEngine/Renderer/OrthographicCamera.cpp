#include "aqpch.h"
#include "OrthographicCamera.h"

void Aquios::OrthographicCamera::UpdateMatrices()
{
	m_ViewMatrix = glm::lookAt(Position, Position + glm::vec3(0, 0, -1), Up);
	m_ProjectionMatrix = glm::ortho(
		-m_ScreenDimensions.x / 2.0f, 
		m_ScreenDimensions.x / 2.0f,
		-m_ScreenDimensions.y / 2.0f,
		m_ScreenDimensions.y / 2.0f,
		0.1f, 100.0f
	);
}
