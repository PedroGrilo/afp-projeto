#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "menus.h"
#define maxforca 100
#define maxpalavras 21

typedef struct
{
    char nome[21];
    char pass[21];
    int pontos;
    int pontosvspc;
    int jogadas;
    int jogadaspc;
} USERSPC;

void chooseTheme(USERSPC p1, char* tema[maxforca])
{
    char op;

    setlocale(LC_ALL,"");
    do
    {
        system("cls");
        printf("\t/***********************************/\n");
        printf("\t/** Jogo da Forca - Escolher Tema **/\n");
        printf("\t/***********************************/\n\n");
        printf("1 - Nomes \t\t\t 5 - Profiss�es\n");
        printf("2 - Terras,Pa�ses,Cidades \t 6 - Objetos\n");
        printf("3 - Animais \t\t\t 7 - Comidas\n");
        printf("4 - Cores \t\t\t 8 - Pe�as de Roupas\n");
        printf("\n0 - Voltar\n\nEscolha a op��o: ");
        scanf(" %c", &op);
    } while (op < 0 && op > 8);

    switch (op)
    {
        case '0':
            menuForca(p1);
            break;
        case '1':
            strcpy(tema, "Nomes");
            break;
        case '2':
            strcpy(tema, "TPC");
            break;
        case '3':
            strcpy(tema, "Animais");
            break;
        case '4':
            strcpy(tema, "Cores");
            break;
        case '5':
            strcpy(tema, "Profissoes");
            break;
        case '6':
            strcpy(tema, "Objetos");
            break;
        case '7':
            strcpy(tema, "Comidas");
            break;
        case '8':
            strcpy(tema, "PdR");
            break;
        default:
            exit(1);
            break;
    }
}

