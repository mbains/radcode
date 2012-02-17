#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <fstream>
#include <time.h>

using namespace std;
//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------

static GLfloat spin = 0.0;
GLsizei wh = 250;
GLsizei ww = 250;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int main(int argc, char **argv);
void MyInit(void);
void Display(void);
void reshape(int w, int h);
void spinDisplay(void);
void mouse(int button, int state, int x, int y);

//-----------------------------------------------------------------------------
// Name: main()
// Desc:
//-----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    MyInit();
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc:
//-----------------------------------------------------------------------------
void MyInit( void )
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

//-----------------------------------------------------------------------------
// Name: Display()
// Desc:
//-----------------------------------------------------------------------------
void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);
   glRectf(-25.0, -25.0, 25.0, 25.0);
   glPopMatrix();
   glutSwapBuffers();
}

//-----------------------------------------------------------------------------
// Name: spinDisplay()
// Desc:
//-----------------------------------------------------------------------------
void spinDisplay(void)
{
   spin = spin + 0.5;
   if(spin > 360.0)
      spin = spin - 360.0;
   sleep(1);
   glutPostRedisplay();
}
//-----------------------------------------------------------------------------
// Name: reshape()
// Desc:
//-----------------------------------------------------------------------------
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
//-----------------------------------------------------------------------------
// Name: mouse()
// Desc:
//-----------------------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
   switch(button)
   {
      case GLUT_LEFT_BUTTON:
         if(state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_RIGHT_BUTTON:
         if(state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;

   }
}

