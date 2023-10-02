#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define tonum(a) isdigit(a) ? a-'0' : a-'a'+10 
#define tocolor(a,b) (tonum(a)+tonum(b)*16)/25.5
#define torgb(hex) tocolor(hex[0],hex[1]),tocolor(hex[2],hex[3]),tocolor(hex[4],hex[5])

int win_id;

//Aqui se capturam as teclas comuns (letras, números e ESC, por exemplo)
void myKeyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 'R': 
    case 'r':// muda a cor corrente para vermelho
      glColor3f(1.0f, 0.0f, 0.0f);
      break;
    case 'G':
    case 'g':// muda a cor corrente para verde
      glColor3f(0.0f, 1.0f, 0.0f);
      break;
    case 'B':
    case 'b':// muda a cor corrente para azul
      glColor3f(0.0f, 0.0f, 1.0f);
      break;
    //case 27:
    //  glutDestroyWindow(win_id);
    //  exit(0);
    //  break;
  }
  glutPostRedisplay();
}

//Aqui se capturam as teclas especiais (Alt, Control, Shift, F1, F2, etc.)
void myKeyboardSpecial(int key, int x, int y ) {
  switch ( key ) {
    case GLUT_KEY_UP:                   // Quando a seta para cima é teclada...
      glutFullScreen ( );               // Vá para o modo tela cheia...
      break;
    case GLUT_KEY_DOWN:                 // Quando a seta para baixo for teclada...
      glutReshapeWindow ( 640, 480 );   // Vá para modo em janela de 640 por 480
      break;
    default:
      printf("Você apertou a tecla especial código: %d\n", key);  // ...para ajudar você a debugar...       
      break;
  }
}

// Função callback chamada para gerenciar eventos do mouse
void myMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {
      float r, g, b;
      r = (double)rand() / (double)RAND_MAX;
      g = (double)rand() / (double)RAND_MAX;
      b = (double)rand() / (double)RAND_MAX;
      glColor3f(r,g,b);
      printf("%.2f, %.2f, %.2f\n", r, g, b);
    }
  glutPostRedisplay();
}

void init(void) 
{
  // Define a cor de fundo da janela de visualização como preto
  glClearColor(torgb("fdffff"), 1.0f);
  // Define o modo de rastreio de cor utilizado para misturar a cor do material nos pontos da face (smoothing)
  glShadeModel (GL_SMOOTH);
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Parâmetros para a luz ambiente, difusa e especular, definindo também a posição da luz
  GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

  // Passa os parâmetros definidos acima para a OpenGL
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Habilita a luz ambiente, a luz zero e o depth buffer
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  //Primeira cor, para depois mudarmos com os eventos
  glColor3f(0.5, 1.0, 0.5);
}

