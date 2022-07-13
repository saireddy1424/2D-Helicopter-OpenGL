#define GLUT_DISABLE_ATEXIT_HACK
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<string.h>

float y=0;
float bx = 0,bx1=0;
float by = 0,by1=0;
int view =0, score = 0;
float theta = 0.0;
char scoreText[10];

void display_string(int x, int y, char *string, int font)
{
    int len,i;
	glColor3f(0,0,0.0);
	glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    if(font==1)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	if(font==2)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	if(font==3)
	        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
	}

}
void gameStartDisplay(){
    glClearColor(0.5, 0.7, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
	display_string(250, 650, "2D HELICOPTER GAME",1);
	display_string(50, 560, "MOUSE",2);
	display_string(80, 520, " PRESS 'LEFT MOUSE BUTTON' TO MOVE HELICOPTER UP",3);
	display_string(80, 480, " RELEASE 'LEFT MOUSE BUTTON' TO MOVE HELICOPTER DOWN",3);

	display_string(50, 400, "INSTRUCTIONS",2);
	display_string(80, 360, "MOVE AWAY FROM OBSTACLES",3);
	display_string(80, 320, "WHEN HELICOPTER HITS OBSTACLES YOU LOOSE",3);
	display_string(50, 240, "PRESS 'p' TO PLAY GAME",2);
	display_string(50, 200, "PRESS 'q' TO QUIT THE GAME",2);
	glutPostRedisplay();
	glutSwapBuffers();

	glFlush();
}
void helicopter()
{
    glColor3f(0, 0, 0);
    glRectf(100,150+y,200,100+y);         //body
    glRectf(145,150+y,155,170+y);         //top

    glRectf(60,115+y,100,130+y);          //tail1
    glRectf(54,115+y,60,160+y);           //t2

    glColor3f(0.5, 1, 1);
    glRectf(120,110+y,160,140+y);         //win1
    glRectf(170,120+y,190,140+y);         //win2

    glBegin(GL_TRIANGLES);
        glVertex2i(47,150+y);         //propeller
        glVertex2i(47,160+y);
        glVertex2i(57,155+y);
        glVertex2i(57,155+y);
        glVertex2i(67,150+y);
        glVertex2i(67,160+y);
    glEnd();

    glutPostRedisplay();
    glutSwapBuffers();
}
void moveBlock1(){
    bx -=0.1;

    if (bx < -1050)
    {
        bx = 0;            //total width is 50
        by = (rand() % 200) +50;
			//by1 = (rand() % 200)+20;
    }
    if  (bx < -700 && bx > -701)
    {
         score++;
    }
}
void moveBlock2(){
    bx1 -=0.1;
    if (bx1 < -1050)
    {
        bx1 = 0;            //total width is 50
        by1 = (rand() % 200)+0;
    }
    if  (bx1 < -1000 && bx1 > -1001)
    {
         score++;
    }

}
void gameOverDisplay(){
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    display_string(400, 700, "GAME OVER", 1);
    display_string(420, 650, "SCORE : ", 2);
    display_string(350, 550, "PRESS 'R' TO RETURN", 2);
    glFlush();
    printf("\t\t\t\t---------------THANKS---------------\n");
    printf("\t\t\t\t---------------- FOR ---------------\n");
    printf("\t\t\t\t---------------PLAYING--------------\n\n\n\n");
    printf("\t\t\t\t\tScore:%s\n\n\n",scoreText);

    exit(0);
}

bool hit(float xb1, float yb1, float xb2, float yb2, float xh1, float yh1, float xh2, float yh2){
    if(xb1 >= xh1 && xb1 <=xh2 && yb1 <= yh1 && yb1 >= yh2){
        return true;
    }
    if(xb2 >= xh1 && xb2 <=xh2 && yb2 <= yh1 && yb2 >= yh2){
        return true;
    }
    /*if(xb1 >= xh1 && xb1 <=xh2 && ybm <= yh1 && ybm >= yh2){
        return true;
    }*/
    return false;
}

void blocks1 (){
       glColor3f(1, 0.2, 0.2);
      // by= (rand() % 2000) ;
     glRectf(630 + bx,300+by1,650 + bx,550+by1);
     if(hit(630 + bx, 550 + by1, 650 + bx, 300 + by1, 60, 185 + y, 200, 100 + y)){
            gameOverDisplay();
     }
}
void blocks2 () {
    glColor3f(1, 0.2, 0.2);
    glRectf(1050 + bx1,by,1070 + bx1,250+by);
    if(hit(1050 + bx1, by, 1070 + bx1, 250 + by, 60, 185 + y, 200, 100 + y)){
            gameOverDisplay();

     }

}
void walls(){
    glColor3f(1,1,0);
    glRectf(0, 800, 800, 780);
    glRectf(0, 0, 800, 20);
}

void fans (){
     glColor3f(1, 1, 1);
    // glRotatef( 90, 0,1, 0 );

    glBegin(GL_POLYGON);
        glVertex2i(90,160+y);            //fan
        glVertex2i(210,180+y);
        glVertex2i(210,185+y);
        glVertex2i(90,165+y);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(90,180+y);            //fan
        glVertex2i(210,160+y);
        glVertex2i(210,165+y);
        glVertex2i(90,185+y);
    glEnd();
}
    /*glBegin(GL_POLYGON);
        glVertex2i(100,150);          //BODY
        glVertex2i(200,150);
        glVertex2i(200,100);
        glVertex2i(100,100);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(145,150);          //TOP
        glVertex2i(155,150);
        glVertex2i(155,170);
        glVertex2i(145,170);
    glEnd();*/
    /*glBegin(GL_POLYGON);
        glVertex2i(90,170);            //fan st
        glVertex2i(210,170);
        glVertex2i(210,180);
        glVertex2i(90,180);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(90,160);            //fan
        glVertex2i(210,180);
        glVertex2i(210,185);
        glVertex2i(90,165);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(90,180);            //fan
        glVertex2i(210,160);
        glVertex2i(210,165);
        glVertex2i(90,185);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(60,115);            //tail1
        glVertex2i(100,115);
        glVertex2i(100,130);
        glVertex2i(60,130);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(54,115);             //tail2
        glVertex2i(60,115);
        glVertex2i(60,160);
        glVertex2i(54,160);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2i(47,150);         //propeller
        glVertex2i(47,160);
        glVertex2i(57,155);
        glVertex2i(57,155);
        glVertex2i(67,150);
        glVertex2i(67,160);
    glEnd();

    glColor3f(0.5, 0.8, 0.9);
    glBegin(GL_POLYGON);
        glVertex2i(120,110);          //window2
        glVertex2i(160,110);
        glVertex2i(160,140);
        glVertex2i(120,140);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(170,120);          //window1
        glVertex2i(190,120);
        glVertex2i(190,140);
        glVertex2i(170,140);
    glEnd();*/



void display()
{
    if(view == 0){
        gameStartDisplay();
    }
    else{
        itoa(score, scoreText, 10);
        glClearColor(0.7, 0.7, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        display_string(20, 750, "SCORE : ", 2);
        display_string(120, 750, scoreText, 2);
        helicopter();
        blocks1();
        blocks2();

        fans();
        walls();

        glFlush();
        glutPostRedisplay();
        glutSwapBuffers();
    }
}


void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 800);
    glMatrixMode(GL_MODELVIEW);
}


void movehelUp(){
    /*if(key==GLUT_KEY_UP){
        if(y<600){
            y+=8;
        }
    }*/
    if(y>630){
        gameOverDisplay();
    }
    else{
        y+=0.1;
    }
    moveBlock1();
    moveBlock2();
}
void movehelDown(){
     if(y<-100){
        gameOverDisplay();
    }
    else{
        y-=0.2;
    }
    moveBlock1();
    moveBlock2();
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:

		if (state == GLUT_DOWN){
			glutIdleFunc(movehelUp);
		}
		else if (state == GLUT_UP){
			glutIdleFunc(movehelDown);
		}
		break;
	default: break;
	}
}
void keyboard(unsigned char key,int u,int d){
   switch(key){
        case 'p': view = 1;
        break;
        case 'r': if(view != 0){
                view = 0;
            }
        break;
        case 'q' :exit(0);

    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0,0);
    glutCreateWindow ("2D Helicopter Game");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard); //keyboard call back func
    glutMainLoop();
    return 0;
}
