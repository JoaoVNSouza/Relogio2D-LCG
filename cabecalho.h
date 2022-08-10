#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

// Constantes.
#define win 100    // Constante que armazena o valor de coordenadas para orientação x.
#define PI 3.14159 // Constante PI.

// Variáveis globais.
GLfloat width, height;          // Armazena o tamanho da janela, para eventos de redimensionar a janela.
GLfloat raio;                   // Variável armazena o tamanho do raio do relógio.
GLint segundos, minutos, horas; // Variável para armazenar o tempo.
GLint rotHora, rotMin, rotSec;  // Variável para armazenar o ângulo de rotação.

/* Protótipos de Funções/Procedimentos. */
// Rotinas callbacks.
static void resize(int, int);
static void display();
static void key(unsigned char, int, int);
static void idle();

// Rotinas diversos.
void inicializa();
void draw_aro();
void draw_interno();

// Primitivas.
void draw_circle(int);
void draw_ponteiros(float);

#endif // CABECALHO_H_INCLUDED
