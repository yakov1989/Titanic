// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"
#include <Windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library
#include "Mmsystem.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
{
	m_pclWnd = pclWnd;
	m_hDC = ::GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect;
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);
	moveX = moveY = moveZ = moveI=0;
	rotateX = rotateY = rotateZ = sunX = 0;
	generateTextureFromImageFile();

	

}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -
CGlView::~CGlView()
{
	// make the rendering context not current
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	// delete the Context
	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -

void CGlView::vDrawOcean() {

	glTranslatef(0.0f, 0.0f, -15.0f);
	//Enable color and light effects
	/*glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);*/

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[OCEAN_IMAGE]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-40, 7.5);
	glTexCoord2f(1, 0); glVertex2f(20, 7.5);
	glTexCoord2f(1, 1); glVertex2f(20, -18);
	glTexCoord2f(0, 1); glVertex2f(-40, -18);
	glEnd();
	glPopMatrix();

}
void CGlView::vDrawSun()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();//(0,0,0) and z towards us								
	glTranslatef(12.0f, 5.0f, -15.0f);


	//draw sun
	GLUquadricObj* obj;
	obj = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[SUN_IMAGE]);
	glPushMatrix();
	glRotatef(sunX, 0, 1, 0);
	gluSphere(obj, 1.1, 20, 20);//Draw sun
	glPopMatrix();
	gluDeleteQuadric(obj);



}
//DRAW ICE

void CGlView::vDrawIce() {


	glTranslated(-12, -9, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	]);
	glBegin(GL_POLYGON);
	glVertex2f(-26.0f,9.0f );
	glVertex2f(-20.0f, 6.0f);
	glVertex2f(-22.0f, -4.0f);
	glVertex2f(-28.0f, -4.0f);
	glVertex2f(-28.0f, 3.0f);
	glEnd();
	glPopMatrix();
}

void CGlView::vDrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 // Clear Screen And Depth Buffer
	vDrawSun();
	vDrawOcean();
	vDrawIce();
	glLoadIdentity();//(0,0,0) and z towards us	

	glTranslatef(0.0f, 0.0f, -20.0f);
	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);


	//axes
	//glBegin(GL_LINES);	
	//	//x  RED
	//	glColor3f(1.0f,1.0f,0.0f);						
	//	glVertex3f( -3.0f, 0.0f, 0.0f);	
	//	glVertex3f( 3.0f, 0.0f, 0.0f);	
	//	//y  GREEN 
	//	glColor3f(0.0f,1.0f,0.0f);						
	//	glVertex3f( 0.0f, -3.0f, 0.0f);	
	//	glVertex3f( 0.0f, 3.0f, 0.0f);	
	//	//z  BLUE
	//	glColor3f(0.0f,0.0f,1.0f);						
	//	glVertex3f( 0.0f, 0.0f, -3.0f);	
	//	glVertex3f( 0.0f, 0.0f, 3.0f);	
	//glEnd();
	//glPopMatrix();





	//Enable color and light effects
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	glTranslatef(12.0f, 0.0f, 0.0f);

//lowest deck


	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-4, -1.5);
	glVertex2f(-1.5, -4);
	glVertex2f(8, -4);
	glVertex2f(10, -1.5);
	glEnd();
	glFlush();

////middle deck


glColor3f(0.5f, 0.5f, 0.5f);
glBegin(GL_POLYGON);
glVertex2f(-1.5, -1.5);
glVertex2f(-1.5, 1.5);
glVertex2f(8.5, 1.5);
glVertex2f(8.5, -1.5);
glEnd();
glFlush();
//
////top deck
//



glColor3f(0.5f, 0.5f, 0.5f);
glBegin(GL_POLYGON);
glVertex2f(-0.5,-0.5);
glVertex2f(-0.5, 2);
glVertex2f(7.5, 2);
glVertex2f(7.5, -0.5);
glEnd();
glFlush();

//
////door
//


glColor3f(1.0 ,0.5, 0.0);
glBegin(GL_POLYGON);
glVertex2f(-1, -1.5);
glVertex2f(-1,0.5);
glVertex2f(0.0 ,0.5);
glVertex2f(0.0, -1.5);
glEnd();
//
////left window
//


glColor3f(1.0f, 1.0f ,1.0f);
glBegin(GL_POLYGON);
glVertex2f(2, 0.5);
glVertex2f(2, 1);
glVertex2f(4, 1);
glVertex2f(4, 0.5);
glEnd();

////right window

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_POLYGON);
glVertex2f(5, 0.5);
glVertex2f(5, 1);
glVertex2f(7, 1);
glVertex2f(7, 0.5);
glEnd();

//left chimney 

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(1, 2);
glVertex2f(1, 3.9);
glVertex2f(2, 3.9);
glVertex2f(2, 2);
glEnd();


////top left chimney

glColor3f(0.9, 0.5, 0.2);
glBegin(GL_POLYGON);
glVertex2f(1.0f, 3.9f);
glVertex2f(1.0f, 4.2f);
glVertex2f(2.0f, 4.2f);
glVertex2f(2.0f, 3.9f);
glEnd();

////middle  chimney

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(3, 2);
glVertex2f(3, 3.9);
glVertex2f(4, 3.9);
glVertex2f(4, 2);
glEnd();

////middle  top chimney

