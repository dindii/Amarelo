#pragma once
#include "Math/vec3.h"
#include "Viewport.h"
#include <Physics/Ray.h>
#include <Physics/HittableList.h>

namespace Amrl
{

	struct ViewportProperties
	{
		vec3<float> lookFrom;
		vec3<float> lookAt;
		vec3<float> lookUp;

		float fieldOfView;
		float imageHeight;
		float imageWidth;
		float aspectRatio;
	};

class Camera
{
public:
	Camera(ViewportProperties& properties)
	{
		m_Width = properties.imageWidth;
		m_Height = properties.imageHeight = static_cast<uint32_t>(properties.imageWidth / properties.aspectRatio);

			vec3<float> basisRight(0.0f);  //u
			vec3<float> basisUp(0.0f);	 //v
			vec3<float> basisView(0.0f);   //w (opposite view dir)


		m_CameraPosition = properties.lookFrom;

		const float focalLength = (properties.lookFrom - properties.lookAt).Length();

		// Set vertical fov.The higher the fov, the bigger the viewport
		//When the viewport is really big, it can shoot many many rays to many more objects. The difference is that everything will look smaller
		//because there is a lot more elements to shoot rays but the image size is the same. 
		//When the fov is small, then the viewport is really small and a grid can barely cover up a whole object. Its very likely that the image will all be a single object
		float theta = Amrl::toRadians(properties.fieldOfView);
		float h = std::tan(theta / 2.0f);
		float viewportHeight = 2.0f * h * focalLength;
		float viewportWidth = viewportHeight * ((float)properties.imageWidth / (float)properties.imageHeight);
		
		basisView = vec3<float>::Normalize(properties.lookFrom - properties.lookAt);
		basisRight = vec3<float>::Normalize(vec3<float>::Cross(properties.lookUp, basisView));
		basisUp = vec3<float>::Normalize(vec3<float>::Cross(basisView, basisRight));
		
		m_ViewportU = viewportWidth * basisRight;
		m_ViewportV = viewportHeight * basisUp;
		
		m_PixelDeltaU = m_ViewportU / properties.imageWidth;
		m_PixelDeltaV = m_ViewportV / properties.imageHeight;
		
		m_ViewportUpperLeft = m_CameraPosition - (focalLength * basisView) - m_ViewportU / 2.0f - m_ViewportV / 2.0f;
		
		m_FirstPixelLoc = m_ViewportUpperLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

		m_Framebuffer = new Image("resultImage.png", m_Width, m_Height, 3);
	};

	vec3<float> RayColor(const Ray& ray, uint32_t maxBounces, const HittableList& world) const;
	void Render(const HittableList& world) const;

private:
	vec3<float> SampleSquare() const;
	Ray GenRay(int32_t x, int32_t y) const;

private:
	
	//samples per pixel on AA;
	int m_SPP = 100;
	float  m_SPPScale = 1.0f / m_SPP;
	int m_MaxBounces = 100;


	Image* m_Framebuffer;

	float m_Width, m_Height;
	vec3<float> m_ViewportU, m_ViewportV;
	vec3<float> m_PixelDeltaU, m_PixelDeltaV;
	vec3<float> m_ViewportUpperLeft;
	vec3<float> m_FirstPixelLoc;
	vec3<float> m_CameraPosition;
};
}