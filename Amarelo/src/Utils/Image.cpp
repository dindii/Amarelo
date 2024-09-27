#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Vendor/stb_image_write.h"
#include <Math/generalmath.h>

Image::Image(const std::string& filename, const uint32_t width, const uint32_t height, const uint8_t channels)
	: m_Width(width), m_Height(height), m_Filename(filename), m_Channels(channels)
{
	m_Data.resize(m_Width * m_Height * m_Channels);
	m_it = m_Data.begin();
}

bool Image::SetPixel(const vec3<float>& val)
{
	vec3<float> gammaCorrectedColor(0.0f, 0.0f, 0.0f); 

	gammaCorrectedColor.r = Amrl::LinearToGama(val.r);
	gammaCorrectedColor.g = Amrl::LinearToGama(val.g);
	gammaCorrectedColor.b = Amrl::LinearToGama(val.b);

	vec3<uint8_t> byteColor = Amrl::ConvertColor(gammaCorrectedColor);

	if (m_it != m_Data.end())
	{
		*(m_it++) = byteColor.r;
		*(m_it++) = byteColor.g;
		*(m_it++) = byteColor.b;
		
		return true;
	}

	return false;
}

bool Image::SetPixel(uint32_t x, uint32_t y, const vec3<float>& val)
{
	vec3<float> gammaCorrectedColor(0.0f, 0.0f, 0.0f);

	gammaCorrectedColor.r = Amrl::LinearToGama(val.r);
	gammaCorrectedColor.g = Amrl::LinearToGama(val.g);
	gammaCorrectedColor.b = Amrl::LinearToGama(val.b);

	vec3<uint8_t> byteColor = Amrl::ConvertColor(gammaCorrectedColor);

	uint32_t idx = (y * m_Width + x) * m_Channels;

	m_Data[idx++] = byteColor.r;
	m_Data[idx++] = byteColor.g;
	m_Data[idx]	  = byteColor.b;

	return true;
}

void Image::Flush()
{
	stbi_flip_vertically_on_write(true);
	stbi_write_png(m_Filename.c_str(), m_Width, m_Height, m_Channels, m_Data.data(), m_Width * m_Channels);
}
