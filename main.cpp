/*
 * Universidade Federal da Grande Dourados - UFGD.
 * Faculdade de Ciências Exatas e Tecnologia - FACET.
 * Bacharelado em Engenharia de Computação.
 *
 * Disciplina: Laboratório de Computação Gráfica - LCG.
 * Professor: Adailton José Alves da Cruz.
 * Período: semestre 2022.1 || ocorrência no 2º semestre do ano de 2022.
 *
 * Programa: main.cpp
 * Desenvolvido por: João Vitor Nascimento De Souza.
 *
 * Objetivo:
 * - Desenhar um relógio.
 * - Fazer ele funcionar como um relógio.
 * Referência: Autoria própria.
 */

// Bibliotecas utilizadas.
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "cabecalho.h"

/*
 * Função principal: responsável pela execução do programa do início ao fim.
 * Entrada: argumentos passados pelos prompt de comando.
 * Saída:
 * - EXIT_SUCESS: finalizado corretamente.
 * - Outros valors: ocorrência de erros na execução.
 */
int main(int argc, char *argv[])
{
    inicializa();                                // Inicializa variáveis.
    glutInit(&argc, argv);                       // Inicicializa com os argumentos passados no prompt de comando.
    glutInitWindowSize(width, height);           // Define o tamanho da janela em pixels.
    glutInitWindowPosition(550, 250);            // Define a posição do canto superior esquerda da janela.
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Descreve as configurações da janela (cores suportadas e suas características).
    glutCreateWindow("Relogio2D");               // Cria a janela e inseri um título.

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Seleciona a cor de fundo para limpeza da tela (R, G, B, A).

    /*
     * Rotinas callback:
     *  Se ocorrer um evento de sistema devido a interação com a janela criada
     *  aciona uma dessas rotinas, executando suas funções internas.
     */
    glutReshapeFunc(resize);  // Executa o procedimento resize.
    glutDisplayFunc(display); // Executa o procedimento display.
    glutKeyboardFunc(key);    // Executa o procedimento key.
    glutIdleFunc(idle);       // Executa o procedimento idle.

    glutMainLoop(); // Mantém o programa executando em loop, aguardando a ocorrência de novos eventos com a janela.

    return EXIT_SUCCESS;
}

// Funções/Procedimentos das rotinas callback.

/*
 * Função responsável por adaptar a janela de visualização (Viewport) e os elementos contidos na janela (Projeção),
 * caso ocorra um evento de redimensionamento de janela.
 * Entrada:
 *  - w: nova largura.
 *  - h: nova altura.
 */
static void resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, width, height); // Porta de visualização, onde será feitos os desenhos dos elementos.
    glMatrixMode(GL_PROJECTION);     // Inicializa os valores de visualização.
    glLoadIdentity();                // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    // Se ocorrer de altura ser 0, altera é pelo menos 1.
    if (height == 0)
        height = 1;

    // Difine o limites para as coordenadas da janela (RANGE em 2D).
    if (width <= height)
        gluOrtho2D(-win, win, -win * height / width, win * height / width);
    else
        gluOrtho2D(-win * width / height, win * width / height, -win, win);
}

/*
 * Procedimento responsável por atualizar o display da janela.
 *  -> Mostra todos os desenhos.
 */
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transformações geométricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    draw_aro();
    draw_interno();

    glFlush(); // Faz os comandos não executados serem executados.
}

/*
 * Procedimento responsável por executar instruções caso ocorra o pressionamento
 * de teclas na janela exibida.
 * Entrada: uma tecla digitada.
 * - "ESC" ou "q": fecha o programa.
 * - "o": volta o programa como original.
 * Saída: Executa uma instrução.
 */
static void key(unsigned char letra, int x, int y)
{
    switch (letra)
    {
    case 27:
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'o':
    case 'O':
        segundos = minutos = horas = 0;
        rotSec = rotMin = rotHora = 0;
        break;
    default:
        break;
    }

    glutPostRedisplay(); // Atualiza o display a cada evento do teclado.
}

