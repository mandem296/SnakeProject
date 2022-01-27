#include <GL/glut.h>
#include <fstream>
#include "math.h"

using namespace std;

int dir;
int d = 1;
int num = 7;
int key1 = 3;
int Score = 0;
int hightScore;
int Scale = 25;
int N = 50, M = 30;
int w = Scale * N;
int h = Scale * M;

char sScore[15];
char sHightScore[15];
float xm = 0.0;
float ym = 0.0;
bool down = false;

struct {
    int x;
    int y;
} s[100];

class Fruct {
public:
    int x, y;
    void New()
    {
        x = rand() % N;
        y = rand() % (M - 3);
    }
    void DrawFruct()
    {
        glColor3f(1.0, 0.9, 0.0);
        glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
    }
} m[2];

class Bomb {
public:
    int x, y;

    void New()
    {
        x = rand() % N;
        y = rand() % (M - 3);
    }
    void DrawBomb()
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (float i = 0; i < 2 * 3.14; i += 3.14 / 4) {
            glVertex2f((x + 0.5) * Scale + (0.5) * Scale * (1.1) * sin(i),
                (y + 0.5) * Scale + (0.5) * Scale * (1.1) * cos(i));
        }
        glEnd();
    }
} u[10];

void draw_string(void* font, const char* string)
{
    while (*string)
        glutStrokeCharacter(font, *string++);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateGlutWindow()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Mode selection: single buffer and RGBA colors
    glutInitWindowSize(w, h);
    glutCreateWindow("Snake");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void timer(int = 0)
{
    if (d == 2) {
        display();
    }
    Tick();

    glutTimerFunc(80, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    CreateGlutWindow();
    glutDisplayFunc(display);
    glutTimerFunc(80, timer, 0);
    glutSpecialFunc(MyKeyboard);
    glutMouseFunc(MousePressed);
    glutMainLoop(); //  enter GLUT event processing loop
    return 0;
}