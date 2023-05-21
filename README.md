# MC504 - Projeto Multithread 

## Projeto dedicado a disciplina MC504 (Sistemas Operacionais) no primeiro semestre de 2023, ministrado pela professora [![Islene Calciolari Garcia](https://www.ic.unicamp.br/~islene/)](https://www.ic.unicamp.br/~islene/). 


Esse projeto consiste na aplicação aplicação prática de conceitos explorados em aula sobre threads. Nesse sentido, com esse conteúdo em mente idealizamos um problema a ser resolvido usando threads, semáforos, entre outras definições vistas em aula. 

## O Problema 

O problema pensado foi adaptado de um dos exemplos apresentados no livro [![The Little Book of Semaphores](https://greenteapress.com/wp/semaphores/)](https://greenteapress.com/wp/semaphores/) seção 7.3, "The Room party Problem".

Nessa perspectiva, o problema idealizado por nosso grupo consiste em uma adaptação, como dito anteriormente, do problema mencionado. Sendo assim, temos a seguinte situação: Um(a) professor(a) chega em sua sala para dar aula, mas é interrompido continuamente por alunos de outras salas que se alocam na frente da sala de sua turma. Ao ultrapassar um certo número de alunos gerando muito barulho, o(a) professor(a) começa a se sentir incomodado(a) com os alunos que não param de aparecer em sua porta, sendo assim, se desloca até ela para expulsar os alunos de lá. O programa entra em loop entre as ações de alunos se alocarem na porta e expulsá-los. 

Dessa forma, teremos algumas restrições:
- Teremos no máximo 18 estudantes que podem se alocar na porta da sala (note que este número é variável e pode ser mudado no código)
- O professor pode expulsar as pessoas da porta de sua sala somente quando o número de estudantes em sua porta for **maior ou igual** a 10
- Enquanto o professor estiver expulsando as pessoas de sua porta nenhum estudante pode se alocar para a frente da mesma
- O professor não sai da porta até que todos os estudantes tenham saido da porta 
- Há apenas um professor, isto é, pessoa que pode expulsar os alunos da porta

## Instruções de compilação e execução

Para compilar o programa, divido em diferentes arquivos (semaphore e bonequinho), utilize o seguinte comando:

- **gcc semaphore.c -o semaphore**

Em seguida, para executá-lo utilize:

- **./semaphore**


## Observação:
- Após pesquisas e testes há uma incompatibilidade entre a biblioteca de semaforos entre o Linux e o MAC OS
- [![SemaphorePosix raises deprecation warnings on macOS / iOS](https://github.com/godotengine/godot/issues/24418)](https://github.com/godotengine/godot/issues/24418)