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



// NOTE: There are a lot of good reasons to use const variables instead
// of #define's.  However, Visual C++ does not allow a const variable
// to be used as an array size or as the case in a switch( ) statement.  So in
// the following, all constants are const variables except those which need to
// be array sizes or cases in switch( ) statements.  Those are #defines.


// title of these windows:

const char *WINDOWTITLE = { "Michael Commins - CS 450 - Project 6" };
const char *GLUITITLE   = { "User Interface Window" };


// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };


// the escape key:

#define ESCAPE		0x1b


// initial window size:

const int INIT_WINDOW_SIZE = { 600 };

// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };


// minimum allowable scale factor:

const float MINSCALE = { 0.05f };


// active mouse buttons (or them together):

const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };


// which projection:

enum Projections
{
	ORTHO,
	PERSP
};


// which button:

enum ButtonVals
{
	RESET,
	QUIT
};


// window background color (rgba):

const GLfloat BACKCOLOR[ ] = { 0., 0., 0., 1. };

// the color numbers:
// this order must match the radio button order

enum Colors
{
	RED,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA,
	WHITE,
	BLACK
};

char * ColorNames[ ] =
{
	"Red",
	"Yellow",
	"Green",
	"Cyan",
	"Blue",
	"Magenta",
	"White",
	"Black"
};


// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] = 
{
	{ 1., 0., 0. },		// red
	{ 1., 1., 0. },		// yellow
	{ 0., 1., 0. },		// green
	{ 0., 1., 1. },		// cyan
	{ 0., 0., 1. },		// blue
	{ 1., 0., 1. },		// magenta
	{ 1., 1., 1. },		// white
	{ 0., 0., 0. },		// black
};

// Project-Specific Constants
const GLint MS_PER_CYCLE = 1000;
const int NUMCURVES = 5;
const int NUMPOINTS = 4;
const int NUMVERTS = 100;

struct Point {
	float x0, y0, z0;       // initial coordinates
	float x, y, z;        // animated coordinates
};

struct Curve {
	float r, g, b, lw;
	Point ps[NUMPOINTS];
};

Curve Curves[NUMCURVES];		// if you are creating a pattern of curves

// fog parameters:

const GLfloat FOGCOLOR[4] = { .0, .0, .0, 1. };
const GLenum  FOGMODE     = { GL_LINEAR };
const GLfloat FOGDENSITY  = { 0.30f };
const GLfloat FOGSTART    = { 1.5 };
const GLfloat FOGEND      = { 4. };



// Project-Specific global variables
float	Time;
float	TwiceTime;
bool	showControl;
bool	Frozen;
GLuint	CurveList;

// non-constant global variables:

int		ActiveButton;			// current button that is down
int		DebugOn;				// != 0 means to print debugging info
int		DepthCueOn;				// != 0 means to use intensity depth cueing
int		DepthBufferOn;			// != 0 means to use the z-buffer
int		DepthFightingOn;		// != 0 means to use the z-buffer
int		MainWindow;				// window id for main graphics window
float	Scale;					// scaling factor
int		WhichColor;				// index into Colors[ ]
int		WhichProjection;		// ORTHO or PERSP
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot;				// rotation angles in degrees


// function prototypes:

void	Animate( );
void	Display( );
void	DoColorMenu( int );
void	DoDepthBufferMenu( int );
void	DoDepthFightingMenu( int );
void	DoDepthMenu( int );
void	DoDebugMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );

void	drawBezierCurve(Curve curve);
void	drawControl(Curve curve);
void	initCurves();
void	resetCurves();
void	RotateX(Point *p, float deg, float xc, float yc, float zc);
void	RotateY(Point *p, float deg, float xc, float yc, float zc);
void	updatePoints();
// main program:

int
main( int argc, char *argv[ ] )
{
	// 

	glutInit( &argc, argv );


	// setup all the graphics stuff:

	InitGraphics( );


	// create the display structures that will not change:

	InitLists( );


	// init all the global variables used by Display( ):
	// this will also post a redisplay

	Reset( );


	// setup all the user interface stuff:

	InitMenus( );


	// draw the scene once and wait for some interaction:
	// (this will never return)

	glutSetWindow( MainWindow );
	glutMainLoop( );


	// this is here to make the compiler happy:

	return 0;
}