glColor3f(0.9, 0.5, 0.2);
glBegin(GL_POLYGON);
glVertex2f(3, 3.9);
glVertex2f(3, 4.2);
glVertex2f(4, 4.2);
glVertex2f(4, 3.9);
glEnd();

////right chimney

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(5.0f, 2.0f);
glVertex2f(5.0f, 3.9f);
glVertex2f(6.0f, 3.9f);
glVertex2f(6.0f, 2.0f);
glEnd();

////right top chimney

glColor3f(0.9, 0.5, 0.2);
glBegin(GL_POLYGON);
glVertex2f(5, 3.9);
glVertex2f(5, 4.2);
glVertex2f(6, 4.2);
glVertex2f(6, 3.9);
glEnd();

//fences 

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(-3.5, -1.5);
glVertex2f(-3.5, -0.5);
glVertex2f(-2.5, -0.5);
glVertex2f(-2.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(-2.5, -1.5);
glVertex2f(-2.5, -0.5);
glVertex2f(-1.5, -0.5);
glVertex2f(-1.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(-1.5, -1.5);
glVertex2f(-1.5, -0.5);
glVertex2f(-0.5, -0.5);
glVertex2f(-0.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(-0.5, -1.5);
glVertex2f(-0.5, -0.5);
glVertex2f(0.5, -0.5);
glVertex2f(0.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(0.5, -1.5);
glVertex2f(0.5, -0.5);
glVertex2f(1.5, -0.5);
glVertex2f(1.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(1.5, -1.5);
glVertex2f(1.5, -0.5);
glVertex2f(2.5, -0.5);
glVertex2f(2.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(2.5, -1.5);
glVertex2f(2.5, -0.5);
glVertex2f(3.5, -0.5);
glVertex2f(3.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(3.5, -1.5);
glVertex2f(3.5, -0.5);
glVertex2f(4.5, -0.5);
glVertex2f(4.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(4.5, -1.5);
glVertex2f(4.5, -0.5);
glVertex2f(5.5, -0.5);
glVertex2f(5.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(5.5, -1.5);
glVertex2f(5.5, -0.5);
glVertex2f(6.5, -0.5);
glVertex2f(6.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(6.5, -1.5);
glVertex2f(6.5, -0.5);
glVertex2f(7.5, -0.5);
glVertex2f(7.5, -1.5);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(7.5f, -1.5f);
glVertex2f(7.5f, -0.5f);
glVertex2f(8.5f, -0.5f);
glVertex2f(8.5f, -1.5f);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(8.5f, -1.5f);
glVertex2f(8.5f, -0.5f);
glVertex2f(9.5f, -0.5f);
glVertex2f(9.5f, -1.5f);
glEnd();


//smoke 1
	glBegin(GL_QUADS);
	glColor3d(0.329412, 0.329412, 0.329412);
	glVertex2f(4.2f, 5.2f);
	glVertex2f(5.2f, 5.2f);
	glVertex2f(5.2f, 5.7f);
	glVertex2f(4.2f, 5.7f);
	glEnd();
	glFlush();
	//smoke2
	glBegin(GL_QUADS);
	glColor3d(0.329412, 0.329412, 0.329412);
	glVertex2f(2.0f, 4.7f);
	glVertex2f(3.0f, 4.7f);
	glVertex2f(3.0f, 5.2f);
	glVertex2f(2.0f, 5.2f);
	glEnd();
	glFlush();


	//Disable color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// swap the buffer
	SwapBuffers(m_hDC);
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags =

		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

	int iGLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	ASSERT(&iGLPixelIndex);

	if (SetPixelFormat(hDC, iGLPixelIndex, &pixelDesc))
		return false;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glViewport(0, 0, iWidth, iHeigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//PlaySound(TEXT("music\\titanic.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeigth, 0.45f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);//generates ID for each texture.

	const char* imageFileName[SIZE] = { "Images\\ship11.bmp","Images\\iceberg.bmp","Images\\sun.bmp","Images\\ocean.bmp" };
	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoad(imageFileName[i]);//loads the width, height, colors from the image file (*.bmp) into opengl structure (AUX_RGBImageRec).

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//working on idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if the target is smaller than the source then minimize it using LINEAR algorithm.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if the target is bigger than the source then maximize it using LINEAR algorithm.
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save texture in memory.
			free(texture);
			texture = NULL;
		}
	}
}
void CGlView::setMoveX(float moveX)
{
	this->moveX = moveX;
}

void CGlView::setMoveY(float moveY)
{
	this->moveY = moveY;
}

void CGlView::setMoveZ(float moveZ)
{
	this->moveZ = moveZ;
}

float CGlView::getMoveX()
{
	return this->moveX;
}

float CGlView::getMoveY()
{
	return this->moveY;
}

float CGlView::getMoveZ()
{
	return this->moveZ;
}

void CGlView::RotateX(int invert) {
	this->rotateX = invert;

}
void CGlView::RotateY(int invert) {
	this->rotateY = invert;
}
void CGlView::RotateZ(int invert) {
	this->rotateZ = invert;
}


int CGlView::getRotX() {
	return this->rotateX;
}
int CGlView::getRotY() {
	return this->rotateY;
}
int CGlView::getRotZ() {
	return this->rotateZ;
}

void CGlView::SunRot(int invert) {
	this->sunX = invert;
}

int CGlView::getSunRot() {
	return this->sunX;
}


