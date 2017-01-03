#include "nehewidget.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include <QKeyEvent>

bool  keys[256];       
bool  vline[11][10];       // ���洹ֱ�����11�������У�ÿ�������е�10���Ƿ��߹�
bool  hline[10][11];       //����ˮƽ�����11�������У�ÿ�������е�10���Ƿ��߹�
bool  ap;        // A���Ƿ��Ѿ�����
bool  filled;        // �����Ƿ�����?
bool  gameover;       // ��Ϸ�Ƿ����?
bool  anti=TRUE;       // �Ƿ����÷�����?
bool  active=TRUE;       

int  loop1;        // ͨ��ѭ������
int  loop2;        // ͨ��ѭ������
int  delay;        // ���˵���ͣʱ��
int  adjust=3;       // ������ʾ���ٶ�
int  lives=5;       // ��ҵ�����
int  level=1;       // �ڲ���Ϸ�ĵȼ�
int  level2=level;       // ��ʾ����Ϸ�ĵȼ�
int  stage=1;       // ��Ϸ�Ĺؿ�

struct  object        // ��¼��Ϸ�еĶ���
{
	int fx, fy;        // ʹ�ƶ����ƽ��
	int x, y;        // ��ǰ��Ϸ�ߵ�λ��
	float spin;        // ��ת����
};
struct object player;        // �����Ϣ
struct object enemy[9];       // ���9�����˵���Ϣ
struct object hourglass;       // ������Ϣ

int  steps[6]={ 1, 2, 4, 5, 10, 20 };    

nehewidget::nehewidget(QWidget *parent)
	: QGLWidget(parent)
{
	fullscreen = false;
	setGeometry(100,100,640,480);
//	setCaption("OpenGL window"); //�����������֧���˰ɣ�
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{
	glDeleteLists(base,256);
}

void nehewidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, texture[0]);    // ѡ���ַ�����
	glColor3f(1.0f,0.5f,1.0f);      
	glPrint(207,24,0,"GRID CRAZY");      // ������Ϸ����"GRID CRAZY"
	glColor3f(1.0f,1.0f,0.0f);     
}

void nehewidget::resizeGL(int w,int h)
{
	if(h==0) h=1;
	glViewport(0,0,(GLint)w,(GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//�������������Qt��OpenGL�°汾�ж���֧���ˣ���ע�͵��ɣ��Ժ󲻵ò���ʱ����취
	//	gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nehewidget::keyPressEvent(QKeyEvent *e)
{
	switch(e->key()) {
	case Qt::Key_F2:
		fullscreen=!fullscreen;
		if(fullscreen) showFullScreen();
		else {
			showNormal();
			setGeometry(0,0,640,480);
		}
		updateGL();
		break;
	case Qt::Key_Escape:
		close();
	}
}

void nehewidget::ResetObjects(void)        // ������Һ͵���
{
	player.x=0;        // ������������Ͻ�
	player.y=0;        
	player.fx=0;        
	player.fy=0;
	for (loop1=0; loop1<(stage*level); loop1++)    // ѭ���漴�������еĵ���
	{
		enemy[loop1].x=5+rand()%6;     
		enemy[loop1].y=rand()%11;     
		enemy[loop1].fx=enemy[loop1].x*60;    
		enemy[loop1].fy=enemy[loop1].y*40;    
	}
}

GLvoid nehewidget::BuildFont(GLvoid)       
{
	base=glGenLists(256);       
	glBindTexture(GL_TEXTURE_2D, texture[0]);    
	for (loop1=0; loop1<256; loop1++)     
	{
		float cx=float(loop1%16)/16.0f;     
		float cy=float(loop1/16)/16.0f;     

		glNewList(base+loop1,GL_COMPILE);    
		glBegin(GL_QUADS);     
		glTexCoord2f(cx,1.0f-cy-0.0625f);  
		glVertex2d(0,16);    
		glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f); 
		glVertex2i(16,16);    
		glTexCoord2f(cx+0.0625f,1.0f-cy);  
		glVertex2i(16,0);    
		glTexCoord2f(cx,1.0f-cy);   
		glVertex2i(0,0);    
		glEnd();      
		glTranslated(15,0,0);     
		glEndList();       
	}         
}

GLvoid nehewidget::glPrint(GLint x, GLint y, int set, const char *fmt, ...)
{
	char  text[256];      
	va_list  ap;       

	if (fmt == NULL)  
		return;        

	va_start(ap, fmt);       
	vsprintf(text, fmt, ap);      
	va_end(ap);        

	if (set>1)        
	{
		set=1;       
	}
	glEnable(GL_TEXTURE_2D);      
	glLoadIdentity();       
	glTranslated(x,y,0);       
	glListBase(base-32+(128*set));      

	if (set==0)        
	{
		glScalef(1.5f,2.0f,1.0f);     
	}

	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);   
	glDisable(GL_TEXTURE_2D);      
}
