#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_STUDENTS 60
#define MAX_DELAY 3

sem_t mutex;
int num_students = 0;
char acao_prof[20] = "dando aula";

void *f_estudante(void *v) {
  int id = *(int *)v;
  int dentro = 0;
  while (1) {
    sleep(rand() % MAX_DELAY + 1);
    sem_wait(&mutex);
    if (strcmp(acao_prof, "dando aula") == 0 && dentro != 1) {
      num_students++;
      dentro = 1;
      printf("estudante %d está na porta\n", id);
      sleep(1);
    } else if (strcmp(acao_prof, "expulsando") == 0 && dentro == 1) {
      num_students--;
      dentro = 0;
      printf("estudante %d saiu da porta\n", id);
      sleep(1);
    } else if (dentro == 1) {
      printf("estudante %d está conversando na porta\n", id);
      sleep(3);
    }
    sem_post(&mutex);
  }
}

void *f_prof(void *v) {
  while (1) {
    sem_wait(&mutex);
    if (strcmp(acao_prof, "dando aula") == 0) {
      if (num_students >= 50) {
        strcpy(acao_prof, "expulsando");
        printf("prof está expulsando os alunos barulhentos\n");
      } else if (num_students == 0) {
        strcpy(acao_prof, "entrando...");
        printf("prof entrou na sala\n");
      }
    } else if (strcmp(acao_prof, "expulsando") == 0 && num_students == 0) {
      strcpy(acao_prof, "dando aula");
      printf("prof voltou para a sala\n");
    } else if (strcmp(acao_prof, "entrando...") == 0) {
      sleep(5);
      printf("prof está dando aula\n");
      strcpy(acao_prof, "dando aula");
    }
    sem_post(&mutex);
    sleep(rand() % MAX_DELAY);
  }
}

int main() {
  pthread_t thr_students[NUM_STUDENTS], thr_prof;
  int ids[NUM_STUDENTS];

  sem_init(&mutex, 0, 1);

  pthread_create(&thr_prof, NULL, f_prof, NULL);
  for (int i = 0; i < NUM_STUDENTS; i++) {
    ids[i] = i;
    pthread_create(&thr_students[i], NULL, f_estudante, &ids[i]);
  }

  pthread_join(thr_prof, NULL);
  for (int i = 0; i < NUM_STUDENTS; i++) {
    pthread_join(thr_students[i], NULL);
  }

  return 0;
}
