#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cliente.h"

Lista_cliente *criarCliente ()
{
    Lista_cliente *l = (Lista_cliente*) malloc (sizeof(Lista_cliente));
    l->inicio = NULL;
    return l;
}

int listaVaziaCliente (Lista_cliente *l)
{
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0; else return 1;
}

int sortearCodigoCliente (Lista_cliente *l)
{
    int codigo = 0;
    srand(time(NULL));

    while (codigo == 0)
    {
        codigo = rand()%9999;
    }

    if (l == NULL || listaVaziaCliente(l) == 0) return codigo;

    No_cliente *aux = l->inicio;
    
    while (aux != NULL)
    {
        if (codigo == aux->valor.codigo)
        {
            codigo = rand()%9999;
            aux = l->inicio;
        }
        aux = aux->prox;
    }

    return codigo;
}

int inserirInicioCliente (Lista_cliente *l, Cliente item) // insere no inicio da lista
{
    if (l == NULL) return NULL_LIST;

    No_cliente *noaux = (No_cliente*) malloc (sizeof(No_cliente));

    if (listaVaziaCliente(l) != 0)
    {
        noaux->valor = item;
        //noaux->valor.codigo = sortearCodigoCliente(l);
        l->inicio->ant = noaux;
        noaux->prox = l->inicio;
        noaux->ant = NULL;
        l->inicio = noaux;
    }
    else
    {
        noaux->valor = item;
        //noaux->valor.codigo = sortearCodigoCliente(l);
        l->inicio = noaux;
        noaux->prox = NULL;
        noaux->ant = NULL;
    }

    return 0;
}

int inserirFimCliente (Lista_cliente *l, Cliente item) // insere no fim da lista
{
    if (l == NULL) return NULL_LIST;

    No_cliente *noaux = (No_cliente*) malloc (sizeof(No_cliente));
    No_cliente *nofim = l->inicio;
    
    noaux->valor = item;
    //noaux->valor.codigo = sortearCodigoCliente(l);
    noaux->prox = NULL;

    if (listaVaziaCliente(l) != 0) 
    {   
        while (nofim->prox != NULL)
        {
            nofim = nofim->prox;
        }
        nofim->prox = noaux;
        noaux->ant = nofim;
    }
    else 
    {
        l->inicio = noaux;
        noaux->ant = NULL;
    }
    return 0;
}

int removerInicioCliente (Lista_cliente *l) // remove no inicio da lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return 0;

    No_cliente *aux = l->inicio;
    
    if (l->inicio->prox == NULL)
    {
        l->inicio = NULL;
        free(aux);
    }
    else
    {
        l->inicio = aux->prox;
        aux->prox->ant = NULL;
        free(aux);
    }
    return 0;
}

int removerFimCliente (Lista_cliente *l) // remove no fim da lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return 0;

    No_cliente *aux = l->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    if (l->inicio->prox != NULL) aux->ant->prox = NULL;
    else l->inicio = NULL;
    free(aux);
    return 0;
}

int removerPosiCliente (Lista_cliente *l, int pos) // remove uma posicao X da lista, se pos >= tamanho da lista ela remove o último elemento
{
    if (l == NULL) return 3;
    if (listaVaziaCliente(l) == 0) return 0;
    if (pos == 0) 
    {
        removerInicioCliente(l); 
        return 0;
    }
    if (pos >= tamanhoCliente(l)-1)
    {
        removerFimCliente(l);
        return 0;
    }

    No_cliente *aux = l->inicio;

    while (pos > 0)
    {
        aux = aux->prox;
        pos--;
    }
    
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux);

    return 0;
}

int removerItemCliente (Lista_cliente *l, int codigo) // remove o item correspondente ao código passado 
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux;
    aux = l->inicio;
    int pos = 0;

    while ((aux != NULL) && (aux->valor.codigo != codigo))
    {
        pos++;
        aux = aux->prox;
    }
    if (aux->valor.codigo == codigo)
    {
        removerPosiCliente(l, pos);
        return 0;
    }
    return 1;
}

int inserirEnderecoCliente (Lista_cliente *l, int codigo, endereco novo_end)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux = l->inicio;
    
    while ((aux != NULL) && (aux->valor.codigo != codigo))
    {
        aux = aux->prox;
    }
    
    if (aux->valor.codigo == codigo)
    {
        /*if(aux->valor.pagamentos == NULL)
        {
            aux->valor.pagamentos = (cartao*) malloc (sizeof(cartao));
            aux->valor.quantidade_cartoes = 0;
        }*/
        aux->valor.quant_enderecos++;
        aux->valor.enderecos = realloc (aux->valor.enderecos, aux->valor.quant_enderecos*sizeof(endereco));
        
        strcpy(aux->valor.enderecos[aux->valor.quant_enderecos-1].rua, novo_end.rua);
        strcpy(aux->valor.enderecos[aux->valor.quant_enderecos-1].numero, novo_end.numero);
        strcpy(aux->valor.enderecos[aux->valor.quant_enderecos-1].cep, novo_end.cep);

        return 0;
    } 

    return 1;
}

