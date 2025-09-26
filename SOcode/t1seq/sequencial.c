#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "config.h" // Configurações como N (número de contas), SALDO_INIT, MAX_FOR, etc.

int banco = SALDO_BANCO; // Saldo inicial do banco
conta contas[N];         // Vetor com N contas bancárias

// Imprime o saldo atual de uma conta
void imprimeSaldo(conta *p) {
   // printf("Saldo de %d: %d\n", p->id, p->saldo);
}

// Realiza um saque da conta para o banco
void sacar(conta *p, unsigned int *seed) {
    int r = rand_r(seed) % RANDOM_MAX + 1; // Valor aleatório para saque
    if (p->saldo > r) {
        banco += r;      // Valor sacado vai para o banco
        p->saldo -= r;   // Diminui da conta
       // printf("Conta de %d sacou %d no banco\n", p->id, r);
    } else {
       // printf("Saldo de %d insuficiente\n", p->id);
    }
}

// Realiza um depósito do banco para a conta
void depositar(conta *p, unsigned int *seed) {
    int r = rand_r(seed) % RANDOM_MAX + 1; // Valor aleatório para depósito
    if (banco > r) {
        banco -= r;      // Diminui do banco
        p->saldo += r;   // Aumenta na conta
       // printf("Conta de %d depositou %d no banco\n", p->id, r);
    } else {
       // printf("Saldo do banco insuficiente\n");
    }
}

// Realiza uma transação entre duas contas diferentes
void transacao(unsigned int *seed) {
    int r = rand_r(seed) % N;
    int s = rand_r(seed) % N;
    if (r == s) return; // Evita transação da conta com ela mesma

    int d = rand_r(seed) % RANDOM_MAX + 1; // Valor da transação
    if (contas[r].saldo >= d) {
        contas[r].saldo -= d;
        contas[s].saldo += d;
       // printf("Transacao entre %d e %d de %d\n", r, s, d);
    }
}

int main() {
    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL); // Marca o tempo de início

    // Inicializa as contas com saldo fixo
    for (int i = 0; i < N; i++) {
        contas[i].saldo = SALDO_INIT;
        contas[i].id = i + 1;
    }

    unsigned int seed_global = time(NULL); // Semente global baseada no tempo atual

    // Para cada conta, executa MAX_FOR operações (depósito ou saque)
    for (int i = 0; i < N; i++) {
        unsigned int seed = seed_global ^ (contas[i].id * 7919); // Gera uma seed única
        for (int j = 0; j < MAX_FOR; j++) {
            int r = rand_r(&seed) % 2; // Escolhe aleatoriamente entre saque e depósito
            if (r == 0)
                depositar(&contas[i], &seed);
            else
                sacar(&contas[i], &seed);

            imprimeSaldo(&contas[i]);
        }
    }

    // Simula P "threads" fazendo transações entre contas
    for (int p = 0; p < P; p++) {
        unsigned int seed = seed_global ^ (9091 + p * 31); // Seed única para cada loop
        for (int i = 0; i < MAX_FOR; i++) {
            transacao(&seed);
        }
    }

    gettimeofday(&fim, NULL); // Acabou o tempo de execução

    
    long segundos = fim.tv_sec - inicio.tv_sec;
    long microssegundos = fim.tv_usec - inicio.tv_usec;
    double tempo_total = segundos + microssegundos * 1e-6;

    
    printf("\n--- Saldo final ---\n");
    printf("Saldo final do banco: %d\n", banco);
    for (int i = 0; i < N; i++) {
       // printf("Saldo final da conta %d: %d\n", contas[i].id, contas[i].saldo);
    }

    printf("\nTempo total (sequencial): %.4f segundos\n", tempo_total);

    return 0;
}
