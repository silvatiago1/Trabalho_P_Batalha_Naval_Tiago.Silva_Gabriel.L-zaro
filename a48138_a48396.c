/**
 * @autores:
 * Nome: Gabriel Lázaro     Número de Aluno: 48396
 * Nome: Tiago Silva        Número de Aluno: 48138
 **/ 

#include <stdio.h>

#define B 6
#define N 8
#define M 8

/**Representa uma coordenada*/
typedef struct
{
    int x;
    int y;
} Position;

/**Associa cada coordenada do barco com um estado**/
typedef struct
{
    int afloat;        //0 indica que está afundada, 1 indica que não
    Position pos;      //Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
    int afloat;        //Posições que ainda não foram afundadas
    int tSize;         //Tamanho do tipo do barco 
    StateCoord coord[5]; //O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
    char type;         //Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
    int numBoatsAfloat; //Número de barcos não afundados
    int numBoats; //Número de barcos que foram colocados
    Boat boats[B]; //Array de barcos. Cada barco é do tipo Boat.
    char board[N][M]; //Array que contém a informação de cada posição do tabuleiro
} Board;


/**
 * NOTA IMPORTANTE: 
 * Não pode alterar nenhuma das assinaturas das funções abaixo. 
 * Este ficheiro tem de ser considerado em conjunção com o enunciado do TP2.
 **/


/**
 * Function: init_board
 * 
 * Inicializa um Board.
 * 
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * b: apontador para o Board que vai ser inicializado
 * 
 **/
void init_board(int n, int m, Board *b)
{
    b->numBoatsAfloat = 0;
    b->numBoats = 0;

    //Inicializa o array board
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        { 
            b->board[i][j] = ' ';
        }
    }
}

/**
 * Function: print_board
 * 
 * Mostra no ecrã o estado atual do tabuleiro.
 * Se a flag é 0 (zero) não mostra os barcos, se for 1, mostra. 
 * Quando a flag é 1, para indicar a posição de cada barco, é colocada em todas
 * as posições do barco a letra que representa o seu tipo.
 * 
 * n: número de linhas do tabuleiro
 * m: número de colunas do tabuleiro
 * board: estado do tabuleiro
 * flag: indicador do modo de visualização do tabuleiro -- se for 0 (zero) não 
 *       mostra os barcos; se for diferente de 0 (zero) mostra.
 */

void print_board(int n, int m, char board[n][m], int flag)
{
    printf("+");
    for (int j = 0; j < n; j++)
    {
        printf("---+");
    }
    printf("\n");

    for (int i = 0; i < m; i++)
    {
        printf("|");
        if (flag) //Mostra tudo
        {
            for (int j = 0; j < n; j++)
            {
                printf(" %c |", board[i][j]);
            }
            printf("\n");
        }
        else // Esconde os barcos
        {
            for (int k = 0; k < n; k++)
            {
                printf("    |");
            }
            printf("\n");
        }

        printf("+");
        for (int j = 0; j < n; j++)
        {
            printf("---+");
        }
        printf("\n");
    }
}


/** 
 * Function: typeToSize
 * 
 * Dado o tipo do barco devolve o seu tamanho.
 * 
 * type: tipo do barco ('P', 'N', 'C', ou 'S')
 * 
 * return
 *  -1 se o tipo de barco for inválido
 *  caso contrário, devolve o tamanho do barco
 **/
int typeToSize(char type)
{
    int tSize;
    switch (type)
    {
    case 'P':
        tSize = 5;
        break;
    case 'N':
        tSize = 4;
        break;
    case 'C':
        tSize = 3;
        break;
    case 'S':
        tSize = 2;
        break;
    default:
        tSize = -1;
        break;
    }
    return tSize;
}

/**
 * Function: init_boat
 * 
 * Dado um apontador para um barco, o tipo, a posição inicial e a direcção, 
 * inicializa o barco com todas as sua posições, tamanho e tipo. 
 * Por exemplo, se o tipo do barco é 'C' (contratorpedeiro),
 * a posição inicial (1,1), e a direcção 'H', então o barco fica inicializado 
 * com os seguintes valores
 * 
 * afloat = 3;
 * tSize = 3;
 * coord = [(1,(1,1)),(1,(1,2)),(1,(1,3))]; Onde (s,(x,y)) representa um elemento do tipo StateCoord
 * type = 'C';
 * 
 * b: barco que vai ser inicializado
 * type: tipo do barco
 * xy: posição inicial do barco
 * dir: direcção do barco
 * 
 **/
void init_boat(Boat *b, char type, Position xy, char dir)
{
    switch (type)
    {
    case 'P':
        b->afloat=5;
        if(dir == 'H')
        {
            for(int i=0;i<5;i++)
            {
                b->coord->pos.x=xy.x;
                printf("%d",b->coord->pos.x=xy.x);
                b->coord->pos.y=xy.y;
                printf("%d\n",b->coord->pos.x=xy.y);
                b->coord->afloat=1;
                xy.y++;
            }
        }
        else
        {
            for(int i=0;i<5;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.x++;
            }
        }
        break;
    case 'N':
        b->afloat=4;
        if(dir == 'H')
        {
            for(int i=0;i<4;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.y++;
            }
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.x++;
            }
        }
        break;
    case 'C':
        b->afloat=3;
        if(dir == 'H')
        {
            for(int i=0;i<3;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.y++;
            }
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.x++;
            }
        }
        break;
    case 'S':
        b->afloat=2;
        if(dir == 'H')
        {
            for(int i=0;i<2;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.y++;
            }
        }
        else
        {
            for(int i=0;i<2;i++)
            {
                b->coord->pos.x=xy.x;
                b->coord->pos.y=xy.y;
                b->coord->afloat=1;
                xy.x++;
            }
        }
        break;
    }
}


