// Proiect SNAKE GAME - Fodor Rares - Noiembrie 2024
#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include <time.h>

#define COLOANE 40
#define LINII 40

extern int score;

int gridX,gridY;
int snakeLength=5;
bool food=1;
int foodX,foodY;
short sDirection = RIGHT;
extern bool gameOver;

int posX[lengthMAX]={20,20,20,20,20},posY[60]={20,19,18,17,16};

void initGrid(int x,int y) // initializarea gridului pentru joc
{
    gridX=x;
    gridY=y;
}
void unit(int,int);
void drawGrid() // crearea gridului pentru joc
{
    for(int x=0;x<gridX;x++)
        for(int y=0;y<gridY;y++) unit(x,y);

}

void unit(int x,int y)
{
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1)
    {   glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {   glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
        /*  ordinea este importanta in desenarea patratului pentru grid
            incepem de la coltul din stanga jos (x,y), apoi miscam in dreapta cu o unitate (x+1,y)
            apoi in coltul din dreapta sus (x+1,y+1) si in sfarsit in (x,y+1) unde patratul se completeaza
        */
    glEnd();
}

void drawFood()
{   if(food)
        random(foodX,foodY);
    food=false;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);
}
void drawSnake()
{
    for(int i=snakeLength-1;i>0;i--)
    {   posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    // actualizarea pozitiei capului in functie de directie
    if(sDirection==UP)
        posY[0]++;
    else if(sDirection==DOWN)
        posY[0]--;
    else if(sDirection==RIGHT)
        posX[0]++;
    else if(sDirection==LEFT)
        posX[0]--;
    for(int i=0;i<snakeLength;i++)
    {   if(i==0) glColor3f(0.0,1.0,0.0);
        else glColor3f(0.0,0.0,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    // verificare coliziune cu perete
    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1)
        gameOver=1;
    if(posX[0]==foodX && posY[0]==foodY)
    {   snakeLength++;
        score++;
        if(snakeLength>lengthMAX) snakeLength=lengthMAX;
        food=true;
    }
    // verificare coliziune cu corp
    for(int i=1;i<snakeLength;i++)
        if(posX[0]==posX[i] && posY[0]==posY[i]) gameOver=1;
}

void random(int &x, int &y)
{
    int maxX=gridX-2;
    int maxY=gridY-2;
    int mini=1;
    srand(time(NULL));
    x = mini+rand() %(maxX-mini);
    y = mini+rand() %(maxY-mini);
}