int inserirCartaoCliente (Lista_cliente *l, int codigo, cartao novo_cartao)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux = l->inicio;
    
    while ((aux != NULL) && (aux->valor.codigo != codigo))
    {
        aux = aux->prox;
    }
    
    if (aux->valor.codigo == codigo)
    {
        /*if(aux->valor.pagamentos == NULL)
        {
            aux->valor.pagamentos = (cartao*) malloc (sizeof(cartao));
            aux->valor.quantidade_cartoes = 0;
        }*/
        aux->valor.quantidade_cartoes++;
        aux->valor.pagamentos = realloc (aux->valor.pagamentos, aux->valor.quantidade_cartoes*sizeof(cartao));
        
        aux->valor.pagamentos[aux->valor.quantidade_cartoes-1].cvv = novo_cartao.cvv;
        strcpy(aux->valor.pagamentos[aux->valor.quantidade_cartoes-1].numero, novo_cartao.numero);
        strcpy(aux->valor.pagamentos[aux->valor.quantidade_cartoes-1].tipo, novo_cartao.tipo);
        strcpy(aux->valor.pagamentos[aux->valor.quantidade_cartoes-1].validade, novo_cartao.validade);

        return 0;
    } 

    return 1;
}

int inserirPedidoHistorico (Lista_cliente *l, int codigo, hist_pedidosClientes novo_pedido)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux = l->inicio;

    while ((aux != NULL) && (aux->valor.codigo != codigo))
    {
        aux = aux->prox;
    }
    
    if (aux->valor.codigo == codigo)
    {  
        aux->valor.quant_pedidos++;
        aux->valor.historico = realloc (aux->valor.historico, aux->valor.quant_pedidos*sizeof(hist_pedidosClientes));
        
        strcpy(aux->valor.historico[aux->valor.quant_pedidos-1].nome_prato, novo_pedido.nome_prato);
        strcpy(aux->valor.historico[aux->valor.quant_pedidos-1].nome_rest, novo_pedido.nome_rest);
        aux->valor.historico[aux->valor.quant_pedidos-1].valor = novo_pedido.valor;

        return 0;
    } 
    
    return 1;
}

int inicializar_cliente (Cliente *item) // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros) 
{
    item->valor_gasto = 0;
    item->quantidade_cartoes = 0;
    item->quant_pedidos = 0;
    item->quant_enderecos = 0;
    item->historico = NULL;
    item->pagamentos = NULL;
    item->enderecos = NULL;
    return 0;
}

int limparCliente (Lista_cliente *l) // limpa a lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return 0;
    while (l->inicio != NULL)
    {
        removerFimCliente(l);
    }
    return 0;
}

int tamanhoCliente (Lista_cliente *l) // retorna o tamanho da lista 
{
    No_cliente *aux = l->inicio;
    int tam = 0;

    while (aux != NULL)
    {
        tam++;
        aux = aux->prox;
    }
    return tam;
}

void mostrar_cliente (Lista_cliente *l) // mostra as principais informações de cada entregador
{
    if (l != NULL)
    {
        printf ("[");
        
        if (listaVaziaCliente(l) != 0)
        {
            No_cliente *aux = l->inicio;
            do
            {
                printf(" {%s, ", aux->valor.nome);
                printf("%s, ", aux->valor.email);
                printf("%d, ", aux->valor.codigo);
                printf("%.2f, ", aux->valor.valor_gasto);
                printf("%d} ", aux->valor.quant_pedidos);
                aux = aux->prox;
            }while(aux != NULL);
        } printf(" ]\n");
    }
}

void mostrar_pagamentos (Cliente item)
{
    int i = 0;
    printf (" ( ");
    for (i = 0; i < item.quantidade_cartoes; i++)
    {
        printf ("{%s, ", item.pagamentos[i].tipo);
        printf ("%c%c%c%c %c%c%c%c", item.pagamentos[i].numero[0], item.pagamentos[i].numero[1], item.pagamentos[i].numero[2], item.pagamentos[i].numero[3], item.pagamentos[i].numero[4], item.pagamentos[i].numero[5], item.pagamentos[i].numero[6], item.pagamentos[i].numero[7]);
        printf (" %c%c%c%c %c%c%c%c, ", item.pagamentos[i].numero[8], item.pagamentos[i].numero[9], item.pagamentos[i].numero[10], item.pagamentos[i].numero[11], item.pagamentos[i].numero[12], item.pagamentos[i].numero[13], item.pagamentos[i].numero[14], item.pagamentos[i].numero[15]);
        printf ("%c%c/%c%c, ", item.pagamentos[i].validade[0], item.pagamentos[i].validade[1], item.pagamentos[i].validade[2], item.pagamentos[i].validade[3]);
        printf ("%d} ", item.pagamentos[i].cvv);
    }
    printf (") ");
}

