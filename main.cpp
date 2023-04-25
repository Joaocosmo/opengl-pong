#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLint LARGURA = 1000,
      ALTURA = 600;

GLint ALTURA_RETANGULO = 200,
      LARGURA_RETANGULO = 5;

GLint BEGIN_RETANGULO = 5,
      END_RETANGULO = LARGURA-5;

GLint RETANGULO_VELOCITY = 5; 


float ty1 = 0.0f, ty2 = 0.0f;
float sx = 1.0f, sy = 1.0f;
float angulo = 0.0f;

struct VERTICE
{
    int x;
    int y;
};

struct RETANGULO
{
    VERTICE vertices[4];
};

RETANGULO *retangulo1, *retangulo2;

RETANGULO* criar_retangulo1(){
    RETANGULO *ret = (RETANGULO*)malloc(sizeof(RETANGULO));
    ret->vertices[0].x = BEGIN_RETANGULO;
    ret->vertices[0].y = ALTURA/2 + ALTURA_RETANGULO/2;
    ret->vertices[1].x = BEGIN_RETANGULO + LARGURA_RETANGULO;
    ret->vertices[1].y = ALTURA/2 + ALTURA_RETANGULO/2;
    ret->vertices[2].x = BEGIN_RETANGULO + LARGURA_RETANGULO;
    ret->vertices[2].y = ALTURA/2 - ALTURA_RETANGULO/2;
    ret->vertices[3].x = BEGIN_RETANGULO;
    ret->vertices[3].y = ALTURA/2 - ALTURA_RETANGULO/2;
    return ret;
}

RETANGULO* criar_retangulo2(){
    RETANGULO *ret = (RETANGULO*)malloc(sizeof(RETANGULO));
    ret->vertices[0].x = END_RETANGULO - LARGURA_RETANGULO;
    ret->vertices[0].y = ALTURA/2 + ALTURA_RETANGULO/2;
    ret->vertices[1].x = END_RETANGULO;
    ret->vertices[1].y = ALTURA/2 + ALTURA_RETANGULO/2;
    ret->vertices[2].x = END_RETANGULO;
    ret->vertices[2].y = ALTURA/2 - ALTURA_RETANGULO/2;
    ret->vertices[3].x = END_RETANGULO - LARGURA_RETANGULO;
    ret->vertices[3].y = ALTURA/2 - ALTURA_RETANGULO/2;
    return ret;
}

void initGlut(int *argc, char **argv){
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LARGURA, ALTURA);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("PONG");
}

void inicializacao(GLvoid){
    // Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
                //esquerda, direita, baixo, cima
    gluOrtho2D(0, LARGURA, ALTURA, 0);
    // glLoadIdentity();
    retangulo1 = criar_retangulo1();
    retangulo2 = criar_retangulo2();
}

// FUNÇÃO QUE REALIZA A TRANSLAÇÃO, ROTACAO E ESCALA DO RETANGULO
void aplicaTransformacoes() {
    for (int i = 0; i < 4; i++)
    {
        retangulo1->vertices[i].y += ty1;
        retangulo2->vertices[i].y += ty2;
    }
    ty1 = 0;
    ty2 = 0;
}

void desenharObjetos(){

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(retangulo1->vertices[i].x, retangulo1->vertices[i].y);
    }
    glEnd(); 

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(retangulo2->vertices[i].x, retangulo2->vertices[i].y);
    }
    glEnd(); 
}

void desenha(GLvoid){
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    aplicaTransformacoes();
    desenharObjetos();

    glFlush();
}


void eventoTeclado(GLubyte key, GLint x, GLint y){
    if(key == 'w')
        ty1 = -RETANGULO_VELOCITY;
    else if(key == 's')
        ty1 = RETANGULO_VELOCITY;


    glutPostRedisplay();
}

//GLUT_KEY_F1 .. GLUT_KEY_F12
//GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME etc.
void eventoTecladoEspecial(GLint key, GLint x, GLint y)
{
    
    if (key == GLUT_KEY_DOWN)
        ty2 = RETANGULO_VELOCITY; // tecla para baixo
    else if (key == GLUT_KEY_UP)
        ty2 = -RETANGULO_VELOCITY; // tecla para cima

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    initGlut(&argc, argv);
    inicializacao();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(eventoTeclado);
    glutSpecialFunc(eventoTecladoEspecial);
    glutMainLoop();
    return 0;
}
