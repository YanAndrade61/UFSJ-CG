#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define tonum(a) isdigit(a) ? a-'0' : a-'a'+10 
#define tocolor(a,b) (tonum(a)+tonum(b)*16)/25.5
#define torgb(hex) tocolor(hex[0],hex[1]),tocolor(hex[2],hex[3]),tocolor(hex[4],hex[5])
#define starshiny(x) x ? "ffffff\0" : "ffde59\0" 

int win_id;
float eye[] = {0,-0.3,1.7};
float up[] = {0,1,0};
float center[] = {0,20,0};
float desl[] = {0,0,5.5};
float sz[] = {1,1,1};
float rgb[] = {0,0,0};
float sp[] = {5,5};
float rot = 0;
float move = 0;

//Aqui se capturam as teclas comuns (letras, números e ESC, por exemplo)
// void myKeyboard(unsigned char key, int x, int y)
// {
//   switch (key) {
//     case 'j': 
//       eye[2] += 0.1;
//       break;
//     case 'J': 
//       eye[2] -= 0.1;
//       break;
//     case 'k': 
//       eye[0] += 0.1;
//       break;
//     case 'K': 
//       eye[0] -= 0.1;
//       break;
//     case 'l': 
//       eye[1] += 0.1;
//       break;
//     case 'L': 
//       eye[1] -= 0.1;
//       break;

//     case 'd': 
//       desl[0] += 1;
//       break;
//     case 'D': 
//       desl[0] -= 1;
//       break;
//     case 's': 
//       desl[1] += 1;
//       break;
//     case 'S': 
//       desl[1] -= 1;
//       break;
//     case 'a': 
//       desl[2] += 1;
//       break;
//     case 'A': 
//       desl[2] -= 1;
//       break;
    
//     case 'e': 
//       sz[0] += 1;
//       break;
//     case 'E': 
//       sz[0] -= 1;
//       break;
//     case 'w': 
//       sz[1] += 1;
//       break;
//     case 'W': 
//       sz[1] -= 1;
//       break;
//     case 'q': 
//       sz[2] += 1;
//       break;
//     case 'Q': 
//       sz[2] -= 1;
//       break;

//     case 'c': 
//       rgb[0] = (rgb[0]+0.1);
//       break;
//     case 'C': 
//       rgb[0] = 0;
//       break;
//     case 'x': 
//       rgb[1] = (rgb[1]+0.1);
//       break;
//     case 'X': 
//       rgb[1] = 0;
//       break;
//     case 'z': 
//       rgb[2] = (rgb[2]+0.1);
//       break;
//     case 'Z': 
//       rgb[2] = 0;
//       break;
//     case 'r': 
//       rot += 1;
//       break;
//     case 'R': 
//       rot -= 1;
//       break;


