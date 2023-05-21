#include "bonequinho.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void limparTerminal() { printf("\033[2J\033[H"); }

void printaMatrizDeBonecos(char ***bonecos, int tamanho)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            printf("%s ", bonecos[j][i]);
        }
        printf("\n");
    }
}

char **bonequinho(int boneco)
{
    char **bonecoLista = (char **)malloc(3 * sizeof(char *));

    for (int i = 0; i < 3; i++)
    {
        bonecoLista[i] = (char *)malloc(5 * sizeof(char));
    }

    if (boneco == 1)
    {
        strcpy(bonecoLista[0], "  @/");
        strcpy(bonecoLista[1], " /| ");
        strcpy(bonecoLista[2], " / \\");
    }
    else if (boneco == 2)
    {
        strcpy(bonecoLista[0], " @__");
        strcpy(bonecoLista[1], "/|  ");
        strcpy(bonecoLista[2], "/ \\ ");
    }
    else if (boneco == 4)
    {
        strcpy(bonecoLista[0], " bla");
        strcpy(bonecoLista[1], " /| ");
        strcpy(bonecoLista[2], " / \\");
    }
    else
    {
        strcpy(bonecoLista[0], "__@|");
        strcpy(bonecoLista[1], "  | ");
        strcpy(bonecoLista[2], " / \\");
    }

    return bonecoLista;
}

void printaLinhaAlunos(int numAlunosPorta, int seed)
{
    char ***matrizBonecos = (char ***)malloc(numAlunosPorta * sizeof(char **));

    int randInt;
    srand(seed);

    for (int i = 0; i < numAlunosPorta; i++)
    {
        randInt = rand() % 3 + 1;
        matrizBonecos[i] = bonequinho(randInt);
    }

    printaMatrizDeBonecos(matrizBonecos, numAlunosPorta);
    printf("\n");

    for (int i = 0; i < numAlunosPorta; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            free(matrizBonecos[i][j]);
        }
        free(matrizBonecos[i]);
    }
    free(matrizBonecos);
}

void handleAlunosNaPorta(int numAlunos)
{
    while (numAlunos >= 5)
    {
        printaLinhaAlunos(5, numAlunos);
        numAlunos -= 5;
    }

    if (numAlunos > 0)
    {
        printaLinhaAlunos(numAlunos, numAlunos);
    }
}
void door()
{
    char *door[] = {" __________", "|     |    |", "|  |CB16|  |",
                    "|          |", "|         ●|", "|          |",
                    "|__________|"};

    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", door[i]);
    }
}

void teacherEnteringDoor()
{
    char *door[] = {" __________",
                    "|          |",
                    "|  |CB16|  | Professor entrando na sala...",
                    "|          |",
                    "|         ●|  @",
                    "|          | /|\\",
                    "|__________| / \\"};

    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", door[i]);
    }
}

void doorTalking(int select)
{
    char *door[] = {" __________    _____________________________",
                    "|     |    |  /  tirei 0 em GA!!             \\",
                    "|  |CB16|  | |   caraca! vai de 10 na p2      |",
                    "|          | |   mas a prova tava facil ein   |",
                    "|         ●| |   bobeou ashduashudaus         |",
                    "|          | |   qual o peso da p2?           |",
                    "|__________| / ______________________________/",
                    "            /_/"};

    char *door2[] = {" __________    ______________________",
                     "|     |    |  / O IFGW odeia os alunos\\",
                     "|  |CB16|  | |  boa       aaf          |",
                     "|          | |    ok  hmm              |",
                     "|         ●| | Como calcula a média    |",
                     "|          | |   dessa matéria?        |",
                     "|__________| / _______________________/",
                     "            /_/ "};
    char *door3[] = {" __________    _________", "|     |    |  /    huh  \\",
                     "|  |CB16|  | | bla BLA   |", "|          | |  hm   aaah|",
                     "|         ●| | kkkk tendi|", "|          | |  ok  hmmm |",
                     "|__________| /  ________/", "            /_/"};

    if (select == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%s\n", door[i]);
        }
    }
    else if (select == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%s\n", door3[i]);
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            printf("%s\n", door2[i]);
        }
    }
}

void teacherInDoor()
{
    char *teacherInDoor[] = {
        " __________",
        "|          |",
        "|  |CB16|  | /¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\",
        "|       @  |/   Estão atrapalhando minha aula!       |",
        "|      /|\\ |\\   Saiam daqui!                         |",
        "|      / \\ | \\______________________________________/",
        "|__________|"};

    for (int i = 0; i < 7; i++)
    {
        printf("%s\n", teacherInDoor[i]);
    }
}