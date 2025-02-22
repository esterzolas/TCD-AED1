// defines de auxilio
#define NULL_QUEUE 3
#define EMPTY_QUEUE 2

//STRUCTS
typedef struct plate pratos;
typedef struct ped pedidos;
typedef struct no_pedidosPendentes No_pedidosPendentes;
typedef struct fila Fila_PedidosPendentes;

// IMPLEMENTACOES
Fila_PedidosPendentes *
criar_filaPedidosPendentes();

int filaVazia(Fila_PedidosPendentes *f);
int filaCheia(Fila_PedidosPendentes *f);

int inserirPedidoPendente(Fila_PedidosPendentes *f, pedidos *x);
int removerPedidoPendente(Fila_PedidosPendentes *f);
int consultarProxPedido(Fila_PedidosPendentes *f, pedidos **x);

void limparFila(Fila_PedidosPendentes *f);
int tamanhoFila(Fila_PedidosPendentes *f);
void mostrarPedidosPendentes(Fila_PedidosPendentes *f);

int mostrarProxPedido(Fila_PedidosPendentes *f);
