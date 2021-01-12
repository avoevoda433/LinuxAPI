/*------------------------------
            LIBRARIES
------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>


/*------------------------------
GLOBAL VARIABLES AND CONSTANTS
------------------------------*/
#define MAP_W 10
#define MAP_H 10

typedef struct
{
    int mine;
    int flag;
    int open;
    int minesAround;
    int selected;
} Cells;

Cells map[MAP_W][MAP_H];
int mines, closedCell;
int selectX = 0;
int selectY = 0;


/*------------------------------
    WINDOW INITIALIZATION
------------------------------*/
void init()
{
    glClearColor(0, 0, 0, 1); // set background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}


void showMine()
{
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0, 0, 0);
        glVertex2f(0.3, 0.3);
        glVertex2f(0.7, 0.3);
        glVertex2f(0.7, 0.7);
        glVertex2f(0.3, 0.7);
    glEnd();
}


void showFlag()
{
    glBegin(GL_TRIANGLES);
        glColor3f(0.9, 0, 0);
        glVertex2f(0.25, 0.75);
        glVertex2f(0.85, 0.5);
        glVertex2f(0.25, 0.25);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3f(0.1, 0.1, 0.1);
        glVertex2f(0.25, 0.75);
        glVertex2f(0.25, 0.0);
    glEnd();
}


void showField()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.6, 0.6, 0.6); glVertex2f(0, 1);
        glColor3f(0.5, 0.5, 0.5); glVertex2f(1, 1); glVertex2f(0, 0);
        glColor3f(0.4, 0.4, 0.4); glVertex2f(1, 0);
    glEnd();
}


void showOpenField()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.9, 0.9, 0.9); glVertex2f(0, 1);
        glColor3f(0.8, 0.8, 0.8); glVertex2f(1, 1); glVertex2f(0, 0);
        glColor3f(0.7, 0.7, 0.7); glVertex2f(1, 0);
    glEnd();
}

void showSelectCell()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.1, 0.8, 0.3); glVertex2f(0, 1);
        glColor3f(0.1, 0.7, 0.2); glVertex2f(1, 1); glVertex2f(0, 0);
        glColor3f(0.1, 0.6, 0.1); glVertex2f(1, 0);
    glEnd();
}

void showOpenSelectCell()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.8, 0.9, 0.0); glVertex2f(0, 1);
        glColor3f(0.7, 0.8, 0.0); glVertex2f(1, 1); glVertex2f(0, 0);
        glColor3f(0.6, 0.7, 0.0); glVertex2f(1, 0);
    glEnd();
}


int isCellMap(int x, int y)
{
    return (x >= 0) && (y >= 0) && (x < MAP_W) && (y < MAP_H);
}


void showMinesAround(int a)
{
    void line(float x1, float y1, float x2, float y2)
    {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glLineWidth(3);
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_LINES);
        if ((a != 1) && (a != 4)) line(0.3, 0.85, 0.7, 0.85);
        if ((a != 0) && (a != 1) && (a != 7)) line(0.3, 0.5, 0.7, 0.5);
        if ((a != 1) && (a != 4) && (a != 7)) line(0.3, 0.15, 0.7, 0.15);

        if ((a != 5) && (a != 6)) line(0.7, 0.5, 0.7, 0.85);
        if ((a != 2)) line(0.7, 0.5, 0.7, 0.15);

        if ((a != 1) && (a != 2) && (a != 3) && (a != 7)) line(0.3, 0.5, 0.3, 0.85);
        if ((a == 0) || (a == 2) || (a == 6) || (a == 8)) line(0.3, 0.5, 0.3, 0.15);
    glEnd();
}


void openFields(int x, int y)
{
    if (!isCellMap(x, y) || map[x][y].open) return;
    map[x][y].open = 1;

    if (map[x][y].mine)
    {
        for (int i = 0; i < MAP_W; i++)
            for (int j = 0; j < MAP_H; j++)
            {
                map[i][j].open = 1;
                showOpenField();
            }
    }
    if (map[x][y].minesAround == 0)
    {
        for (int dx = -1; dx < 2; dx++)
        {
            for (int dy = -1; dy < 2; dy++)
            {
                if (isCellMap(x+dx, y+dy))
                {
                    openFields(x+dx, y+dy);
                }
            }
        }
    }
}


