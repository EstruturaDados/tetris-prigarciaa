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
//     NÍVEL MESTRE — FUNÇÕES AVANÇADAS E UNDO (SNAPSHOT)
// =======================================================

// ESTRUTURAS PARA SALVAR SNAPSHOT DO ESTADO (UNDO)
typedef struct {
    Fila fila;
    Pilha pilha;
    int geradorID;
    int valido; // 0 = inválido (nenhum snapshot), 1 = válido
} Snapshot;

Snapshot ultimoSnapshot;

void salvarSnapshot(Fila *f, Pilha *p) {
    ultimoSnapshot.fila = *f;
    ultimoSnapshot.pilha = *p;
    ultimoSnapshot.geradorID = geradorID;
    ultimoSnapshot.valido = 1;
}

void limparSnapshot() {
    ultimoSnapshot.valido = 0;
}

int podeDesfazer() {
    return ultimoSnapshot.valido == 1;
}

void desfazer(Fila *f, Pilha *p) {
    if (!podeDesfazer()) {
        printf("\nNada para desfazer.\n");
        return;
    }
    *f = ultimoSnapshot.fila;
    *p = ultimoSnapshot.pilha;
    geradorID = ultimoSnapshot.geradorID;
    limparSnapshot();
    printf("\nA última ação foi desfeita.\n");
}

// 4 - TROCAR PEÇA DA FRENTE DA FILA COM O TOPO DA PILHA
void trocarFrenteComTopo(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("\nNão é possível trocar: fila vazia.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("\nNão é possível trocar: pilha vazia.\n");
        return;
    }

    salvarSnapshot(f, p);

    // indices
    int idxFrente = f->frente;
    int idxTopo = p->topo;

    Peca temp = f->itens[idxFrente];
    f->itens[idxFrente] = p->itens[idxTopo];
    p->itens[idxTopo] = temp;

    printf("\nTroca realizada: frente da fila <-> topo da pilha\n");
}

// 5 - TROCAR 3 PRIMEIROS DA FILA COM AS 3 PEÇAS DA PILHA
void trocarTresPrimeiros(Fila *f, Pilha *p) {
    if (f->quantidade < 3) {
        printf("\nNão há 3 peças suficientes na fila para trocar.\n");
        return;
    }
    if (p->topo != TAM_PILHA - 1) {
        printf("\nA pilha deve ter exatamente 3 peças para essa operação.\n");
        return;
    }

    salvarSnapshot(f, p);

    // PEGA OS ÍNDICES CIRCULARES DOS 3 PRIMEIROS DA FILA
    int idx0 = f->frente;
    int idx1 = (f->frente + 1) % TAM_FILA;
    int idx2 = (f->frente + 2) % TAM_FILA;

    // TROCAS CORRESPONDENTES COM p->itens[0..2]
    Peca tmp0 = f->itens[idx0];
    Peca tmp1 = f->itens[idx1];
    Peca tmp2 = f->itens[idx2];

    // FILA RECEBE PILHA
    f->itens[idx0] = p->itens[0];
    f->itens[idx1] = p->itens[1];
    f->itens[idx2] = p->itens[2];

    // PILHA RECEBE ANTIGOS PRIMEIROS DA FILA (PRESERVANDO ORDEM)
    p->itens[0] = tmp0;
    p->itens[1] = tmp1;
    p->itens[2] = tmp2;

    printf("\nTroca realizada: 3 primeiros da fila <-> 3 da pilha\n");
}

