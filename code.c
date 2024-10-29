#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EM_EXECUCAO,
    BLOQUEADO,
    CONCLUIDO
} ProcessState;

typedef struct {
    int id;
    int time_remaining;
    ProcessState state;
} Process;

int verif(Process processes[], int num_processes)
{
    for (int i = 0; i < num_processes; i++)
    {
        if (processes[i].state != CONCLUIDO)
        {
            return 1;
        }
    }
    return 0;
}

void round_robin(Process processes[], int num_processes, int quantum) {
    int current_time = 0;
 

    while (verif(processes, num_processes)) {
  
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].state == PRONTO) {
            
                processes[i].state = EM_EXECUCAO;
                printf("Tempo %d: Processo %d em execucao\n", current_time, processes[i].id);

                int ver = 0;
                if (processes[i].time_remaining > quantum) {
                   ver = quantum;
                } else {
                   ver = processes[i].time_remaining ;
                }
          


                for (int t = 0; t < ver; t++) {
                    current_time++;
                    processes[i].time_remaining--;

                    printf("Tempo %d: Processo %d - Tempo restante: %d\n", current_time, processes[i].id, processes[i].time_remaining);
                }

              
                if (processes[i].time_remaining == 0) {
                    processes[i].state = CONCLUIDO;
                    printf("Tempo %d: Processo %d concluido\n", current_time, processes[i].id);
                } else {
                    processes[i].state = PRONTO;
                }
            }
        }
    }
}

int main() {

    Process processes[] = {
        {1, 5, PRONTO},
        {2, 3, PRONTO},
        {3, 7, PRONTO},
         {4, 8, PRONTO}
    };

    int num_processes = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;

  
    round_robin(processes, num_processes, quantum);

  
    printf("\nEstado final dos processos:\n");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].state == CONCLUIDO) {
            printf("Processo %d: Concluido\n", processes[i].id);
        }
    }

    return 0;
}
