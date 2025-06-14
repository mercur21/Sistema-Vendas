#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_VENDAS 100
#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_CPF 15

typedef struct {
    int id;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
} Cliente;

typedef struct {
    int id;
    char nome[TAM_NOME];
    float preco;
    int estoque;
} Produto;

typedef struct {
    int id_produto;
    int quantidade;
    float preco_unitario;
} ItemVenda;

typedef struct {
    int id;
    int id_cliente;
    time_t data;
    ItemVenda itens[MAX_ITENS];
    int num_itens;
    float total;
} Venda;

Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
Venda vendas[MAX_VENDAS];
int total_clientes = 0;
int total_produtos = 0;
int total_vendas = 0;
int id_cliente = 1;
int id_produto = 1;
int id_venda = 1;

void insere_cliente();
void insere_produto();
void efetivar_venda();
void listar_clientes();
void listar_produtos();
void listar_vendas();
void atualizar_cliente();
void atualizar_produto();
void excluir_cliente();
void excluir_produto();
void excluir_venda();

int main() {
    int opcao;

    do {
        printf("\nSistema de Gestao\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Listar clientes\n");
        printf("4 - Listar produtos\n");
        printf("5 - Atualizar cliente\n");
        printf("6 - Atualizar produto\n");
        printf("7 - Excluir cliente\n");
        printf("8 - Excluir produto\n");
        printf("9 - Efetivar venda\n");
        printf("10 - Listar vendas\n");
        printf("11 - Excluir venda\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 0: printf("Encerrando...\n"); break;
            case 1: insere_cliente(); break;
            case 2: insere_produto(); break;
            case 3: listar_clientes(); break;
            case 4: listar_produtos(); break;
            case 5: atualizar_cliente(); break;
            case 6: atualizar_produto(); break;
            case 7: excluir_cliente(); break;
            case 8: excluir_produto(); break;
            case 9: efetivar_venda(); break;
            case 10: listar_vendas(); break;
            case 11: excluir_venda(); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

void insere_cliente() {
    if (total_clientes < MAX_CLIENTES) {
        Cliente c;
        c.id = id_cliente++;
        printf("Digite o nome do cliente: ");
        fgets(c.nome, TAM_NOME, stdin);
        c.nome[strcspn(c.nome, "\n")] = '\0';
        printf("Digite o CPF: ");
        fgets(c.cpf, TAM_CPF, stdin);
        c.cpf[strcspn(c.cpf, "\n")] = '\0';
        clientes[total_clientes++] = c;
        printf("Cliente cadastrado com sucesso! ID: %d\n", c.id);
    } else {
        printf("Limite maximo de clientes atingido!\n");
    }
}

void insere_produto() {
    if (total_produtos < MAX_PRODUTOS) {
        Produto p;
        p.id = id_produto++;
        printf("Digite o nome do produto: ");
        fgets(p.nome, TAM_NOME, stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';
        printf("Digite o preco: ");
        scanf("%f", &p.preco);
        printf("Digite o estoque: ");
        scanf("%d", &p.estoque);
        getchar();
        produtos[total_produtos++] = p;
        printf("Produto cadastrado com sucesso! ID: %d\n", p.id);
    } else {
        printf("Limite maximo de produtos atingido!\n");
    }
}

void efetivar_venda() {
    if (total_vendas >= MAX_VENDAS) {
        printf("Limite maximo de vendas atingido!\n");
        return;
    }
    if (total_clientes == 0 || total_produtos == 0) {
        printf("Necessario ter clientes e produtos cadastrados!\n");
        return;
    }

    Venda v;
    v.id = id_venda++;
    v.num_itens = 0;
    v.total = 0.0;
    v.data = time(NULL);

    listar_clientes();
    printf("\nDigite o ID do cliente: ");
    scanf("%d", &v.id_cliente);
    getchar();

    char continuar = 's';
    while (continuar == 's' && v.num_itens < MAX_ITENS) {
        listar_produtos();
        printf("\nDigite o ID do produto: ");
        int id_prod;
        scanf("%d", &id_prod);
        getchar();

        ItemVenda item;
        item.id_produto = id_prod;

        printf("Digite a quantidade: ");
        scanf("%d", &item.quantidade);
        getchar();

        // Busca preço do produto
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].id == id_prod) {
                item.preco_unitario = produtos[i].preco;
                break;
            }
        }

        v.itens[v.num_itens] = item;
        v.num_itens++;
        v.total += item.quantidade * item.preco_unitario;

        printf("Item adicionado. Deseja adicionar outro? (s/n): ");
        continuar = getchar();
        getchar();
    }

    vendas[total_vendas++] = v;
    printf("Venda efetivada com sucesso! ID: %d, Total: R$ %.2f\n", v.id, v.total);
}

void listar_clientes() {
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("ID: %d, Nome: %s, CPF: %s\n", 
               clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
}

void listar_produtos() {
    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("ID: %d, Nome: %s, Preco: R$ %.2f, Estoque: %d\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

void listar_vendas() {
    printf("\nVendas registradas:\n");
    for (int i = 0; i < total_vendas; i++) {
        Venda v = vendas[i];
        printf("\nID Venda: %d, Cliente ID: %d", v.id, v.id_cliente);
        printf("\nData: %s", ctime(&v.data));
        
        for (int j = 0; j < v.num_itens; j++) {
            ItemVenda item = v.itens[j];
            // Busca nome do produto
            char nome_produto[TAM_NOME] = "Desconhecido";
            for (int k = 0; k < total_produtos; k++) {
                if (produtos[k].id == item.id_produto) {
                    strcpy(nome_produto, produtos[k].nome);
                    break;
                }
            }
            printf("  Produto: %s (ID: %d), Quantidade: %d, Preco unitario: R$ %.2f\n",
                   nome_produto, item.id_produto, item.quantidade, item.preco_unitario);
        }
        printf("Total da venda: R$ %.2f\n", v.total);
    }
}

void atualizar_cliente() {
    listar_clientes();
    printf("\nDigite o ID do cliente para atualizar: ");
    int id;
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].id == id) {
            printf("Novo nome: ");
            fgets(clientes[i].nome, TAM_NOME, stdin);
            clientes[i].nome[strcspn(clientes[i].nome, "\n")] = '\0';
            printf("Novo CPF: ");
            fgets(clientes[i].cpf, TAM_CPF, stdin);
            clientes[i].cpf[strcspn(clientes[i].cpf, "\n")] = '\0';
            printf("Cliente atualizado!\n");
            return;
        }
    }
    printf("Cliente nao encontrado!\n");
}

void atualizar_produto() {
    listar_produtos();
    printf("\nDigite o ID do produto para atualizar: ");
    int id;
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            printf("Novo nome: ");
            fgets(produtos[i].nome, TAM_NOME, stdin);
            produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';
            printf("Novo preco: ");
            scanf("%f", &produtos[i].preco);
            printf("Novo estoque: ");
            scanf("%d", &produtos[i].estoque);
            getchar();
            printf("Produto atualizado!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void excluir_cliente() {
    listar_clientes();
    printf("\nDigite o ID do cliente para excluir: ");
    int id;
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].id == id) {
            for (int j = i; j < total_clientes - 1; j++) {
                clientes[j] = clientes[j+1];
            }
            total_clientes--;
            printf("Cliente excluido com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado!\n");
}

void excluir_produto() {
    listar_produtos();
    printf("\nDigite o ID do produto para excluir: ");
    int id;
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            for (int j = i; j < total_produtos - 1; j++) {
                produtos[j] = produtos[j+1];
            }
            total_produtos--;
            printf("Produto excluido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void excluir_venda() {
    listar_vendas();
    printf("\nDigite o ID da venda para excluir: ");
    int id;
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].id == id) {
            for (int j = i; j < total_vendas - 1; j++) {
                vendas[j] = vendas[j+1];
            }
            total_vendas--;
            printf("Venda excluida com sucesso!\n");
            return;
        }
    }
    printf("Venda nao encontrada!\n");
}
