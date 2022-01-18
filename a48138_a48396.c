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
    int afloat;   //0 indica que está afundada, 1 indica que não
    Position pos; //Coordenada
} StateCoord;

/**Representa um barco**/
typedef struct
{
    int afloat;          //Posições que ainda não foram afundadas
    int tSize;           //Tamanho do tipo do barco
    StateCoord coord[5]; //O barco maior tem 5 coordenadas, usando o tSize garantimos que acedemos apenas às existentes
    char type;           //Caracter que representa o tipo do barco
} Boat;

/**Representa um tabuleiro**/
typedef struct
{
    int numBoatsAfloat; //Número de barcos não afundados
    int numBoats;       //Número de barcos que foram colocados
    Boat boats[B];      //Array de barcos. Cada barco é do tipo Boat.
    char board[N][M];   //Array que contém a informação de cada posição do tabuleiro
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
    b->afloat = typeToSize(type);
    b->tSize = b->afloat;
    b->type = type;
    for (int i = 0; i < b->tSize; i++)
    {
        if (dir == 'H')
        {
            b->coord[i].pos.x = xy.x;
            b->coord[i].pos.y = xy.y + i;
        }
        else
        {
            b->coord[i].pos.x = xy.x + i;
            b->coord[i].pos.y = xy.y;
        }
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
    int check = 1;
    for (int i = 0; i < boat->tSize; i++)
    {
        if (board[boat->coord[i].pos.x][boat->coord[i].pos.y] != ' ')
        {
            check = 0;
            break;
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
    int typesize = typeToSize(type);
    int ret, cont;

    Position temp = {x1, y1};

    Boat bat;
    init_boat(&bat, type, temp, dir);

    if (x1 < N && y1 < M && x1 >= 0 && y1 >= 0)
    {
        int check = check_free(N, M, &bat, board->board);
        if (typesize != -1)
        {
            if (check == 1)
            {
                if (dir == 'H')
                {
                    cont = 1;
                    if (y1 + typesize < N)
                    {
                        for (int j = y1; j < y1 + typesize; j++)
                        {
                            board->board[x1][j] = type;
                        }
                        ret = 0;
                        board->numBoatsAfloat++;
                        board->numBoats++;
                    }
                    else
                    {
                        ret = -2;
                        printf("Coordenadas inválidas.\n");
                    }
                }
                if(dir == 'V')
                {
                    cont = 1;
                    if (x1 + typesize < M)
                    {
                        for (int j = x1; j < x1 + typesize; j++)
                        {
                            board->board[j][y1] = type;
                        }
                        ret = 0;
                        board->numBoatsAfloat++;
                        board->numBoats++;
                    }
                    else
                    {
                        ret = -2;
                        printf("Coordenadas inválidas.\n");
                    }
                }
            }
            else
            {
                ret = -1;
                printf("Essa posição já está ocupada,esolha outra!\n");
            }
        }
        else
        {
            ret = -4;
        }
    }
    else
    {
        ret = -2;
        printf("Coordenadas inválidas!\n");
    }
    if (cont != 1)
    {
        printf("Direção errada\n");
        ret = -3;
    }
    return ret;
}

/**
 * Function: check_sink
 * 
 *  * Verifica se ao atacar a posição (x,y) algum barco é afundado. 
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
    char ret;
    for (int i = 0; i < board->boats->tSize; i++)
    {
        if (board->boats->coord[i].pos.x == x && board->boats->coord[i].pos.y == y && board->boats->afloat == 1)
        {
            ret = board->boats->type;
            break;
        }
        else
        {
            ret = 'F';
        }
    }
    if (x > 9 || x < 0 || y < 0 || y > 10)
    {
        ret = 'I';
    }
    return ret;
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
    int hit = -1;
    for (int i = 0; i < board->numBoatsAfloat; i++)
    {
        if (x == board->boats->coord[x].pos.x && y == board->boats->coord[y].pos.y && board->boats->coord[i].afloat == 1)
        {
            char temp = check_sink(x, y, board->board);
            if (temp == 'I')
            {
                hit = -2;
            }
            else
            {
                board->boats->coord[i].afloat = 0;
                if (temp == 'F')
                {
                    hit = 1;
                }
                else
                {
                    hit = typeToSize(board->boats->type);
                }
            }
        }
    }
    return hit;
}

//int colocaNavio()
int main(void)
{
    char dir;
    int x, y;

    Board brd;
    Boat bt;
    StateCoord xy;
    init_board(N, M, &brd);
    print_board(N, M, brd.board, 1);

    printf("Qual é o tipo de barco que prentede colocar? (P/N/C/S)\n");
    scanf("%c", &bt.type);

    bt.tSize = typeToSize(bt.type);

    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
    scanf(" %c", &dir);

    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
    scanf("%d", &xy.pos.x);

    printf("\n\tColuna: ");
    scanf("%d", &xy.pos.y);

    //init_boat(&bt, bt.type,xy.pos, dir);

    //check_free(N, M, &bt, brd.board);

    place_boat(xy.pos.x, xy.pos.y, dir, bt.type, &brd);

    print_board(N, M, brd.board, 1);

    printf("Digite a posição que pretende atacar:\n");
    printf("Linha: ");
    scanf("%d", &x);
    printf("Coluna: ");
    scanf("%d", &y);

    check_sink(x, y, &brd);

    print_board(N, M, brd.board, 1);

    /**Exemplo de uso da print_board e da place_boat**/
    /**Precisa de as implementar primeiro**/
    //print_board(N, M, brd.board, 0);
    //place_boat(1,3, 'H', 'P', &brd);
    return 0;
}