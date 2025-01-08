#include "main.h"
#include "minimax.h"


void copiarTauler(char copia[N][N],char tauler[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            copia[i][j]=tauler[i][j];
        }
    }
}

int calculaColumna(char tauler[N][N], int fill_index){ //quina columna està lliure segons fills[·]
    fill_index=fill_index+1; //igualem index de fills amb el numero de la columna
    int col=0;
    for(int j=0;j<N;j++){
        if(tauler[N-1][j]==0){
            col++;  //li sumem 1 si la columna està buida
            if(col==fill_index){
                return j;  //parem quan la n-essima fila lliure és igual a la posicio de fills[]
            }
        }
    }
    return col;
}

int calculaFila(char tauler[N][N], int col){
    for(int i=0;i<N;i++){
        if(tauler[i][col]==0){
            return i;
        }
    }
    return -1;
}

void aplicarTirada(char tauler[N][N], int fila, int col, int nivell){
    if(nivell%2==0){ //nivell és parell, juga humà
        tauler[fila][col]=1;
    }
    else{ //nivell és senar, juga ordinador
        tauler[fila][col]=2;
    }
}

int calcularNumFills(char tauler[N][N]){
    int numFills=0;
    for(int j=0;j<N;j++){
        if(tauler[N-1][j]==0){
            numFills++;
        }
    }
    return numFills;
}

///calculs funcio heuristica
int fitxesSeguidesFila(char tauler [N][N], int numJugador){
    for(int i=0;i<N;i++){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador && tauler[i][j+1]==0 && tauler[i][j+2]==numJugador){
                if(tauler[i][j+3]==numJugador){
                    return 10000;  //fitxa+espai+fitxa+fitxa. li donem el mateix valor que tenir-ne tres seguides
                }
                else
                    return 500; //fitxa+espai+fitxa. Una mica pitjor que tenir-ne dues seguides
            }
            else if(tauler[i][j]==numJugador && tauler[i][j+1]==numJugador){
                if(tauler[i][j+2]==numJugador){
                    return 10000; //n'hi ha tres seguits
                }
                if(tauler[i][j+2]==0 && tauler[i][j+3]==numJugador){
                    return 10000; //fitxa+fitxa+espai+fitxa. mateix valor que tres seguides
                }
                else
                    return 1000; //n'hi ha dos seguits
            }
            else  //no n'hi ha dos de seguits
                return 0;
        }
    }
    return 0;
}

int fitxesSeguidesColumna(char tauler [N][N], int numJugador){
    for(int j=0;j<N;j++){
        for(int i=0;i<N-3;i++){
            if(tauler[i][j]==numJugador && tauler[i+1][j]==0 && tauler[i+2][j]==numJugador){
                if(tauler[i+3][j]==numJugador){
                    return 10000;  //fitxa+espai+fitxa+fitxa. li donem el mateix valor que tenir-ne tres seguides
                }
                else
                    return 500; //fitxa+espai+fitxa. Una mica pitjor que tenir-ne dues seguides
            }
            else if(tauler[i][j]==numJugador && tauler[i+1][j]==numJugador){
                if(tauler[i+2][j]==numJugador){
                    return 10000; //n'hi ha tres seguits
                }
                if(tauler[i+2][j]==0 && tauler[i+3][j]==numJugador){
                    return 10000; //fitxa+fitxa+espai+fitxa. mateix valor que tres seguides
                }
                else
                    return 1000; //n'hi ha dos seguits
            }
            else{
                return 0; //no n'hi ha dos de seguits
            }
        }
    }
    return 0;
}

int fitxesSeguidesDiagonalAscendent(char tauler[N][N], int numJugador){
     for(int i=0;i<N-3;i++){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador && tauler[i+1][j+1]==0 && tauler[i+2][j+2]==numJugador){
                if(tauler[i+3][j+3]==numJugador){
                    return 10000;  //fitxa+espai+fitxa+fitxa. li donem el mateix valor que tenir-ne tres seguides
                }
                else
                    return 500; //fitxa+espai+fitxa. Una mica pitjor que tenir-ne dues seguides
            }
            else if(tauler[i][j]==numJugador && tauler[i+1][j+1]==numJugador){
                if(tauler[i+2][j+2]==numJugador){
                    return 10000; //n'hi ha tres seguits
                }
                else if(tauler[i+2][j+2]==0 && tauler[i+3][j+3]==numJugador){
                    return 10000; //fitxa+fitxa+espai+fitxa. mateix valor que tres seguides
                }
                else
                    return 1000;  //n'hi ha dos seguits
            }
            else
                return 0; //no n'hi ha dos de seguits
        }
    }
    return 0;
}

