#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

//DEFINES E CONSTANTES    
#define TAM_FILA 5
#define TAM_PILHA 3

// STRUCTS
typedef struct {
    char tipo; // I, O, T, L
    int id; // identificador sequencial
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// PILHA (AVENTUREIRO)
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// FUNÇÕES NÍVEL NOVATO (FILA CIRCULAR)
char tipos[] = {'I', 'O', 'T', 'L'};
int geradorID = 1;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->quantidade = 0;
}

int filaVazia(Fila *f) {
    return (f->quantidade == 0);
}

int filaCheia(Fila *f) {
    return (f->quantidade == TAM_FILA);
}

Peca gerarPeca() {
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = geradorID++;
    return p;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("A fila está cheia! Não é possível inserir.\n");
        return;
    }

    f->itens[f->tras] = p;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'x', -1};

    if (filaVazia(f)) {
        printf("A fila está vazia! Nada para remover.\n");
        return removida;
    }

    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;

    return removida;
}

void mostrarFila(Fila *f) {
    printf("\n===== FILA DE PEÇAS FUTURAS =====\n");

    if (filaVazia(f)) {
        printf("Fila vazia\n");
        return;
    }

    int indice = f->frente;

    for (int i = 0; i < f->quantidade; i++) {
        Peca p = f->itens[indice];
        printf("Posição %d -> Peca %c (ID %d)\n", i + 1, p.tipo, p.id);
        indice = (indice + 1) % TAM_FILA;
    }
}

// =======================================================
//     NÍVEL AVENTUREIRO — PILHA DE RESERVA
// =======================================================

void incializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("A pilha está cheia! Não é possível enviar.\n");
        return;
    }
    p->itens[++p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca lixo = {'x', -1};

    if (pilhaVazia(p)) {
        printf("A pilha está vazia! Nada para usar.\n");
        return lixo;
    }

    return p->itens[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("\n===== PILHA DE RESERVA =====\n");

    if (pilhaVazia(p)) {
        printf("Pilha vazia\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        printf("Topo %d -> Peça %c (ID %d)\n", i, p->itens[i].tipo, p->itens[i].id);

    }
}

// =======================================================
//            MAIN — NOVATO + AVENTUREIRO
// =======================================================

int main(){

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    incializarPilha(&pilha);

    // PREENCHE A FILA COM 5 PEÇAS INICIAIS
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        printf("\n===== MENU NÍVEL NOVATO + AVENTUREIRO =====\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Enviar peça da fila para a reserva (pilha)\n");
        printf("3 - Usar peça reserva\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            // ----- NÍVEL NOVATO -----
            case 1: {
                Peca jogada = dequeue(&fila);

                if (jogada.id != -1) {
                    printf("Peça jogada: %c (ID %d)\n",
                           jogada.tipo, jogada.id);
                }

                // REPOSIÇÃO AUTOMÁTICA
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                    printf("Nova peça gerada: %c (ID %d)\n",
                           nova.tipo, nova.id);
                }           
            

                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            // ----- NÍVEL AVENTUREIRO -----
            case 2: {
                if (pilhaCheia(&pilha)) {
                    printf("A pilha está cheia! Não é possível enviar.\n");
                    break;
                }

                Peca retirada = dequeue(&fila);

                if (retirada.id != -1) {
                    push(&pilha, retirada);
                    printf("Peça enviada para reserva: %c (ID %d)\n",
                           retirada.tipo, retirada.id);
                }

                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca());
                }

                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

             case 3: {
                Peca usada = pop(&pilha);

                if (usada.id != -1) {
                    printf("Peça usada da reserva: %c (ID %d)\n",
                           usada.tipo, usada.id);
                }

                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");         
        }

    } while (opcao != 0);

    return 0; 

}
        

   


















