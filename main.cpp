// Proiect SNAKE GAME - Fodor Rares - Noiembrie 2024
#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"

#define COLOANE 40
#define LINII 40
#define FPS 12

extern short sDirection;
bool gameOver;

int score=0;

void timer_callback(int);
void display_callback();
void reshape_callback(int,int);
void keyboard_callback(int,int,int);

void init() // functie pentru initializarea culorii display-ului
{
    glClearColor(0.0,0.0,0.0,1.0);
    initGrid(COLOANE,LINII);
}

int main(int argc, char **argv)
{   glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    glutCreateWindow("SNAKE GAME");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}


void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if(gameOver)
    {   char _score[10];
        itoa(score,_score,10);
        char text[50]="Scorul tau: ";
        strcat(text, _score);
        MessageBox(NULL, text, "GAME OVER",0);
        exit(0);
    }
}
void reshape_callback(int w,int h)// pentru proiectia ortografica
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLOANE,0.0,LINII,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}
void keyboard_callback(int key,int,int)
{
    switch(key)
    {   case GLUT_KEY_UP:
            if(sDirection!=DOWN)
                sDirection = UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection!=UP)
                sDirection = DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection!=LEFT)
                sDirection = RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection!=RIGHT)
                sDirection = LEFT;
            break;
    }
}
