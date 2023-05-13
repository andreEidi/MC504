#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define o número máximo de estudantes que podem se acumular na porta da sala
#define NUM_STUDENTS 20
// Define a quantidade de estudantes que devem estar na porta para que o professor sinta-se incomodado para expulsá-los
#define MAX_STUDENTS_DOOR 10
#define MAX_DELAY 3

// O mutex evita que as threads utilizem variaveis ao mesmo tempo, visto que cada função (professor e estudante) disputam as variaveis abaixo
sem_t mutex;
// Variavel atômica que indica quantos alunos estão alocados na porta da sala de aula
int num_students = 0;
// Indica a situação do professor no momento
char acao_prof[20] = "dando aula";

void *f_estudante(void *v)
{
  // Recebe como argumento o id do aluno
  int id = *(int *)v;
  // Variavel dentro sinaliza se o aluno de id x já está alocado na porta do professor
  int dentro = 0;
  while (1)
  {
    sleep(rand() % MAX_DELAY + 1);
    sem_wait(&mutex);
    if (strcmp(acao_prof, "dando aula") == 0 && dentro != 1)
    {
      // Aluno se coloca na porta do professor enquanto o professor dá a aula
      num_students++;
      dentro = 1;
      printf("estudante %d está na porta\n", id);
      sleep(1);
    }
    else if (strcmp(acao_prof, "expulsando") == 0 && dentro == 1)
    {
      // O aluno sai da sala enquanto o professor está a expulsá-los
      // Vale mencionar que nenhum aluno entra na sala enquanto o professor realiza esta ação
      num_students--;
      dentro = 0;
      printf("estudante %d saiu da porta\n", id);
      sleep(1);
    }
    else if (dentro == 1)
    {
      // Se o aluno já está na porta apenas é sinalizado que ele está conversando/atrapalhando a aula
      // Isso acontece pela existencia do while, sendo assim mesmo já estando na porta continua disputando o mutex
      printf("estudante %d está conversando na porta\n", id);
      sleep(3);
    }
    sem_post(&mutex);
  }
}

void *f_prof(void *v)
{
  while (1)
  {
    sem_wait(&mutex);
    if (strcmp(acao_prof, "dando aula") == 0)
    {
      if (num_students >= MAX_STUDENTS_DOOR)
      {
        // Caso o professor tenha "pegado" o mutex e o número de estudantes for maior que a tolerância e começa a expulsá-los
        strcpy(acao_prof, "expulsando");
        printf("prof está expulsando os alunos barulhentos\n");
      }
      else if (num_students == 0)
      {
        // Como o prof começa na situação "Dando aula" este será a primeira situação do problema, no caso o prof entra para começar a aula
        strcpy(acao_prof, "entrando...");
        printf("prof entrou na sala\n");
      }
    }
    else if (strcmp(acao_prof, "expulsando") == 0 && num_students == 0)
    {
      // Quanto tiver terminado de expulsá-los retoma a aula normalmente
      strcpy(acao_prof, "dando aula");
      printf("prof voltou para a sala\n");
    }
    else if (strcmp(acao_prof, "entrando...") == 0)
    {
      sleep(5);
      printf("prof está dando aula\n");
      strcpy(acao_prof, "dando aula");
    }
    sem_post(&mutex);
    sleep(rand() % MAX_DELAY);
  }
}

int main()
{
  pthread_t thr_students[NUM_STUDENTS], thr_prof;
  int ids[NUM_STUDENTS];

  // Mutex começa com valor 1 para poder ser consumido
  sem_init(&mutex, 0, 1);

  pthread_create(&thr_prof, NULL, f_prof, NULL);
  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    ids[i] = i;
    pthread_create(&thr_students[i], NULL, f_estudante, &ids[i]);
  }

  pthread_join(thr_prof, NULL);
  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    pthread_join(thr_students[i], NULL);
  }

  return 0;
}
