// glutEx1.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include <windows.h>

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

#define checkImageWidth 64
#define checkImageHeight 64

GLuint texture[3];
GLubyte checkImage[checkImageHeight][checkImageWidth][4];

void DrawCube()
{
	glBegin(GL_QUADS);  //启用四边形带绘制模式绘制

    // 绘制前面，这里开始确定纹理坐标，然后是确定点的位置
    glTexCoord2i(0, 0); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2i(1, 0); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2i(1, 1); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2i(0, 1); glVertex3f(-0.5f,  0.5f,  0.5f);

    // 绘制后面
    glTexCoord2i(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2i(1, 1); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2i(0, 1); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2i(0, 0); glVertex3f( 0.5f, -0.5f, -0.5f);

    // 上面
    glTexCoord2i(0, 1); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2i(0, 0); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2i(1, 0); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2i(1, 1); glVertex3f( 0.5f,  0.5f, -0.5f);

    //底面
    glTexCoord2i(1, 1); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2i(0, 1); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2i(0, 0); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2i(1, 0); glVertex3f(-0.5f, -0.5f,  0.5f);
    
    // 右面
    glTexCoord2i(1, 0); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2i(1, 1); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2i(0, 1); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2i(0, 0); glVertex3f( 0.5f, -0.5f,  0.5f);

    // 左面
    glTexCoord2i(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2i(1, 0); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2i(1, 1); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2i(0, 1); glVertex3f(-0.5f,  0.5f, -0.5f);

    glEnd();
}

void Draw_Leg();

void single()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
}

void multi()
{
	
}

void Draw_Triangle() // This function draws a triangle with RGB colors
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);  //选择纹理texture[0]
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	single();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
//	glutSolidCube(1.0);
	DrawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);  //选择纹理texture[0]

	glPushMatrix();
	//。。。
	//如果是某四边形，还必须设定纹理坐标，如下所示：茶壶不需要此步
	glBegin(GL_QUADS);
	glTexCoord2i(1, 1); glVertex3i(0.5, 0.5, 0);
	glTexCoord2i(1, 0); glVertex3i(0.5, -0.5, 0);
	glTexCoord2i(0, 0); glVertex3i(-0.5, -0.5, 0);
	glTexCoord2i(0, 1); glVertex3i(-0.5, 0.5, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);	//关闭纹理texture[0]
*/
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
//	glutSolidCube(1.0);
	DrawCube();
}

#define BITMAP_ID 0x4D42
int count = 0;

// 纹理标示符数组，保存两个纹理的标示符
// 描述: 通过指针，返回filename 指定的bitmap文件中数据。
// 同时也返回bitmap信息头.（不支持-bit位图）
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char	*bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量

	// 以“二进制+读”模式打开文件filename
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	fprintf(stderr, "size: %ld\n", bitmapInfoHeader->biSizeImage);
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	fprintf(stderr, "count: %d\n", ++count);
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0;
		imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}

void texload(int i, char *filename)
{

	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
	unsigned char*   bitmapData;                                       // 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	//    if (bitmapData==NULL)
	//        fprintf(stderr, "FILE NOT EXISTS\n");

	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 	    //mipmap层次(通常为，表示最上层)
		GL_RGB,	//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2
		0, //边框(0=无边框, 1=有边框)
		GL_RGB,	//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		bitmapData);	//bitmap数据指针  
}

void mytexture(int k) {
	int i, j, c;
	for (i = 0; i<checkImageHeight; i++)
		for (j = 0; j<checkImageWidth; j++) {
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)0;
			checkImage[i][j][2] = (GLubyte)0;
			checkImage[i][j][3] = (GLubyte)255;
		}
}

int s = 0;

void init()
{
	fprintf(stderr, "alloc: %d\n", ++s);
	glGenTextures(3, texture);                                         // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
	texload(0, "Monet.bmp");
	texload(1, "Crack.bmp");
	//下面生成自定义纹理
	mytexture(2); //参考opengl red book，理解后请解释函数的步骤。
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //设置像素存储模式控制所读取的图像数据的行对齐方式.
	//    glTexImage2D(GL_TEXTURE_2D,0,3,TEXW,TEXH,0,GL_RGB,GL_UNSIGNED_BYTE,tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
	}
	case 'd': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
	}
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	}
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
	}
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
	}
	case 'c': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
	}
	}
	updateView(wHeight, wWidth);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ³¡¾°£¨0£¬0£¬0£©µÄÊÓµãÖÐÐÄ (0,5,50)£¬YÖáÏòÉÏ

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Triangle();						// Draw triangle

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	init();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}