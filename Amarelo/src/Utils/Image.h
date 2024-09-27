#pragma once
#include <stdint.h>
#include <vector>
#include "Math/vec3.h"

class Image
{
public:
	Image() : m_Width(0), m_Height(0), m_Channels(0) {};
	Image(const std::string& filename, const uint32_t width, const uint32_t height, const uint8_t channels);

	inline uint32_t GetHeight() const { return m_Height; }
	inline uint32_t GetWidth() const { return m_Width; }

	bool SetPixel(const vec3<float>& val);
	bool SetPixel(uint32_t x, uint32_t y, const vec3<float>& val);

	void Flush();

private:
	std::vector<uint8_t>::iterator m_it;
	uint8_t  m_Channels;
	uint32_t m_Width, m_Height;
	std::vector<uint8_t> m_Data;
	std::string m_Filename;
};