//     case 'b': 
//       sp[0] += 1;
//       break;
//     case 'B': 
//       sp[0] -= 1;
//       break;
//     case 'g': 
//       sp[1] += 1;
//       break;
//     case 'G': 
//       sp[1] -= 1;
//       break;
//     case 'v':
//       printf("eye: %.2f %.2f %.2f\n",eye[0],eye[1],eye[2]);
//       printf("desl: %.2f %.2f %.2f\n",desl[0],desl[1],desl[2]);
//       printf("sz: %.2f %.2f %.2f\n", sz[0], sz[1], sz[2]);
//       printf("rgb: %.2f %.2f %.2f\n", rgb[0], rgb[1], rgb[2]);
//       printf("rot: %.2f\n",rot);
//       break;
//     case 'f':
//       glutDestroyWindow(win_id);
//       exit(0);
//       break;
//   }
//   glutPostRedisplay();
// }

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
  glClearColor(torgb("00ffff"), 1.0f);
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
  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
  
  // Cenario - Terreno
  glPushMatrix();
    glColor3f(0.878,0.875, 0.616);
    glScalef(1000,1000,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(0,-16,-17.5);
    glScalef(1000,1000,1);
    glutSolidCube(1);
  glPopMatrix();
    glPushMatrix();
    glColor3f(0.878, 0.875, 0.616);
    glTranslatef(0,0,-36.5);
    glScalef(1000,1200,10);
    glutSolidCube(1);
  glPopMatrix();
  // Cenario - Passarela
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(-7,32,2.5);
    glScalef(5,-3,3);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(-7,-64,5.5);
    glScalef(-8,-2,-4);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(-7,-86,1.5);
    glScalef(12,1,5);
    glutSolidCube(1);
  glPopMatrix();

  //Cenario - lula1
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(58,54,11.5);
    glScalef(6,6,5);
    glRotatef(126,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(56,60,7.5);
    glScalef(1,0,12);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(58,60,7.5);
    glScalef(1,0,5);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
    glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(60,60,7.5);
    glScalef(1,0,9);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();

  //Cenario - Lula2
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(69, 0, 27.5);
    glScalef(6,6,5);
    glRotatef(126,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(71,2,22.5);
    glScalef(1,0,12);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(67,0,23.5);
    glScalef(1,0,5);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();
    glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(69,0,23.50);
    glScalef(1,0,9);
    glRotatef(302,0,0,1);
    glutSolidCube(1);
  glPopMatrix();

  // Bob Esponja - BOTAS
  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(26, -79,5.5);
    glScalef(3, 18, 1);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(37, -79,5.5);
    glScalef(3, 18, 1);
    glutSolidCube(1);
  glPopMatrix();

  // Bob Esponja - PERNAS
  glPushMatrix();
    glColor3f(1.7,1,0);
    glTranslatef(26, -14, 5.5);
    glScalef(3,-109,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(1.7,1,0);
    glTranslatef(37, -14, 5.5);
    glScalef(3,-109,1);
    glutSolidCube(1);
  glPopMatrix();
  
  // Bob esponja - Calça
  glPushMatrix();
    glColor3f(1.6,0,0);
    glTranslatef(31, 22, 9.5);
    glScalef(21, 85, -1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(31, 98, 9.5);
    glScalef(21, 70, -1);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(31, -60, 23.5);
    glScalef(1, 1, 1);
    glRotatef(180,0,1,0);
    glutSolidCone(2,6,10,10);
  glPopMatrix();

  // Bob esponja - Corpo
  glPushMatrix();
    glColor3f(1.7,1,0);
    glTranslatef(31, 14, 25.5);
    glScalef(21, 204, -1);
    glutSolidCube(1);
  glPopMatrix();

  // Bob esponja - Braço
  glPushMatrix();
    glColor3f(1.7,1,0);
    glTranslatef(14, 0, 25.5);
    glScalef(14, 1, -3);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(1.7,1,0);
    glTranslatef(48, 0, 25.5);
    glScalef(14, 1, -3);
    glutSolidCube(1);
  glPopMatrix();

  // Bob esponja - Boca
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(31, -66, 29.5);
    glScalef(-10, 1, 1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(29, -66, 28.5);
    glScalef(-3, 3, 2);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(33, -66, 28.5);
    glScalef(-3, 3, 2);
    glutSolidCube(1);
  glPopMatrix();

  // Bob esponja - Olho
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(28, -16, 30.5);
    glScalef(2, 2, -3);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(27, -34, 31.5);
    glScalef(1, 2, 1);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(36, -16, 30.5);
    glScalef(2, 2, -3);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(35, -34, 31.5);
    glScalef(1, 2, 1);
    glutSolidSphere(1,10,10);
  glPopMatrix();

  //Cenario - Abacaxi 
  glPushMatrix();
    glColor3f(4,0,0);
    glTranslatef(-8, 99, 6.5);
    glScalef(13, -5, 24);
    glutSolidSphere(1,5,5);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 255, 0);
    glTranslatef(-7, 101, 32.5);
    glScalef(-2, -3, 1);
    glRotatef(180,0,1,0);
    glutSolidCone(10,10,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 255, 255);
    glTranslatef(-7, 0, 46.5);
    glScalef(1,1,1);
    glRotatef(180,0,1,0);
    glutSolidCone(5,10,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 255, 255);
    glTranslatef(4, 0, 47.5);
    glScalef(1,1,1);
    glRotatef(180,0,1,0);
    glutSolidCone(5,10,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 255, 255);
    glTranslatef(-4, 0, 47.5);
    glScalef(1, 1, 1);
    glRotatef(180,0,1,0);
    glutSolidCone(5,10,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 255, 255);
    glTranslatef(-15, 0, 46.5);
    glScalef(1,1,1);
    glRotatef(180,0,1,0);
    glutSolidCone(5,10,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(-7,112,3.5);
    glScalef(1,5,2);
    glRotatef(180,0,1,0);
    glutSolidSphere(5, 10, 10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255, 255, 255);
    glTranslatef(-12,1,25.5);
    glScalef(3,1,3);
    // glRotatef(180,0,1,0);
    glutSolidSphere(1, 10, 10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(255, 255, 255);
    glTranslatef(1,-60,21.5);
    glScalef(2,1,2);
    // glRotatef(180,0,1,0);
    glutSolidSphere(1, 10, 10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(1,0,16.5);
    glScalef(1,1,1);
    glRotatef(91,1,0,0);
    glutSolidTorus(1,3,10,10);
  glPopMatrix();

  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(-12,0,25.5);
    glScalef(1,1,1);
    glRotatef(91,1,0,0);
    glutSolidTorus(1,3,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(211/255.0, 211/255.0, 211/255.0);
    glTranslatef(3,100,19.5);
    glScalef(1,1,4);
    glRotatef(72,0,1,0);
    glutSolidIcosahedron();
  glPopMatrix();

  // Patrick - Corpo
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-49,3,14.5);
    glScalef(12,1,10);
    glutSolidSphere(1,5,5);
  glPopMatrix();
    glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-49,3,19.5);
    glScalef(7,1,17);
    glutSolidSphere(1,5,5);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-39,3,16.5);
    glScalef(11,1,4);
    glRotatef(60,0,1,0);
    glutSolidSphere(1,5,5);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-59,3,16.5);
    glScalef(11,1,4);
    glRotatef(60,0,1,0);
    glutSolidSphere(1,5,5);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-52,-36,5.5);
    glScalef(-2,2,7);
    glRotatef(259,0,1,0);
    glutSolidSphere(1,5,5);
  glPopMatrix();
  glPushMatrix();
    glColor3f(6.5,1,1.6);
    glTranslatef(-44,-34,4.5);
    glScalef(2,3,8);
    glutSolidSphere(1,5,5);
  glPopMatrix();

  //Patrick - Calça
  glPushMatrix();
    glColor3f(0,255,0);
    glTranslatef(-48,-41,9.5);
    glScalef(16,1,7);
    glutSolidCube(1);
  glPopMatrix();

  //Patrick - Olho
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(-51,-16,30.5);
    glScalef(2, 2, -3);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-51,-34,30.5);
    glScalef(1, 2, 1);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  
  glPushMatrix();
    glColor3f(255,255,255);
    glTranslatef(-46,-16,30.5);
    glScalef(2, 2, -3);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-46,-34,30.5);
    glScalef(1, 2, 1);
    glutSolidSphere(1,10,10);
  glPopMatrix();
  

  // glutPostRedisplay();
  
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
  // glutKeyboardFunc(myKeyboard);
  // Estabelece a função "keyboardSpecial" como a função callback de evento de teclado especial.
  glutSpecialFunc(myKeyboardSpecial);
  // Estabelece a função "mouse" como a função callback de evento de mouse.
  glutMouseFunc(myMouse);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}