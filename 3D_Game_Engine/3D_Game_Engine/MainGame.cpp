#include "MainGame.h"
#include <string>
#include <vector>
#include <iostream>

#define LEFT_ROTATION_PANE m_input.getMouseCoords().x < 700
#define RIGHT_ROTATION_PANE m_input.getMouseCoords().x > m_width - 700

#define TOP_ROTATION_PANE m_input.getMouseCoords().y < 200
#define BOTTOM_ROTATION_PANE m_input.getMouseCoords().y > m_height - 200

void MainGame::run()
{
	std::string title = "Computer Graphics 2";
	ViewPort m(title, m_width, m_height, 0);
	setViewPort(m);

	init();
}

void MainGame::init()
{
	//// MODEL:
	m_model.LoadMesh("./Assets/Models/sphere.obj", "");

	// TEXTURE:
	Texture texture("./Assets/SkyBoxes/dice_block/left.jpg");
	m_shapeTexture = texture;
	Texture bulbTexture("./Assets/Textures/aluminium-texture-6102637.jpg");
	m_bulbTex = bulbTexture;

	std::vector <std::string> cubeTextures;
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/right.jpg");
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/left.jpg");
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/top.jpg");
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/bottom.jpg");
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/back.jpg");
	cubeTextures.push_back("./Assets/SkyBoxes/CN_Tower/front.jpg");

	Texture cubeTexture;
	cubeTexture.createCubeMap(
		cubeTextures[0].c_str(),
		cubeTextures[1].c_str(),
		cubeTextures[2].c_str(),
		cubeTextures[3].c_str(),
		cubeTextures[4].c_str(),
		cubeTextures[5].c_str()
		);

	std::vector <std::string> diceCubeTextures;
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/right.jpg");
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/left.jpg");
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/top.jpg");
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/bottom.jpg");
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/back.jpg");
	diceCubeTextures.push_back("./Assets/SkyBoxes/dice_block/front.jpg");

	Texture diceCubeTexture;
	diceCubeTexture.createCubeMap(
		diceCubeTextures[0].c_str(),
		diceCubeTextures[1].c_str(),
		diceCubeTextures[2].c_str(),
		diceCubeTextures[3].c_str(),
		diceCubeTextures[4].c_str(),
		diceCubeTextures[5].c_str()
		);

	m_skyBoxTex = cubeTexture;
	m_diceBlockTex = diceCubeTexture;

	// SHAPE:
	m_shape.createShape(CUBOID, 20.0f, 0.0f);
	Mesh cubeMesh(m_shape.getVertices(), m_shape.getVertices().size());

	m_shape2.createShape(CUBOID);
	Mesh cube2Mesh(m_shape2.getVertices(), m_shape2.getVertices().size());

	m_shape3.createShape(CUBOID);
	Mesh cube3Mesh(m_shape3.getVertices(), m_shape3.getVertices().size());

	m_lightBulb.createShape(SPHERE, 0.15f, 2.0f, 16);
	Mesh bulbMesh(m_lightBulb.getVertices(), m_lightBulb.getVertices().size());

	m_skyBox.createShape(CUBOID);
	Mesh skyBoxMesh(m_skyBox.getVertices(), m_skyBox.getVertices().size());

	// Create Blinn-Phong Shader

	ShaderNova basic;

	std::vector<std::string> shaderFiles;
	shaderFiles.push_back("./Assets/Shaders/blinnPhongVert.glsl");
	shaderFiles.push_back("./Assets/Shaders/blinnPhongFrag.glsl");

	basic.compileShadersFromFile(shaderFiles);

	basic.addAttributes("position");
	basic.addAttributes("textureCoords");
	basic.addAttributes("normal");
	basic.linkShaders();

	setShaderProgram(basic);

	// Create Reflection Shader

	ShaderNova reflection;

	std::vector<std::string> reflectionShaderFiles;
	reflectionShaderFiles.push_back("./Assets/Shaders/reflectionVert.glsl");
	reflectionShaderFiles.push_back("./Assets/Shaders/reflectionFrag.glsl");

	reflection.compileShadersFromFile(reflectionShaderFiles);

	reflection.addAttributes("position");
	reflection.addAttributes("textureCoords");
	reflection.addAttributes("normal");
	reflection.linkShaders();

	setReflectionShaderProgram(reflection);

	// Create Refraction Shader

	ShaderNova refraction;

	std::vector<std::string> refractionShaderFiles;
	refractionShaderFiles.push_back("./Assets/Shaders/refractionVert.glsl");
	refractionShaderFiles.push_back("./Assets/Shaders/refractionFrag.glsl");

	refraction.compileShadersFromFile(refractionShaderFiles);

	refraction.addAttributes("position");
	refraction.addAttributes("normal");
	refraction.linkShaders();

	setRefractionShaderProgram(refraction);

	// Create Reference Shader (Testing Purposes)

	ShaderNova ref;

	std::vector<std::string> refShaderFiles;
	refShaderFiles.push_back("./Assets/Shaders/refVert.glsl");
	refShaderFiles.push_back("./Assets/Shaders/refFrag.glsl");

	ref.compileShadersFromFile(refShaderFiles);

	ref.addAttributes("position");
	ref.addAttributes("normal");
	ref.linkShaders();

	setRefractionShaderProgram(ref);

	// CAMERA INIT:
	m_cam.setPosition(glm::vec3(0.0f, -3.0f, 10.0f));
	m_cam.setFieldOfView(70.0f);
	m_cam.setViewportAspectRatio((float)m_width / (float)m_height);
	m_cam.setNearAndFarPlanes(1.0f, 20000.0f);

	// START GAMELOOP:
	gameLoop();
}