// 7 - INVERTER FILA COM PILHA (TROCA OS 3 PRIMEIROS DA FILA COM A PILHA, INVERTENDO A ORDEM)
void inverterFilaComPilha(Fila *f, Pilha *p) {
    if (f->quantidade < 3) {
        printf("\nNão há 3 peças suficientes na fila para inverter.\n");
        return;
    }
    if (p->topo == -1) {
        printf("\nA pilha está vazia — nada a inverter.\n");
        return;
    }

    salvarSnapshot(f, p);

    // INDICE DOS 3 PRIMEIROS DA FILA
    int idx0 = f->frente;
    int idx1 = (f->frente + 1) % TAM_FILA;
    int idx2 = (f->frente + 2) % TAM_FILA;

    // PARA INVERTER VAMOS:
    // COLOCAR OS 3 PRIMEIROS DA PILHA NA FILA NOS 3 PRIMEIROS EM ORDEM INVERSA
    // COLOCAR OS 3 PRIMEIROS DA FILA NA PILHA EM ORDEM INVERSA
    // CALCULAMOS QUANTOS ELEMENTOS HÁ NA PILHA (p->topo+1), LIMITAMOS A 3
    int countPilha = p->topo + 1;
    if (countPilha > 3) countPilha = 3;

    // SALVA OS 3 PRIMEIROS DA FILA
    Peca f0 = f->itens[idx0];
    Peca f1 = f->itens[idx1];
    Peca f2 = f->itens[idx2];

    // CRIA ARRAY TEMPORÁRIO COM PILHA ATUAL(ATÉ 3), EM ORDEM topo->base
    Peca pilhaArr[3];
    for (int i = 0; i < 3; i++) {
        if (i <= p->topo) pilhaArr[i] = p->itens[i];
        else pilhaArr[i] = (Peca){'x', -1};
    }

    // COLOCA NA FILA OS ELEMENTOS DA PILHA EM ORDEM INVERTIDA: p[it2], p[it1], p[it0]
    // SE A PILHA TIVER MENOS DE 3, COLOCA OS QUE EXISTEM COMENÇANDO EM idx0
    int placed = 0;
    for (int i = countPilha - 1; i >= 0; i--) {
        if (placed == 0) f->itens[idx0] = pilhaArr[i];
        else if (placed == 1) f->itens[idx1] = pilhaArr[i];
        else if (placed == 2) f->itens[idx2] = pilhaArr[i];
        placed++;
    }

    // SE A PILHA TEM MENOS QUE 3, OS LUGARES RESTANTES NA FILA MANTÉM SEUS VALORES ANTIGOS
     if (countPilha < 3) {
        if (countPilha <= 0) {
            // NADA COLOCADO: MANTEMOS f0,f1,f2
            f->itens[idx0] = f0;
            f->itens[idx1] = f1;
            f->itens[idx2] = f2;
        } else if (countPilha == 1) {
            // SÓ UM ELEMENETO DA PILHA FOI COLOCADO EM idx0, MANTER f1,f2
            f->itens[idx1] = f1;
            f->itens[idx2] = f2;
        } else if (countPilha == 2) {
            // DOIS COLOCADOS, MANTER f2
            f->itens[idx2] = f2;
        }
    }

    // AGORA COLOCAMOS NA PILHA OS ANTIGOS f0,f1,f2 EM ORDEM INVERTIDA: f2,f1,f0
    // AJUSTAMOS O TOPO CONFORME QUANTOS ELEMENTOS TEREMOS (até 3)
    p->topo = 2; // VAMOS PREENCHER OS 3 SLOTS (SE QUISER MANTER TAMANHO MENORES, PODEMOS AJUSTAR)
    p->itens[0] = f2;
    p->itens[1] = f1;
    p->itens[2] = f0;

    printf("\nInversão realizada entre fila (3 primeiros) e pilha (invertendo ordens)\n");
}




// =======================================================
//            MAIN — NOVATO + AVENTUREIRO + MESTRE
// =======================================================

int main(){

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    incializarPilha(&pilha);

    limparSnapshot();

    // PREENCHE A FILA COM 5 PEÇAS INICIAIS
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        printf("\n===== MENU NÍVEL NOVATO + AVENTUREIRO + MESTRE =====\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Enviar peça da fila para a reserva (pilha)\n");
        printf("3 - Usar peça reserva\n");
        printf("4 - trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - trocar os 3 primeiros da fila com as 3 da pilha (pilha deve ter 3)\n");
        printf("6 - Desfazer última ação\n");
        printf("7 - Inverter fila com pilha (3 primeiros / inverter ordens)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            // ----- NÍVEL NOVATO -----
            case 1: {
                // SALVAR ESTADO PARA PERMITIR DESFAZER DESSA AÇÃO
                salvarSnapshot(&fila, &pilha);

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

                salvarSnapshot(&fila, &pilha);

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
                if (pilhaVazia(&pilha)) {
                    printf("A pilha está vazia! Nada para usar.\n");
                    break;
                }

                salvarSnapshot(&fila, &pilha);

                Peca usada = pop(&pilha);

                if (usada.id != -1) {
                    printf("Peça usada da reserva: %c (ID %d)\n",
                           usada.tipo, usada.id);
                }

                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            // ----- NÍVEL MESTRE -----
            case 4: {
                trocarFrenteComTopo(&fila, &pilha);
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            case 5: {
                trocarTresPrimeiros(&fila, &pilha);
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            case 6: {
                desfazer(&fila, &pilha);
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            }

            case 7: {
                inverterFilaComPilha(&fila, &pilha);
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
        

   


















