// GlView.h: interface for the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_)
#define AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_
#include <gl\GLAUX.H>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SIZE 4
#define TITANIC_IMAGE 0
#define ICE_IMAGE 1
#define SUN_IMAGE 2
#define OCEAN_IMAGE 3



class CGlView  
{
public:
	CGlView(CWnd *pclWnd);
	~CGlView();
	

	protected:
	private:
		void vInitGl(int iWidth, int iHeigth);
		BOOL bSetWindowPixelFormat(HDC hDC);
		BOOL bCreateViewGLContext(HDC hDC);

	// members //////////////////////////////////////////////////////////
	public:
	protected:
	private:			
		HGLRC	m_hGLContext;	// required GLContext
		CWnd *m_pclWnd;			// window inwhich opengl will be drawn
		HDC		m_hDC;			// handle to m_pclWnds device context
		float moveX, moveY, moveZ,moveI;
		int rotateX, rotateY, rotateZ;
		unsigned int idTexture[SIZE];
		AUX_RGBImageRec *  texture;
		int sunX;

public:
	void vDrawGLScene();
	void vDrawSun();
	void vDrawOcean();
	void vDrawIce();
	void generateTextureFromImageFile();

	void setMoveX(float moveX);
	void setMoveY(float moveY);
	void setMoveZ(float moveZ);
	void setMoveIceY(float moveI);

	float getMoveX();
	float getMoveY();
	float getMoveZ();
	float getMoveIce();

	void RotateX(int invert);
	void RotateY(int invert);
	void RotateZ(int invert);

	int getRotX();
	int getRotY();
	int getRotZ();
	void SunRot(int invert);
	int getSunRot();



};

#endif