void MainGame::processInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_appState = AppState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_input.setMouseCoords((float)e.motion.x, (float)e.motion.y);
			m_offset = getGLWindowCoords((float)e.motion.x, (float)e.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			break;
		case SDL_KEYDOWN:
			m_input.keyPressed(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_input.keyReleased(e.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_input.keyPressed(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_input.keyReleased(e.button.button);
			break;
		default:
			break;
		}

		if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				SDL_Log("Window %d shown", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				SDL_Log("Window %d hidden", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_Log("Window %d exposed", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d",
					e.window.windowID, e.window.data1,
					e.window.data2);
				break;
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window %d resized to %dx%d",
					e.window.windowID, e.window.data1,
					e.window.data2);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d",
					e.window.windowID, e.window.data1,
					e.window.data2);
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				SDL_Log("Window %d restored", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_ENTER:
				SDL_Log("Mouse entered window %d",
					e.window.windowID);
				break;
			case SDL_WINDOWEVENT_LEAVE:
				SDL_Log("Mouse left window %d", e.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				SDL_Log("Window %d gained keyboard focus",
					e.window.windowID);
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				SDL_Log("Window %d lost keyboard focus",
					e.window.windowID);
				break;
			case SDL_WINDOWEVENT_CLOSE:
				SDL_Log("Window %d closed", e.window.windowID);
				break;
			default:
				SDL_Log("Window %d got unknown event %d",
					e.window.windowID, e.window.event);
				break;
			}
		}
	}

	if (m_input.isKeyDown(SDLK_ESCAPE))
	{
		m_appState = AppState::EXIT;
	}
	if (m_input.isKeyDown(SDLK_w))
	{
		m_cam.setPosition((m_cam.position() + m_cam.forward()));
	}
	if (m_input.isKeyDown(SDLK_s))
	{
		m_cam.setPosition((m_cam.position() - m_cam.forward()));
	}
	if (m_input.isKeyDown(SDLK_a))
	{
		m_cam.setPosition((m_cam.position() - m_cam.right()));
	}
	if (m_input.isKeyDown(SDLK_d))
	{
		m_cam.setPosition((m_cam.position() + m_cam.right()));
	}
	if (m_input.isKeyDown(SDLK_r))
	{
		m_cam.setPosition((m_cam.position() + m_cam.up()));
	}
	if (m_input.isKeyDown(SDLK_f))
	{
		m_cam.setPosition((m_cam.position() - m_cam.up()));
	}
	if (LEFT_ROTATION_PANE || RIGHT_ROTATION_PANE)
	{
		m_cam.offsetOrientation(0.0f, m_offset.x * 3.5f);
	}

	if (TOP_ROTATION_PANE || BOTTOM_ROTATION_PANE)
	{
		m_cam.offsetOrientation(-m_offset.y * 3.5f, 0.0f);
	}
}

void MainGame::draw()
{
	//////////////////////////////////////////////////////////////////////

	m_shader.startUse();

	m_shape2.setPosition(glm::vec3(30.0f, 10.0f, -40.0f));
	m_shape2.setRotation(glm::vec3(sinf(m_counter)));
	m_shape2.setScale(glm::vec3(20.0f));

	GLint camMUniform = m_shader.getUniformLocation("camera");
	glm::mat4 cameraMMatrix = m_cam.matrix();
	glUniformMatrix4fv(camMUniform, 1, GL_FALSE, &cameraMMatrix[0][0]);

	GLint modelMUniform = m_shader.getUniformLocation("model");
	glm::mat4 modelMMatrix = m_shape2.getModel();
	glUniformMatrix4fv(modelMUniform, 1, GL_FALSE, &modelMMatrix[0][0]);

	GLint normalMUniform = m_shader.getUniformLocation("normalMat");
	glm::mat4 normalMMatrix = m_shape2.getNormalMatrix();
	glUniformMatrix4fv(normalMUniform, 1, GL_FALSE, &normalMMatrix[0][0]);

	GLint lightMUniform = m_shader.getUniformLocation("lightPos");

	glm::vec3 lightPosition = glm::vec3(
		cosf(m_counter * 1000),
		sinf(m_counter * 400),
		cosf(m_counter * 1000) + 5.0f);

	glUniform3fv(lightMUniform, 1, &lightPosition[0]);

	m_shapeTexture.bind2D(0);

	m_shape2.draw();

	m_shader.stopUse();


	///////////////////////////////////

	m_reflectionShader.startUse();

	GLint viewSkyBox = m_reflectionShader.getUniformLocation("view");
	glm::mat4 viewMatSkyBox = m_cam.view();
	glUniformMatrix4fv(viewSkyBox, 1, GL_FALSE, &viewMatSkyBox[0][0]);

	GLint projectionSkyBox = m_reflectionShader.getUniformLocation("projection");
	glm::mat4 projectionMatSkyBox = m_cam.projection();
	glUniformMatrix4fv(projectionSkyBox, 1, GL_FALSE, &projectionMatSkyBox[0][0]);

	GLint modelUniformSkyBox = m_reflectionShader.getUniformLocation("model");
	glm::mat4 modelMatrixSkyBox = m_skyBox.getModel();
	glUniformMatrix4fv(modelUniformSkyBox, 1, GL_FALSE, &modelMatrixSkyBox[0][0]);

	GLint camPosSkyBox = m_reflectionShader.getUniformLocation("camPosition");
	glm::vec3 camPositionSkyBox = m_cam.position();
	glUniform3fv(camPosSkyBox, 1, &camPositionSkyBox[0]);

	GLint tintColourSkyBox = m_reflectionShader.getUniformLocation("MaterialColor");
	glm::vec4 tintColourVecSkyBox = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(tintColourSkyBox, 1, GL_FALSE, &tintColourVecSkyBox[0]);

	GLint drawSkyBoxA = m_reflectionShader.getUniformLocation("DrawSkyBox");
	bool isSkyBoxA = true;
	glUniform1i(drawSkyBoxA, isSkyBoxA);

	GLint reflectFactorSkyBox = m_reflectionShader.getUniformLocation("ReflectFactor");
	float reflectAmountSkyBox = 1.0f;
	glUniform1f(reflectFactorSkyBox, reflectAmountSkyBox);

	m_skyBoxTex.bindCube(0);

	m_skyBox.setPosition(m_cam.position());
	m_skyBox.setRotation(glm::vec3(0.0f));
	m_skyBox.setScale(glm::vec3(2000.0f));

	m_skyBox.draw();

	m_reflectionShader.stopUse();

	////////////////////////////////////////////////////////////////////
	//REFRACTION SHADER

	m_refractionShader.startUse();

	GLint view1 = m_refractionShader.getUniformLocation("view");
	glm::mat4 view1Mat = m_cam.view();
	glUniformMatrix4fv(view1, 1, GL_FALSE, &view1Mat[0][0]);

	GLint projection1 = m_refractionShader.getUniformLocation("projection");
	glm::mat4 projection1Mat = m_cam.projection();
	glUniformMatrix4fv(projection1, 1, GL_FALSE, &projection1Mat[0][0]);

	GLint modelUniform1 = m_refractionShader.getUniformLocation("model");
	glm::mat4 modelMatrix1 = m_shape3.getModel();
	glUniformMatrix4fv(modelUniform1, 1, GL_FALSE, &modelMatrix1[0][0]);

	GLint camPos1 = m_refractionShader.getUniformLocation("camPosition");
	glm::vec3 camPosition1 = m_cam.position();
	glUniform3fv(camPos1, 1, &camPosition1[0]);

	//GLint reflectFactorRefraction = m_refractionShader.getUniformLocation("ReflectFactor");
	//float reflectAmountRefraction = 1.0f;
	//glUniform1f(reflectFactorRefraction, reflectAmountRefraction);

	//GLint refractFactor = m_refractionShader.getUniformLocation("RefractFactor");
	//float refractAmount = 1.0f;
	//glUniform1f(refractFactor, refractAmount);

	//GLint lightUniform = m_refractionShader.getUniformLocation("lightPos");
	//glUniform3fv(lightUniform, 1, &lightPosition[0]);

	//m_shapeTexture.bind2D(0);
	m_skyBoxTex.bindCube(0);

	m_shape3.setPosition(glm::vec3(70.0f, 10.0f, -90.0f));
	m_shape3.setRotation(glm::vec3(0.0f));
	m_shape3.setScale(glm::vec3(10.0f));

	m_shape3.draw();

	m_refractionShader.stopUse();


	///////////////////////////////////
	//REFLECTION SHADER

	m_reflectionShader.startUse();

	GLint view = m_reflectionShader.getUniformLocation("view");
	glm::mat4 viewMat = m_cam.view();
	glUniformMatrix4fv(view, 1, GL_FALSE, &viewMat[0][0]);

	GLint projection = m_reflectionShader.getUniformLocation("projection");
	glm::mat4 projectionMat = m_cam.projection();
	glUniformMatrix4fv(projection, 1, GL_FALSE, &projectionMat[0][0]);

	GLint modelUniform = m_reflectionShader.getUniformLocation("model");
	glm::mat4 modelMatrix = m_shape.getModel();
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);

	GLint camPos = m_reflectionShader.getUniformLocation("camPosition");
	glm::vec3 camPosition = m_cam.position();// +m_cam.forward();
	glUniform3fv(camPos, 1, &camPosition[0]);

	GLint tintColour = m_reflectionShader.getUniformLocation("MaterialColor");
	glm::vec4 tintColourVec = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(tintColour, 1, GL_FALSE, &tintColourVec[0]);

	GLint drawSkyBox = m_reflectionShader.getUniformLocation("DrawSkyBox");
	bool isSkyBox = false;
	glUniform1i(drawSkyBox, isSkyBox);

	GLint reflectFactor = m_reflectionShader.getUniformLocation("ReflectFactor");
	float reflectAmount = 0.85f;
	glUniform1f(reflectFactor, reflectAmount);

	//GLint lightUniform = m_refractionShader.getUniformLocation("lightPos");
	//glUniform3fv(lightUniform, 1, &lightPosition[0]);

	m_skyBoxTex.bindCube(0);

	m_shape.setPosition(glm::vec3(-70.0f, 10.0f, 90.0f));
	m_shape.setRotation(glm::vec3(0.0f));
	m_shape.setScale(glm::vec3(1.0f));

	m_shape.draw();

	m_reflectionShader.stopUse();

	//////////////////////////////////////////////////////////////////////

	m_shader.startUse();

	GLint camLUniform = m_shader.getUniformLocation("camera");
	glm::mat4 cameraLMatrix = m_cam.matrix();
	glUniformMatrix4fv(camLUniform, 1, GL_FALSE, &cameraLMatrix[0][0]);

	GLint modelLUniform = m_shader.getUniformLocation("model");
	glm::mat4 modelLMatrix = m_lightBulb.getModel();
	glUniformMatrix4fv(modelLUniform, 1, GL_FALSE, &modelLMatrix[0][0]);

	GLint normalLUniform = m_shader.getUniformLocation("normalMat");
	glm::mat4 normalLMatrix = m_lightBulb.getNormalMatrix();
	glUniformMatrix4fv(normalLUniform, 1, GL_FALSE, &normalLMatrix[0][0]);

	GLint lightLUniform = m_shader.getUniformLocation("lightPos");
	glUniform3fv(lightLUniform, 1, &lightPosition[0]);

	m_bulbTex.bind2D(0);

	m_lightBulb.setPosition(lightPosition - 1.0f);
	m_lightBulb.setRotation(glm::vec3(0.0f));
	m_lightBulb.setScale(glm::vec3(1.0f));

	m_lightBulb.draw();

	m_shader.stopUse();

	/////////////////////////////////////////////////////////////////////

	m_counter += 0.0001f;
}

void MainGame::gameLoop()
{
	while (m_appState == AppState::RUNNING)
	{
		m_view.Update();
		m_view.swapBuffer(0.0f, 0.0f, 0.0f, 1.0f);
		m_input.update();

		draw();

		processInput();
	}

	SDL_Quit();
	exit(0);
}