int fitxesSeguidesDiagonalDescendent(char tauler[N][N], int numJugador){
     for(int i=N-1;i>2;i--){
        for(int j=0;j<N-3;j++){
            if(tauler[i][j]==numJugador && tauler[i-1][j+1]==0 && tauler[i-2][j+2]==numJugador){
                if(tauler[i-3][j+3]==numJugador){
                    return 10000;  //fitxa+espai+fitxa+fitxa. li donem el mateix valor que tenir-ne tres seguides
                }
                else
                    return 500; //fitxa+espai+fitxa. Una mica pitjor que tenir-ne dues seguides
            }
            else if(tauler[i][j]==numJugador && tauler[i-1][j+1]==numJugador){
                if(tauler[i-2][j+2]==numJugador){
                   return 10000; //n'hi ha tres seguits
                }
                else if(tauler[i-2][j+2]==0 && tauler[i-3][j+3]==numJugador){
                    return 10000; //fitxa+fitxa+espai+fitxa. mateix valor que tres seguides
                }
                else
                    return 1000; //n'hi ha dos seguits
            }
            else
                return 0; //no n'hi ha dos de seguits
        }
    }
    return 0;
}

int bloqueja4enRatllaColumna(char tauler[N][N], int numJugador, int numContrincant){
    int l=0;
    int h=0;
    for(int j=0;j<N;j++){
        for(int i=0;i<N-3;i++){
            for(int k=0;k<4;k++){
                if(tauler[i+k][j]==numContrincant){
                    l++;
                }
                else if(tauler[i+k][j]==numJugador){
                    h++;
                }
            }
            if(l==3 && h==1){
                return 1000000;
            }
        }
     }
     return 0;
}

int bloqueja4enRatllaFila(char tauler[N][N], int numJugador, int numContrincant){
    for(int i=0;i<N;i++){
        for(int j=0;j<N-3;j++){
            int l=0;
            int h=0;
            for(int k=0;k<4;k++){
                if(tauler[i][j+k]==numContrincant){
                    l++;
                }
                else if(tauler[i][j+k]==numJugador){
                    h++;
                }
            }
            if(l==3 && h==1){
                return 100000;
            }
        }
     }
     return 0;
}

int bloqueja4enRatllaDiagonalAscendent(char tauler[N][N], int numJugador, int numContrincant){
    for(int i=0;i<N-3;i++){
        for(int j=0;j<N-3;j++){
            int l=0;
            int h=0;
            for(int k=0;k<4;k++){
                if(tauler[i+k][j+k]==numContrincant){
                    l++;
                }
                else if(tauler[i+k][j+k]==numJugador){
                    h++;
                }
            }
            if(l==3 && h==1){
                return 100000;
            }
        }
     }
     return 0;
}

int bloqueja4enRatllaDiagonalDescendent(char tauler[N][N], int numJugador, int numContrincant){
    for(int i=N-1;i>2;i--){
        for(int j=0;j<N-3;j++){
            int l=0;
            int h=0;
            for(int k=0;k<4;k++){
                if(tauler[i-k][j+k]==numContrincant){
                    l++;
                }
                else if(tauler[i-k][j+k]==numJugador){
                    h++;
                }
            }
            if(l==3 && h==1){
                return 100000;
            }
        }
     }
     return 0;
}

///

