#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <windows.h>

#define N 8
void SetColor(int ForgC);
void imprimirTauler(char tauler [N][N]);
int afegirFitxa(char tauler[N][N], int posicio_col, int numJugador);
int taulerPle(char tauler [N][N]);
void nomJugador(char Jugador[10]);
int columnaJugador();
void tirarjugada(char tauler [N][N], int numJugador, int num_col);
int comprovarFila(char tauler [N][N], int numJugador);
int comprovarColuma(char tauler [N][N], int numJugador);
int comprovarDiagonal(char tauler[N][N], int numJugador);

int comprovarGuanyador(char tauler[N][N], int numJugador );
void taulerInicial(char tauler[N][N]);

#endif // MAIN_H_INCLUDED
