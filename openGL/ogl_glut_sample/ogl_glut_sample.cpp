//-----------------------------------------------------------------------------
//           Name: ogl_glut_sample.cpp
//         Author: Kevin Harris
//  Last Modified: 08/06/04
//    Description:  This sample is a basic demonstration of how to use GLUT or 
//                  it's replacement, freeglut to create cross-platform, 
//                  windowed OpenGL samples.
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
int    g_window    = 0;
GLuint g_textureID = 0;

float g_fSpinX           = 0.0f;
float g_fSpinY           = 0.0f;
int   g_nLastMousePositX = 0;
int   g_nLastMousePositY = 0;

struct Vertex
{
    float tu, tv;
    float x, y, z;
};

Vertex g_quadVertices[] =
{
    { 0.0f,0.0f, -1.0f,-1.0f, 0.0f },
    { 1.0f,0.0f,  1.0f,-1.0f, 0.0f },
    { 1.0f,1.0f,  1.0f, 1.0f, 0.0f },
    { 0.0f,1.0f, -1.0f, 1.0f, 0.0f }
};

struct BMPImage 
{
    int   width;
    int   height;
    char *data;
};

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int main(int argc, char **argv);
void init(void);
void getBitmapImageData(char *pFileName, BMPImage *pImage);
void loadTexture(void);
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void idleFunc(void);
void reshapeFunc(int w, int h);
void displayFunc(void);

//-----------------------------------------------------------------------------
// Name: main()
// Desc: 
//-----------------------------------------------------------------------------
int main( int argc, char **argv )
{
	glutInit( &argc, argv );

    init();

    glutSwapBuffers();
    glutMainLoop();

    return 0;
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------
void init( void )
{
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowSize( 640, 480 );
	g_window = glutCreateWindow( "GLUT/freeglut sample" );

	glutDisplayFunc( displayFunc );
	glutKeyboardFunc( keyboardFunc );
	glutMouseFunc( mouseFunc );
	glutMotionFunc( motionFunc );
	glutReshapeFunc( reshapeFunc );
	glutIdleFunc( idleFunc );

	loadTexture();

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_TEXTURE_2D );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
}

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found\n",pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);
	
    if( nNumPlanes != 1 )
		printf( "ERROR: getBitmapImageData - Plane count from %s is not 1: %u\n", pFileName, nNumPlanes );

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n", pFileName );
	
    if( nNumBPP != 24 )
		printf( "ERROR: getBitmapImageData - BPP from %s is not 24: %u\n", pFileName, nNumBPP );

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

	// Calculate the image's total size in bytes. Note how we multiply the 
	// result of (width * height) by 3. This is becuase a 24 bit color BMP 
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );
	
    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n", pFileName);

    //
	// Finally, rearrange BGR to RGB
	//
	
	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{ 
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}

//-----------------------------------------------------------------------------
// Name: loadTexture()
// Desc: 
//-----------------------------------------------------------------------------
void loadTexture( void )	
{
	BMPImage textureImage;
	
    getBitmapImageData( "test.bmp", &textureImage );

	glGenTextures( 1, &g_textureID );
	glBindTexture( GL_TEXTURE_2D, g_textureID );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage.width, textureImage.height, 
	               0, GL_RGB, GL_UNSIGNED_BYTE, textureImage.data );
}

//-----------------------------------------------------------------------------
// Name: keyboardFunc()
// Desc: Called when a keyboard key is pressed
//-----------------------------------------------------------------------------
void keyboardFunc( unsigned char key, int x, int y ) 
{
    switch( key )
    {
        case 27:
			glutDestroyWindow( g_window );
        	exit(0);
			break;
    }
}

//-----------------------------------------------------------------------------
// Name: mouseFunc()
// Desc: Called when a mouse button is pressed
//-----------------------------------------------------------------------------
void mouseFunc( int button, int state, int x, int y )
{
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		g_nLastMousePositX = x;
        g_nLastMousePositY = y;
	}
}

//-----------------------------------------------------------------------------
// Name: motionFunc()
// Desc: Called when the mouse moves
//-----------------------------------------------------------------------------
void motionFunc( int x, int y )
{
	g_fSpinX -= (x - g_nLastMousePositX);
	g_fSpinY -= (y - g_nLastMousePositY);

	g_nLastMousePositX = x;
    g_nLastMousePositY = y;
}

//-----------------------------------------------------------------------------
// Name: idleFunc()
// Desc: Called during idle time
//-----------------------------------------------------------------------------
void idleFunc( void )
{
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
// Name: reshapeFunc()
// Desc: Called when the window size has been changed by the user
//-----------------------------------------------------------------------------
void reshapeFunc( int w, int h )
{
	glViewport( 0, 0, w, h );
}

//-----------------------------------------------------------------------------
// Name: displayFunc()
// Desc: Called when GLUT is ready to render
//-----------------------------------------------------------------------------
void displayFunc( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, -5.0f );
    glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
    glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );

    glBindTexture( GL_TEXTURE_2D, g_textureID );
    glInterleavedArrays( GL_T2F_V3F, 0, g_quadVertices );
    glDrawArrays( GL_QUADS, 0, 4 );

    glutSwapBuffers();
}