double funcioHeuristica(char tauler[N][N]){

    int bones; //situacions favorables per la màquina, com més gran, més bona la situació
    bones=bloqueja4enRatllaFila(tauler,2,1)+
    bloqueja4enRatllaColumna(tauler,2,1)+
    bloqueja4enRatllaDiagonalAscendent(tauler,2,1)+
    bloqueja4enRatllaDiagonalDescendent(tauler,2,1)+
    fitxesSeguidesColumna(tauler,2)+
    fitxesSeguidesFila(tauler,2)+
    fitxesSeguidesDiagonalAscendent(tauler,2)+
    fitxesSeguidesDiagonalDescendent(tauler,2);

    double dolentes;  //situacions favorables pel jugador, la jugada de la maquina és més dolenta si li dona aventatge al jugador
    dolentes=bloqueja4enRatllaFila(tauler,1,2)+
    bloqueja4enRatllaColumna(tauler,1,2)+
    bloqueja4enRatllaDiagonalAscendent(tauler,1,2)+
    bloqueja4enRatllaDiagonalDescendent(tauler,1,2)+
    fitxesSeguidesColumna(tauler,1)+
    fitxesSeguidesFila(tauler,1)+
    fitxesSeguidesDiagonalAscendent(tauler,1)+
    fitxesSeguidesDiagonalDescendent(tauler,1);

    double valor=bones-dolentes;
    return valor;
}

Node *crearNode(Node *pare, int fill_index, int nivell){
    Node *p=malloc(sizeof(Node));
    copiarTauler(p->tauler,pare->tauler);
    int col=calculaColumna(p->tauler,fill_index);
    int fila=calculaFila(p->tauler,col);
    aplicarTirada(p->tauler,fila,col, nivell);

    int guanyador;
    if(nivell%2==0){
        guanyador=comprovarGuanyador(p->tauler,1);
    }
    else
        guanyador=comprovarGuanyador(p->tauler,2);

    if (guanyador==0 && nivell<NIVELLS){  //no guanya ningú i no passa de NIVELLS
        p->n_fills=calcularNumFills(p->tauler);
        p->fills=malloc(p->n_fills*sizeof(Node *));
    }
    else{//node fulla
        p->n_fills=0;
        p->fills=NULL;
        if(guanyador==1){  //Algú ha guanyat
            if(nivell%2==0){
                p->valor=-900000000;
            }
            else{
                p->valor=900000000;
            }
        }
        else
            p->valor=funcioHeuristica(p->tauler);
    }
    return p;
}

void crearArbreRecursiva(Node *pare, int nivell){
    for(int i=0;i<pare->n_fills;i++){
        pare->fills[i]=crearNode(pare, i, nivell+1); //crea tants nodes com n_fills
        crearArbreRecursiva(pare->fills[i], nivell+1);  //crea nodes a cada node creat
    }
}

void minimax(Node *node, int nivell){
    for(int i=0;i<node->n_fills;i++) {
        minimax(node->fills[i],nivell+1);
        node->valor=node->fills[0]->valor;  //li dono el valor del primer fill fulla
    }
    if(nivell%2==1){ //és la tirada de l'humà i ha de ser minim
                     //el pare esta en un nivell senar, la variable nivell es del pare perque esta fora del "for" ja
        for(int i=0; i<node->n_fills;i++){
            node->valor= MIN(node->valor,node->fills[i]->valor);
        }
    }
    else if(nivell%2==0){  //tirada de la màquina i ha de ser màxim
        for(int i=1; i<node->n_fills; i++){
            node->valor= MAX(node->valor,node->fills[i]->valor);
        }
    }
}

void destruirArbre(Node *node, int nivell){
    for(int i=0;i<node->n_fills;i++) {
        destruirArbre(node->fills[i],nivell+1);
        if(i==node->n_fills-1){
            free(node->fills);
        }
    }
    free(node);
}

int decidirColumna(Node *arrel){
    for(int i=0; i<arrel->n_fills;i++){
        if(arrel->valor==arrel->fills[i]->valor){
            return calculaColumna(arrel->tauler,i);
        }
    }
    return 0;
}

int columnaOrdinador(char taulerInici[N][N]){
    Node *arrel=malloc(sizeof(Node));
    copiarTauler(arrel->tauler, taulerInici);  //fa la copia al tauler de l'arrel directament (els taulers son apuntadors, es modifica directament)
    arrel->n_fills=calcularNumFills(arrel->tauler);
    arrel->fills=malloc(arrel->n_fills * sizeof(Node *));
    crearArbreRecursiva(arrel,0);
    minimax(arrel,0);
    int r=decidirColumna(arrel);
    destruirArbre(arrel,0);
    return r+1;
}

