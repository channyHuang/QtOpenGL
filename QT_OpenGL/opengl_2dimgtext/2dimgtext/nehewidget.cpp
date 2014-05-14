#include "nehewidget.h"

#include <gl/GLU.h>
#include <gl/GL.h>
#include <QVector2D>
#include <QKeyEvent>
#include <QOpenGLFunctions>

namespace {
	GLuint  texture[2];                             // Storage For Our Font Texture
	GLuint  loop;                                   // Generic Loop Variable

	GLfloat cnt1;                                   // 1st Counter Used To Move Text & For Coloring
	GLfloat cnt2;                                   // 2nd Counter Used To Move Text & For Coloring

	struct FyjBitmapChar
	{
		QVector<QVector2D> texCoords;
		int right; //�ַ����
		int height;//�ַ��߶�
		int ascillValue;
	};

	struct FyjBitmapFont
	{
		char *name;
		int quality;
		FyjBitmapChar *characters;
	};

	static FyjBitmapChar chars1[128];
	static FyjBitmapChar chars2[128];

	const FyjBitmapFont font1 = {"standard", 128, chars1};
	const FyjBitmapFont font2 = {"Itatic", 128, chars2};

	void buildFont()
	{
		float   cx;                      // Holds Our X Character Coord
		float   cy;                     // Holds Our Y Character Coord
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		for (loop = 0; loop < 256; loop++) {
			cx = float(loop%16)/16.0f; //��ǰ�ַ���x��������
			cy = float(loop/16)/16.0f; //��ǰ�ַ���y��������
			if (loop < 128) {
				chars1[loop].texCoords<<QVector2D(cx, cy + 0.0625f)
					<<QVector2D(cx+0.0625f, cy+0.0625f)
					<<QVector2D(cx+0.0625f, cy)
					<<QVector2D(cx, cy);
				chars1[loop].height = 16;
				chars1[loop].right = 10;
				chars1[loop].ascillValue = loop+32;
			} else {
				chars2[loop-128].texCoords<<QVector2D(cx, cy + 0.0625f)
					<<QVector2D(cx+0.0625f, cy+0.0625f)
					<<QVector2D(cx+0.0625f, cy)
					<<QVector2D(cx, cy);
				chars2[loop-128].height = 12;
				chars2[loop-128].right = 10;
				chars2[loop-128].ascillValue = loop-128+32;
			}
		}
	}

