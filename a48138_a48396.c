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
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'P' || board[i][j] == 'N' || board[i][j] == 'C' || board[i][j] == 'S')
                {
                    printf("   |");
                }
                else
                {
                    printf(" %c |", board[i][j]);
                }
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
        b->coord[i].afloat = 1;
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
    int ret;

    Position temp = {x1, y1};

    Boat bat;
    init_boat(&bat, type, temp, dir);

    if (x1 < N && y1 < M && x1 >= 0 && y1 >= 0)
    {
        int check = check_free(N, M, &bat, board->board);
        if (typesize != -1)
        {
            if (dir == 'H')
            {
                if (y1 + typesize <= M) //Verificar se é < ou <=
                {
                    if (check == 1)
                    {
                        for (int j = y1; j < y1 + typesize; j++)
                        {
                            board->board[x1][j] = type;
                        }
                        /*for (int j = 0; j < board->boats[board->numBoats].tSize; j++)
                        {
                            board->boats[board->numBoats].coord[j].afloat = 1;
                        }*/
                        ret = 0;
                        board->boats[board->numBoats] = bat;
                        board->boats[board->numBoats].afloat = typesize;
                        board->numBoatsAfloat++;
                        board->numBoats++;
                    }
                    else
                    {
                        ret = -1;
                    }
                }
                else
                {
                    ret = -2;
                }
            }
            else if (dir == 'V')
            {
                if (x1 + typesize <= N)
                {
                    if (check == 1)
                    {
                        for (int j = x1; j < x1 + typesize; j++)
                        {
                            board->board[j][y1] = type;
                        }
                        /*for(int i = 0; )
                            for (int j = 0; j < board->boats[board->numBoats].tSize; j++)
                            {
                                board->boats[board->numBoats].coord[j].afloat = 1;
                            }*/
                        ret = 0;
                        board->boats[board->numBoats] = bat;
                        board->boats[board->numBoats].afloat = typesize;
                        board->numBoatsAfloat++;
                        board->numBoats++;
                    }
                    else
                    {
                        ret = -1;
                    }
                }
                else
                {
                    ret = -2;
                }
            }
            else
            {
                ret = -3;
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
    char ret = 'F';
    //printf("%d\n", board->numBoats);
    for (int i = 0; i < board->numBoats; i++)
    {
        for (int j = 0; j < board->boats[i].tSize; j++)
        {
            if (board->boats[i].coord[j].pos.x == x && board->boats[i].coord[j].pos.y == y) //&& board->boats[i].afloat == 1)
            {
                board->boats[i].coord[j].afloat = 0;
                board->boats[i].afloat--;
                if (board->boats[i].afloat == 0) //afundou
                {
                    ret = board->boats[i].type;
                    board->numBoatsAfloat--;
                    for (int k = 0; k < board->boats[i].tSize; k++)
                    {
                        board->board[board->boats[i].coord[k].pos.x][board->boats[i].coord[k].pos.y] = 'A';
                    }
                }
                break;
            }
        }
        if (ret != 'F') //se ja encontrou um faz break
        {
            break;
        }
    }
    if (x >= N || y >= M || x < 0 || y < 0)
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
    char check;
    if (board->board[x][y] != ' ')
    {
        if (board->board[x][y] == 'F' || board->board[x][y] == 'A' || board->board[x][y] == '*')
        {
            hit = 0;
        }
        else
        { //caso que acerte num barco

            board->board[x][y] = '*';
            hit = 1;
            check = check_sink(x, y, board);
            if (check != 'F' && check != 'I')
            {
                hit = typeToSize(check);
            }
        }
    }
    else
    {
        board->board[x][y] = 'F';
    }
    return hit;
}

//int colocaNavio()
int main(void)
{
    char dir;
    int x, y, fint;
    int flag = 1, player1 = 0, player2 = 0, player = 0;
    char type, leave = 'N', jogador1[15], jogador2[15];

    printf("Jogador 1, digite o seu nome:\n");
    scanf("%s", jogador1);
    printf("Jogador 2, digite o seu nome:\n");
    scanf("%s", jogador2);

    for (int turn = 0; leave == 'N'; turn++)
    {
        if (turn % 2 == 0)
        {
            player = 1;
        }
        else
        {
            player = 2;
        }

        Board brd;
        init_board(N, M, &brd);
        print_board(N, M, brd.board, flag);
        int p = 1, n = 1, c = 2, s = 2;
        if (player == 1)
        {
            printf("%s, coloque os navios:\n", jogador1);
        }
        else
        {
            printf("%s, coloque os navios:\n", jogador2);
        }

        while (brd.numBoats < 6)
        {
            printf("Ainda tem a seguinte quantidade de cada tipo de barco para colocar:\n\tPorta-aviões[P]-> %d;\n\tNavios-tanque[N]-> %d;\n\tContratorpedeiros[C]-> %d;\n\tSubmarinos[S]-> %d.\n\n", p, n, c, s);
            printf("Insira a letra inicial do barco que pretende colocar no tabuleiro:\n");
            scanf(" %c", &type);

            switch (type)
            {
            case 'P':
                if (p > 0)
                {
                    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
                    scanf(" %c", &dir);
                    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
                    scanf("%d", &x);
                    printf("\tColuna: ");
                    scanf("%d", &y);

                    fint = place_boat(x, y, dir, type, &brd);
                    print_board(N, M, brd.board, flag);

                    if (fint == 0)
                    {
                        p--;
                    }
                    else if (fint == -1)
                    {
                        printf("Colisão de barcos!\nNão pode colocar barcos por cima de barcos já existentes!!\n");
                    }
                    else if (fint == -2)
                    {
                        printf("Essa posição está fora do tabuleiro, coloque os barcos dentro do tabuleiro!\n");
                    }
                    else if (fint == -3)
                    {
                        printf("Direção inválida!\nPor favor escolha H ou V!!\n");
                    }

                    //print_board(N, M, brd.board, flag);
                }
                else
                {
                    print_board(N, M, brd.board, flag);
                    printf("Já atingiu o limite de Porta-aviões, por favor esolha outro tipo de barco para colocar!\n\n");
                }
                break;

            case 'N':
                if (n > 0)
                {
                    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
                    scanf(" %c", &dir);
                    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
                    scanf("%d", &x);
                    printf("\tColuna: ");
                    scanf("%d", &y);

                    fint = place_boat(x, y, dir, type, &brd);
                    print_board(N, M, brd.board, flag);

                    if (fint == 0)
                    {
                        n--;
                    }
                    else if (fint == -1)
                    {
                        printf("Colisão de barcos!\nNão pode colocar barcos por cima de barcos já existentes!!\n");
                    }
                    else if (fint == -2)
                    {
                        printf("Essa posição está fora do tabuleiro, coloque os barcos dentro do tabuleiro!\n");
                    }
                    else if (fint == -3)
                    {
                        printf("Direção inválida!\nPor favor escolha H ou V!!\n");
                    }

                    //print_board(N, M, brd.board, flag);
                }
                else
                {
                    print_board(N, M, brd.board, flag);
                    printf("Já atingiu o limite de Navios-tanque, por favor esolha outro tipo de barco para colocar!\n\n");
                }
                break;

            case 'C':
                if (c > 0)
                {
                    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
                    scanf(" %c", &dir);
                    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
                    scanf("%d", &x);
                    printf("\tColuna: ");
                    scanf("%d", &y);

                    fint = place_boat(x, y, dir, type, &brd);
                    print_board(N, M, brd.board, flag);

                    if (fint == 0)
                    {
                        c--;
                    }
                    else if (fint == -1)
                    {
                        printf("Colisão de barcos!\nNão pode colocar barcos por cima de barcos já existentes!!\n");
                    }
                    else if (fint == -2)
                    {
                        printf("Essa posição está fora do tabuleiro, coloque os barcos dentro do tabuleiro!\n");
                    }
                    else if (fint == -3)
                    {
                        printf("Direção inválida!\nPor favor escolha H ou V!!\n");
                    }

                    //print_board(N, M, brd.board, flag);
                }
                else
                {
                    print_board(N, M, brd.board, flag);
                    printf("Já atingiu o limite de Contratorpedeiros, por favor escolha outro tipo de barco para colocar!\n\n");
                }
                break;

            case 'S':
                if (s > 0)
                {
                    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
                    scanf(" %c", &dir);
                    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
                    scanf("%d", &x);
                    printf("\tColuna: ");
                    scanf("%d", &y);

                    fint = place_boat(x, y, dir, type, &brd);
                    print_board(N, M, brd.board, flag);

                    if (fint == 0)
                    {
                        s--;
                    }
                    else if (fint == -1)
                    {
                        printf("Colisão de barcos!\nNão pode colocar barcos por cima de barcos já existentes!!\n");
                    }
                    else if (fint == -2)
                    {
                        printf("Essa posição está fora do tabuleiro, coloque os barcos dentro do tabuleiro!\n");
                    }
                    else if (fint == -3)
                    {
                        printf("Direção inválida!\nPor favor escolha H ou V!!\n");
                    }
                    //print_board(N, M, brd.board, flag);
                }
                else
                {
                    print_board(N, M, brd.board, flag);
                    printf("Já atingiu o limite de Submarinos, por favor esolha outro tipo de barco para colocar!\n\n");
                }
                break;

            default:
                printf("Tipo de navio inválido, por favor escolha outro tipo de navio!\n\n");
                break;
            }
        }
        printf("\n\nTodos os barcos foram colocados com sucesso!\n");
        flag = 0;

        print_board(N, M, brd.board, flag);

        if (player == 1)
        {
            printf("%s, hora de atacar!\n", jogador2);
        }
        else
        {
            printf("%s, hora de atacar!\n", jogador1);
        }

        for (int tatakae = 0; tatakae < 40 && brd.numBoatsAfloat != 0; tatakae++)
        {
            //Nota:Perguntar à professora se é para retirar 1 quando já atacamos a posição;
            printf("Digite a posição que pretende atacar:\n");
            printf("Linha: ");
            scanf("%d", &x);
            printf("Coluna: ");
            scanf("%d", &y);

            fint = target(x, y, &brd);
            print_board(N, M, brd.board, flag);
            switch (fint)
            {
            case -1:
                printf("Acertou na água!!\n");
                break;
            case -2:
                printf("Posição inválida, escolha outra!\n");
                break;
            case 0:
                printf("Essa posição já foi atacada, escolha outra!\n");
                tatakae--;
                break;
            case 1:
                printf("Atingiu um barco sem o afundar!\n");
                break;
            case 2:
                printf("Afundou um submarino!!!\n");
                break;
            case 3:
                printf("Afundou um contraturpedeiro!!!\n");
            case 4:
                printf("Afundou um navio-tanque!!!\n");
            case 5:
                printf("Afundou um porta-aviões!!!\n");
            default:

                break;
            }

            /*if(fint==-1)
            {
                printf("Acertou na água!!\n");
            }
            else if(fint==1)
            {
                printf("Atingiu um barco sem o afundar!\n");
            }
            else if(fint==2)
            {
                printf("Afundou um submarino!!!\n");
            }
            else if(fint==3)
            {
                printf("Afundou um contraturpedeiro!!!\n");
            }
            else if(fint==4)
            {
               printf("Afundou um navio-tanque!!!\n");
            }
            else if(fint==5)
            {
                printf("Afundou um porta-aviões!!!\n");
            }
            else if(fint==0)
            {
                printf("Essa posição já foi atacada, escolha outra!\n");
                tatakae--;
            }
            else if(tatakae==-2)
            {
                printf("Posição inválida, escolha outra!\n");
            }*/
            //print_board(N, M, brd.board, flag);

            if (brd.numBoatsAfloat == 0)
            {
                if (player == 1)
                {
                    printf("O %s venceu esta rodada!!!\nParabéns!\n\n", jogador2);
                    player2++;
                }
                else
                {
                    printf("O %s venceu esta rodada!!!\nParabéns!\n\n", jogador1);
                    player1++;
                }
            }
            else if (brd.numBoatsAfloat != 0 && tatakae >= 40)
            {
                if (player == 1)
                {
                    printf("O %s venceu esta rodada!!!\nParabéns!\n\n", jogador1);
                    player1++;
                }
                else
                {
                    printf("O %s venceu esta rodada!!!\nParabéns!\n\n", jogador2);
                    player2++;
                }
            }
        }
        printf("%s: %d-%d :%s\n", jogador1, player1, player2, jogador2);

        printf("Se deseja saír do jogo prima Y\n");
        scanf(" %c", &leave);

        if (leave == 'Y')
        {
            if (player1 > player2)
            {
                printf("O %s ganhou o jogo!!!\nMUITOS PARABÉNS!!!\n", jogador1);
            }
            else if (player1 < player2)
            {
                printf("O %s ganhou o jogo!!!\nMUITOS PARABÉNS!!!\n", jogador2);
            }
            else
            {
                printf("!!!EMPATE!!!\n");
            }
            printf("Resultado final:\n");
            printf("%s: %d-%d :%s\n", jogador1, player1, player2, jogador2);
        }
    }

    //StateCoord xy;
    /*init_board(N, M, &brd);
    print_board(N, M, brd.board, 1);

    printf("Qual é o tipo de barco que prentede colocar? (P/N/C/S)\n");
    scanf("%c", &type);

    //bt.tSize = typeToSize(bt.type);

    printf("Digite qual a direção do barco\n\t H-> Horizontal\n\t V-> Vertical\n");
    scanf(" %c", &dir);

    printf("Indique onde pretende colocar o seu barco:\n\tLinha: ");
    scanf("%d", &xx);

    printf("\tColuna: ");
    scanf("%d", &yy);

    //init_boat(&bt, bt.type,xy.pos, dir);

    //check_free(N, M, &bt, brd.board);

    place_boat(xx, yy, dir, type, &brd);

    print_board(N, M, brd.board, 1);

    printf("Digite a posição que pretende atacar:\n");
    printf("Linha: ");
    scanf("%d", &x);
    printf("Coluna: ");
    scanf("%d", &y);

    //check_sink(x, y, &brd);
    target(x, y, &brd);
    print_board(N, M, brd.board, 0);*/

    /**Exemplo de uso da print_board e da place_boat**/
    /**Precisa de as implementar primeiro**/
    //print_board(N, M, brd.board, 0);
    //place_boat(1,3, 'H', 'P', &brd);
    return 0;
}