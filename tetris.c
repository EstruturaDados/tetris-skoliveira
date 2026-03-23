#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX_FILA 5
#define MAX_PILHA 3

// --- Estruturas ---

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// --- Funções ---
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enqueue(Fila *f, Peca nova);
void dequeue(Fila *f, Peca *removida);
void mostrarFila(Fila *f);
Peca gerarPeca(int *id);

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
void push(Pilha *p, Peca nova);
void pop(Pilha *p, Peca *removida);
void peek(Pilha *p, Peca *visualizada);
void mostrarPilha(Pilha *p);

void exibirMenu();
void limparBufferEntrada();

int main() {

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

    // Inicializa a semente com o tempo atual
    srand(time(NULL));

    Fila f;
    inicializarFila(&f);

    Pilha p;
    inicializarPilha(&p);

    // id inicial = zero
    int id = 0;

    // lotar a fila
    for(int i=0; i<MAX_FILA; i++) {
        enqueue(&f, gerarPeca(&id));
    }

    int opcao;
    do{
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        Peca peca;
        switch (opcao)
        {
        case 1:
            dequeue(&f, &peca);
            enqueue(&f, gerarPeca(&id));
            mostrarFila(&f);
            mostrarPilha(&p);
            break;
        case 2:
            dequeue(&f, &peca);
            enqueue(&f, gerarPeca(&id));
            push(&p, peca);
            mostrarFila(&f);
            mostrarPilha(&p);
            break;
        case 3:
            Peca peca;
            pop(&p, &peca);
            mostrarFila(&f);
            mostrarPilha(&p);
            break;
        case 0:
            return 0;
        
        default:
            printf("\nDigite um index valido!");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        }
    } while(1);

    mostrarFila(&f);

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


    return 0;
}

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
 
    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void dequeue(Fila *f, Peca *removida) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *removida = f->pecas[f->inicio];             
    f->inicio = (f->inicio + 1) % MAX_FILA;     
    f->total--;                        
}

void mostrarFila(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c %d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;              // Avança o topo
    p->pecas[p->topo] = nova;  // Insere o novo elemento
}

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia. Não há elementos para remover.\n");
        return;
    }

    *removida = p->pecas[p->topo];  // Copia o valor do topo
    p->topo--;               // Decrementa o topo
}

void peek(Pilha *p, Peca *visualizada) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nada para espiar.\n");
        return;
    }

    *visualizada = p->pecas[p->topo];
}

void mostrarPilha(Pilha *p) {
    printf("\nPilha (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n\nPressione Enter para continuar...");
    getchar();
}

Peca gerarPeca(int *id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    char tipo = tipos[rand() % sizeof(tipos)];
    Peca p;
    p.tipo = tipo;
    p.id = *id;
    *id += 1;
    return p;
}

void exibirMenu() {
    printf("\n1. Jogar peca");
    printf("\n2. Reservar Peca");
    printf("\n3. Usar Peca Reserva");
    printf("\n0. Sair");
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}