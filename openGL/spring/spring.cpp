

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <fstream>
#include <math.h>
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
void drawSpring(void);
void reShape(int w, int h);
void Spring(void);
void mouse(int button, int state, int x, int y);
void spinDisplay(void);
//-----------------------------------------------------------------------------
// Name: main()
// Desc:
//-----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(150, 90);
    glutCreateWindow("Display R");
    MyInit();
    glutDisplayFunc(drawSpring);
    glutReshapeFunc(reShape);
    glutMouseFunc(mouse);
    glutMainLoop();

}

//-----------------------------------------------------------------------------
// Name: init()
// Desc:
//-----------------------------------------------------------------------------
void MyInit(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glColor3f(1.0f, 0.0f, 0.0f);
   glLineWidth(1.0);
}
//void MyInit( void )
//{
//    glClearColor(1.0, 1.0, 0.0, 0.0);
//    glColor3f(0.0f, 0.0f, 1.0f);
//    //glLineWidth(5.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
//}
//-----------------------------------------------------------------------------
// Name: drawSpring()
// Desc:
//-----------------------------------------------------------------------------
void drawSpring(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   Spring();
}
//-----------------------------------------------------------------------------
// Name: reShape()
// Desc:
//-----------------------------------------------------------------------------
void reShape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-11.0, 11.0, -11.0, 11.0, 11.0, -11.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(40.0, 0.0, 1.0, 1.0);
}

void Spring(void)
{
    GLfloat degtorads, theta, z;
    degtorads = M_PI/180.0;
    z = 0.0;
    glRotatef(spin, 0.2f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for(theta = 0; theta<=1500.0; theta += 1.0)
    {
        glVertex3f(3.0* cos(theta*degtorads), 3.0 * sin(theta*degtorads), z);
        z = z + 0.005;
    }
    glEnd();
    glFlush();
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
         {
            glutIdleFunc(spinDisplay);
            printf("Pushed must down\n");
         }
         break;
      case GLUT_RIGHT_BUTTON:
         if(state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;

   }
}

//-----------------------------------------------------------------------------
// Name: spinDisplay()
// Desc:
//-----------------------------------------------------------------------------
void spinDisplay(void)
{
  struct timespec time;
  struct timespec rem;
  time.tv_nsec = 100000000; //1 ms 
  time.tv_sec = 0;

  if (nanosleep(&time, &rem) == -1)
     printf("sleep failed]\n");
  spin = spin + 0.1;
   if(spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}