void display(void)
{
  // Limpa a janela de visualização com a cor de fundo especificada, e limpa também o depth buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Entra no modo de definição de matriz de visualização
  glMatrixMode(GL_MODELVIEW);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a posição da câmera, para onde ela aponta e qual o vetor UP
  gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
  
  // Desenha um teapot de lado de 10 unidades  

  //Frente - parede
  glColor3f(torgb("22b8ec"));
  glPushMatrix();
  glTranslatef(0,-20,0);
  glScalef(40,40,1);
  glutSolidCube(1);
  glPopMatrix();

  //Frente - porta
  glPushMatrix();
  glTranslatef(0,-30,1);
  glColor3f(torgb("825a00"));
  glScalef(12,20,1);
  glutSolidCube(1);
  glPopMatrix();

  //Frente - maçaneta
  glPushMatrix();
  glTranslatef(3,-30,1);
  glColor3f(torgb("000000"));
  glScalef(2,2,1);
  glutSolidSphere(1,360,50);
  glPopMatrix();

  glPushMatrix();
  //Lateral - parede
  glTranslatef(40,-20,0);
  glColor3f(torgb("150a68"));
  glPushMatrix();
  glScalef(40,40,1);
  glutSolidCube(1);
  glPopMatrix();

  //Janela1
  glPushMatrix();
  glTranslatef(-10,0,1);
  glColor3f(torgb("a6a6a6"));
  glPushMatrix();
  glScalef(12,12,1);
  glutSolidCube(1);
  glPopMatrix();

  glTranslatef(0,0,1);
  glColor3f(torgb("d9d9d9"));
  glPushMatrix();
  glScalef(6,12,1);
  glutSolidCube(1);
  glPopMatrix();
  glPopMatrix();

  //Janela2
  glPushMatrix();
  glTranslatef(10,0,1);
  glColor3f(torgb("a6a6a6"));
  glPushMatrix();
  glScalef(12,12,1);
  glutSolidCube(1);
  glPopMatrix();

  glTranslatef(0,0,1);
  glColor3f(torgb("d9d9d9"));
  glPushMatrix();
  glScalef(6,12,1);
  glutSolidCube(1);
  glPopMatrix();
  glPopMatrix();
  
  glPopMatrix();
  
  //Telhado - frente
  glColor3f(torgb("825a00"));
  glPushMatrix();
  glTranslatef(0,0,-1);
  glRotatef(90,-1,0.5,0.6);
  glScalef(21,21,20);
  glutSolidCone(1,1,20,10);
  glPopMatrix();

  // //Telhado - meio
  // glTranslatef(40,0,0);
  // glColor3f(torgb("413500"));
  // glPushMatrix();
  // glScalef(80,40,1);
  // desenhaQuadrado();
  // glPopMatrix();
  // // //Telhado - final
  // glTranslatef(40,0,0);
  // glColor3f(torgb("413500"));
  // glPushMatrix();
  // glScalef(80,40,1);
  // desenhaTriangulo();
  // glPopMatrix();    

  glPopMatrix();


  // Oito - janela
  // glTranslatef(-100,55,0);
  // glColor3f(torgb("ffffff"));
  // glPushMatrix();
  // glScalef(10,10,1);
  // dese;
  // glPopMatrix();

  // glColor3f(torgb("22b8ec"));
  // glPushMatrix();
  // glScalef(8,8,1);
  // desenhaCirculo();
  // glPopMatrix();
  // glPopMatrix();

  glTranslatef(50,30,0);
  glColor3f(torgb("e9975c"));
  glPushMatrix();
  glScalef(20,10,1);
  glutSolidCube(1);
  glPopMatrix();
  
  glTranslatef(0,10,0);
  glColor3f(torgb("e9975c"));
  glPushMatrix();
  glScalef(30,10,1);
  glutSolidCube(1);
  glPopMatrix();
  
  // glTranslatef(-150,10,0);
  // glColor3f(torgb("22b8ec"));
  // glPushMatrix();
  // glScalef(40,40,1);
  // desenhaCirculo();
  // glPopMatrix();

  // // glTranslatef(0,25,0);
  // // glColor3f(torgb(starshiny(star)));
  // // glPushMatrix();
  // // glRotatef(45,0,0,1);
  // // glScalef(10,10,1);
  // // glutSolidCube(1);
  // // glPopMatrix();

  // glTranslatef(-20,-20,0);
  // glPushMatrix();
  // glRotatef(45,0,0,1);
  // glScalef(10,10,1);
  // glutSolidCube(1);
  // glPopMatrix();

  // glTranslatef(45,0,0);
  // glPushMatrix();
  // glRotatef(45,0,0,1);
  // glScalef(10,10,1);
  // glutSolidCube(1);
  // glPopMatrix();

  // glTranslatef(-15,-10,0);
  // glPushMatrix();
  // glRotatef(45,0,0,1);
  // glScalef(7,7,1);
  // glutSolidCube(1);
  // glPopMatrix();


  // glTranslatef(-10,-20,0);
  // glPushMatrix();
  // glRotatef(45,0,0,1);
  // glScalef(10,10,1);
  // glutSolidCube(1);
  // glPopMatrix();

  
  // Executa os comandos OpenGL, e depois troca os buffers de vídeo
  glFlush();
}

void reshape (int w, int h)
{
  // Define o viewport como o tamanho da janela
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  // Entra no modo de definição de matriz de projeção
  glMatrixMode (GL_PROJECTION);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a projeção ortogonal
  if (w <= h)
    // Se a largura for menor que a altura, a projeção é feita para manter a proporção da janela
    glOrtho (-50, 50, -50*(GLfloat)h/(GLfloat)w, 50*(GLfloat)h/(GLfloat)w, -100.0, 100.0);
  else
    // Se a altura for menor que a largura, a projeção é feita para manter a proporção da janela
    glOrtho (-50*(GLfloat)w/(GLfloat)h, 50*(GLfloat)w/(GLfloat)h, -50, 50, -100.0, 100.0);
   
}

int main(int argc, char** argv)
{
  // Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas
  glutInit(&argc, argv);
  // Inicializa o display, indicando que usará:
  // - um buffer de imagem (single buffer);
  // - buffer de profundidade;
  // - padrão de cores RGB)
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  // Especifica as dimensões da janela de exibição
  glutInitWindowSize (1080, 720); 
  // Especifica a posição inicial da janela de exibição
  glutInitWindowPosition (100, 100);
  // Cria a janela de exibição
  win_id = glutCreateWindow (argv[0]);
  // Chama a função init
  init ();
  // Estabelece a função "display" como a função callback de exibição.
  glutDisplayFunc(display); 
  // Estabelece a função "reshape" como a função callback de redimensionamento da janela de exibição.
  glutReshapeFunc(reshape);
  // Estabelece a função "keyboard" como a função callback de evento de teclado.
  glutKeyboardFunc(myKeyboard);
  // Estabelece a função "keyboardSpecial" como a função callback de evento de teclado especial.
  glutSpecialFunc(myKeyboardSpecial);
  // Estabelece a função "mouse" como a função callback de evento de mouse.
  glutMouseFunc(myMouse);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}