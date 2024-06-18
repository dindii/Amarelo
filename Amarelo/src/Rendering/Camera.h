#pragma once
#include "Math/vec3.h"
#include "Viewport.h"
#include <Physics/Ray.h>
#include <Physics/HittableList.h>

namespace Amrl
{

class Camera
{
public:
	Camera(const vec3<float> cameraPosition, Viewport* viewport) : m_cameraPosition(cameraPosition), m_Viewport(viewport)
	{
		//m_Viewport->SetAnchorPoint(cameraPosition);
	};

	Camera() : m_cameraPosition(0.0f), m_cameraRight(0.0f), m_cameraUp(0.0f), m_cameraForward(0.0f), m_SPP(1), m_Viewport(nullptr) {};

	inline vec3<float> GetCameraPosition() const { return m_cameraPosition; }
	inline vec3<float> GetCameraRight() const { return m_cameraRight; }
	inline vec3<float> GetCameraUp() const { return m_cameraUp; }
	inline Viewport GetCameraViewport() const { return *m_Viewport; }

	inline void AttachViewport(Viewport* viewport) { m_Viewport = viewport; }

	vec3<float> RayColor(const Ray& ray, uint32_t maxBounces, const HittableList& world) const;
	void Render(const HittableList& world) const;

private:
	vec3<float> SampleSquare() const;
	Ray GenRay(int32_t x, int32_t y) const;

private:
	Viewport* m_Viewport;
	vec3<float>  m_cameraPosition;
	vec3<float>  m_cameraRight;
	vec3<float>	 m_cameraUp;
	vec3<float>	 m_cameraForward;
	
	//samples per pixel on AA;
	int m_SPP = 100;
	float  m_SPPScale = 1.0f / m_SPP;
	int m_MaxBounces = 100;
};
}