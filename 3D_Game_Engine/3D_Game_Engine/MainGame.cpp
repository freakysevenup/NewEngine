#include "MainGame.h"
#include <string>
#include <vector>
#include <iostream>

#define LEFT_ROTATION_PANE m_input.getMouseCoords().x < (0.0f + m_width / 4.0f)
#define RIGHT_ROTATION_PANE m_input.getMouseCoords().x > (m_width - m_width / 4.0f)

#define TOP_ROTATION_PANE m_input.getMouseCoords().y < (0 + m_height / 4.0f)
#define BOTTOM_ROTATION_PANE m_input.getMouseCoords().y > (m_height - m_height / 4.0f)

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
	m_model.LoadMesh("./Assets/Models/HumanFighter_Final.obj", "./Assets/Models/");
	m_model2.LoadMesh("./Assets/Models/HumanFighter_Final.obj", "./Assets/Models/");

	// TEXTURE:
	Texture texture("./Assets/SkyBoxes/dice_block/left.jpg");
	m_shapeTexture = texture;
	Texture bulbTexture("./Assets/Textures/aluminium-texture-6102637.jpg");
	m_bulbTex = bulbTexture;

	Texture humanTex("./Assets/Textures/HumanShip.png");
	m_humanShipTex = humanTex;

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
	m_shape.createShape(CUBOID, 30.0f, 0.0f);
	Mesh cubeMesh(m_shape.getVertices(), m_shape.getVertices().size());

	m_shape2.createShape(CUBOID);
	Mesh cube2Mesh(m_shape2.getVertices(), m_shape2.getVertices().size());

	m_shape3.createShape(CUBOID, 30.0f, 2.0f);
	Mesh cube3Mesh(m_shape3.getVertices(), m_shape3.getVertices().size());

	m_shape4.createShape(CUBOID, 30.0f, 2.0f);
	Mesh cube4Mesh(m_shape4.getVertices(), m_shape4.getVertices().size());

	m_shape5.createShape(CUBOID, 30.0f, 0.0f);
	Mesh cube5Mesh(m_shape5.getVertices(), m_shape5.getVertices().size());

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
	refraction.addAttributes("textureCoords");
	refraction.addAttributes("normal");
	refraction.linkShaders();

	setRefractionShaderProgram(refraction);

	// Create Toon/Cel Shader

	ShaderNova toonCel;

	std::vector<std::string> toonCelShaderFiles;
	toonCelShaderFiles.push_back("./Assets/Shaders/celShaderVert.glsl");
	toonCelShaderFiles.push_back("./Assets/Shaders/celShaderFrag.glsl");

	toonCel.compileShadersFromFile(toonCelShaderFiles);

	toonCel.addAttributes("position");
	toonCel.addAttributes("textureCoords");
	toonCel.addAttributes("normal");
	toonCel.linkShaders();

	setToonCelShaderProgram(toonCel);

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

	////////////////////////////////////////////////////////////////////
	//REFRACTION SHADER

	m_material.Eta = 0.1f;
	m_material.ReflectionFactor = 1.0f;

	m_refractionShader.startUse();

	GLint REFRACTIONView = m_refractionShader.getUniformLocation("view");
	glm::mat4 REFRACTIONViewMat = m_cam.view();
	glUniformMatrix4fv(REFRACTIONView, 1, GL_FALSE, &REFRACTIONViewMat[0][0]);

	GLint REFRACTIONProjection = m_refractionShader.getUniformLocation("projection");
	glm::mat4 REFRACTIONProjectionMat = m_cam.projection();
	glUniformMatrix4fv(REFRACTIONProjection, 1, GL_FALSE, &REFRACTIONProjectionMat[0][0]);

	GLint REFRACTIONModel = m_refractionShader.getUniformLocation("model");
	glm::mat4 REFRACTIONModelMatrix = m_model2.getModel();
	glUniformMatrix4fv(REFRACTIONModel, 1, GL_FALSE, &REFRACTIONModelMatrix[0][0]);

	GLint REFRACTIONCamPos = m_refractionShader.getUniformLocation("camPosition");
	glm::vec3 REFRACTIONCamVec = m_cam.position();
	glUniform3fv(REFRACTIONCamPos, 1, &REFRACTIONCamVec[0]);

	GLint REFRACTIONDrawSkyBox = m_refractionShader.getUniformLocation("DrawSkyBox");
	bool REFRACTIONisSkyBox = false;
	glUniform1i(REFRACTIONDrawSkyBox, REFRACTIONisSkyBox);

	GLint REFRACTIONMaterialEta = m_refractionShader.getUniformLocation("Material.Eta");
	float REFRACTIONMaterialEtaFactor = m_material.Eta;
	glUniform1f(REFRACTIONMaterialEta, REFRACTIONMaterialEtaFactor);

	GLint REFRACTIONMaterialReflectFactor = m_refractionShader.getUniformLocation("Material.ReflectionFactor");
	float REFRACTIONMaterialReflectAmount = m_material.ReflectionFactor;
	glUniform1f(REFRACTIONMaterialReflectFactor, REFRACTIONMaterialReflectAmount);

	m_skyBoxTex.bindCube(0);

	m_model2.setPosition(glm::vec3(90.0f, 10.0f, 110.0f));
	m_model2.setRotation(glm::vec3(0.0f));
	m_model2.setScale(glm::vec3(1.0f));

	//m_shape3.draw();
	m_model2.Render();

	m_refractionShader.stopUse();

	////////////////////////////////////////////////////////////////////
	//TOON/CEL SHADER

	//m_light.position = glm::vec3(
	//	cosf(m_counter * 1000),
	//	sinf(m_counter * 400),
	//	cosf(m_counter * 1000) + 5.0f);
	//m_light.intensity = glm::vec3(1.0f);

	//m_celShader.startUse();

	//m_shape4.setPosition(glm::vec3(30.0f, 10.0f, -40.0f));
	//m_shape4.setRotation(glm::vec3(sinf(m_counter)));
	//m_shape4.setScale(glm::vec3(1.0f));

	//GLint TOONViewUniform = m_celShader.getUniformLocation("view");
	//glm::mat4 TOONViewMMatrix = m_cam.matrix();
	//glUniformMatrix4fv(TOONViewUniform, 1, GL_FALSE, &TOONViewMMatrix[0][0]);

	//GLint TOONProjectionUniform = m_celShader.getUniformLocation("projection");
	//glm::mat4 TOONProjectionMMatrix = m_cam.matrix();
	//glUniformMatrix4fv(TOONProjectionUniform, 1, GL_FALSE, &TOONProjectionMMatrix[0][0]);

	//GLint TOONmodelMUniform = m_celShader.getUniformLocation("model");
	//glm::mat4 TOONmodelMMatrix = m_shape4.getModel();
	//glUniformMatrix4fv(TOONmodelMUniform, 1, GL_FALSE, &TOONmodelMMatrix[0][0]);

	//GLint TOONCamPos = m_celShader.getUniformLocation("camPosition");
	//glm::vec3 TOONCamVec = glm::vec3(0.0f, 0.0f, 0.0f);// m_cam.position();
	//glUniform3fv(TOONCamPos, 1, &TOONCamVec[0]);

	//GLint TOONlightPosUniform = m_celShader.getUniformLocation("lightPos");
	//glm::vec3 TOONlightPosition = m_light.position;
	//glUniform3fv(TOONlightPosUniform, 1, &TOONlightPosition[0]);

	//GLint TOONlightIntensityUniform = m_celShader.getUniformLocation("shininess");
	//float TOONshininess = 20.0f;
	//glUniform1i(TOONlightIntensityUniform, TOONshininess);

	//GLint TOONDiffuseUniform = m_celShader.getUniformLocation("material_diffuse");
	//glm::vec4 TOONDiffuseVec = glm::vec4(0.8, 0.0, 0.0, 1.0);
	//glUniform3fv(TOONDiffuseUniform, 1, &TOONDiffuseVec[0]);

	//GLint TOONSpecularUniform = m_celShader.getUniformLocation("material_specular");
	//glm::vec4 TOONSpecularVec = glm::vec4(1.0, 0.0, 0.0, 1.0);
	//glUniform3fv(TOONSpecularUniform, 1, &TOONSpecularVec[0]);

	//GLint TOONAmbientUniform = m_celShader.getUniformLocation("material_ambient");
	//glm::vec4 TOONAmbientVec = glm::vec4(0.8, 0.8, 0.8, 1.0);
	//glUniform3fv(TOONAmbientUniform, 1, &TOONAmbientVec[0]);

	//m_bulbTex.bind2D(0);

	//m_shape4.draw();
	////m_model3.Render();

	//m_celShader.stopUse();

	//////////////////////////////////////////////////////////////////////
	// BLINN_PHONG

	m_shader.startUse();

	m_shape2.setPosition(glm::vec3(100.0f, 10.f, -100.0f));
	m_shape2.setRotation(glm::vec3(sinf(m_counter)));
	m_shape2.setScale(glm::vec3(20.0f));

	GLint BLINN_PHONGcamMUniform = m_shader.getUniformLocation("camera");
	glm::mat4 BLINN_PHONGcameraMMatrix = m_cam.matrix();
	glUniformMatrix4fv(BLINN_PHONGcamMUniform, 1, GL_FALSE, &BLINN_PHONGcameraMMatrix[0][0]);

	GLint BLINN_PHONGmodelMUniform = m_shader.getUniformLocation("model");
	glm::mat4 BLINN_PHONGmodelMMatrix = m_shape2.getModel();
	glUniformMatrix4fv(BLINN_PHONGmodelMUniform, 1, GL_FALSE, &BLINN_PHONGmodelMMatrix[0][0]);

	GLint BLINN_PHONGnormalMUniform = m_shader.getUniformLocation("normalMat");
	glm::mat4 BLINN_PHONGnormalMMatrix = m_shape2.getNormalMatrix();
	glUniformMatrix4fv(BLINN_PHONGnormalMUniform, 1, GL_FALSE, &BLINN_PHONGnormalMMatrix[0][0]);

	GLint BLINN_PHONGlightMUniform = m_shader.getUniformLocation("lightPos");

	glm::vec3 BLINN_PHONGlightPosition = glm::vec3(
		-100.0f, 100.0f + sinf(m_counter * 100) * 100.0f, 0.0f);

	glUniform3fv(BLINN_PHONGlightMUniform, 1, &BLINN_PHONGlightPosition[0]);

	m_shapeTexture.bind2D(0);

	m_shape2.draw();
	//m_model.Render();

	m_shader.stopUse();

	//////////////////////////////////////////////////////////////////////
	// DICE_BLOCK

	m_reflectionShader.startUse();

	GLint DICE_BLOCKview = m_reflectionShader.getUniformLocation("view");
	glm::mat4 DICE_BLOCKviewMat = m_cam.view();
	glUniformMatrix4fv(DICE_BLOCKview, 1, GL_FALSE, &DICE_BLOCKviewMat[0][0]);

	GLint DICE_BLOCKprojection = m_reflectionShader.getUniformLocation("projection");
	glm::mat4 DICE_BLOCKprojectionMat = m_cam.projection();
	glUniformMatrix4fv(DICE_BLOCKprojection, 1, GL_FALSE, &DICE_BLOCKprojectionMat[0][0]);

	GLint DICE_BLOCKmodelUniform = m_reflectionShader.getUniformLocation("model");
	glm::mat4 DICE_BLOCKmodelMatrix = m_shape5.getModel();
	glUniformMatrix4fv(DICE_BLOCKmodelUniform, 1, GL_FALSE, &DICE_BLOCKmodelMatrix[0][0]);

	GLint DICE_BLOCKcamPos = m_reflectionShader.getUniformLocation("camPosition");
	glm::vec3 DICE_BLOCKcamPosition = m_cam.position();
	glUniform3fv(DICE_BLOCKcamPos, 1, &DICE_BLOCKcamPosition[0]);

	GLint DICE_BLOCKdrawDICE_BLOCK = m_reflectionShader.getUniformLocation("DrawSkyBox");
	bool DICE_BLOCKisDICE_BLOCK = true;
	glUniform1i(DICE_BLOCKdrawDICE_BLOCK, DICE_BLOCKisDICE_BLOCK);

	GLint DICE_BLOCKreflectFactor = m_reflectionShader.getUniformLocation("ReflectFactor");
	float DICE_BLOCKreflectAmount = 0.1f;
	glUniform1f(DICE_BLOCKreflectFactor, DICE_BLOCKreflectAmount);

	GLint DICE_BLOCKlightMUniform = m_reflectionShader.getUniformLocation("lightPos");
	glUniform3fv(DICE_BLOCKlightMUniform, 1, &BLINN_PHONGlightPosition[0]);

	m_diceBlockTex.bindCube(0);

	m_shape5.setPosition(glm::vec3(-100.0f, 10.0f, -100.0f));
	m_shape5.setRotation(glm::vec3(cosf(m_counter) * 200.0f, sinf(m_counter) * 200.0f, cosf(m_counter) * 200.0f));
	m_shape5.setScale(glm::vec3(1.0f));

	m_shape5.draw();

	m_reflectionShader.stopUse();

	///////////////////////////////////
	//SKYBOX - REFLECTION

	m_reflectionShader.startUse();

	GLint SKYBOXview = m_reflectionShader.getUniformLocation("view");
	glm::mat4 SKYBOXviewMat = m_cam.view();
	glUniformMatrix4fv(SKYBOXview, 1, GL_FALSE, &SKYBOXviewMat[0][0]);

	GLint SKYBOXprojection = m_reflectionShader.getUniformLocation("projection");
	glm::mat4 SKYBOXprojectionMat = m_cam.projection();
	glUniformMatrix4fv(SKYBOXprojection, 1, GL_FALSE, &SKYBOXprojectionMat[0][0]);

	GLint SKYBOXmodelUniform = m_reflectionShader.getUniformLocation("model");
	glm::mat4 SKYBOXmodelMatrix = m_skyBox.getModel();
	glUniformMatrix4fv(SKYBOXmodelUniform, 1, GL_FALSE, &SKYBOXmodelMatrix[0][0]);

	GLint SKYBOXcamPos = m_reflectionShader.getUniformLocation("camPosition");
	glm::vec3 SKYBOXcamPosition = m_cam.position();
	glUniform3fv(SKYBOXcamPos, 1, &SKYBOXcamPosition[0]);

	GLint SKYBOXdrawSkyBox = m_reflectionShader.getUniformLocation("DrawSkyBox");
	bool SKYBOXisSkyBox = true;
	glUniform1i(SKYBOXdrawSkyBox, SKYBOXisSkyBox);

	GLint SKYBOXreflectFactor = m_reflectionShader.getUniformLocation("ReflectFactor");
	float SKYBOXreflectAmount = 0.1f;
	glUniform1f(SKYBOXreflectFactor, SKYBOXreflectAmount);

	GLint SKYBOXlightMUniform = m_reflectionShader.getUniformLocation("lightPos");
	glUniform3fv(SKYBOXlightMUniform, 1, &BLINN_PHONGlightPosition[0]);

	m_skyBoxTex.bindCube(0);

	m_skyBox.setPosition(m_cam.position());
	m_skyBox.setRotation(glm::vec3(0.0f));
	m_skyBox.setScale(glm::vec3(2000.0f));

	m_skyBox.draw();

	m_reflectionShader.stopUse();

	///////////////////////////////////
	//REFLECTION SHADER

	m_reflectionShader.startUse();

	GLint REFLECTIONView = m_reflectionShader.getUniformLocation("view");
	glm::mat4 REFLECTIONViewMat = m_cam.view();
	glUniformMatrix4fv(REFLECTIONView, 1, GL_FALSE, &REFLECTIONViewMat[0][0]);

	GLint REFLECTIONProjection = m_reflectionShader.getUniformLocation("projection");
	glm::mat4 REFLECTIONProjectionMat = m_cam.projection();
	glUniformMatrix4fv(REFLECTIONProjection, 1, GL_FALSE, &REFLECTIONProjectionMat[0][0]);

	GLint REFLECTIONModel = m_reflectionShader.getUniformLocation("model");
	glm::mat4 REFLECTIONModelMatrix = m_model.getModel();
	glUniformMatrix4fv(REFLECTIONModel, 1, GL_FALSE, &REFLECTIONModelMatrix[0][0]);

	GLint REFLECTIONCamPos = m_reflectionShader.getUniformLocation("camPosition");
	glm::vec3 REFLECTIONCamVec = m_cam.position();
	glUniform3fv(REFLECTIONCamPos, 1, &REFLECTIONCamVec[0]);

	GLint REFLECTIONDrawSkyBox = m_reflectionShader.getUniformLocation("DrawSkyBox");
	bool REFLECTIONisSkyBox = false;
	glUniform1i(REFLECTIONDrawSkyBox, REFLECTIONisSkyBox);

	GLint REFLECTIONReflectFactor = m_reflectionShader.getUniformLocation("ReflectFactor");
	float REFLECTIONReflectAmount = 1.0f;
	glUniform1f(REFLECTIONReflectFactor, REFLECTIONReflectAmount);

	GLint REFLECTIONlightMUniform = m_reflectionShader.getUniformLocation("lightPos");
	glUniform3fv(REFLECTIONlightMUniform, 1, &BLINN_PHONGlightPosition[0]);

	m_humanShipTex.bind2D(0);
	m_skyBoxTex.bindCube(0);

	m_model.setPosition(glm::vec3(-90.0f, 10.0f, 110.0f));
	m_model.setRotation(glm::vec3(0.0f));
	m_model.setScale(glm::vec3(1.0f));

	//m_shape.draw();
	m_model.Render();

	m_reflectionShader.stopUse();


	//////////////////////////////////////////////////////////////////////
	//BLINN_PHONG - LightBulb
	m_shader.startUse();

	GLint LightBulbcamLUniform = m_shader.getUniformLocation("camera");
	glm::mat4 LightBulbcameraLMatrix = m_cam.matrix();
	glUniformMatrix4fv(LightBulbcamLUniform, 1, GL_FALSE, &LightBulbcameraLMatrix[0][0]);

	GLint LightBulbmodelLUniform = m_shader.getUniformLocation("model");
	glm::mat4 LightBulbmodelLMatrix = m_lightBulb.getModel();
	glUniformMatrix4fv(LightBulbmodelLUniform, 1, GL_FALSE, &LightBulbmodelLMatrix[0][0]);

	GLint LightBulbnormalLUniform = m_shader.getUniformLocation("normalMat");
	glm::mat4 LightBulbnormalLMatrix = m_lightBulb.getNormalMatrix();
	glUniformMatrix4fv(LightBulbnormalLUniform, 1, GL_FALSE, &LightBulbnormalLMatrix[0][0]);

	GLint LightBulblightLUniform = m_shader.getUniformLocation("lightPos");
	glUniform3fv(LightBulblightLUniform, 1, &BLINN_PHONGlightPosition[0]);

	m_bulbTex.bind2D(0);

	m_lightBulb.setPosition(BLINN_PHONGlightPosition);
	m_lightBulb.setRotation(glm::vec3(0.0f));
	m_lightBulb.setScale(glm::vec3(10.0f));

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

