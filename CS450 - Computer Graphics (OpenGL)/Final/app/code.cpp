#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include "glew.h"
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "glslprogram.h"


GLSLProgram	*Pattern;
float		 Time;




void
Display()
{

		Pattern->Use();
	Pattern->SetUniformVariable("uTime", Time);
	glCallList(SphereList);
	Pattern->Use(0);

}


void
InitGraphics()
{

	. . .

		// do this *after* opening the window and init'ing glew:

		Pattern = new GLSLProgram();
	bool valid = Pattern->Create("pattern.vert", "pattern.frag");
	if (!valid)
	{
		fprintf(stderr, "Shader cannot be created!\n");
		DoMainMenu(QUIT);
	}
	else
	{
		fprintf(stderr, "Shader created.\n");
	}
	Pattern->SetVerbose(false);
}




// not great programming style, but if you are uncomfortable with compiling
// multiple files in visual studio, this works too...

#include "glslprogram.cpp"