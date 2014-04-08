#include<gl\glut.h>

const GLint screenWidth=350,screenHeight=350;

const GLdouble angle=20,near=1.0,far=20;

const char axes[]={'x','y','z'};

const GLdouble cubevertices[8][3]={
	{-1.0,-1.0,1.0},
	{-1.0,1.0,1.0},
	{1.0,1.0,1.0},
	{1.0,-1.0,1.0},
	{-1.0,-1.0,-1.0},
	{-1.0,1.0,-1.0},
	{1.0,1.0,-1.0},
	{1.0,-1.0,-1.0}};

const GLfloat colors[6][3]={
	{1.0,0.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,1.0,0.0},
	{0.0,1.0,1.0},
	{1.0,0.0,1.0}};

void init(){	//1. FAZA: 3D MODELOVANJE
	glClearColor(1.0,1.0,1.0,0.0);	//bijela pozadina
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0,-5.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);	//tg,objekat,up //NAPOMENA: OVako gledamo kocku sa svih strana, mjenjema ovih param.
}

void reshape(int h,int w){      //glViewport podrazumijevano preslikava cijeli okvir! TRANSFORAMCIJA 2D POGLEDA
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,(GLfloat)h/(GLfloat)w,near,far); //PERSPEKTIVNA PROJEKCIJA
}

void drawSide(const GLfloat color[],char axe,GLdouble value){    //1-boja strane,2-ravan,3-vrijednost vezana za ravan
	int j=0;
	if(axe=='x') j=0;
	else if(axe=='y') j=1;
	else j=2;
	if(j!=2)	glBegin(GL_TRIANGLE_STRIP);
	else		glBegin(GL_QUADS);
	glColor3fv(color);
	for(int i=0;i<sizeof(cubevertices)/sizeof(*cubevertices);i++)
		if(cubevertices[i][j]==value)
			glVertex3dv(cubevertices[i]);
	glEnd();	
}

void display(){    //2.FAZA: TRANSFORMACIJA 3D POGLEDA -> ovdje bi se koristile transformacije!
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	//"cistimo" i DEPTH_BUFFER
	GLfloat value=1.0;   //robusnost - dovoljno je samo ovaj parametar promjeniti!
	for(int i=0,j=0;i<sizeof(colors)/sizeof(*colors);i++){
		drawSide(colors[i],axes[j],value);
		if(i!=0 && i%2!=0)	j++;
		value=-value;	
		}
	glFlush();
}

void main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(screenWidth,screenHeight);
	glutCreateWindow("Cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);	//persprektivna prenosi dubinu, zato je bolja! 
	init();
	glutMainLoop();
}
