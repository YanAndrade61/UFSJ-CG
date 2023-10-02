/* X compile line: cc -o simple simple.c -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm */
#include <GL/glut.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define tonum(a) isdigit(a) ? a-'0' : a-'a'+10 
#define tocolor(a,b) (tonum(a)+tonum(b)*16)/25.5
#define torgb(hex) tocolor(hex[0],hex[1]),tocolor(hex[2],hex[3]),tocolor(hex[4],hex[5])
#define starshiny(x) x ? "ffffff\0" : "ffde59\0" 

typedef struct ponto{
  int x;
  int y;
} ponto;

typedef struct figura{
  ponto pontos[1000];
  char hex[10];
  int tipo;
  int n;
} figura;

int estrelabrilho = 0, nuvemvx = 5, nuvemvy = 5, nuvem_dist=1;

void draw(figura pol){
  glBegin(pol.tipo);
    glColor3f(torgb(pol.hex));
    for(int i = 0; i < pol.n; i++)
      glVertex2i(pol.pontos[i].x, pol.pontos[i].y);
  glEnd();
}

figura build_quad(int x, int y, int width, int height, char *cor, int losango){
  
  figura f;
  f.pontos[0].x = losango ? x+width/2 : x;
  f.pontos[0].y = y;
  f.pontos[1].x = x+width; 
  f.pontos[1].y = losango ? y+width/2 : y;
  f.pontos[2].x = losango ? x+width/2 : x+width; 
  f.pontos[2].y = y+height;
  f.pontos[3].x = x; 
  f.pontos[3].y = losango ? y+width/2 : y+height;
  f.tipo = GL_QUADS;
  strcpy(f.hex,cor);  
  f.n = 4;

  return f;
}

figura build_circle(int x, int y, int r, int div, char *cor){
  
  figura f;
  f.n = 0;
  for (int i = 0; i < 360; i+=div){
    f.pontos[i].x = r*cos(i) + x;
    f.pontos[i].y = r*sin(i) + y;
    f.n+=1;
  }
  f.tipo = GL_POLYGON;
  strcpy(f.hex,cor);  

  return f;
}

figura build_triangle(int x, int y, int width, int height, char *cor){
  
  figura f;
  f.pontos[0].x = x; f.pontos[0].y = y;
  f.pontos[1].x = x+width; f.pontos[1].y = y;
  f.pontos[2].x = x+width/2; f.pontos[2].y = y+height;
  f.tipo = GL_TRIANGLES;
  strcpy(f.hex,cor);  
  f.n = 3;

  return f;
}

void reshape(int w, int h) {

  glViewport(0, 0, w, h);       
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();             
  glOrtho(0, w, 0, h, -1, 1);   
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  figura chao = build_quad(0,0,1080,110,"007400\0",0);
  draw(chao);

  figura frente = build_quad(362,110,320,320,"9d1919\0",0);
  figura lateral = build_quad(682,110,320,320,"b40505\0",0);
  draw(frente);
  draw(lateral);  
  
  figura janela1ex = build_quad(740,242,100,100,"a6a6a6\0",0);
  figura janela1in = build_quad(773,242,40,100,"d9d9d9\0",0);
  draw(janela1ex);
  draw(janela1in);
  
  figura janela2ex = build_quad(879,242,100,100,"a6a6a6\0",0);
  figura janela2in = build_quad(909,242,40,100,"d9d9d9\0",0);
  draw(janela2ex);
  draw(janela2in);

  figura porta = build_quad(484,110,80,150,"825a00\0",0);
  figura fechadura = build_circle(540,176,9,1,"000000\0");
  draw(porta);
  draw(fechadura);

  figura teto1 = build_triangle(362,430,320,150,"825a00\0");
  figura teto2 = build_quad(522,430,320,150,"795403\0",0);
  figura teto3 = build_triangle(682,430,320,150,"795403\0");
  draw(teto2);
  draw(teto1);
  draw(teto3);

  figura oitoex = build_circle(524,490,47,1,"a6a6a6\0");
  figura oitoin = build_quad(476,443,94,94,"d9d9d9\0",1);
  draw(oitoex);
  draw(oitoin);

  figura chamine1 = build_quad(646,580,80,60,"dd5400\0",0);
  figura chamine2 = build_quad(636,640,100,30,"dd5400\0",0);
  draw(chamine1);
  draw(chamine2);

  figura lua1 = build_circle(167,905,95,1,"ffde59\0");
  figura lua2 = build_circle(225,905,95,1,"000074\0");
  draw(lua1);
  draw(lua2);

  figura estrela1 = build_quad(457,876,30,30,starshiny(estrelabrilho),1);
  figura estrela2 = build_quad(395,830,30,30,starshiny(estrelabrilho),1);
  figura estrela3 = build_quad(520,830,30,30,starshiny(estrelabrilho),1);
  figura estrela4 = build_quad(484,810,30,30,starshiny(estrelabrilho),1);
  figura estrela5 = build_quad(457,756,30,30,starshiny(estrelabrilho),1);
  draw(estrela1);
  draw(estrela2);
  draw(estrela3);
  draw(estrela4);
  draw(estrela5);

  int aux = nuvemvx, freq = 100;
  while(aux > 0){
    figura nuvem1 = build_circle(662+aux,725+aux,39,1,"ffffff\0");
    figura nuvem2 = build_circle(701+aux,725+aux,39,1,"ffffff\0");
    figura nuvem3 = build_circle(690+aux,750+aux,39,1,"ffffff\0");
    draw(nuvem1);
    draw(nuvem2);
    draw(nuvem3);

    aux-=freq;
  }

  glFlush();

  estrelabrilho = (estrelabrilho+1)%2;
  nuvemvx = (nuvemvx+1)%1000000;
  glutPostRedisplay();

}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(1080,1080);
  glutCreateWindow("Simple House");
  glClearColor(torgb("000074"), 1.0f);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
