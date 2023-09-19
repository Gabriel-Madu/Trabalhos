#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

typedef struct produto{
    char nome[TAM];
    double preco;
    int ID;
    struct produto *proximo;
}Produto;

typedef struct{
    Produto *inicio;
}Lista;

void criar_lista(Lista *lista);
void adicionar_produto(Lista *lista, double preco, int ID, char *nome);
Produto *remover_produto(Lista *lista, int num);
void imprimir(Lista lista);
void carregar_lista(Lista *lista);
void salvar_lista(Lista lista);

int main(){

    int opcao, ID;
    double preco;
    char nome[TAM];
    Lista lista;
    Produto *removido;

    criar_lista(&lista);

    do{
        printf("\n\t1 - Adicionar produto\n\t2 - Remover produto\n\t3 - Imprimir lista\n\t4 - Carregar lista do arquivo 'produtos.bin'\n\t5 - Salvar lista atual no arquivo 'produtos.bin'\n\t0 - Sair\n\t");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("\nDigite um produto: ");
            scanf("%s", nome);
            printf("Digite seu preco: ");
            scanf("%lf", &preco);
            printf("Digite sua ID: ");
            scanf("%d", &ID);
            adicionar_produto(&lista, preco, ID, nome);
            break;
        case 2:
            printf("Digite a ID do produto a ser removido: ");
            scanf("%d", &ID);
            removido = remover_produto(&lista, ID);
            if(removido){
                printf("Produto removido: %s\n", removido->nome);
                free(removido);
            }
            else
                printf("Produto inexistente!\n");
            break;
        case 3:
            imprimir(lista);
            break;
        case 4:
            carregar_lista(&lista);
            break;
        case 5:
            salvar_lista(lista);
            break;
        default:
            if(opcao != 0)
                printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}

void criar_lista(Lista *lista){
    lista->inicio = NULL;
}

void adicionar_produto(Lista *lista, double preco, int ID, char *nome){
    Produto *aux, *novo = malloc(sizeof(Produto));

    if(novo){
        novo->preco = preco;
        novo->ID = ID;
        strcpy(novo->nome, nome);

        if(lista->inicio == NULL){
            novo->proximo = NULL;
            lista->inicio = novo;
        }
        else if(novo->preco <= lista->inicio->preco){
            novo->proximo = lista->inicio;
            lista->inicio = novo;
        }
        else{
            aux = lista->inicio;
            while(aux->proximo && novo->preco > aux->proximo->preco){
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

Produto *remover_produto(Lista *lista, int num){
    Produto *aux = lista->inicio;
    Produto *remover = NULL;
    Produto *anterior = NULL;

    while(aux){
        if(aux->ID == num){
            if(anterior){
                anterior->proximo = aux->proximo;
            }
            else{
                lista->inicio = aux->proximo;
            }

            remover = aux;
            aux = aux->proximo;
            
            return remover;
        }
        else{
            anterior = aux;
            aux = aux->proximo;
        }
    }
    return remover;
}

void imprimir(Lista lista){
    Produto *produto = lista.inicio;

    while(produto){
        printf("NOME: %s\n", produto->nome);
        printf("PRECO: %.2lf\n", produto->preco);
        printf("ID: %d\n\n", produto->ID);
        produto = produto->proximo;
    }
    printf("\n\n");
}

void carregar_lista(Lista* lista){
    FILE *arquivo = fopen("produtos.bin", "rb");

    if(arquivo){
        criar_lista(lista);

        while(1){
            Produto *novo = malloc(sizeof(Produto));
            if(!novo){
                printf("Erro ao alocar memoria!\n");
                break;
            }

            size_t elementos_lidos = fread(novo, sizeof(Produto), 1, arquivo);

            if(elementos_lidos != 1){
                free(novo);
                break;
            }

            novo->proximo = NULL;

            if(lista->inicio == NULL){
                lista->inicio = novo;
            }
            else{
                Produto *atual = lista->inicio;
                while(atual->proximo){
                    atual = atual->proximo;
                }
                atual->proximo = novo;
            }
        }
        fclose(arquivo);
        printf("Lista carregada do arquivo 'produtos.bin'.\n");
    }
    else
        printf("Nao foi possivel carregar a lista do arquivo 'produtos.bin'.\n");
}

void salvar_lista(Lista lista){
    FILE *arquivo = fopen("produtos.bin", "wb");

    if(arquivo){
        Produto *produto = lista.inicio;

        while(produto){
            fwrite(produto, sizeof(Produto), 1, arquivo);
            produto = produto->proximo;
        }
        fclose(arquivo);
        printf("Lista salva no arquivo 'produtos.bin'.\n");
    }
    else
        printf("Nao foi possivel salvar a lista no arquivo 'produtos.bin'.\n");
}