void mostrar_pedidos (Cliente item)
{
    int i = 0;
    printf (" ( ");
    for (i = 0; i < item.quant_pedidos; i++)
    {
        printf ("{%s, ", item.historico[i].nome_rest);
        printf ("%s, ", item.historico[i].nome_prato);
        printf ("R$%.2f} ", item.historico[i].valor);
    }
    printf (") ");
}

void mostrar_enderecos (Cliente item)
{
    int i = 0;
    printf (" ( ");
    for (i = 0; i < item.quant_enderecos; i++)
    {
        printf ("{%s, ", item.enderecos[i].rua);
        printf ("%s, ", item.enderecos[i].numero);
        printf ("%s} ", item.enderecos[i].cep);
    }
    printf (") ");
}

void mostrar_tudo_cliente (Lista_cliente *l) // mostra TODAS as informações do entregador
{
    if (l != NULL)
    {   
        if (listaVaziaCliente(l) != 0)
        {
            printf ("[ ");
            No_cliente *aux = l->inicio;
            do
            {
                printf("{%s, ", aux->valor.nome);
                printf("%s, ", aux->valor.email);
                printf("%s, ", aux->valor.cpf);
                printf("%d, ", aux->valor.codigo);
                printf("%.2f, ", aux->valor.valor_gasto);
                printf("%d} ", aux->valor.quant_pedidos);
                mostrar_pagamentos(aux->valor);
                mostrar_pedidos(aux->valor);
                mostrar_enderecos(aux->valor);
                printf("\n");
                aux = aux->prox;
            }while(aux != NULL);
            printf (" ]\n");
        }
    }
}

int alterarSenha (Lista_cliente *l, int codigo, char *nova_senha1, char *nova_senha2)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST; 

    No_cliente *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {        
        if (strcmp(nova_senha1, nova_senha2) == 0)
        {
            strcpy(aux->valor.senha_8d, nova_senha1);
        }
    } else return 1;
    return 0;
}

int comparar_char (char *a, char *b)
{
    if (strlen(a) != strlen(b)) return 2;
    if (strcmp(a, b) != 0) return 3;
    return 0;
}

int alterarEmail (Lista_cliente *l, int codigo, char *novo_email)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST; 

    No_cliente *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        strcpy(aux->valor.senha_8d, novo_email);
    } else return 1;
    return 0;
}

int loginCliente (Lista_cliente *l, char *email, char *senha, Cliente *item)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux = l->inicio;

    while (aux->prox != NULL && (strcmp(aux->valor.email, email) != 0))
    {
        aux = aux->prox;
    }

    if (strcmp(aux->valor.email, email) != 0) return 1;
    if ((strcmp(aux->valor.email, email) == 0) && (strcmp(aux->valor.senha_8d, senha) == 0))
    {
        copiarCliente(&aux->valor, &(*item));
        return 0;
    }
    return 1;
}

void copiarCliente (Cliente *A, Cliente *B) // função de auxílio. copia todas as informações de um elemento para outro
{
    int i;
    B->quant_pedidos = A->quant_pedidos;
    B->valor_gasto = A->valor_gasto;
    B->codigo = A->codigo;
    B->quantidade_cartoes = A->quantidade_cartoes;
    strcpy (B->cpf, A->cpf);
    strcpy (B->email, A->email);
    strcpy (B->nome, A->nome);
    strcpy (B->senha_8d, A->senha_8d);

    B->pagamentos = (cartao*) realloc (B->pagamentos, A->quantidade_cartoes*sizeof(cartao));
    for (i = 0; i < A->quantidade_cartoes; i++)
    {
        B->pagamentos[i].cvv = A->pagamentos[i].cvv;
        strcpy(B->pagamentos[i].numero, A->pagamentos[i].numero);
        strcpy(B->pagamentos[i].tipo, A->pagamentos[i].tipo);
        strcpy(B->pagamentos[i].validade, A->pagamentos[i].validade);
    }

    B->historico = (hist_pedidosClientes*) realloc (B->historico, A->quant_pedidos*sizeof(hist_pedidosClientes));
    for (i = 0; i < A->quant_pedidos; i++)
    {
        B->historico[i].valor = A->historico[i].valor;
        strcpy(B->historico[i].nome_prato, A->historico[i].nome_prato);
        strcpy(B->historico[i].nome_rest, A->historico[i].nome_rest);
    }

    B->enderecos = (endereco*) realloc (B->enderecos, A->quant_enderecos*sizeof(endereco));
    for (i = 0; i < A->quant_enderecos; i++)
    {
        strcpy(B->enderecos[i].cep, A->enderecos[i].cep);
        strcpy(B->enderecos[i].numero, A->enderecos[i].numero);
        strcpy(B->enderecos[i].rua, A->enderecos[i].rua);
    }
}

int buscarItemCliente (Lista_cliente *l, int codigo, Cliente *item) // busca o entregador correspondente ao codigo e retorna ele por parametro
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaCliente(l) == 0) return EMPTY_LIST;

    No_cliente *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        copiarCliente(&(aux->valor), &(*item));
        return 0;
    }
    else return 1;
}