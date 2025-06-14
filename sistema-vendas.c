#include <stdio.h>
#include <string.h>
#define MAX 100
#define MAXITENS 10

typedef struct { int produto; int qt; float pu; } Item;
typedef struct { int id; char nome[50]; char cpf[15]; } Cliente;
typedef struct { int id; char nome[50]; float preco; int estoque; } Produto;
typedef struct { int id; int cliente; Item itens[MAXITENS]; int nItens; float total; } Venda;

Cliente clientes[MAX];
Produto produtos[MAX];
Venda vendas[MAX];
int nCli = 0, nProd = 0, nVenda = 0;
int idCli = 1, idProd = 1, idVenda = 1;

char scbuf[100];

void exibirMenu(char opcs[][50], int n) {
    for(int i=0; i<n; i++) printf("%d - %s\n", i, opcs[i]);
    printf("Selecione: ");
}

void cadastrarCliente(){
    clientes[nCli].id = idCli;
    printf("Nome do cliente: "); scanf(" %49[^"]", clientes[nCli].nome);
    printf("CPF do cliente: "); scanf(" %14s", clientes[nCli].cpf);
    nCli++; idCli++;
}

void listarClientes(){
    for(int i=0;i<nCli;i++)
        printf("id:%d nome:%s cpf:%s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
}

void atualizarCliente(){
    int cid;
    printf("ID do cliente: "); scanf("%d", &cid);
    for(int i=0;i<nCli;i++){
        if(clientes[i].id==cid){
            printf("Novo nome: "); scanf(" %49[^"]", clientes[i].nome);
            printf("Novo CPF: "); scanf(" %14s", clientes[i].cpf);
            return;
        }
    }
    printf("Cliente nao encontrado\n");
}

void removerCliente(){
    int cid;
    printf("ID para remover: "); scanf("%d", &cid);
    int j=0;
    for(int i=0;i<nCli;i++){
        if(clientes[i].id!=cid){ clientes[j++] = clientes[i]; }
    }
    nCli = j;
}

void cadastrarProduto(){
    produtos[nProd].id = idProd;
    printf("Nome do produto: "); scanf(" %49[^"]", produtos[nProd].nome);
    printf("Preco: "); scanf("%f", &produtos[nProd].preco);
    printf("Estoque: "); scanf("%d", &produtos[nProd].estoque);
    nProd++; idProd++;
}

void listarProdutos(){
    for(int i=0;i<nProd;i++)
        printf("id:%d nome:%s preco:%.2f est:%d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
}

void atualizarProduto(){
    int pid;
    printf("ID do produto: "); scanf("%d", &pid);
    for(int i=0;i<nProd;i++){
        if(produtos[i].id==pid){
            printf("Novo nome: "); scanf(" %49[^"]", produtos[i].nome);
            printf("Novo preco: "); scanf("%f", &produtos[i].preco);
            printf("Novo estoque: "); scanf("%d", &produtos[i].estoque);
            return;
        }
    }
    printf("Produto nao encontrado\n");
}

void removerProduto(){
    int pid;
    printf("ID para remover: "); scanf("%d", &pid);
    int j=0;
    for(int i=0;i<nProd;i++){
        if(produtos[i].id!=pid){ produtos[j++] = produtos[i]; }
    }
    nProd = j;
}

void novaVenda(){
    vendas[nVenda].id = idVenda;
    printf("ID do cliente: "); scanf("%d", &vendas[nVenda].cliente);
    int q;
    printf("Quantidade de itens: "); scanf("%d", &q);
    vendas[nVenda].nItens = q;
    float tot = 0;
    for(int i=0;i<q && i<MAXITENS;i++){
        printf("ID do produto: "); scanf("%d", &vendas[nVenda].itens[i].produto);
        printf("Qtde: "); scanf("%d", &vendas[nVenda].itens[i].qt);
        printf("Preco unitario: "); scanf("%f", &vendas[nVenda].itens[i].pu);
        tot += vendas[nVenda].itens[i].qt * vendas[nVenda].itens[i].pu;
    }
    vendas[nVenda].total = tot;
    nVenda++; idVenda++;
}

void listarVendas(){
    for(int i=0;i<nVenda;i++){
        printf("id:%d cli:%d total:%.2f\n", vendas[i].id, vendas[i].cliente, vendas[i].total);
    }
}

void removerVenda(){
    int vid;
    printf("ID da venda: "); scanf("%d", &vid);
    int j=0;
    for(int i=0;i<nVenda;i++){
        if(vendas[i].id!=vid){ vendas[j++] = vendas[i]; }
    }
    nVenda = j;
}

int main(){
    char m1[4][50] = {"Clientes", "Produtos", "Vendas", "Sair"};
    int opc = -1;
    while(opc!=3){
        printf("\n--- SisVenda C ---\n");
        exibirMenu(m1,4);
        scanf("%d", &opc);
        if(opc==0){
            int sc;
            char c1[5][50]={"Cadastrar","Listar","Atualizar","Remover","Voltar"};
            while(sc!=4){
                exibirMenu(c1,5);
                scanf("%d", &sc);
                if(sc==0) cadastrarCliente();
                if(sc==1) listarClientes();
                if(sc==2) atualizarCliente();
                if(sc==3) removerCliente();
            }
        }
        if(opc==1){
            int sp;
            char c2[5][50]={"Cadastrar","Listar","Atualizar","Remover","Voltar"};
            while(sp!=4){
                exibirMenu(c2,5);
                scanf("%d", &sp);
                if(sp==0) cadastrarProduto();
                if(sp==1) listarProdutos();
                if(sp==2) atualizarProduto();
                if(sp==3) removerProduto();
            }
        }
        if(opc==2){
            int sv;
            char c3[4][50]={"Nova Venda","Listar","Remover","Voltar"};
            while(sv!=3){
                exibirMenu(c3,4);
                scanf("%d", &sv);
                if(sv==0) novaVenda();
                if(sv==1) listarVendas();
                if(sv==2) removerVenda();
            }
        }
    }
    return 0;
}
