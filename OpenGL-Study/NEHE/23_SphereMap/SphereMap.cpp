/*
 *		��Щ��������Jeff Molofee ��2000��д�ģ��ٴ��ұ����лFredric Echols����Ϊ��ʹ��Щ���뿴���������͸�Ч����ʹ������ʹ�á�
 *		����㷢����Щ�����������������������ҵ�վ�� http://nehe.gamedev.net/default.asp ��������֪����
 *********************************************************************************************************************************
 *		����Quadratic.cpp�ļ��޸�
 *		����ĵ�����DancingWind����ģ������ʲô������e-mail:zhouwei02@mails.tsinghua.edu.cn
 *		//old code			//�����˴�����//ɾ��
 *		/********************************************************************************************************************/	/*
 *		new code			//�µĴ���λ������/*************/ /*֮�䣬���ڲ���
 *		/********************************************************************************************************************/	/*
/***********************************�����Ĵ���***********************************************************************************/
/********************************************************************************************************************************/

/*********************�������ӵĿ��ļ�*******************************************************************************************/
#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	
/********************************************************************************************************************************/

#include <windows.h>		// Windows��ͷ�ļ�
#include <GL/glew.h>			// �������µ�gl.h,glu.h��
//#include <glut.h>			// ����OpenGLʵ�ÿ�
#include <stdio.h>			// ��׼����/������ͷ�ļ�
#include <GL/glaux.h>			// GLaux���ͷ�ļ�

GLfloat		xrot;										// X ��ת��
GLfloat		yrot;										// Y ��ת��
GLfloat		zrot;										// Z ��ת��
GLfloat		xspeed;										// X ��ת�ٶ�
GLfloat		yspeed;										// Y ��ת�ٶ�

BOOL		light;										// ��Դ�Ŀ�/��
BOOL		lp;											// L��������ô?
BOOL		fp;											// F��������ô?

GLfloat	z=-5.0f;										// ������Ļ�ľ���

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	// ���������
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		// ��������
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	// ��Դλ��
GLuint	filter;											// �˲�����
//GLuint	texture[3];										// 3�������Ĵ���ռ�

bool    sp;												// �ո���Ƿ���

int	part1;												// Բ�̵���ʼ�Ƕ�
int	part2;												// Բ�̵Ľ����Ƕ�
int	p1=0;												// ����1
int	p2=1;												// ����1
GLUquadricObj *quadratic;								// ���μ�����
GLuint  object=0;										// ���μ������ʾ��
/***********************************�����Ĵ���***********************************************************************************/
GLuint	texture[6];								// ����6������ 