void showGame()
{
    glLoadIdentity();
    glScalef(2.0/MAP_W, 2.0/MAP_H, 1);
    glTranslated(-MAP_W*0.5, -MAP_H*0.5, 0);

    for (int i = 0; i < MAP_W; i++)
    {
        for(int j = 0; j < MAP_H; j++)
            {
                glPushMatrix();
                glTranslatef(i, j, 0);

                if (map[i][j].open && !map[i][j].selected)
                {
                    showOpenField();
                    if (map[i][j].mine) showMine();
                    else if (map[i][j].minesAround > 0)
                        showMinesAround(map[i][j].minesAround);
                }
                else if (map[i][j].open && map[i][j].selected)
                {
                    showOpenSelectCell();
                    if (map[i][j].mine) showMine();
                    else if (map[i][j].minesAround > 0)
                        showMinesAround(map[i][j].minesAround);
                }
                else if (!map[i][j].open && map[i][j].selected)
                {
                    showSelectCell();
                    if (map[i][j].flag) showFlag();
                }
                else if (!map[i][j].open && !map[i][j].selected)
                {
                    showField();
                    if (map[i][j].flag) showFlag();
                }
                else showField();
                glPopMatrix();
            }
    }
}


/*------------------------------
        DRAW FUNCTION
------------------------------*/
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    showGame();

    glFlush();
}


/*------------------------------
        USER FUNCTION
------------------------------*/
void newGame()
{
    srand(time(NULL));
    memset(map, 0, sizeof(map));

    mines = 12;
    closedCell = MAP_W * MAP_H;
    for (int i = 0; i < mines; i++)
    {
        int x = rand() % MAP_W;
        int y = rand() % MAP_H;

        if (map[x][y].mine) i--;
        else
        {
            map[x][y].mine = 1;

            for (int dx = -1; dx < 2; dx++)
            {
                for (int dy = -1; dy < 2; dy++)
                {
                    if (isCellMap(x+dx, y+dy))
                    {
                        map[x+dx][y+dy].minesAround++;
                    }
                }
            }
        }
    }
    map[selectX][selectY].selected = 1;
}


void processSpecialKeys(int key, int a, int b) {
	switch(key) {
		case GLUT_KEY_UP:
            if (selectY+1 < MAP_H)
            {
                map[selectX][selectY].selected = 0;
                map[selectX][++selectY].selected = 1;
                display();
            }
            break;
		case GLUT_KEY_DOWN:
            if (selectY-1 >= 0)
            {
                map[selectX][selectY].selected = 0;
                map[selectX][--selectY].selected = 1;
                display();
            }
            break;
		case GLUT_KEY_LEFT:
            if (selectX-1 >= 0)
            {
                map[selectX][selectY].selected = 0;
                map[--selectX][selectY].selected = 1;
                display();
            }
            break;
        case GLUT_KEY_RIGHT:
            if (selectX+1 < MAP_W)
            {
                map[selectX][selectY].selected = 0;
                map[++selectX][selectY].selected = 1;
                display();
            }
            break;
	}
}


void processNormalKeys(unsigned char key, int a, int b)
{
	if (key == 13)
	{
        openFields(selectX, selectY);
        display();
	}
	if (key == 32)
	{
        if (map[selectX][selectY].flag)
            map[selectX][selectY].flag = 0;
        else map[selectX][selectY].flag = 1;
        display();
	}
	if (key == 114 || key == 82) newGame(); display();
}


/*------------------------------
        MAIN FUNCTION
------------------------------*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /* window settings */
    glutInitWindowSize(500, 500); // window size
    glutInitWindowPosition(500, 300); // window position
    glutCreateWindow("Miner"); // window name
    init();

    newGame();

    /* rendering objects */
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();

    return 0;
}
