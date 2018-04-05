#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "opengl.h"
static const int WINDOW_WIDTH = 400;
static const int WINDOW_HEIGHT = 300;

/* scene functions defined in scene.c */
extern void sceneInit(void);
extern void sceneRender(void);
extern void sceneCycle(void);

static int g_window;

static void
handleKeyPress(unsigned char key, int x, int y)
{
	switch(key) {
		default:
			break;
		case 27: /* escape */
			glutDestroyWindow(g_window);
			exit(0);
			break;
	}
}

static void
setPerspective(float fov, float aspect, float near, float far)
{
	float f;
	float mat[16];

	f = 1.0f / tanf(fov / 2.0f);

	mat[0] = f / aspect;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;

	mat[4] = 0.0f;
	mat[5] = f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;

	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = (far + near) / (near  - far);
	mat[11] = -1.0f;

	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = (2.0f * far * near) / (near - far);
	mat[15] = 0.0f;

	glMultMatrixf(mat);
}

int
main(int argc, char *argv[])
{
	/* initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	g_window = glutCreateWindow("OpenGL demo - http://joshbeam.com/");
	/* setup callbacks */
	glutDisplayFunc(sceneRender);
	glutIdleFunc(sceneCycle);
	glutKeyboardFunc(handleKeyPress);

	/* setup initial GL settings */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	/* set projection matrix */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective(M_PI / 4.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);

	/* initialize scene and start GLUT main loop */
	sceneInit();
	glutMainLoop();
	return 0;
}
