
#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
using    namespace std;

#define FROM_RIGHT      1 
#define FROM_LEFT       2 
#define FROM_TOP        3 
#define FROM_BOTTOM     4 
 
static int WINDOW_WIDTH = 100;
static int WINDOW_HEIGHT = 600;

int playerResult_1=0;
int playerResult_2=0;
static float Xspeed=4,Yspeed=4; 
static float delta=4; 
GLint RETANGULO_VELOCITY = 20; 
float ty1 = 0.0f, ty2 = 0.0f;

//Positivo ou neativo de acordo com a colisão da bola
//Colisão direita delta - para xspeed
//Colisão esquerda delta + para xspeed
//Colisão superior delta + para yspeed
//Colisão inferior delta - para yspeed

char string [100];
struct RECTA
{ 
   float left,top,right,bottom; 
};
RECTA ball={100,100,120,120};
RECTA wall ;
RECTA player_1 ={5,200,10,400}; 
RECTA player_2 ={990,200,995,400}; 
//Desenhar estruturas RECTA
void DrawRectangle(RECTA  rect) 
{ 
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
}

void atualizarPosJogadores(){
   player_1.top += ty1;
   player_2.top += ty2;
   player_1.bottom += ty1;
   player_2.bottom += ty2;
   ty1 = 0;
   ty2 = 0;
   if (player_1.top <=0)
   {
      player_1.top= 0;
      player_1.bottom= 200;
   }
   if (player_2.top <=0)
   {
      player_2.top= 0;
      player_2.bottom= 200;
   }
   if (player_1.bottom >= 600)
   {
      player_1.top= 400;
      player_1.bottom= 600;
   }
   if (player_2.bottom >= 600)
   {
      player_2.top= 400;
      player_2.bottom= 600;
   }        
}
//Atualizar os valores de posicionamento da bola
void Timer(int v) 
{ 
        ball.left+=Xspeed; 
        ball.right+=Xspeed; 
        ball.top+=Yspeed; 
        ball.bottom+=Yspeed; 
        atualizarPosJogadores();
        glutTimerFunc(1,Timer,1); // Acada 1 milisegundo cama Timer
}
//Desenha texto
void drawText(char*string,int x,int y)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,-0.1,1);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();

}
//Fecha o joo
void stop()
{
   printf("game over");
   exit(0);
}
//Testa se houve colisão e retorna o tipo de colição
int verificarColisaoParede(RECTA  ball , RECTA wall) 
{ 
        if(ball.right >=wall.right) 
         return FROM_RIGHT;  
        if(ball.left <=wall.left) 
         return FROM_LEFT;  
        if(ball.top <=wall.top) 
         return FROM_TOP;  
        if(ball.bottom >=wall.bottom) 
          return FROM_BOTTOM;  
        else return 0 ; 
}
//Calcula pontuação do jogador 1
bool Teste_Goll_P1(RECTA ball,RECTA player) //Esquerda
{  
   if(ball.left <= player.right && ball.top>= player.top && ball.bottom <=player.bottom ) 
   {
      return true;  
   }
   return false;  
}
bool Teste_Goll_P2(RECTA ball,RECTA player) //Direita
{  
   if(ball.right >= player.left && ball.top>= player.top && ball.bottom <=player.bottom ) 
   {
      return true;  
   }
   return false;  
}
//GLUT_KEY_F1 .. GLUT_KEY_F12
//GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME etc.
void eventoTecladoEspecial(GLint key, GLint x, GLint y)
{
   if (key == GLUT_KEY_DOWN)
      ty2 = RETANGULO_VELOCITY; // tecla para baixo
   else if (key == GLUT_KEY_UP)
      ty2 = -RETANGULO_VELOCITY; // tecla para cima
}
void eventoTeclado(GLubyte key, GLint x, GLint y){
   if(key == 'w')
      ty1 = -RETANGULO_VELOCITY;
   else if(key == 's')
      ty1 = RETANGULO_VELOCITY;
}
// OpenGL Setting
void Setting(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Expecifica dicas para interpretação
}
// OnWindowResize - Alteração no tamanho da janela
void reshape (int w, int h)
{
	WINDOW_WIDTH =w ;
	WINDOW_HEIGHT =h ;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, w, h, 0);


   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

}
int pcResult =0;/* äÊíÌÉ ÇáßãÈíæÊÑ äÎÒäåÇ åäÇ  */
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
 
	sprintf(string,"Player 1 %d ",playerResult_1); // ÊÍæíá ÑÞã Çáì äÕ
	drawText(string,10,80); // ØÈÇÚÉ ÇáäÕ
	sprintf(string,"Player 2: %d ",playerResult_2);
	drawText(string,10,120);

	wall.left=wall.top=0;
	wall.right=WINDOW_WIDTH;
	wall.bottom=WINDOW_HEIGHT;

	DrawRectangle(ball);

	if(verificarColisaoParede(ball,wall)== FROM_RIGHT) {
      Xspeed=-delta; 
      playerResult_1++;
   }

   if(verificarColisaoParede(ball,wall)== FROM_LEFT) {
      Xspeed=delta;
      playerResult_2++;
   } 

   if(verificarColisaoParede(ball,wall)== FROM_TOP) 
    Yspeed=delta; 

   if(verificarColisaoParede(ball,wall)== FROM_BOTTOM) 
	  Yspeed=-delta; 

 	DrawRectangle(player_1); 
   DrawRectangle(player_2); 

   if(Teste_Goll_P1(ball,player_1)) 
      Xspeed=delta; 
   if(Teste_Goll_P2(ball,player_2)) 
      Xspeed=-delta;
	glutSwapBuffers(); //Troca de buffer
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1000, 600); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("GAME");
   Setting (); 
   glutDisplayFunc(Render); 
   glutIdleFunc(Render);
   glutTimerFunc(1,Timer,1);
   glutReshapeFunc(reshape); //Chamada quando há alteração no tamanho da janela
   glutKeyboardFunc(eventoTeclado);
   glutSpecialFunc(eventoTecladoEspecial);
   glutMainLoop();
   return 0;
}
