//Scene.h

#pragma once

#include "Pyramid.h"
#include "Area.hpp"
#include "Shaders.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
	public:

	Scene();	
	void RenderFunction();
	void Reshape(int width, int height);
	void initOpenGL();

	
	void CreateShader();
	static const GLchar* VertexShader;
	static const GLchar* FragmentShader;

	bool keyStates[256] = { false };
	char specialKeyStates[256] = { false };

	void movePyramid();
	void rotatePyramid();
	void moveCamera();
	void printStats(bool CameraMode = false);
	void ToggleCamLock();
	void cursorMovement(float xoffset, float yoffset);
	const bool getCursorLockStatus() { return Cursor_Lock; }
	bool Cursor_Lock = true;
private:
	int Width = 800;
	int Height = 600;
	float X_Angle, Y_Angle;
	float X_Pos, Y_Pos;
	float Cam_Pos_X, Cam_Pos_Y, Cam_Pos_Z;
	float CamYaw = -90.0f; // looking towards -Z initially
	float CamPitch = 0.0f;
	glm::vec3 CamFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CamUp = glm::vec3(0.0f, 1.0f, 0.0f);
	bool Cam_Lock = true;
	Pyramid pyramid;
	Area area;
	float lastTime = 0.0f;
};