void
Animate( )
{
	int ms = glutGet(GLUT_ELAPSED_TIME);
	ms %= MS_PER_CYCLE;
	Time = (float)ms / (float)MS_PER_CYCLE;

	ms = glutGet(GLUT_ELAPSED_TIME);
	ms %= MS_PER_CYCLE * 2;
	TwiceTime = (float)ms / (float)(MS_PER_CYCLE * 2);

	// force a call to Display( ) next time it is convenient:

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// draw the complete scene:

void
Display()
{
	if (DebugOn != 0)
	{
		fprintf(stderr, "Display\n");
	}


	// set which window we want to do the graphics into:

	glutSetWindow(MainWindow);


	// erase the background:

	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (DepthBufferOn != 0)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);


	// specify shading to be flat:

	glShadeModel(GL_FLAT);


	// set the viewport to a square centered in the window:

	GLsizei vx = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei vy = glutGet(GLUT_WINDOW_HEIGHT);
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = (vx - v) / 2;
	GLint yb = (vy - v) / 2;
	glViewport(xl, yb, v, v);


	// set the viewing volume:
	// remember that the Z clipping  values are actually
	// given as DISTANCES IN FRONT OF THE EYE
	// USE gluOrtho2D( ) IF YOU ARE DOING 2D !

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (WhichProjection == ORTHO)
		glOrtho(-3., 3., -3., 3., 0.1, 1000.);
	else
		gluPerspective(90., 1., 0.1, 1000.);


	// place the objects into the scene:

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set the eye position, look-at position, and up-vector:

	gluLookAt(0., 5., 10., 0., 0., 0., 0., 1., 0.);

	// rotate
	glRotatef((GLfloat)Yrot, 0., 1., 0.);
	glRotatef((GLfloat)Xrot, 1., 0., 0.);


	// uniformly scale the scene:
	if (Scale < MINSCALE) Scale = MINSCALE;
	glScalef((GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale);

	// set the fog parameters:

	if (DepthCueOn != 0)
	{
		glFogi(GL_FOG_MODE, FOGMODE);
		glFogfv(GL_FOG_COLOR, FOGCOLOR);
		glFogf(GL_FOG_DENSITY, FOGDENSITY);
		glFogf(GL_FOG_START, FOGSTART);
		glFogf(GL_FOG_END, FOGEND);
		glEnable(GL_FOG);
	}
	else
	{
		glDisable(GL_FOG);
	}

	// since we are using glScalef( ), be sure normals get unitized:

	glEnable(GL_NORMALIZE);

	//Modify points based on time
	updatePoints();

	//draw control points and lines
	if (showControl) {
		glPushMatrix();
		for (int i = 0; i < NUMCURVES; i++) {
			drawControl(Curves[i]);
		}
		glPopMatrix();
	}

	//draw the curves
	glPushMatrix();
	for (int i = 0; i < NUMCURVES; i++) {
		drawBezierCurve(Curves[i]);
	}
	glPopMatrix();

	// swap the double-buffered framebuffers:

	glutSwapBuffers();


	// be sure the graphics buffer has been sent:
	// note: be sure to use glFlush( ) here, not glFinish( ) !

	glFlush();
}

void
DoColorMenu( int id )
{
	WhichColor = id - RED;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDebugMenu( int id )
{
	DebugOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthBufferMenu( int id )
{
	DepthBufferOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthFightingMenu( int id )
{
	DepthFightingOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthMenu( int id )
{
	DepthCueOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// main menu callback:

void
DoMainMenu( int id )
{
	switch( id )
	{
		case RESET:
			Reset( );
			break;

		case QUIT:
			// gracefully close out the graphics:
			// gracefully close the graphics window:
			// gracefully exit the program:
			glutSetWindow( MainWindow );
			glFinish( );
			glutDestroyWindow( MainWindow );
			exit( 0 );
			break;

		default:
			fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
	}

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
	WhichProjection = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
	glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );

	char c;			// one character to print
	for( ; ( c = *s ) != '\0'; s++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
	}
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
	glPushMatrix( );
		glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
		float sf = ht / ( 119.05f + 33.33f );
		glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
		char c;			// one character to print
		for( ; ( c = *s ) != '\0'; s++ )
		{
			glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
		}
	glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
	// get # of milliseconds since the start of the program:

	int ms = glutGet( GLUT_ELAPSED_TIME );

	// convert it to seconds:

	return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
	glutSetWindow( MainWindow );

	int numColors = sizeof( Colors ) / ( 3*sizeof(int) );
	int colormenu = glutCreateMenu( DoColorMenu );
	for( int i = 0; i < numColors; i++ )
	{
		glutAddMenuEntry( ColorNames[i], i );
	}

	int depthcuemenu = glutCreateMenu( DoDepthMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthbuffermenu = glutCreateMenu( DoDepthBufferMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthfightingmenu = glutCreateMenu( DoDepthFightingMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int debugmenu = glutCreateMenu( DoDebugMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int projmenu = glutCreateMenu( DoProjectMenu );
	glutAddMenuEntry( "Orthographic",  ORTHO );
	glutAddMenuEntry( "Perspective",   PERSP );

	int mainmenu = glutCreateMenu( DoMainMenu );
	glutAddSubMenu(   "Colors",        colormenu);
	glutAddSubMenu(   "Depth Buffer",  depthbuffermenu);
	glutAddSubMenu(   "Depth Fighting",depthfightingmenu);
	glutAddSubMenu(   "Depth Cue",     depthcuemenu);
	glutAddSubMenu(   "Projection",    projmenu );
	glutAddMenuEntry( "Reset",         RESET );
	glutAddSubMenu(   "Debug",         debugmenu);
	glutAddMenuEntry( "Quit",          QUIT );

// attach the pop-up menu to the right mouse button:

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}

void
InitGraphics( )
{
	// request the display modes:
	// ask for red-green-blue-alpha color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

	// set the initial window configuration:

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );

	// open the window and set its title:

	MainWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );

	// set the framebuffer clear values:

	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );

	// setup the callback functions:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow( MainWindow );
	glutDisplayFunc( Display );
	glutReshapeFunc( Resize );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( Visibility );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStateFunc( NULL );
	glutTimerFunc( -1, NULL, 0 );
	glutIdleFunc( Animate );

	// init glew (a window must be open to do this):

#ifdef WIN32
	GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	// initialize the curves and points
	initCurves();

}

void
InitLists( )
{
	
}


// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Keyboard: '%c' (0x%0x)\n", c, c );

	switch( c )
	{
		case 'o':
		case 'O':
			WhichProjection = ORTHO;
			break;

		case 'p':
		case 'P':
			WhichProjection = PERSP;
			break;

		case 'q':
		case 'Q':
		case ESCAPE:
			DoMainMenu( QUIT );	// will not return here
			break;				// happy compiler

		case 'f':
		case 'F':
			Frozen = !Frozen;
			if (Frozen) {
				glutIdleFunc(NULL);
			} else {
				glutIdleFunc(Animate);
			}
			break;

		case 'c':
		case 'C':
			showControl = !showControl;
			break;

		default:
			fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
	}

	// force a call to Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
	int b = 0;			// LEFT, MIDDLE, or RIGHT

	if( DebugOn != 0 )
		fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );

	
	// get the proper button bit mask:

	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			b = LEFT;		break;

		case GLUT_MIDDLE_BUTTON:
			b = MIDDLE;		break;

		case GLUT_RIGHT_BUTTON:
			b = RIGHT;		break;

		default:
			b = 0;
			fprintf( stderr, "Unknown mouse button: %d\n", button );
	}


	// button down sets the bit, up clears the bit:

	if( state == GLUT_DOWN )
	{
		Xmouse = x;
		Ymouse = y;
		ActiveButton |= b;		// set the proper bit
	}
	else
	{
		ActiveButton &= ~b;		// clear the proper bit
	}
}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
	if( DebugOn != 0 )
		fprintf( stderr, "MouseMotion: %d, %d\n", x, y );


	int dx = x - Xmouse;		// change in mouse coords
	int dy = y - Ymouse;

	if( ( ActiveButton & LEFT ) != 0 )
	{
		Xrot += ( ANGFACT*dy );
		Yrot += ( ANGFACT*dx );
	}


	if( ( ActiveButton & RIGHT ) != 0 )
	{
		Scale += SCLFACT * (float) ( dx - dy );

		// keep object from turning inside-out or disappearing:

		if( Scale < MINSCALE )
			Scale = MINSCALE;
	}

	Xmouse = x;			// new current position
	Ymouse = y;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}

void
Reset( )
{
	ActiveButton = 0;
	DebugOn = 0;
	DepthBufferOn = 1;
	DepthFightingOn = 0;
	DepthCueOn = 0;
	Scale  = 1.0;
	WhichColor = WHITE;
	WhichProjection = PERSP;
	Xrot = Yrot = 0.;
	Frozen = false;
	showControl = true;

	resetCurves();
}

// called when user resizes the window:

void
Resize( int width, int height )
{
	if( DebugOn != 0 )
		fprintf( stderr, "ReSize: %d, %d\n", width, height );

	// don't really need to do anything since window size is
	// checked each time in Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}

// handle a change to the window's visibility:

void
Visibility ( int state )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Visibility: %d\n", state );

	if( state == GLUT_VISIBLE )
	{
		glutSetWindow( MainWindow );
		glutPostRedisplay( );
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid
		// animating or redrawing it ...
	}
}

void drawBezierCurve(Curve curve) {	glLineWidth(curve.lw);
	//glColor3f(curve.r, curve.g, curve.b);
	glBegin(GL_LINE_STRIP);
	for (int it = 0; it < NUMVERTS; it++) {
		float t = (float)it / (float)NUMVERTS;
		float omt = 1.f - t;
		float x = omt * omt*omt*curve.ps[0].x + 3.f*t*omt*omt*curve.ps[1].x + 3.f*t*t*omt*curve.ps[2].x + t * t*t*curve.ps[3].x;
		float y = omt * omt*omt*curve.ps[0].y + 3.f*t*omt*omt*curve.ps[1].y + 3.f*t*t*omt*curve.ps[2].y + t * t*t*curve.ps[3].y;
		float z = omt * omt*omt*curve.ps[0].z + 3.f*t*omt*omt*curve.ps[1].z + 3.f*t*t*omt*curve.ps[2].z + t * t*t*curve.ps[3].z;
		glColor3f(x / 20 + .4, y / 10 + .4, z / 5 + .4);
		glVertex3f(x, y, z);
	}
	glEnd();
	glLineWidth(1.);}void drawControl(Curve curve) {	glLineWidth(1.f);	glPointSize(4.f);	glColor3f(Colors[WHITE][0], Colors[WHITE][1], Colors[WHITE][2]);	glBegin(GL_LINE_STRIP);	for (int i = 0; i < NUMPOINTS; i++) {		glVertex3f(curve.ps[i].x, curve.ps[i].y, curve.ps[i].z);	}	glEnd();	glBegin(GL_POINTS);	for (int j = 0; j < NUMPOINTS; j++) {		glVertex3f(curve.ps[j].x, curve.ps[j].y, curve.ps[j].z);	}	glEnd();}void initCurves() {	for (int i = 0; i < NUMCURVES; i++) {		Curves[i].r = Colors[i][0];		Curves[i].g = Colors[i][1];		Curves[i].b = Colors[i][2];	}	Curves[0].lw = 4.f;	Curves[0].ps[0].x0 = -5.f;	Curves[0].ps[0].y0 = -0.1f;	Curves[0].ps[0].z0 = 0.f;	Curves[0].ps[1].x0 = -8.f;	Curves[0].ps[1].y0 = -4.f;	Curves[0].ps[1].z0 = 0.f;	Curves[0].ps[2].x0 = -8.f;	Curves[0].ps[2].y0 = -0.5f;	Curves[0].ps[2].z0 = 0.f;	Curves[0].ps[3].x0 = -7.f;	Curves[0].ps[3].y0 = 0.f;	Curves[0].ps[3].z0 = 0.f;	Curves[1].lw = 4.f;	Curves[1].ps[0].x0 = -5.f;	Curves[1].ps[0].y0 = 0.1f;	Curves[1].ps[0].z0 = 0.f;	Curves[1].ps[1].x0 = -8.f;	Curves[1].ps[1].y0 = 4.f;	Curves[1].ps[1].z0 = 0.f;	Curves[1].ps[2].x0 = -8.f;	Curves[1].ps[2].y0 = 0.5f;	Curves[1].ps[2].z0 = 0.f;	Curves[1].ps[3].x0 = -7.f;	Curves[1].ps[3].y0 = 0.f;	Curves[1].ps[3].z0 = 0.f;	Curves[2].lw = 2.f;	Curves[2].ps[0].x0 = -5.f;	Curves[2].ps[0].y0 = 0.1f;	Curves[2].ps[0].z0 = 0.f;	Curves[2].ps[1].x0 = 10.f;	Curves[2].ps[1].y0 = 6.f;	Curves[2].ps[1].z0 = 0.f;	Curves[2].ps[2].x0 = 12.f;	Curves[2].ps[2].y0 = -8.f;	Curves[2].ps[2].z0 = 0.f;	Curves[2].ps[3].x0 = -5.45f;	Curves[2].ps[3].y0 = 0.1f;	Curves[2].ps[3].z0 = 0.f;	Curves[3].lw = 4.f;	Curves[3].ps[0].x0 = 4.f;	Curves[3].ps[0].y0 = -2.f;	Curves[3].ps[0].z0 = 0.f;	Curves[3].ps[1].x0 = 3.f;	Curves[3].ps[1].y0 = -3.f;	Curves[3].ps[1].z0 = 2.f;	Curves[3].ps[2].x0 = 2.f;	Curves[3].ps[2].y0 = -3.f;	Curves[3].ps[2].z0 = 1.5f;	Curves[3].ps[3].x0 = 3.f;	Curves[3].ps[3].y0 = -2.f;	Curves[3].ps[3].z0 = 0.f;	Curves[4].lw = 4.f;	Curves[4].ps[0].x0 = 4.f;	Curves[4].ps[0].y0 = -2.f;	Curves[4].ps[0].z0 = 0.f;	Curves[4].ps[1].x0 = 3.f;	Curves[4].ps[1].y0 = -3.f;	Curves[4].ps[1].z0 = -2.f;	Curves[4].ps[2].x0 = 2.f;	Curves[4].ps[2].y0 = -3.f;	Curves[4].ps[2].z0 = -1.5f;	Curves[4].ps[3].x0 = 3.f;	Curves[4].ps[3].y0 = -2.f;	Curves[4].ps[3].z0 = 0.f;	resetCurves();}void resetCurves() {		for (int i = 0; i < NUMCURVES; i++) {		for (int j = 0; j < NUMPOINTS; j++) {			Curves[i].ps[j].x = Curves[i].ps[j].x0;			Curves[i].ps[j].y = Curves[i].ps[j].y0;			Curves[i].ps[j].z = Curves[i].ps[j].z0;		}	}}void
RotateX(Point *p, float deg, float xc, float yc, float zc) {
	float rad = deg * (M_PI / 180.f);         // radians
	float x = p->x - xc;
	float y = p->y - yc;
	float z = p->z - zc;

	float xp = x;
	float yp = y * cos(rad) - z * sin(rad);
	float zp = y * sin(rad) + z * cos(rad);

	p->x = xp + xc;
	p->y = yp + yc;
	p->z = zp + zc;
}

void
RotateY(Point *p, float deg, float xc, float yc, float zc)
{
	float rad = deg * (M_PI / 180.f);         // radians
	float x = p->x0 - xc;
	float y = p->y0 - yc;
	float z = p->z0 - zc;

	float xp = x * cos(rad) + z * sin(rad);
	float yp = y;
	float zp = -x * sin(rad) + z * cos(rad);

	p->x = xp + xc;
	p->y = yp + yc;
	p->z = zp + zc;
}

void updatePoints() {

	RotateY(&Curves[0].ps[1], 35 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[0].ps[2], 30 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[0].ps[3], 25 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);

	RotateY(&Curves[1].ps[1], 35 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[1].ps[2], 30 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[1].ps[3], 25 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);

	RotateY(&Curves[2].ps[1], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[2].ps[2], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);

	RotateY(&Curves[3].ps[0], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[3].ps[1], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[3].ps[2], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[3].ps[3], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);

	RotateY(&Curves[4].ps[0], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[4].ps[1], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[4].ps[2], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	RotateY(&Curves[4].ps[3], 10 * sin(2 * M_PI * TwiceTime), -5.f, 0.f, 0.f);
	
	RotateX(&Curves[3].ps[1], -20 * sin(2 * M_PI * Time), Curves[3].ps[0].x, Curves[3].ps[0].y, Curves[3].ps[0].z);
	RotateX(&Curves[3].ps[2], -20 * sin(2 * M_PI * Time), Curves[3].ps[3].x, Curves[3].ps[3].y, Curves[3].ps[3].z);

	RotateX(&Curves[4].ps[1], 20 * sin(2 * M_PI * Time), Curves[4].ps[0].x, Curves[4].ps[0].y, Curves[4].ps[0].z);
	RotateX(&Curves[4].ps[2], 20 * sin(2 * M_PI * Time), Curves[4].ps[3].x, Curves[4].ps[3].y, Curves[4].ps[3].z);

	
}