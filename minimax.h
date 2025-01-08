#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#define NIVELLS 6
#define MAX(A,B)  ((A)>(B)?(A):(B))
#define MIN(A,B)  ((A)>(B)?(B):(A))


typedef struct node{
    struct node* *fills;
    int n_fills;
    char tauler[N][N];
    double valor;
}Node;

void copiarTauler(char copia[N][N],char tauler[N][N]);
int calculaColumna(char tauler[N][N], int fill_index);
int calculaFila(char tauler[N][N], int col);
void aplicarTirada(char tauler[N][N], int fila, int col, int nivell);
int calcularNumFills(char tauler[N][N]);

int fitxesSeguidesFila(char tauler [N][N], int numJugador);
int fitxesSeguidesColumna(char tauler [N][N], int numJugador);
int fitxesSeguidesDiagonalAscendent(char tauler[N][N], int numJugador);
int fitxesSeguidesDiagonalDescendent(char tauler[N][N], int numJugador);

int bloqueja4enRatllaFila(char tauler[N][N], int numJugador, int numOponent);
int bloqueja4enRatllaColumna(char tauler[N][N], int numJugador, int numOponent);
int guanyarFuncioHeuristica(char tauler[N][N], int numJugador);

double funcioHeuristica(char tauler[N][N]);

Node *crearNode(Node *pare, int fill_index, int nivell);
void crearArbreRecursiva(Node *pare, int nivell);
void minimax(Node *node, int nivell);

void destruirArbre(Node *node, int nivell);
int decidirColumna(Node *arrel);
int columnaOrdinador(char taulerInici[N][N]);

#endif // MINIMAX_H_INCLUDED
