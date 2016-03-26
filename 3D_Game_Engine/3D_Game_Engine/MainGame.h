#include "Core/ViewPort.h"
#include "Core/Camera3D.h"
#include "Core/InputManager.h"
#include "Rendering/ShaderNova.h"
#include "Rendering/Shape.h"
#include "Rendering/AssImpModelLoader.h"

enum AppState
{
	RUNNING,
	EXIT
};

class MainGame
{

public:

	MainGame() 
	{
	}

	~MainGame() {}

	void run();

private:

	void init();
	void draw();
	void gameLoop();
	void processInput();

	void setViewPort(ViewPort & view) { m_view = view; }
	void setTexture(Texture & tex) { m_shapeTexture = tex; }
	void setShaderProgram(ShaderNova & shader) { m_shader = shader; }
	void setReflectionShaderProgram(ShaderNova & shader) { m_reflectionShader = shader; }
	void setRefractionShaderProgram(ShaderNova & shader) { m_refractionShader = shader; }
	void setRefShaderProgram(ShaderNova & shader) { m_refShader = shader; }

	inline glm::vec2 getGLWindowCoords(float x, float y)
	{
		float X_Coord = x;
		float Y_Coord = y;

		X_Coord -= m_width / 2.0f;
		Y_Coord -= m_height / 2.0f;

		Y_Coord *= -1;

		X_Coord /= 1000.0f;
		Y_Coord /= 1000.0f;

		return glm::vec2(X_Coord, Y_Coord);
	}

	// VARIABLES:
	int m_width = 1024, m_height = 1024;

	Camera3D m_cam;
	ViewPort m_view;
	ShaderNova m_shader, m_reflectionShader, m_refractionShader, m_refShader;
	Shape m_shape, m_shape2, m_shape3, m_lightBulb, m_skyBox;
	Texture m_shapeTexture, m_bulbTex, m_skyBoxTex, m_diceBlockTex;
	InputManager m_input;
	ModelMesh m_model;

	glm::vec2 m_offset;

	float m_counter = 0;
	AppState m_appState = AppState::RUNNING;
};

