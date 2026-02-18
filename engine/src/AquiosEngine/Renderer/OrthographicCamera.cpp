#include "aqpch.h"
#include "OrthographicCamera.h"

void Aquios::OrthographicCamera::Update()
{
	m_ViewMatrix = glm::lookAt(Position, Target, Up);
	m_ProjMatrix = glm::ortho(0.0f, ScreenDimensions.x, 0.0f, ScreenDimensions.y, 0.1f, 100.0f);
}
