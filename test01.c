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
    int remaining_time;
    ProcessState state;
} Processo;

void pcas(Processo processo[], int num_processos, int quantum) {
    int time = 0;
    int all_done;

    do {
        all_done = 1;

        for (int i = 0; i < num_processos; i++) {
            if (processo[i].remaining_time > 0) {
                all_done = 0;
                processo[i].state = EM_EXECUCAO;
                printf("Tempo %d: Processo %d em execução\n", time, processo[i].id);

                int exec_time = (processo[i].remaining_time < quantum) ? processo[i].remaining_time : quantum;

                processo[i].remaining_time -= exec_time;
                time += exec_time;

                printf("Tempo %d: Processo %d, tempo restante %d\n", time, processo[i].id, processo[i].remaining_time);

                if (processo[i].remaining_time == 0) {
                    processo[i].state = CONCLUIDO;
                    printf("Tempo %d: Processo %d concluído\n", time, processo[i].id);
                }
            }
        }
    } while (!all_done);

   
    printf("\nEstado final dos processos:\n");
    for (int i = 0; i < num_processos; i++) {
        printf("Processo %d: %s\n", processo[i].id, 
            processo[i].state == CONCLUIDO ? "Concluído" : "Ainda em execução");
    }
}

int main() {
    Processo processo[] = {
        {1, 7, PRONTO},
        {2, 5, PRONTO},
        {3, 8, PRONTO}
    };

    int num_processos = sizeof(processo) / sizeof(processo[0]);
    int quantum = 2; 
    pcas(processo, num_processos, quantum);

    return 0;
}