	void renderBitmapCharacter(FyjBitmapChar c, int fontSize)
	{
		Q_ASSERT_X(c.ascillValue >= 32 && c.ascillValue <= 127,
			"renderBitmapCharacter", "unspported char");
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		QVector<QVector2D> vertices;
		vertices<<QVector2D(0, 0)
			<<QVector2D(fontSize, 0)
			<<QVector2D(fontSize, fontSize)
			<<QVector2D(0, fontSize);
		glVertexPointer(2, GL_FLOAT, 0, vertices.constData());
		glTexCoordPointer(2, GL_FLOAT, 0, c.texCoords.constData());
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void renderBitmapString(GLint x, GLint y, QString string, int set, int fontSize)
	{
		int numOfReturnChar = 0;
		if (string.isNull() || string.isEmpty())
			return;
		if (set > 1)
			set = 1;
		FyjBitmapFont currentFont;
		if (set == 0)
			currentFont = font1;
		else
			currentFont = font2;

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
//		glOrtho(0,640,0,480,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
//		glTranslatef(x, y, 0);
		for(int i = 0; i < string.length(); i++) {
			char c = string.at(i).toLatin1();
			if (c == '\n') {
				numOfReturnChar++;
				glLoadIdentity();
//				glTranslatef(x, y - numOfReturnChar * currentFont.characters[0].height, 0);
				continue;
			}
			renderBitmapCharacter(currentFont.characters[c-32], fontSize);
//			glTranslatef(currentFont.characters[c-32].right * fontSize/16, 0, 0);
		}
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

	void glPrint(GLint x, GLint y, int set, int fontSize, const char *fmt, ...)
	{
		char   text[256];              // Holds Our String
		va_list     ap;                 // Pointer To List Of Arguments
		if (fmt == NULL)                    // If There's No Text
			return;                     // Do Nothing
		va_start(ap, fmt);                  // Parses The String For Variables
		vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
		va_end(ap);                     // Results Are Stored In Text

		renderBitmapString(x, y, QString(text), set, fontSize);
	}

	void drawTextureMappedQuad()
	{
		QVector<QVector2D> vertices;
		QVector<QVector2D> texCoords;
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		vertices<<QVector2D(-1.0f, 1.0f)
			<<QVector2D(1.0f, 1.0f)
			<<QVector2D(1.0f,-1.0f)
			<<QVector2D(-1.0f,-1.0f);
		texCoords<<QVector2D(0.0f,0.0f)
			<<QVector2D(1.0f,0.0f)
			<<QVector2D(1.0f,1.0f)
			<<QVector2D(0.0f,1.0f);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
		glVertexPointer(2, GL_FLOAT, 0, vertices.constData());
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

}

nehewidget::nehewidget(QWidget *parent,bool fs)
	: QGLWidget(parent)
{
	fullscreen=fs;
	setGeometry(100,100,640,480);
	//	setCaption("OpenGL window"); //�����������֧���˰ɣ�
	setWindowTitle("OpenGL Window");
	if(fullscreen) showFullScreen();
}

nehewidget::~nehewidget()
{

}

void nehewidget::loadTextures()
{
	texture[0] = bindTexture(QString("./texture.bmp"),
		GL_TEXTURE_2D,
		GL_RGBA,
		QGLContext::LinearFilteringBindOption);
	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	texture[1] = bindTexture(QString("./0.bmp"),
		GL_TEXTURE_2D,
		GL_RGBA,
		QGLContext::LinearFilteringBindOption);
	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}

void nehewidget::initializeGL()
{
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	buildFont();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glShadeModel(GL_SMOOTH);   // Enables Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Black Background
	glClearDepth(1.0f);             // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);        // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);        // The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
}

void nehewidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear The Screen And The Depth Buffer
	glLoadIdentity();       // Reset The Current Modelview Matrix

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(45.0f,0.0f,0.0f,1.0f);
	glRotatef(cnt1*30.0f,1.0f,1.0f,0.0f);
	glDisable(GL_BLEND);
	glColor3f(1.0f,1.0f,1.0f);
	drawTextureMappedQuad();

	glRotatef(90.0f,1.0f,1.0f,0.0f);
	drawTextureMappedQuad();

	glEnable(GL_BLEND);
	glLoadIdentity();

	glColor3f(1.0f*float(cos(cnt1)),1.0f*float(sin(cnt2)),1.0f-0.5f*float(cos(cnt1+cnt2)));
	glPrint(int((280+250*cos(cnt1))),int(235+200*sin(cnt2)),0, 16, "NeHe");

	glColor3f(1.0f*float(sin(cnt2)),1.0f-0.5f*float(cos(cnt1+cnt2)),1.0f*float(cos(cnt1)));
	glPrint(int((280+230*cos(cnt2))),int(235+200*sin(cnt1)), 1, 24, "OpenGL");

	glColor3f(0.0f,0.0f,1.0f);
	glPrint(int(240+200*cos((cnt2+cnt1)/5)),2, 0, 16, "Giuseppe D'Agata");

	glColor3f(1.0f,1.0f,1.0f);
	glPrint(int(242+200*cos((cnt2+cnt1)/5)),2, 0, 16, "Giuseppe D'Agata");

	cnt1+=0.01f;
	cnt2+=0.0081f;
}

void nehewidget::resizeGL(int w,int h)
{
	if(h==0) h=1;
	glViewport(0,0,(GLint)w,(GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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