// main.cpp


// no more comments in this file

#include "Scene.h"

Scene scene;

void DisplayWrapper() {
				
						}
void TimerFunc(int value) {
	scene.movePyramid();
	scene.rotatePyramid();
	scene.moveCamera();
	glutPostRedisplay();
				scene.RenderFunction();

	glutTimerFunc(5, TimerFunc, 0);
}

void ReshapeWrapper(int w, int h) { scene.Reshape(w, h); }

void SpecialKeyWrapper(int key, int, int) { scene.specialKeyStates[key] = true; }

void SpecialKeyUpWrapper(int key, int, int) { scene.specialKeyStates[key] = false; }

void KeyboardWrapper(unsigned char key, int, int) { scene.keyStates[key] = true; }

void KeyboardUpWrapper(unsigned char key, int, int) {
	scene.keyStates[key] = false;
	if (key == 'q') scene.ToggleCamLock();
	if (key == 'c') scene.Cursor_Lock = !scene.Cursor_Lock;
}


static void MousePassiveMotionWrapper(int x, int y) {
	if (scene.getCursorLockStatus()) {
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		scene.cursorMovement(x - glutGet(GLUT_WINDOW_WIDTH) / 2, y - glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	scene.initOpenGL();
	std::cout << "WASD - Rotation\nArrow Keys - Movement\nR - Reset Angle\nT - Reset Position\nQ - Toggle Camera Lock\nU - Reset Camera\nC - Toggle Cursor Lock\n";

	

	glutDisplayFunc(DisplayWrapper);
	//glutIdleFunc(DisplayWrapper);
	glutReshapeFunc(ReshapeWrapper);
	glutKeyboardFunc(KeyboardWrapper);
	glutKeyboardUpFunc(KeyboardUpWrapper);
	glutSpecialFunc(SpecialKeyWrapper);
	glutSpecialUpFunc(SpecialKeyUpWrapper);
	glutPassiveMotionFunc(MousePassiveMotionWrapper);

	glutTimerFunc(10, TimerFunc, 0);


	glutMainLoop();
}