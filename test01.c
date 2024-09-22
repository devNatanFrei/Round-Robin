#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} ProcessState;

// Estrutura para representar um processo
typedef struct {
    int id;
    int time_remaining;
    ProcessState state;
} Process;

// Função para escalonar processos usando o algoritmo FCFS
void round_robin(Process processes[], int num_processes, int quantum) {
    int current_time = 0;
    int all_done = 0;

  while (!all_done)
  {
    all_done = 1;
    for (int i = 0; i < num_processes; i++)
    {
      if (processes[i].time_remaining > 0)
      {
        all_done = 0;
        processes[i].state = EM_EXECUCAO;
        printf("Tempo %d: Processo %d em execucao\n", current_time, processes[i].id);
       
        int exec_time = (processes[i].time_remaining > quantum) ? quantum : processes[i].time_remaining;

        current_time += exec_time;
        processes[i].time_remaining -= exec_time;

        printf("Tempo %d: Processo %d - Tempo restante: %d\n", current_time, processes[i].id, processes[i].time_remaining);

        if (processes[i].time_remaining == 0)
        {
          processes[i].state = CONCLUIDO;
          printf("Tempo %d: Processo %d concluido\n", current_time, processes[i].id);
      }else{
          processes[i].state = PRONTO;
        }

        }
    }
  }
}
  


int main() {
    // Exemplo de utilização
    Process processes[] = {
        {1, 5, PRONTO},
        {2, 3, PRONTO},
        {3, 7, PRONTO}
        // Adicione mais processos conforme necessário
    };

    int num_processes = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;
    // Chamar a função de escalonamento FCFS
    round_robin(processes, num_processes, quantum);

    // Exibir o estado final dos processos
    printf("Estado final dos processos:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Processo %d: Estado %d\n", processes[i].id, processes[i].state);
    }

    return 0;
}