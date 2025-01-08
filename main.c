#include "main.h"
#include "minimax.h"

void SetColor(int ForgC){
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


void imprimirTauler(char tauler [N][N]){
    printf(" ------------------------------------------------\n");
    for(int i=N-1; i>=0; i--){//Bucle per fer files
            printf("|");
        for(int j=0; j<N; j++){
            if(tauler[i][j]==0){
                printf("     |");
            }
            else if(tauler[i][j]==1){
                printf("  ");
                SetColor(17);
                printf("o");
                SetColor(15);
                printf("  |");
            }
            else if(tauler[i][j]==2){
                printf("  ");
                SetColor(4);
                printf("x");
                SetColor(15);
                printf("  |");
            }
        }
        printf("\n ------------------------------------------------\n");
        }
}

void nomJugador(char Jugador[10]){
    printf("Nom jugador:");
    scanf("%s",Jugador);
}

int columnaPlena(char tauler [N][N], int num_col){
    while(tauler[N-1][num_col-1]!=0){
        printf("La columna esta plena. Tria una columna diferent de %d\n",num_col);
        scanf("%d",&num_col);
        return num_col;
    }
    return num_col;
}
int taulerPle(char tauler[N][N]){
    int k=0;
    for(int i=0; i<N; i++){
        if(tauler[N-1][i]!=0){
            k++;
        }
    }
    if(k==N){
        printf("S'ha omplert el tauler\n");
        return 1;
    }
    else{
        return 0;
    }
}

int afegirFitxa(char tauler[N][N], int posicio_col, int numJugador){
    for(int i=0;i<N;i++){
        if(tauler[i][posicio_col]==0){
            tauler[i][posicio_col]=numJugador;
            return 0;
        }
    }
    return 0;
}

int columnaJugador(){
    int num_col;
    printf("En quina colummna vols co·locar la fitxa?\n");
    scanf("%d",&num_col);
    while(num_col<1 || num_col>N){
        printf("No existeix aquesta columna en el joc.\n Tria una columna entre 1 i 8:\n");
        scanf("%d",&num_col);
    }
    return num_col;
}

void tirarjugada(char tauler[N][N], int numJugador, int num_col){
    int numero_col, posicio_col;
    numero_col=columnaPlena(tauler, num_col);
    posicio_col=numero_col-1;
    afegirFitxa(tauler, posicio_col, numJugador);
    imprimirTauler(tauler);
}

int comprovarFila(char tauler [N][N], int numJugador){
    for(int i=0;i<N;i++){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador &&
               tauler[i][j+1]==numJugador &&
               tauler[i][j+2]==numJugador&&
               tauler[i][j+3]==numJugador){
                    return 1;
            }
        }
    }
    return 0;
}

int comprovarColuma(char tauler [N][N], int numJugador){
    for(int j=0;j<N;j++){
        for(int i=0;i<N-3;i++){
            if(tauler[i][j]==numJugador &&
               tauler[i+1][j]==numJugador &&
               tauler[i+2][j]==numJugador &&
               tauler[i+3][j]==numJugador){
                    return 1;
            }
        }
    }
    return 0;
}

int comprovarDiagonal(char tauler[N][N], int numJugador){
    //diagonal ascendent
    for(int i=0;i<N-3;i++){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador &&
               tauler[i+1][j+1]==numJugador &&
               tauler[i+2][j+2]==numJugador &&
               tauler[i+3][j+3]==numJugador){
                   return 1;
               }
        }
    }
    //diagonal descendent
    for(int i=N-1;i>2;i--){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador &&
               tauler[i-1][j+1]==numJugador &&
               tauler[i-2][j+2]==numJugador &&
               tauler[i-3][j+3]==numJugador){
                   return 1;
               }
        }
    }
    return 0;
}

int comprovarGuanyador(char tauler[N][N], int numJugador ){
    if(comprovarColuma(tauler,numJugador)==1 ||
       comprovarFila(tauler,numJugador)==1 ||
       comprovarDiagonal(tauler,numJugador)==1){
        return 1;
    }
    return 0;
}

void taulerInicial(char tauler[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            tauler[i][j]=0;
        }
    }
}

int main(){

    char nom_jugador[10];
    nomJugador(nom_jugador);

    char tauler[N][N];
    taulerInicial(tauler);
    imprimirTauler(tauler);

    for(int i=0; i<N*N; i++){
        ///TIRADA HUMÀ
        printf("Torn de %s:\n",nom_jugador);
        tirarjugada(tauler,1,columnaJugador());
        if(comprovarGuanyador(tauler,1)==1){
            printf("Ha guanyat %s\n",nom_jugador);
            return 0;
        }
        if(taulerPle(tauler)==1){
            return 0;
        }
        ///TIRADA ORDINADOR
        tirarjugada(tauler,2,columnaOrdinador(tauler)); //el que em retorna el minimax
        if(comprovarGuanyador(tauler,2)==1){
            printf("Ha guanyat l'ordinador\n");
            return 0;
        }
        if(taulerPle(tauler)==1){
            return 0;
        }
    }
    return 0;
}