void wordspc(USERSPC p1)
{
    char repetir, forca[maxforca], frase[maxforca],
        msg[maxforca] = {}, palavrast[maxpalavras][maxforca], c, tema[maxpalavras][maxforca],
        temapesq[maxforca], palavrapesq[maxforca], temas[maxforca];

    int i = 0, k = 0, max = 0, random = 0;

    chooseTheme(p1, &temas);

    // ler as palavras do ficheiro
    srand(time(NULL));
    FILE* palavras;

    palavras = fopen("palavras.txt", "r+");

    if (palavras != NULL)
    {
        while (fscanf(palavras, "%s - %s \n", &temapesq, &palavrapesq) != EOF)
        {
            if (strcmp(temapesq, temas) == 0)
            {
                strcpy(tema[max], temapesq);
                strcpy(palavrast[max], palavrapesq);
                max++;
            }else{
                printf("\n> N�o existe palavras para este tema no ficheiro.\n\nPressione qualquer tecla para continuar.");
                fflush(stdin);
                getchar();
                menuForca(p1);
            }
        }


        random = rand() % max;

        strcpy(forca, palavrast[random]);
        i = strlen(palavrast[random]);

        for (k = 0; k < i; k++)
        {
            // criar uma variavel, com os underscores correspondentes � frase
            // introduzida.

            if (verificacoes(forca) == 0)
            {
                if (forca[k] == ' ')
                {
                    fflush(stdin);
                    frase[k] = ' ';
                }
                else
                {
                    fflush(stdin);
                    frase[k] = '_';
                }
            }
        }

        system("cls");
        guesserpc(forca, frase, p1, tema[random]);
    }else{
        printf("\n> Erro ao abrir ficheiro.\n\nPressione qualquer tecla para continuar.");
        fflush(stdin);
        getchar();
        menuForca(p1);
    }
}
void guesserpc(char forca[maxforca], char frase[maxforca], USERSPC p1, char tema[maxforca])
{
    // player 2, adivinhar a palavra/frase do player 1

    char tentativa[26], falhas[6], msg[maxforca] = {}, voltar;
    int i = 0, k = 0, samechar = 0, guesssize = strlen(forca), falha = 1, falhascount = 0,
        counter = 0;
    do
    {
        fflush(stdin);
        if (samechar != 1)
            system("cls");
        if (falhascount != 7 && falhascount != 6)
            header(p1.nome, msg, falhascount, tentativa, i);

        if (strcmp(tema, "TPC") == 0)
            printf("Tema : Terras,Pa�ses,Cidades\n\n");
        else if (strcmp(tema, "PdR") == 0)
            printf("Tema : Pe�as de Roupa\n\n");
        else
            printf("Tema : %s\n\n", tema);
        fflush(stdin);

        for (int i = 0; i < guesssize; i++)
            printf("%c ", frase[i]);
        if (falhascount != 7 && falhascount != 6)
        {
            puts("\n\nIntroduza uma letra 0-Desistir > "); // desistir do jogo
            fflush(stdin);
            scanf("%c", &tentativa[i]);
            strcpy(msg, "");
            if (i < 2 && isvogal(tentativa[i]))
            {
                system("cls");
                strcpy(msg, "\nNao sao aceites vogais at� � terceira ronda, tente "
                            "novamente!\n");
                continue;
            }

            if (isdigit(tentativa[i]))
            {
                if (tentativa[i] != '0')
                {
                    system("cls");
                    strcpy(msg, "\nNao sao aceites numeros, tente novamente!\n");
                    continue;
                }
                else
                {
                    system("cls");
                    strcpy(msg, "\n");
                    falhascount = 7;
                    continue;
                }
            }
            if (tentativa[i] == ' ')
            {
                system("cls");
                strcpy(msg, "\nNao sao aceites espacos, tente novamente!\n");

                continue;
            }
            else if (!((tolower(tentativa[i]) >= 97 && tolower(tentativa[i]) <= 122)
                         || tentativa[i] == 32))
            {
                system("cls");
                strcpy(msg, "\nNao sao aceites caracteres especiais, tente novamente!\n");

                continue;
            }
            else
            {
                for (k = 0; k < i; k++)
                {
                    if (tolower(tentativa[i]) == tolower(tentativa[k]))
                    {
                        system("cls");
                        strcpy(msg, "\nERRO: Esse caracter j� foi introduzido\n");
                        i--;
                        samechar = 1;
                        continue;
                    }
                    else
                    {
                        samechar = 0;
                    }
                }
            }
            falha = 1;

            if (samechar == 0)
            {
                for (k = 0; k < guesssize; k++)
                {
                    if (tolower(tentativa[i]) == tolower(forca[k]))
                    {
                        frase[k] = tolower(tentativa[i]);
                        falha = 0;
                    }
                }
                if (falha == 1 && falhascount < 6 && samechar == 0) // player 1
                {
                    falhas[falhascount] = tentativa[i];
                    falhascount++;
                }
                else if (falhascount > 6)
                {
                    system("cls");
                    header(p1.nome, msg, 7, tentativa, i);
                    printf("Perdeu o jogo contra o PC!!\n");
                    printf("\n\nDeseja voltar ao menu?[S/N]");
                    getchar();
                    scanf(" %c", &voltar);
                    if (tolower(voltar) == 's')
                        menuForca(p1);
                    else
                        printf("\nVolte sempre");
                    exit(1);
                }
                if (strcmp(forca, frase) == 0) // player 1
                {
                    system("cls");
                    header(p1.nome, msg, 8, tentativa, i);
                    printf("Ganhou o jogo contra o PC !!\n\n");
                    savepointspc(falhascount, p1, guesssize);
                }
            }
            i++;
        }
        else
        {
            system("cls");
            header(p1.nome, msg, 7, tentativa, i);
            printf("Perdeu o jogo contra o PC!!\n");
            printf("\n\nDeseja voltar ao menu?[S/N]");
            fflush(stdin);
            scanf(" %c", &voltar);
            if (tolower(voltar) == 's')
                menuForca(p1);
            else
                printf("\nVolte sempre");
            exit(1);
        }
    } while (i < 26);
}
void savepointspc(int erros, USERSPC p1, int stringlength)
{
    typedef struct
    {
        char nome[21];
        char pass[21];
        int pontos;
        int pontosvspc;
        int jogadas;
        int jogadaspc;
    } reader;

    reader usersubdata, buffer;

    char voltar;

    FILE* getpoints;
    long int recsize;
    usersubdata.pontos = p1.pontos;
    usersubdata.pontosvspc = p1.pontosvspc;
    switch (erros)
    {
        case 0:
            printf("Ganhou: %d pontos\n", (10));
            usersubdata.pontosvspc += (10);
            break;
        case 1:
            printf("Ganhou: %d pontos\n", (8));
            usersubdata.pontosvspc += (8);
            break;
        case 2:
            printf("Ganhou: %d pontos\n", (6));
            usersubdata.pontosvspc += (6);
            break;
        case 3:
            printf("Ganhou: %d pontos\n", (4));
            usersubdata.pontosvspc += (4);
            break;
        case 4:
            printf("Ganhou: %d pontos\n", (3));
            usersubdata.pontosvspc += (3);
            break;
        case 5:
            printf("Ganhou: %d pontos\n", (2));
            usersubdata.pontosvspc += (2);
            break;
        default:
            printf("Ganhou: %d pontos\n", (0));
            usersubdata.pontosvspc += (0);
            break;
    }

    getpoints = fopen("users.dat", "rb+");
    rewind(getpoints);
    strcpy(usersubdata.nome, p1.nome);
    strcpy(usersubdata.pass, p1.pass);
    usersubdata.pontos = p1.pontos;
    usersubdata.jogadas = p1.jogadas;
    usersubdata.jogadaspc = p1.jogadaspc + 1;

    recsize = sizeof(reader);
    while (fread(&buffer, recsize, 1, getpoints) == 1)
    {
        if (strcmp(buffer.nome, p1.nome) == 0)
        {
            fseek(getpoints, -recsize, SEEK_CUR);
            fflush(getpoints);
            fwrite(&usersubdata, recsize, 1, getpoints);
            break;
        }
    }
    fclose(getpoints);

    printf("Para um total de: %d pontos!", usersubdata.pontosvspc);
    printf("\n\nDeseja voltar ao menu?[S/N]");
    fflush(stdin);
    scanf(" %c", &voltar);
    if (tolower(voltar) == 's')
    {
        menuForca(usersubdata);
    }
    else
        printf("Volte sempre\n");

    exit(1);
}
