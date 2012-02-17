

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glut.h>
#include <GL/glu.h>
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
void DisplaySnoopy(void);

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

    glutDisplayFunc(DisplaySnoopy);
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
void DisplaySnoopy (void)
{
    char line_fill;
    GLfloat xj, yj;
    int j, no_of_pts;
    fstream inStream;
    inStream.open("snoopy3.txt", ios::in);
    if(!inStream)
    {
        cout << "file failed to open\n";
        return;
    }
    glClear (GL_COLOR_BUFFER_BIT);
    glScalef(5.0, 5.0, 1.0);
    do
    {
        inStream >> no_of_pts >> line_fill;
        if(line_fill == 'l')
            glBegin(GL_LINE_STRIP);
        else
            glBegin(GL_POLYGON);
        for(j = 1; j<=no_of_pts; j++)
        {
            inStream >> xj >> yj;
            glVertex2f(xj, yj);
        }
        glEnd();
    } while( (no_of_pts = inStream.get()) !=EOF );
    glFlush();
}
