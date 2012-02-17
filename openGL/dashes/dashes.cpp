#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <fstream>


using namespace std;
//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------

GLsizei wh = 250;
GLsizei ww = 250;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int main(int argc, char **argv);
void MyInit(void);
void DisplayLines(void);

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

    glutDisplayFunc(DisplayLines);
    glutMainLoop();
    
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc:
//-----------------------------------------------------------------------------
void MyInit( void )
{
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    //glLineWidth(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
}

//-----------------------------------------------------------------------------
// Name: DisplayLines()
// Desc:
//-----------------------------------------------------------------------------
void DisplayLines (void)
{
    GLint xj, yj, j;
    glClear (GL_COLOR_BUFFER_BIT);
    //ofstream inStream;
    ifstream inStream("R.txt", ios::in);// ("R.txt", ios::out );
    //inStream.open("R.txt", ios::in);
    if(!inStream)
    {
        cout << "File would not open\n";
        return;
    }

    glBegin(GL_LINE_STRIP);
    for (j=1; j<=7; j++)
    {
        inStream >> xj >> yj;
        cout << xj << " " << yj << "\n";
        glVertex2i(xj, yj);
    }
    glEnd();
    glFlush();
}
