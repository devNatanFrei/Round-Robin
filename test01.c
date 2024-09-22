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

// Função para escalonar processos usando o algoritmo Round Robin
void round_robin(Process processes[], int num_processes, int quantum) {
    int current_time = 0;
    int all_done = 0;

    while (!all_done) {
        all_done = 1;

        // Iterar sobre todos os processos
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].time_remaining > 0) {
                all_done = 0;
                processes[i].state = EM_EXECUCAO;
                printf("Tempo %d: Processo %d em execução\n", current_time, processes[i].id);

                // Executar o processo pelo quantum ou pelo tempo restante, o que for menor
                int exec_time = (processes[i].time_remaining > quantum) ? quantum : processes[i].time_remaining;

                // Simular a execução segundo a unidade de tempo de 1 em 1
                for (int t = 0; t < exec_time; t++) {
                    current_time++;
                    processes[i].time_remaining--;

                    printf("Tempo %d: Processo %d - Tempo restante: %d\n", current_time, processes[i].id, processes[i].time_remaining);
                }

                // Verificar se o processo foi concluído
                if (processes[i].time_remaining == 0) {
                    processes[i].state = CONCLUIDO;
                    printf("Tempo %d: Processo %d concluído\n", current_time, processes[i].id);
                } else {
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
    };

    int num_processes = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;

    // Chamar a função de escalonamento Round Robin
    round_robin(processes, num_processes, quantum);

    // Exibir o estado final dos processos
    printf("\nEstado final dos processos:\n");
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].state == CONCLUIDO) {
            printf("Processo %d: Concluído\n", processes[i].id);
        }
    }

    return 0;
}
