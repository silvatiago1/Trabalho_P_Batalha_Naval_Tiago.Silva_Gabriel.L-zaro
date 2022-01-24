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
        else // Esconde os barcos-> Se no board estiver a letra de um barco (P/N/C/S) esconde a letra e apresenta espaço em branco, caso não esteja apresenta o que está no board
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
int typeToSize(char type) //Utilizador escolhe o tipo do barco e a função retorna o respetivo tamanho, caso o tipo de barco seja inválido a função retorna -1
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
void init_boat(Boat *b, char type, Position xy, char dir) //Valores das coordenadas do barcos, caso o jogador escolha H mantém-se o valor x e soma-se i ao y, caso escolha V mantém-se o y e soma-se o i ao x e dá-se valor de 1 ao afloat nessas mesmas coordenadas
{
    b->afloat = typeToSize(type);
    b->tSize = b->afloat;
    b->type = type;
    for (int i = 0; i < b->tSize; i++) //percorrer o barco
    {
        if (dir == 'H') //Se for horizontal mover as colunas
        {
            b->coord[i].pos.x = xy.x;
            b->coord[i].pos.y = xy.y + i;
        }
        else //Se for vertical percorrer as linhas
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
int check_free(int n, int m, Boat *boat, char board[n][m]) //Verifica se as posições que se pretende colocar o barco estão livres, se estiver devolve 0 e faz break, se não estiver devolve 1
{
    int check = 1;
    for (int i = 0; i < boat->tSize; i++) //percorre o tamanho do barco
    {
        if (board[boat->coord[i].pos.x][boat->coord[i].pos.y] != ' ') //verifica se a posição está vazia
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
    int typesize = typeToSize(type); //Invoca a função typeToSize para saber qual é o tamanho do barco que o jogador pretende colocar no board
    int ret;

    Position temp = {x1, y1};

    Boat bat;
    init_boat(&bat, type, temp, dir);

    if (x1 < N && y1 < M && x1 >= 0 && y1 >= 0)
    {
        int check = check_free(N, M, &bat, board->board); //Invoca a função check_free, se as posições estiverem livre coloca a letra respetiva a esse barco nessas posições e devolve 0
        if (typesize != -1)
        {
            if (dir == 'H')
            {
                if (y1 + typesize <= M) //Verifica se as coordenadas são válidas, caso não sejam devolve -2
                {
                    if (check == 1)
                    {
                        for (int j = y1; j < y1 + typesize; j++)
                        {
                            board->board[x1][j] = type; //Coloca a respetiva letra do barco nas coordenadas escolhidas
                        }
                        ret = 0;
                        board->boats[board->numBoats] = bat;
                        board->boats[board->numBoats].afloat = typesize;
                        board->numBoatsAfloat++; //Aumenta 1 valor no número de barcos colocados e não afundados
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
    for (int i = 0; i < board->numBoats; i++)
    {
        for (int j = 0; j < board->boats[i].tSize; j++)
        {
            if (board->boats[i].coord[j].pos.x == x && board->boats[i].coord[j].pos.y == y)
            {
                board->boats[i].coord[j].afloat = 0; //Se acertou no barco, dá valor 0 ao afloat das coordenadas, o que significa que essa posição foi afundada
                board->boats[i].afloat--;            //Reduz um valor á variável afloat que representa o número de posições que ainda não foram afundadas
                if (board->boats[i].afloat == 0)     //Se o número de posições que ainda não foram afundadas for 0, então é porque o barco foi afundado
                {
                    ret = board->boats[i].type; //devolve a letra do barco que foi afundado
                    board->numBoatsAfloat--;    //Reduz um valor no número de barcos que ainda não foram afundados
                    for (int k = 0; k < board->boats[i].tSize; k++)
                    {
                        board->board[board->boats[i].coord[k].pos.x][board->boats[i].coord[k].pos.y] = 'A'; //Apresenta 'A' nas coordenadas do barco que foi afundado
                    }
                }
                break;
            }
        }
        if (ret != 'F') //se ja encontrou um valor diferente de 'F', ou seja, se o barco foi afundado faz break
        {
            break;
        }
    }
    if (x >= N || y >= M || x < 0 || y < 0) //Se as coordenadas que o jogador pretende atacar forem inválidas devolve 'I'
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
    
    if(x>=0&&x<8&&y>=0&&y<8)
    {
        if (board->board[x][y] != ' ')
        {
            if (board->board[x][y] == 'F' || board->board[x][y] == 'A' || board->board[x][y] == '*') //Se nas coordenadas que o jogador pretende atacar estiver
            {                                                                                        //'F' ou 'A' ou '*' devolve o valor 0, uma vez que esta posição já foi atacada anteriormente
                hit = 0;
            }
            else
            { //caso que acerte num barco coloca * no board nas coordenadas atacadas e devolve 1

                board->board[x][y] = '*';
                hit = 1;
                check = check_sink(x, y, board);  //Invoca a função check_sink, se o valor que essa função retornar for diferente de 'F' e 'I', ou seja, tem coordenadas
                if (check != 'F' && check != 'I') //válidas e se foi afundado um barco, devolve a letra do barco que foi afundado
                {
                    hit = typeToSize(check);
                }
            }
        }
        else
        {
            board->board[x][y] = 'F'; //Caso o jogador dois não atinja nenhum barco, coloca 'F' no board nessas coordenadas
        }
    }
    else
    {
        hit=-2;
    }
    return hit;
}

//int colocaNavio()
int main(void)
{
    char dir, consult = 'n';
    int x, y, fint, exitgame = 0;
    int flag = 1, player1 = 0, player2 = 0, player = 0;
    char type, leave = 'N', jogador1[15], jogador2[15];

    printf("Jogador 1, digite o seu nome:\n");
    scanf("%s", jogador1);
    printf("Jogador 2, digite o seu nome:\n");
    scanf("%s", jogador2);

    while (exitgame == 0) //O jogo continua aberto até o utilizador escolher fechá-lo
    {
        for (int turn = 0; leave == 'N'; turn++) //A cada jogo terminado aumenta 1 no valor turn, se turn for par o jogador 1 começa a colocar os navios,
        {                                        //se for ímpar é o jogador 2 que começa a colocar os navios
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

            while (brd.numBoats < 6) //Enquanto todos os barcos disponíveis não forem colocados o jogo vai continuar a pedir ao defensor para colocar barcos
            {
                printf("Ainda tem a seguinte quantidade de cada tipo de barco para colocar:\n\tPorta-aviões[P]-> %d;\n\tNavios-tanque[N]-> %d;\n\tContratorpedeiros[C]-> %d;\n\tSubmarinos[S]-> %d.\n\n", p, n, c, s);
                printf("Insira a letra inicial do barco que pretende colocar no tabuleiro:\n");
                scanf(" %c", &type);
                printf("Se deseja saír do jogo atual prima Y, caso contrário prima qualquer outra tecla\n");
                scanf(" %c", &leave);
                if (leave == 'Y')
                {
                    break;
                }

                switch (type) //O utilizador vai colocar o tipo de barco que escolheu
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

                        fint = place_boat(x, y, dir, type, &brd); //A variável fint serve para se verificar se o barco foi colocado com sucesso ou se houve um problema
                                                                  //No segundo caso ajuda a identificar o problema
                        print_board(N, M, brd.board, flag);

                        if (fint == 0) //Caso não ocorram problemas o número de barcos que o utilizador pode colocar do tipo escolhido diminui
                        {
                            p--;
                        }
                        else if (fint == -1) //Os restantes casos são todos os erros possíveis
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
                    }
                    else //Caso já não haja mais barcos do tipo pretendido disponíveis
                    {
                        print_board(N, M, brd.board, flag);
                        printf("Já atingiu o limite de Submarinos, por favor escolha outro tipo de barco para colocar!\n\n");
                    }
                    break;

                default:
                    printf("Tipo de navio inválido, por favor escolha outro tipo de navio!\n\n");
                    break;
                }
            }
            printf("\n\nTodos os barcos foram colocados com sucesso!\n");
            flag = 0; //A flag muda para 0 de modo a que o atacante não veja a posição dos barcos

            print_board(N, M, brd.board, flag);

            if (player == 1)
            {
                printf("%s, hora de atacar!\n", jogador2);
            }
            else
            {
                printf("%s, hora de atacar!\n", jogador1);
            }

            for (int attack = 0; attack < 40 && brd.numBoatsAfloat != 0; attack++) //O ataque continua até o jogador atingir o limite de ataques ou afundar todos os barcos
            {
                printf("Se quiser ver as posições dos barcos prima c, caso contrário prima qualquer outro botão menos o k\n\n");
                if (consult != 'k') //O atacante apenas é avisado de que vai perder se ainda não tiver escolhido ver o tabuleiro
                {
                    printf("Se o fizer perderá automaticamente!\n");
                }
                scanf(" %c",&consult);
                printf("Se deseja saír do jogo atual prima Y, caso contrário prima qualquer outra tecla\n");
                scanf(" %c", &leave);
                if (leave == 'Y')
                {
                    break;
                }            
                if (consult == 'c')
                {
                    print_board(N, M, brd.board, 1);
                    if (player == 1)
                    {
                        printf("O %s perdeu!\n", jogador2);
                    }
                    else
                    {
                        printf("O %s perdeu!\n", jogador1);
                    }
                    consult='k';//O k é a variável que guarda a desistência do atacante
                }

                if (player == 1)
                {
                    printf("%s ainda tem %d jogadas de ataque!\n", jogador2, 40 - attack);
                }
                else
                {
                    printf("%s ainda tem %d jogadas de ataque!\n", jogador1, 40 - attack);
                }

                printf("Digite a posição que pretende atacar:\n");
                printf("Linha: ");
                scanf("%d", &x);
                printf("Coluna: ");
                scanf("%d", &y);

                fint = target(x, y, &brd); //fint é um indicador do que aconteceu com o disparo do atacante
                print_board(N, M, brd.board, flag);
                switch (fint)
                {
                case -1:
                    printf("Acertou na água!!\n");
                    break;
                case -2:
                    printf("Posição inválida, escolha outra!\n");//Quando o atacante esolhe uma posição inválida não perde uma rodada
                    attack--;
                    break;
                case 0:
                    printf("Essa posição já foi atacada, escolha outra!\n");
                    attack--;
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
                if (brd.numBoatsAfloat == 0)
                {
                    if (player == 1 && consult != 'k')
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
                else if (brd.numBoatsAfloat != 0 && attack >= 40)
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
            printf("%s: %d-%d :%s\n", jogador1, player1, player2, jogador2); //Resultado atual do jogo

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
        printf("Se deseja iniciar um jogo novo clique 0\nCaso queira fechar o jogo clique em qualquer outra tecla\n");
        scanf("%d", &exitgame);
    }
    return 0;
}