/*
 * Rotina que executa instruções enquanto a janela estiver aberta (roda em segundo-plano).
 * Objetivo:
 * - fazer contagem de segundos, horas e minutos.
 * - aumentar o ângulo de rotação para os ponteiros, variando com o passar do tempo.
 */
static void idle()
{
    Sleep(1000); // Pausa de 1 segundo.
    segundos++;
    rotSec -= 6;
    if (segundos == 60)
    {
        segundos = 0;
        rotSec = 0;
        minutos++;
        rotMin -= 6;
    }
    if (minutos == 60)
    {
        minutos = 0;
        horas++;
        rotHora -= 6;
    }

    printf("\t(HH:MM:SS) = (%d:%d:%d)\n", horas, minutos, segundos);

    glutPostRedisplay();
}

// Funções/Procedimentos.

/*
 * Inicialização das variáveis globais.
 */
void inicializa()
{
    width = 400;
    height = 400;
    raio = 85;
    segundos = minutos = segundos = 0;
    rotHora = rotMin = rotSec = 0;
}

/*
 * Rotina para desenhar o aro do relógio.
 * - Desenha os pontinhas que representa os valores de (0 a 60).
 */
void draw_aro()
{
    int i;
    float radiano, angulo = 0, aumento = 6;

    glColor3f(1, 1, 1); // Cor Branco.
    glLineWidth(2);     // Tamanho dos métricas.
    glBegin(GL_LINES);
    for (i = 0; i < 60; i++)
    {
        radiano = angulo * (PI / 180);
        glVertex2f(raio * cos(radiano), raio * sin(radiano));

        if (i % 5 == 0) // Índices multiplos de 5 são maiores.
            glVertex2f((raio - 9) * cos(radiano), (raio - 9) * sin(radiano));
        else
            glVertex2f((raio - 3) * cos(radiano), (raio - 3) * sin(radiano));
        angulo += aumento;
    }
    glEnd();
}

/*
 * Rotina para desenhar os componentes internos do relógio.
 * - Ponteiros.
 * - Eixo central.
 */
void draw_interno()
{
    /* Ponteiro das horas. */
    glColor3f(1, 1, 0); // Cor Amarelo.
    glLineWidth(5);     // Tamanho de linha maior.
    glLoadIdentity();
    glRotatef(rotHora, 0, 0, 1); // Rotaciona ponteiro dos segundos.
    draw_ponteiros(raio / 2);    // Ponteiro das horas.

    /* Ponteiro das minutos. */
    glLoadIdentity();
    glRotatef(rotMin, 0, 0, 1); // Rotaciona ponteiro dos segundos.
    draw_ponteiros(raio / 1.5); // Ponteiro dos minutos.

    /* Ponteiro das segundos. */
    glColor3f(1, 0, 0); // Cor vermelho.
    glLineWidth(1);     // Tamanho de linha menor.
    glLoadIdentity();
    glRotatef(rotSec, 0, 0, 1); // Rotaciona ponteiro dos segundos.
    draw_ponteiros(raio / 1.2); // Ponteiro dos segundos.

    /* Desenhando eixo central. */
    glColor3f(1, 1, 0); // Cor Amarelo.
    glLoadIdentity();
    draw_circle(raio / 17); // Eixo dos ponteiros.
}

/*
 * Rotina para desenhar os ponteiros em cima do eixo y.
 * Entrada: Tamanho do ponteiro.
 * Saída: desenha um ponteiro.
 */
void draw_ponteiros(float tam)
{
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, tam);
    glEnd();
}

/*
 * Primitiva que desenha um círculo pintado no centro dos eixos de coordenadas.
 * Entrada: o tamanho do raio da circunferência.
 * Saída: desenha um círculo.
 */
void draw_circle(int r)
{
    int i;
    float radiano, angulo = 0, aumento = 6;

    glBegin(GL_POLYGON);
    for (i = 0; i < 60; i++)
    {
        radiano = angulo * (PI / 180);
        glVertex2f(r * cos(radiano), r * sin(radiano));
        angulo += aumento;
    }
    glEnd();
}
