#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

using namespace std;

#define FROM_RIGHT 1
#define FROM_LEFT 2
#define FROM_TOP 3
#define FROM_BOTTOM 4

static int WINDOW_WIDTH = 1000;
static int WINDOW_HEIGHT = 600;

int playerResult_1 = 0;
int playerResult_2 = 0;
float Xspeed = 4, Yspeed = 4;
float delta = 4;
GLint playerSpeed = 20;
float ty1 = 0.0f, ty2 = 0.0f;

//Positivo ou neativo de acordo com a colisão da bola
//Colisão direita delta - para xspeed
//Colisão esquerda delta + para xspeed
//Colisão superior delta + para yspeed
//Colisão inferior delta - para yspeed

char string[100];
struct RECTA {
  float left, top, right, bottom;
};
struct CIRCLE {
  float x, y, radius,left, top, right, bottom;
};
CIRCLE ball = {100,120,20, 100,100,120,120};
RECTA wall;
RECTA player_1 = {30,200,35,400};
RECTA player_2 = {970,200,975,400};

//Desenhar estruturas RECTA
void DrawRectangle(RECTA rect) {
  glBegin(GL_QUADS);
   glVertex2f(rect.left, rect.bottom); //Left - Bottom 
   glVertex2f(rect.right, rect.bottom);
   glVertex2f(rect.right, rect.top);
   glVertex2f(rect.left, rect.top);
  glEnd();
}
//Desenhar estrutua CIRCLE
void DrawCircle(CIRCLE circl){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	float PI = 3.14159265358979323846;
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(circl.x, circl.y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(circl.x + (circl.radius * cos(i *  twicePi / triangleAmount)),circl.y + (circl.radius * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
}
//Atualiza posição das barras dos jogadores
void updatePosPlayer() {
  player_1.top += ty1;
  player_2.top += ty2;
  player_1.bottom += ty1;
  player_2.bottom += ty2;
  ty1 = 0;
  ty2 = 0;
  if (player_1.top <= 0) {
    player_1.top = 0;
    player_1.bottom = 200;
  }
  if (player_2.top <= 0) {
    player_2.top = 0;
    player_2.bottom = 200;
  }
  if (player_1.bottom >= 600) {
    player_1.top = 400;
    player_1.bottom = 600;
  }
  if (player_2.bottom >= 600) {
    player_2.top = 400;
    player_2.bottom = 600;
  }
}
//Atualizar os valores de posicionamento da bola e barra
void Timer(int v) {
  ball.left += Xspeed;
  ball.right += Xspeed;
  ball.top += Yspeed;
  ball.bottom += Yspeed;
  ball.x += Xspeed;
  ball.y += Yspeed;
  updatePosPlayer();
  glutTimerFunc(1, Timer, 1); // Acada 1 milisegundo cama Timer
}
//Desenha texto
void drawText(char * string, int x, int y) {
  char * c;
  glPushMatrix();
  glTranslatef(x, y, 0);
  glScalef(0.3, -0.3, 1);
  for (c = string;* c != '\0'; c++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, * c);
  }
  glPopMatrix();
}
//Fecha o joo
void stop() {
  printf("game over");
  exit(0);
}
//Testa se houve colisão e retorna o tipo de colição
int checkCollisionBallWall(CIRCLE ball, RECTA wall) {
  if (ball.right >= wall.right)
    return FROM_RIGHT;
  if (ball.left <= wall.left)
    return FROM_LEFT;
  if (ball.top <= wall.top)
    return FROM_TOP;
  if (ball.bottom >= wall.bottom)
    return FROM_BOTTOM;
  else return 0;
}
//Varifica gol do jogador 1
bool checkGollPlayer1(CIRCLE ball, RECTA player) //Esquerda
{
  if (ball.left <= player.right && ball.top >= player.top && ball.bottom <= player.bottom) {
    return true;
  }
  return false;
}
//Varifica gol do jogador 2
bool checkgollPlayer2(CIRCLE ball, RECTA player) //Direita
{
  if (ball.right >= player.left && ball.top >= player.top && ball.bottom <= player.bottom) {
    return true;
  }
  return false;
}
//Adiciona velocidade a bola e barras de acordo com a media dos pontos
void addSpeedWall(){
   int mediaGols = (playerResult_1 + playerResult_2) / 2; 
   if (mediaGols > 10)
   {
      delta = 16; 
      playerSpeed = 50;
   }else if(mediaGols > 8)
   {
      delta = 14; 
      playerSpeed = 40;
   }else if(mediaGols > 6)
   {
      delta = 12; 
      playerSpeed = 30;
   }else if(mediaGols > 5)
   {
      delta = 10;    
      playerSpeed = 25;  
   }else if(mediaGols > 4)
   {
      delta = 9;
   }else if(mediaGols > 3)
   {
      delta = 8;
   }else if(mediaGols > 1)
   {
      delta = 6;
   }
}
//Verifica seleção de teclas especiais
void eventSpecialKeyboard(GLint key, GLint x, GLint y) {
  if (key == GLUT_KEY_DOWN)
    ty2 = playerSpeed; // tecla para baixo
  else if (key == GLUT_KEY_UP)
    ty2 = -playerSpeed; // tecla para cima
}
//Verifica seleção de teclas normais
void eventKeyboard(GLubyte key, GLint x, GLint y) {
  if (key == 'w')
    ty1 = -playerSpeed;
  else if (key == 's')
    ty1 = playerSpeed;
}
// OpenGL Setting
void Setting(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Expecifica dicas para interpretação
}
// OnWindowResize - Alteração no tamanho da janela
void reshape(int w, int h) {
  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}
// Aplica os elementos em tela(a mais importante)
void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  sprintf(string, " %d ", playerResult_1);
  drawText(string, 300, 40); 
  sprintf(string, " %d ", playerResult_2);
  drawText(string, 600, 40);

  wall.left = wall.top = 0;
  wall.right = WINDOW_WIDTH;
  wall.bottom = WINDOW_HEIGHT;

  DrawCircle(ball);

  switch (checkCollisionBallWall(ball, wall) )
  {
      case FROM_RIGHT:
         Xspeed = -delta;
         playerResult_1++;
         break;
      case FROM_LEFT:
         Xspeed = delta;
         playerResult_2++;
         break;
      case FROM_TOP:
         Yspeed = delta;
         break;
      case FROM_BOTTOM:
         Yspeed = -delta;
         break;
      default:
         break;
  }

  DrawRectangle(player_1);
  DrawRectangle(player_2);

  if (checkGollPlayer1(ball, player_1))
    Xspeed = delta;
  if (checkgollPlayer2(ball, player_2))
    Xspeed = -delta;

  addSpeedWall();

  glutSwapBuffers(); //Troca de buffer

}

int main(int argc, char ** argv) {
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("GAME");
  Setting();
  glutDisplayFunc(Render);
  glutIdleFunc(Render);
  glutTimerFunc(1, Timer, 1);
  glutReshapeFunc(reshape); //Chamada quando há alteração no tamanho da janela
  glutKeyboardFunc(eventKeyboard);
  glutSpecialFunc(eventSpecialKeyboard);
  glutMainLoop();
  return 0;
}