//GLvoid glDrawCube()					// ����������
//{
//		glBegin(GL_QUADS);			
//		// ǰ��
//		glNormal3f( 0.0f, 0.0f, 1.0f);		
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
//		// ����
//		glNormal3f( 0.0f, 0.0f,-1.0f);		
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
//		// ����
//		glNormal3f( 0.0f, 1.0f, 0.0f);		
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
//		// ����
//		glNormal3f( 0.0f,-1.0f, 0.0f);		
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
//		// ����
//		glNormal3f( 1.0f, 0.0f, 0.0f);		
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
//		// ����
//		glNormal3f(-1.0f, 0.0f, 0.0f);		
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
//	glEnd();					
//}
GLvoid glDrawCube()
{
		glBegin(GL_QUADS);
		// ǰ��
		glNormal3f( 0.0f, 0.0f, 0.5f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// ����
		glNormal3f( 0.0f, 0.0f,-0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// ����
		glNormal3f( 0.0f, 0.5f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// ����
		glNormal3f( 0.0f,-0.5f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// ����
		glNormal3f( 0.5f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// ����
		glNormal3f(-0.5f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

/********************************************************************************************************************************/
HDC			hDC=NULL;		// ������ɫ���������
HGLRC		hRC=NULL;		// OpenGL��Ⱦ���������
HWND		hWnd=NULL;		// �������ǵĴ��ھ��
HINSTANCE	hInstance;		// ��������ʵ��

bool	keys[256];			// ������̰���������
bool	active=TRUE;		// ���ڵĻ��־��ȱʡΪTRUE
bool	fullscreen=TRUE;	// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// WndProc�Ķ���
AUX_RGBImageRec *LoadBMP(CHAR *Filename)				// ����λͼͼ��
{
	FILE *File=NULL;									// �ļ����
	if (!Filename)										// ȷ���ļ������ṩ
	{
		return NULL;									// ���û�ṩ������ NULL
	}
	File=fopen(Filename,"r");							// ���Դ��ļ�
	if (File)											// �ļ�����ô?
	{
		fclose(File);									// �رվ��
		return auxDIBImageLoadA(Filename);				// ����λͼ������ָ��
	}
	return NULL;										// �������ʧ�ܣ����� NULL
}

//int LoadGLTextures()									// ����λͼ(��������Ĵ���)��ת��������
//{
//	int Status=FALSE;									// ״ָ̬ʾ��
//	AUX_RGBImageRec *TextureImage[1];					// ���������Ĵ洢�ռ�
//	memset(TextureImage,0,sizeof(void *)*1);			// ��ָ����Ϊ NULL
//
//	// ����λͼ������д�����λͼ�����ڵĻ��˳�
////	if (TextureImage[0]=LoadBMP("Data/Wall.bmp"))
///***********************************�����Ĵ���***********************************************************************************/
//	if (TextureImage[0]=LoadBMP("Data/Wall.bmp"))
///********************************************************************************************************************************/
//	{
//		Status=TRUE;							// ״̬��Ϊ TRUE
//		glGenTextures(3, &texture[0]);					// ��������
//		// ���� Nearest �˲���ͼ
//		glBindTexture(GL_TEXTURE_2D, texture[0]);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//
//		// ���������˲�����
//		glBindTexture(GL_TEXTURE_2D, texture[1]);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//
//		// ���� MipMapped ����
//		glBindTexture(GL_TEXTURE_2D, texture[2]);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
//	}
//	if (TextureImage[0])								// �����Ƿ����
//	{
//		if (TextureImage[0]->data)						// ����ͼ���Ƿ����
//		{
//			free(TextureImage[0]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
//		}
//
//		free(TextureImage[0]);							// �ͷ�ͼ��ṹ
//	}
//	return Status;										// ���� Status
//}
/***********************************�����Ĵ���***********************************************************************************/
int LoadGLTextures()								
{
	int Status=FALSE;							

	AUX_RGBImageRec *TextureImage[2];									// ���������ı���ռ�

	memset(TextureImage,0,sizeof(void *)*2);  		         			// ���Ϊ0

	// ����*.bmpͼ��
	if ((TextureImage[0]=LoadBMP("Data/BG.bmp")) &&						// ����ͼ
		(TextureImage[1]=LoadBMP("Data/Reflect.bmp")))					// ����ͼ����������ͼ��
	{
		Status=TRUE;							

		glGenTextures(6, &texture[0]);									// ����6������
		
		for (int loop=0; loop<=1; loop++)
		{
			// �����ٽ����������ͼ
			glBindTexture(GL_TEXTURE_2D, texture[loop]);				// ��������0��1
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);

			// �������ι�������ͼ
			glBindTexture(GL_TEXTURE_2D, texture[loop+2]);				// ��������2��3
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);

			// ��������Mipmap����ͼ
			glBindTexture(GL_TEXTURE_2D, texture[loop+4]);				// ��������4��5
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY,
				GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
		}
		for (int loop=0; loop<=1; loop++)
		{
	        if (TextureImage[loop])										// ���ͼ����������
		    {
			        if (TextureImage[loop]->data)			
				    {
					        free(TextureImage[loop]->data);	
					}
					free(TextureImage[loop]);		
			}
		}
	}

	return Status;				
}
/********************************************************************************************************************************/
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// ����OpenGL���ڴ�С
{
	if (height==0)										// ��ֹ�����
	{
		height=1;										// ��Height��Ϊ1
	}

	glViewport(0,0,width,height);						// ���õ�ǰ���ӿ�

	glMatrixMode(GL_PROJECTION);						// ѡ��ͶӰ����
	glLoadIdentity();									// ����ͶӰ����

	// �����ӿڵĴ�С
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�͹۲����
	glLoadIdentity();									// ����ģ�͹۲����
}

int InitGL(GLvoid)										// �˴���ʼ��OpenGL������������
{
	if (!LoadGLTextures())								// ������������������
	{
		return FALSE;									// ���δ�����룬����FALSE
	}
	quadratic=gluNewQuadric();							// �������μ�����
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// ʹ��ƽ������
	gluQuadricTexture(quadratic, GL_TRUE);				// ʹ������
/***********************************�����Ĵ���***********************************************************************************/
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// ����s����������Զ�����
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// ����t����������Զ�����
/********************************************************************************************************************************/
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// ���������
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// ���ù�Դλ��
	glEnable(GL_LIGHT1);								// ����һ�Ź�Դ
	glEnable(GL_TEXTURE_2D);							// ��������ӳ��
	glShadeModel(GL_SMOOTH);							// ������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ��ɫ����
	glClearDepth(1.0f);									// ������Ȼ���
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����ϵͳ��͸�ӽ�������
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	return TRUE;										// ��ʼ�� OK
}

int DrawGLScene(GLvoid)									// �����￪ʼ�������еĻ���
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����
	glTranslatef(0.0f,0.0f,z);							// ����/�Ƴ���Ļ z ����λ

	glRotatef(xrot,1.0f,0.0f,0.0f);						// ��X����ת
	glRotatef(yrot,0.0f,1.0f,0.0f);						// ��Y����ת
//	glBindTexture(GL_TEXTURE_2D, texture[filter]);		// ѡ����filter����������
/***********************************�����Ĵ���***********************************************************************************/
	glEnable(GL_TEXTURE_GEN_S);						// �Զ�����s������������
	glEnable(GL_TEXTURE_GEN_T);						// �Զ�����t������������
	glBindTexture(GL_TEXTURE_2D, texture[filter+(filter+1)]);		// ������
	glPushMatrix();

	switch(object)						// ������һ�ֶ��μ�����
	{
	case 0:							// ����������
		glDrawCube();					
		break;	
	case 1:							// ����Բ����
		glTranslatef(0.0f,0.0f,-1.5f);			
		gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);	
		break;						
	//case 2:							// ����Բ��
	//	gluDisk(quadratic,0.5f,1.5f,32,32);		
	//	break;		
	case 2:							// ������
		gluSphere(quadratic,1.3f,32,32);		
		break;		
	case 3:							// ����Բ׶
		glTranslatef(0.0f,0.0f,-1.5f);			
		gluCylinder(quadratic,1.0f,0.0f,3.0f,32,32);	
		break;	
	//case 5:							// ���Ʋ���Բ��
	//	part1+=p1;					
	//	part2+=p2;					

	//	if(part1>359)					
	//	{
	//		p1=0;					
	//		part1=0;				
	//		p2=1;					
	//		part2=0;				
	//	}
	//	if(part2>359)					
	//	{
	//		p1=1;					
	//		p2=0;					
	//	}
	//	gluPartialDisk(quadratic,0.5f,1.5f,32,32,part1,part2-part1);	
	//	break;						
	};
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);						// ��ֹ�Զ�������������
	glDisable(GL_TEXTURE_GEN_T);
/********************************************************************************************************************************/
	xrot+=xspeed;													// xrot ���� xspeed ��λ
	yrot+=yspeed;													// yrot ���� yspeed ��λ
	return TRUE;										// һ�� OK
}

GLvoid KillGLWindow(GLvoid)								// �������ٴ���
{
/***********************************�����Ĵ���***********************************************************************************/
	gluDeleteQuadric(quadratic);				// ɾ�����μ�����
/********************************************************************************************************************************/
	if (fullscreen)										// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings(NULL,0);					// �ǵĻ����л�������
		ShowCursor(TRUE);								// ��ʾ���ָ��
	}

	if (hRC)											//����ӵ��OpenGL��������?
	{
		if (!wglMakeCurrent(NULL,NULL))					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox(NULL,"�ͷ�DC��RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// �����ܷ�ɾ��RC?
		{
			MessageBox(NULL,"�ͷ�RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// ��RC��Ϊ NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// �����ܷ��ͷ� DC?
	{
		MessageBox(NULL,"�ͷ�DCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// �� DC ��Ϊ NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// �ܷ����ٴ���?
	{
		MessageBox(NULL,"�ͷŴ��ھ��ʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// �� hWnd ��Ϊ NULL
	}

	if (!UnregisterClass("OpenG",hInstance))			// �ܷ�ע����?
	{
		MessageBox(NULL,"����ע�������ࡣ","�رմ���",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// �� hInstance ��Ϊ NULL
	}
}

/*	���������������OpenGL���ڣ�����Ϊ��									*
 *	title			- ���ڱ���												*
 *	width			- ���ڿ���												*
 *	height			- ���ڸ߶�												*
 *	bits			- ��ɫ��λ�8/16/32��									*
 *	fullscreenflag	- �Ƿ�ʹ��ȫ��ģʽ��ȫ��ģʽ(TRUE)������ģʽ(FALSE)		*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// �������ƥ��Ľ��
	WNDCLASS	wc;						// ������ṹ
	DWORD		dwExStyle;				// ��չ���ڷ��
	DWORD		dwStyle;				// ���ڷ��
	RECT		WindowRect;				// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left=(long)0;			// ��Left   ��Ϊ 0
	WindowRect.right=(long)width;		// ��Right  ��ΪҪ��Ŀ���
	WindowRect.top=(long)0;				// ��Top    ��Ϊ 0
	WindowRect.bottom=(long)height;		// ��Bottom ��ΪҪ��ĸ߶�

	fullscreen=fullscreenflag;			// ����ȫ��ȫ����־

	hInstance			= GetModuleHandle(NULL);				// ȡ�����Ǵ��ڵ�ʵ��
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc������Ϣ
	wc.cbClsExtra		= 0;									// �޶��ⴰ������
	wc.cbWndExtra		= 0;									// �޶��ⴰ������
	wc.hInstance		= hInstance;							// ����ʵ��
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// װ��ȱʡͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// װ�����ָ��
	wc.hbrBackground	= NULL;									// GL����Ҫ����
	wc.lpszMenuName		= NULL;									// ����Ҫ�˵�
	wc.lpszClassName	= "OpenG";							// �趨������

	if (!RegisterClass(&wc))									// ����ע�ᴰ����
	{
		MessageBox(NULL,"ע�ᴰ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// �˳�������FALSE
	}
	
	if (fullscreen)												// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;								// �豸ģʽ
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= width;				// ��ѡ��Ļ����
		dmScreenSettings.dmPelsHeight	= height;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= bits;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬��
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if (MessageBox(NULL,"ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��","NeHe G",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				//����û�ѡ�񴰿�ģʽ������fullscreen ��ֵ��ΪFALSE,�����������
				fullscreen=FALSE;		// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				//����û�ѡ���˳���������Ϣ���ڸ�֪�û����򽫽�����������FALSE���߳��򴰿�δ�ܳɹ������������˳���
				MessageBox(NULL,"���򽫱��ر�","����",MB_OK|MB_ICONSTOP);
				return FALSE;									// �˳������� FALSE
			}
		}
	}

	if (fullscreen)												// �Դ���ȫ��ģʽ��?
	{
		dwExStyle=WS_EX_APPWINDOW;								// ��չ������
		dwStyle=WS_POPUP;										// ������
		ShowCursor(FALSE);										// �������ָ��
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle=WS_OVERLAPPEDWINDOW;							// ������
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// �������ڴﵽ����Ҫ��Ĵ�С

	// ��������
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// ��չ������
								"OpenG",							// ������
								title,								// ���ڱ���
								dwStyle |							// ����Ĵ���������
								WS_CLIPSIBLINGS |					// ����Ĵ���������
								WS_CLIPCHILDREN,					// ����Ĵ���������
								0, 0,								// ����λ��
								WindowRect.right-WindowRect.left,	// ��������õĴ��ڿ���
								WindowRect.bottom-WindowRect.top,	// ��������õĴ��ڸ߶�
								NULL,								// �޸�����
								NULL,								// �޲˵�
								hInstance,							// ʵ��
								NULL)))								// ����WM_CREATE�����κζ���
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ڴ�������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				//pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// ������ʽ�������Ĵ�С
		1,											// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,							// ����֧��˫����
		PFD_TYPE_RGBA,								// ���� RGBA ��ʽ
		bits,										// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,							// ���Ե�ɫ��λ
		0,											// ��Alpha����
		0,											// ����Shift Bit
		0,											// ���ۼӻ���
		0, 0, 0, 0,									// ���Ծۼ�λ
		16,											// 16λ Z-���� (��Ȼ���) 
		0,											// ���ɰ建��
		0,											// �޸�������
		PFD_MAIN_PLANE,								// ����ͼ��
		0,											// ��ʹ���ص���
		0, 0, 0										// ���Բ�����
	};
	
	if (!(hDC=GetDC(hWnd)))							// ȡ���豸��������ô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ�������豸������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ����ƥ������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// �ܹ��������ظ�ʽô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"�����������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// �ܷ�ȡ��OpenGL��Ⱦ������?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���OpenGL��Ⱦ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// ���Լ�����ɫ������
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܼ��ǰ��OpenGL��Ȼ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// ��ʾ����
	SetForegroundWindow(hWnd);						// ����������ȼ�
	SetFocus(hWnd);									// ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height);					// ����͸�� GL ��Ļ

	if (!InitGL())									// ��ʼ���½���GL����
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"��ʼ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	return TRUE;									// �ɹ�
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// ���ڵľ��	
							UINT	uMsg,			// ���ڵ���Ϣ
							WPARAM	wParam,			// ���ӵ���Ϣ����
							LPARAM	lParam)			// ���ӵ���Ϣ����
{
	switch (uMsg)									// ���Windows��Ϣ
	{
		case WM_ACTIVATE:							// ���Ӵ��ڼ�����Ϣ
		{
			if (!HIWORD(wParam))					// �����С��״̬
			{
				active=TRUE;						// �����ڼ���״̬
			}
			else
			{
				active=FALSE;						// �����ټ���
			}

			return 0;								// ������Ϣѭ��
		}

		case WM_SYSCOMMAND:							// ϵͳ�ж�����
		{
			switch (wParam)							// ���ϵͳ����
			{
				case SC_SCREENSAVE:					// ����Ҫ����?
				case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
				return 0;							// ��ֹ����
			}
			break;									// �˳�
		}

		case WM_CLOSE:								// �յ�Close��Ϣ?
		{
			PostQuitMessage(0);						// �����˳���Ϣ
			return 0;								// ����
		}

		case WM_KEYDOWN:							// �м�����ô?
		{
			keys[wParam] = TRUE;					// ����ǣ���ΪTRUE
			return 0;								// ����
		}

		case WM_KEYUP:								// �м��ſ�ô?
		{
			keys[wParam] = FALSE;					// ����ǣ���ΪFALSE
			return 0;								// ����
		}

		case WM_SIZE:								// ����OpenGL���ڴ�С
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width,HiWord=Height
			return 0;								// ����
		}
	}

	// �� DefWindowProc��������δ��������Ϣ��
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// ��ǰ����ʵ��
					HINSTANCE	hPrevInstance,		// ǰһ������ʵ��
					LPSTR		lpCmdLine,			// �����в���
					int			nCmdShow)			// ������ʾ״̬
{
	MSG		msg;									// Windowsx��Ϣ�ṹ
	BOOL	done=FALSE;								// �����˳�ѭ����Bool ����

	// ��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL,"������ȫ��ģʽ������ô��", "����ȫ��ģʽ",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// FALSEΪ����ģʽ
	}

	// ����OpenGL����
//	if (!CreateGLWindow("NeHe's ���μ�����",640,480,16,fullscreen))
/***********************************�����Ĵ���***********************************************************************************/
	if (!CreateGLWindow("NeHe's ���λ���ӳ��",640,480,16,fullscreen))
/********************************************************************************************************************************/
	{
		return 0;									// ʧ���˳�
	}

	while(!done)									// ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// ����Ϣ�ڵȴ���?
		{
			if (msg.message==WM_QUIT)				// �յ��˳���Ϣ?
			{
				done=TRUE;							// �ǣ���done=TRUE
			}
			else									// ���ǣ�����������Ϣ
			{
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}
		else										// ���û����Ϣ
		{
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active)								// ���򼤻��ô?
			{
				if (keys[VK_ESCAPE])				// ESC ������ô?
				{
					done=TRUE;						// ESC �����˳��ź�
				}
				else								// �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();					// ���Ƴ���
					SwapBuffers(hDC);				// �������� (˫����)
						if (keys['L'] && !lp)				// L ���Ѱ��²����ɿ���?
						{
							lp=TRUE;						// lp ��Ϊ TRUE
							light=!light;					// �л���Դ�� TRUE/FALSE
							if (!light)						// ���û�й�Դ
							{
								glDisable(GL_LIGHTING);		// ���ù�Դ
							}
							else							// ����
							{
								glEnable(GL_LIGHTING);		// ���ù�Դ
							}
						}

						if (!keys['L'])						// L���ɿ���ô?
						{
							lp=FALSE;						// ���ǣ���lp��ΪFALSE
						}

						if (keys['F'] && !fp)				// F��������ô?
						{
							fp=TRUE;						// fp ��Ϊ TRUE
							filter+=1;						// filter��ֵ��һ
							if (filter>2)					// ����2��ô?
							{
								filter=0;					// ��������Ϊ0
							}
						}

						if (!keys['F'])						// F���ſ���ô?
						{
							fp=FALSE;						// ����fp��ΪFALSE
						}

						if (keys[VK_PRIOR])					// PageUp������?
						{
							z-=0.02f;						// �����£���ľ��������Ļ�ڲ�
						}

						if (keys[VK_NEXT])					// PageDown������ô
						{
							z+=0.02f;						// �����µĻ�����ľ������۲���
						}

						if (keys[VK_UP])					// Up�����������ô?
						{
							xspeed-=0.01f;					// ����,����xspeed
						}

						if (keys[VK_DOWN])					// Down�����������ô?
						{
							xspeed+=0.01f;					// ����,����xspeed
						}

						if (keys[VK_RIGHT])					// Right�����������ô?
						{	
							yspeed+=0.01f;					// ����,����yspeed
						}

						if (keys[VK_LEFT])					// Left�����������ô?
						{
							yspeed-=0.01f;					// ����, ����yspeed
						}
						if (keys[' '] && !sp)				// �ո��Ƿ���
						{
							sp=TRUE;						// ��,�������һ�ֶ��μ�����
							object++;		
/***********************************�����Ĵ���***********************************************************************************/
//							if(object>5)		
							if(object>3)
/********************************************************************************************************************************/
								object=0;	
						}
						if (!keys[' '])						// �ո��Ƿ��ͷ�
						{
							sp=FALSE;						// ��¼���״̬
						}
				}
			}

			if (keys[VK_F1])						// F1��������ô?
			{
				keys[VK_F1]=FALSE;					// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();						// ���ٵ�ǰ�Ĵ���
				fullscreen=!fullscreen;				// �л� ȫ�� / ���� ģʽ
				// �ؽ� OpenGL ����
//				if (!CreateGLWindow("NeHe's ���μ�����",640,480,16,fullscreen))
/***********************************�����Ĵ���***********************************************************************************/
				if (!CreateGLWindow("NeHe's ���λ���ӳ��",640,480,16,fullscreen))
/********************************************************************************************************************************/
				{
					return 0;						// �������δ�ܴ����������˳�
				}
			}
		}
	}

	// �رճ���
	KillGLWindow();									// ���ٴ���
	return (msg.wParam);							// �˳�����
}