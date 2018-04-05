/*
 */

#ifndef __OPENGL_H__
#define __OPENGL_H__

#ifdef APPLE
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glext.h>
	#include <GL/glut.h>
#endif /* APPLE */

#endif /* __OPENGL_H__ */
