//Scene.cpp

#include "Scene.h"

Shader* shader;

Scene::Scene() : X_Pos(0), Y_Pos(0), X_Angle(-10), Y_Angle(-10), Cam_Pos_X(0), Cam_Pos_Y(1), Cam_Pos_Z(5) {}

void Scene::initOpenGL() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Moving Pyramid");
	glutPositionWindow(800, 150);

	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed!" << std::endl;
		exit(EXIT_FAILURE);
	}

	CreateShader();


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}


void Scene::printStats(bool CameraMode) {
	static int Iteration = 0;
	if (Iteration == 100) {
		if (!CameraMode)
		std::cout << "\rPyramid Position: (" << X_Pos << ", " << Y_Pos << ") "
			<< "Rotation: (" << X_Angle << ", " << Y_Angle << ")           " 
			<< std::flush;
		else
		std::cout << "\rCamera Position: (" << Cam_Pos_X << ", " << Cam_Pos_Y << ", " << Cam_Pos_Z << ") " 
			<< "Camera Lock: " << (Cam_Lock ? "ON " : "OFF ") << "Cursor Lock: " << (Cursor_Lock ? "ON       " : "OFF                 ")
			<< std::flush;
		Iteration = 0;
		}
	else
	Iteration++;

}


void Scene::RenderFunction() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();
		
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(X_Pos, Y_Pos, 0.0f));
	model = glm::rotate(model, glm::radians(X_Angle), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(Y_Angle), glm::vec3(1, 0, 0));
	
	glm::mat4 view;
	if (Cam_Lock == false)
	{
		
			CamFront = glm::normalize(glm::vec3(
				cos(glm::radians(CamYaw)) * cos(glm::radians(CamPitch)),
				sin(glm::radians(CamPitch)),
				sin(glm::radians(CamYaw)) * cos(glm::radians(CamPitch))));
			glm::vec3 eye = glm::vec3(Cam_Pos_X, Cam_Pos_Y, Cam_Pos_Z);

			view = glm::lookAt(
				eye,
				eye + CamFront,
				CamUp
			);
		}

	else 
		{
		CamFront = glm::vec3(0.0f, 0.0f, -1.0f);
		view = glm::lookAt(
			glm::vec3(Cam_Pos_X, Cam_Pos_Y, Cam_Pos_Z),
			glm::vec3(X_Pos, Y_Pos, 0.0f),
			CamUp
		);
	}
	glm::mat4 projection = glm::perspective(
									glm::radians(45.0f), 
									(float)Width / Height,		// aspect 
									0.1f,						// nearest point
									100.0f						// furthest point
									);

	GLint modelLoc = glGetUniformLocation(shader->ProgramId, "model");
	GLint viewLoc = glGetUniformLocation(shader->ProgramId, "view");
	GLint projLoc = glGetUniformLocation(shader->ProgramId, "projection");
	GLint lightPosLoc = glGetUniformLocation(shader->ProgramId, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(shader->ProgramId, "viewPos");

	glUniform3f(lightPosLoc, 0.0f, 5.0f, 0.0f); 
	glUniform3f(viewPosLoc, Cam_Pos_X, Cam_Pos_Y, Cam_Pos_Z);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw moving pyramid with its model matrix
	pyramid.Draw();

	// Draw static plane: reset model to identity so it does not move with pyramid
	glm::mat4 planeModel = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(planeModel));
	area.Draw();

	glutSwapBuffers();
}



void Scene::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h,0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::movePyramid() {
	float Step = 0.01f;
	/*if (specialKeyStates[GLUT_KEY_UP]) Y_Pos += Step;
	if (specialKeyStates[GLUT_KEY_DOWN]) Y_Pos -= Step;
	if (specialKeyStates[GLUT_KEY_LEFT]) X_Pos -= Step;
	if (specialKeyStates[GLUT_KEY_RIGHT]) X_Pos += Step;*/
	
	if (X_Pos < -4) X_Pos = 4;
	if (X_Pos > 4) X_Pos = -4;
	if (Y_Pos < -3) Y_Pos = 3;
	if (Y_Pos > 3) Y_Pos = -3;

	glutPostRedisplay();
	printStats(true);
}

void Scene::rotatePyramid() {
	float AngleStep = 1.0;

	if (specialKeyStates[GLUT_KEY_DOWN]) Y_Angle += AngleStep;
	if (specialKeyStates[GLUT_KEY_UP]) Y_Angle -= AngleStep;
	if (specialKeyStates[GLUT_KEY_LEFT]) X_Angle += AngleStep;
	if (specialKeyStates[GLUT_KEY_RIGHT]) X_Angle -= AngleStep;
	if (keyStates['r'] || keyStates['R']) { Y_Angle = 0; X_Angle = 0;}
	if (keyStates['f'] || keyStates['F']) { Y_Pos = 0; X_Pos = 0;}
	
	if (keyStates[27]) exit(EXIT_SUCCESS);

	if ((X_Angle >= 360) || (X_Angle <= -360)) X_Angle = 0;
	if ((Y_Angle >= 360) || (Y_Angle <= -360)) Y_Angle = 0;

	glutPostRedisplay();
	printStats(true);
}

void Scene::moveCamera() {
	float CamStep = 0.1f;
	float TurnStep = 1.0f;

	if (keyStates['j'] || keyStates['J']) CamYaw -= TurnStep;
	if (keyStates['l'] || keyStates['L']) CamYaw += TurnStep;
	if (keyStates['i'] || keyStates['I']) CamPitch += TurnStep;
	if (keyStates['k'] || keyStates['K']) CamPitch -= TurnStep;
	if (keyStates['u'] || keyStates['U']) { 
		CamYaw = -90.0f; CamPitch = 0.0f; 
		Cam_Pos_X = 0.0f; Cam_Pos_Y = 1.0f; Cam_Pos_Z = 5.0f;
	}
	
	CamPitch = glm::clamp(CamPitch, -89.0f, 89.0f);

	glm::vec3 front = CamFront;
	glm::vec3 right = glm::normalize(glm::cross(front, CamUp));
	glm::vec3 up = CamUp;

	glm::vec3 camPos(Cam_Pos_X, Cam_Pos_Y, Cam_Pos_Z);
	if (keyStates['w'] || keyStates['W'])    camPos += front * CamStep;
	if (keyStates['s'] || keyStates['S'])    camPos -= front * CamStep;
	if (keyStates['a'] || keyStates['A'])    camPos -= right * CamStep;
	if (keyStates['d'] || keyStates['D'])    camPos += right * CamStep;

	if (keyStates[32])                       camPos += up * CamStep; // Space key

	Cam_Pos_X = camPos.x;
	Cam_Pos_Y = camPos.y;
	Cam_Pos_Z = camPos.z;

	glutPostRedisplay();
}	

void Scene::ToggleCamLock() {
	Cam_Lock = !Cam_Lock;
}

void Scene::cursorMovement(float xoffset, float yoffset)
{
	float sensitivity = 0.5f; 
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	CamYaw += xoffset;
	CamPitch -= yoffset;
	CamPitch = glm::clamp(CamPitch, -89.0f, 89.0f);
}

void Scene::CreateShader() {
	shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl"); 
	//shader->Use();
	pyramid.Init(shader->ProgramId);
	area.Init(shader->ProgramId);
}