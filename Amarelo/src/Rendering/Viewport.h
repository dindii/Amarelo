#pragma once
#include <Utils/Image.h>
struct Viewport
{
public:
	Viewport(const float height, const float width, const float depth, const float imgHeight, const float imgWidth) 
	{
		m_Height = height;
		m_Width = width;

		m_ViewportU = vec3<float>(m_Width, 0.0f, 0.0f);
		m_ViewportV = vec3<float>(0.0f, m_Height, 0.0f);

		m_PixelDeltaU = m_ViewportU / imgWidth;
		m_PixelDeltaV = m_ViewportV / imgHeight;

		vec3<float> center(0.0f, 0.0f, 0.0f);
		vec3<float> focalLength(0.0f, 0.0f, depth);
		m_ViewportUpperLeft = center - focalLength - (m_ViewportU / 2.0f) - (m_ViewportV / 2.0f);
		m_FirstPixelLoc = m_ViewportUpperLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

	};

	inline void AttachOutputImage(Image* image) { m_Framebuffer = image; }
	inline Image* GetOutputImage() { return m_Framebuffer; }

public:
	Image* m_Framebuffer;

	float m_Width, m_Height;
	vec3<float> m_ViewportU, m_ViewportV;
	vec3<float> m_PixelDeltaU, m_PixelDeltaV;
	vec3<float> m_ViewportUpperLeft;
	vec3<float> m_FirstPixelLoc; 
};