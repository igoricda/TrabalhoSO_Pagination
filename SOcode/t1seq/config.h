// config.h
#ifndef CONFIG_H
#define CONFIG_H

#define N 10 // Número de contas
#define P 3 // Número de transações simultâneas
#define SALDO_INIT 10000  // Saldo inicial de cada conta
#define SALDO_BANCO 500000  // Saldo do banco
#define SALDO_TOTAL (N * SALDO_INIT + SALDO_BANCO) // Saldo total esperado
#define RANDOM_MAX 1500 // Valor máximo para saque ou depósito
#define MAX_FOR 10000 // Número máximo de iterações

typedef struct {
    int saldo;
    int id;
} conta;

#endif

