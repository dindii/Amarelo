#pragma once
#include "Math/vec3.h"
#include "Viewport.h"

//Fixed camera for now, without any rotation

class Camera
{
public:
	Camera(const vec3<float> cameraPosition, Viewport* viewport) : m_cameraPosition(cameraPosition), m_Viewport(viewport)
	{
		m_Viewport->SetAnchorPoint(cameraPosition);
	};

	Camera() : m_cameraPosition(0.0f), m_cameraRight(0.0f), m_cameraUp(0.0f), m_cameraForward(0.0f), m_Viewport(nullptr) {};


	inline vec3<float> GetCameraPosition() const { return m_cameraPosition; }
	inline vec3<float> GetCameraRight() const { return m_cameraRight; }
	inline vec3<float> GetCameraUp() const { return m_cameraUp; }

	inline Viewport GetCameraViewport() const { return *m_Viewport; }

	//As far as the viewport is not part of the camera, i interpreted that a viewport always follow the camera
	//to be honest, a viewport may not even exist but the camera need some parameters to shoot some rays in that and until that pos
	//so that's why i will keep this here. This all was my interpretation of the viewport.
	inline void AttachViewport(Viewport* viewport) { m_Viewport = viewport; }

private:
	//It is not quoted in the tutorial yet but i think i should find a way to rotate the viewport together?
	Viewport* m_Viewport;
	vec3<float>  m_cameraPosition;
	vec3<float>  m_cameraRight;
	vec3<float>	 m_cameraUp;
	vec3<float>	 m_cameraForward;
};