/**
 * Function: check_free
 * 
 * Verifica se estão livres todas as posições que serão ocupadas por um 
 * barco no tabuleiro.
 * 
 * n: dimensão x do tabuleiro
 * m: dimensão y do tabuleiro
 * boat: barco a colocar no tabuleiro
 * board: estado atual do tabuleiro
 * 
 * returns:
 *  1 se todas as posições estão livres
 *  0 caso contrário
 * 
 **/
int check_free(int n, int m, Boat *boat, char board[n][m])
{
    int check;
    printf("oi%d\n", boat->coord->pos.x);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(board[i][j] == ' ' && i==boat->coord->pos.x && j==boat->coord->pos.y)
            {
                check=1;
            }
            else
            {
                check=0;
            }
        }
    }
    return check;
}

/** 
 * Function: place_boat
 * 
 * Cria e coloca, se tal for possível, um barco no tabuleiro.
 * 
 * x1: coordenada x inicial do barco  
 * y1: coordenada y inicial do barco  
 * dir: dirrecção do barco ('H' ou 'V')
 * type: o tipo de barco 
 * board: estado atual do tabuleiro
 *
 * returns: 
 * 0 se o barco for colocado com sucesso.
 * -1 se alguma das posições já está ocupada.
 * -2 se as coordenadas forem inválidas.
 * -3 se a direcção for inválida.
 * -4 se o tipo de barco for inválido.
 **/
int place_boat(int x1, int y1, int dir, char type, Board *board)
{
    int typesize=typeToSize(type);
    int ret;
    int numboat=board->numBoats;

    int check=check_free(N,M,board->boats,board->board);
    printf("%i",check);
    
    if(check==1)
    {
        if(dir==0)
        {
            for (int i = x1; i<x1+1; i++)
            {
                for (int j = y1; j < y1+typesize; j++)
                {
                    board->board[i][j]=type;
                }
            }
        }
        else
        {    
            for (int i = y1; i<y1+1; i++)
            {
                for (int j = x1; j < x1+typesize; j++)
                {
                    board->board[j][i]=type;
                }
            }
        }
        ret=1;
    }
    else
    {
        ret=0;
        printf("Essa posição já está ocupada,esolha outra!\n");
    }

    return ret;
}

/**
 * Function: check_sink
 * 
 * Verifica se ao atacar a posição (x,y) algum barco é afundado. 
 * 
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 * 
 * returns:
 *   'F' se não for afundado nenhum barco.
 *   Se afundar um barco devolve a letra que representa o seu tipo: 'P', 'N', 'C' ou 'S' 
 *   'I' se a coordenada for inválida.
 * 
 **/
char check_sink(int x, int y, Board *board)
{
    //Implementar

    return 'O';
}

/**
 * Function: target
 * 
 * Ataca a coordenada (x,y) no tabuleiro.
 * Se a coordenada (x,y) é parte de um barco, então coloca um '*' nessa 
 * posição '*'; caso contrário coloca a letra 'F' nessa posição; caso afunde 
 * um barco coloca em todas as posições desse barco a letra 'A'.
 * 
 * x: coordenada x a atacar
 * y: coordenada y a atacar
 * board: estado atual do tabuleiro
 * 
 * returns:
 *   0 se a posicao já foi atacada anteriormente
 *   1 se acerta numa coordenada de um barco mas sem o afundar
 *   -1 se nao tiver sucesso
 *   -2 se a coordenada for inválida. 
 *   caso afunde um barco, devolve o número correspondente ao tamanho do barco 
 *   que afundou (valor de 2 a 5)
 * 
 **/
int target(int x, int y, Board *board)
{
    //Implementar

    return -3;
}

//int colocaNavio()
int main(void)
{
    char dir;
    int horv;

    Board brd;
    Boat bt;
    StateCoord xy;
    init_board(N, M, &brd);
    print_board(N, M, brd.board, 1);

    printf("Qual é o tipo de barco que prentede colocar?\n");
    scanf("%c",&bt.type);

    bt.tSize = typeToSize(bt.type);

    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
    scanf(" %c", &dir);

    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
    scanf("%d", &xy.pos.x);

    if(dir=='H')
    {
        horv=0;
    }
    else
    {
        horv=1;
    }

    printf("\n\tColuna: ");
    scanf("%d", &xy.pos.y);

    printf("%d\n",xy.pos.y);

    init_boat(&brd.boats[0], bt.type,xy.pos, dir);

    check_free(N, M, &brd.boats[0], brd.board);

    place_boat(xy.pos.x,xy.pos.y,horv,brd.boats[0].type,&brd);

    print_board(N, M, brd.board, 1);

    /**Exemplo de uso da print_board e da place_boat**/
    /**Precisa de as implementar primeiro**/
    //print_board(N, M, brd.board, 0);
    //place_boat(1,3, 'H', 'P', &brd);
    return 0;
}