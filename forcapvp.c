#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[21];
    char pass[21];
    int pontos;
}
USERS;

loginMenu();
int isvogal(char letra){

    if(letra=='a'||letra=='e'||letra=='i'||letra=='o'||letra=='u')
        return 1;
    else
        return 0;
}

void header(char nome[], char msg[], int vidas)
{
    system("cls");
    printf("/**********************************/\n");
    printf("/** Jogo da Forca - Player %-06s**/\n", nome);
    printf("/**********************************/\n");
    vida(vidas);
    puts(msg);

}

void words(USERS p1, USERS p2)
{
    char repetir, forca[100], frase[100], msg[100] = {};
    int i = 0, k = 0;
    do
    {
        system("cls");
        do
        {
            printf("/**********************************/\n");
            printf("/** Jogo da Forca - Player %-06s**/\n", p1.nome);
            printf("/**********************************/\n");

            printf("Introduza a sua palavra/frase > ");
            fflush(stdin);
            gets(forca);
            system("cls");
        }
        while(verificacoes(forca));
        i = strlen(forca);
        system("cls");

        for(k=0; k<i; k++)
        {
            if(verificacoes(forca)==0)
            {
                if(forca[k]==' ')
                {
                    fflush(stdin);
                    frase[k]=' ';
                }
                else
                {
                    fflush(stdin);
                    frase[k] = '_';
                }
            }
        }
        frase[k] = '\0';
        printf("Frase: %s\n\n", forca);
        printf("Deseja alterar a frase? [S/N]\n");
        fflush(stdin);
        scanf("%c",&repetir);
    }
    while (tolower(repetir) == 's');
    system("cls");
    guesser(forca, frase, p2, p1);
}
void guesser(char forca[100], char frase[100], USERS p2, USERS p1)
{

    char tentativa[26], falhas[6], msg[100] = {}, voltar;
    int i = 0, k = 0, samechar = 0, guesssize = strlen(forca), falha = 1, falhascount = 0, counter = 0;
    do
    {

        fflush(stdin);
        if (samechar != 1)
            system("cls");

        header(p2.nome, msg, falhascount);
        fflush(stdin);

        for (int i = 0; i < guesssize; i++)
            printf("%c ", frase[i]);

        puts("\n\nIntroduza uma letra > ");
        fflush(stdin);
        scanf("%c",&tentativa[i]);
        strcpy(msg, "");

        for(k=0;k<3;k++){
            if(isvogal(tentativa[k])==1){
                system("cls");
                strcpy(msg, "\nNao sao aceites vogais até à terceira ronda, tente novamente!\n");
                i--;
                continue;
            }
        }
        k=0;
        if (isdigit(tentativa[i]))
        {
            system("cls");
            strcpy(msg, "\nNao sao aceites numeros, tente novamente!\n");
            i--;
            continue;
        }
        else if (tentativa[i] == 32)
        {
            system("cls");
            strcpy(msg, "\nNao sao aceites espacos, tente novamente!\n");
            i--;
            continue;
        }
        else if (tentativa[i] == '\n')
        {
            system("cls");
            strcpy(msg, "\nNao introduziu nenhuma letra, tente novamente!\n");
            i--;
            continue;
        }

        falha = 1;

        for (k = 0; k < i; k++)
        {
            if (tentativa[i] == tentativa[k])
            {
                system("cls");
                strcpy(msg, "\nERRO: Esse caracter já foi introduzido\n");
                i--;
                samechar = 1;
                continue;

            }
            else
            {
                samechar = 0;
            }

        }


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
            if (falha == 1 && falhascount < 5 && samechar == 0) //player 1
            {
                falhas[falhascount] = tentativa[i];
                falhascount++;
            }
            else if (falhascount >= 5)
            {
                system("cls");
                header(p1.nome, msg, 7);
                printf("Perdeu o jogo (%s) contra o Player '%s' !!\n", p1.nome, p2.nome);
                savepoints(falhascount,p1,guesssize);
                printf("\n\nDeseja voltar ao menu?[S/N]");
                getchar();
                scanf(" %c", & voltar);
                if (tolower(voltar) == 's')
                    menuForca(p1);
                else
                    printf("\nVolte sempre");
                exit(1);
            }
            if (strcmp(forca, frase) == 0) //player 2
            {
                system("cls");
                header(p2.nome, msg, 8);
                printf("Ganhou o jogo (%s) contra o Player '%s' !!\n Ganhou ", p2.nome, p1.nome);
                savepoints(falhascount,p2,guesssize); //mudar
                printf("\nDeseja voltar ao menu?[S/N]");
                getchar();
                scanf(" %c", & voltar);
                if (tolower(voltar) == 's')
                    menuForca(p1);
                else
                    printf("Volte sempre\n");
                exit(1);
            }
        }
        i++;
    }
    while (i < 26);
}
void savepoints(int erros, USERS p2,int stringlength)
{

    typedef struct
    {
        char nome[21];
        char pass[21];
        int pontos;
    }reader;
    reader usersubdata,buffer;

    FILE * getpoints;
    long int recsize;


    int pontos[7] = {10,8,6,4,3,2,0};
    usersubdata.pontos=p2.pontos;
    switch (erros)
    {
        case 0 :
            printf("%d pontos\n",(10 ));
            usersubdata.pontos += (10 );
            break;
        case 1:
            printf("%d pontos\n",(8 ));
            usersubdata.pontos += (8 );
            break;
        case 2:
            printf("%d pontos\n",(6 ));
            usersubdata.pontos += (6 );
            break;
        case 3:
            printf("%d pontos\n",(4 ));
            usersubdata.pontos += (4 );
            break;
        case 4:
            printf("%d pontos\n",(3));
            usersubdata.pontos += (3);
            break;
        case 5:
            printf("2 pontos\n",(2 ));
            usersubdata.pontos += (2 );
            break;
        default:
            printf("%d pontos\n",(0 ));
            usersubdata.pontos += (0 );
            break;
    }

    printf("Para um total de %d pontos!",usersubdata.pontos);
    getpoints=fopen("users.dat","rb+");
    rewind(getpoints);
    strcpy(usersubdata.nome,p2.nome);
    strcpy(usersubdata.pass,p2.pass);
    recsize=sizeof(reader);
    while(fread(&buffer,recsize,1,getpoints)==1){
        if(strcmp(buffer.nome,p2.nome)==0){
                fseek(getpoints,-recsize,SEEK_CUR);
                fflush(getpoints);
                fwrite(&usersubdata,recsize,1,getpoints);
                break;
        }
    }
    fclose(getpoints);
}


int verificacoes(char nome[]){
    if(strlen(nome)<3)
    {
        printf("A frase NÃO pode conter menos de 3 caracteres\n\n");
        return 1;
    }
    else if(nome[0]==32)
    {
        printf("A frase NÃO pode conter espaços iniciais\n\n");
        return 1;
    }
    else
    {

        int tst = 0;

        for(int i=0; i<strlen(nome); i++)
        {
            if((nome[i] >=97 && nome[i] <= 122)|| nome[i]==32)
            {
                tst = 0;
            }
            else
            {
                tst = 1;
                break;
            }
        }

        if(tst == 1)
        {
            printf("A frase SÓ pode conter letras.\n\n");
            return 1;
        }
        else
            return 0;
    }
}
