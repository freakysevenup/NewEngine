#pragma once
#include "Texture.h"
#include <map>

class MaterialInfo
{
public:
	MaterialInfo() {}
	~MaterialInfo() {}

	void setTexture(const Texture& diffuse) { m_diffuse = diffuse; }
	void setNormalTexture(const Texture& normal) { m_normalMap = normal; }
	void setdisplacementTexture(const Texture& displace) { m_displacementMap = displace; }
	void setDisplacementMapOffset(const float offset) { m_dispMapOffset = offset; }
	void setSpecularIntensity(const float intensity) { m_specularIntensity = intensity; }
	void setSpecularPower(const float power) { m_specularPower = power; }
	void setDisplacementScale(const float scale) 
	{ 
		m_dispMapScale = scale; 
		float baseBias = (m_dispMapScale / 2.0f);
		m_dispMapBias = -baseBias + baseBias * m_dispMapOffset;
	}

private:
	Texture m_displacementMap;
	Texture m_normalMap;
	Texture m_diffuse;
	float m_dispMapScale;
	float m_dispMapBias;
	float m_specularIntensity;
	float m_specularPower;
	float m_dispMapOffset;
};

class Material
{
public:
	Material();
	Material( 
		float specularIntensity,
		float specularPower,
		const Texture& diffuse,
		const Texture& normalMap = Texture("default_normal.jpg"),
		const Texture& dispMap = Texture("default_disp.png"), 
		float dispMapScale = 0.0f, 
		float dispMapOffset = 0.0f);
	virtual ~Material();

private:

};

