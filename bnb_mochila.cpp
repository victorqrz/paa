#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct {
    int id;       //Identificação do nó
    int *sol;     //Vetor binário que contém a solução parcial do nó
    int solW;     //Peso da solução parcial
    int solV;     //Valor da solução parcial
    int nextItem; //Índice (no vetor items) do próximo item a ser considerado
    int ub;       //Limitante superior considerando a solução parcial
} tNode;

typedef struct {
    int id; //Identificação do item (corresponde à ordem da entrada)
    int v;  //Valor do item
    int w;  //Peso do item
} tItem;

typedef struct {
    int size;      //Tamanho atual da fila (número de elementos)
    int maxSize;   //Tamanho máximo que a fila suporta
    tNode *nodes;  //Vetor contendo os nós na fila
} tQueue;

int globalLb;        //Valor da melhor solução global
int *globalBestSol;  //Melhor solução global
int nItems;          //Número de items da entrada
tItem *items;        //Itens da entrada
int W;               //Capacidade da mochila
int nodeCount = 0;   //Contador de nós da árvore de estado

//Funções auxiliares para comparação de itens (por razão valor/peso) e de nós (por limitante)
int compItem(const void* item1, const void* item2);
int compNode(const void* node1, const void* node2);

//Função para calcular o limitante superior em um nó
int setNodeUb(tNode *n);

//Funções para manipular a fila
//createQueue() cria uma fila vazia com o tamanho máximo especificado
//insertNode() insere um nó n na fila q na mantendo a fila ordenada pelo limitante
//caso a fila já esteja cheia, o tamanho máximo da fila é duplicado
//removeNode() remove o primeiro nó da fila e puxa os demais elementos para o início
tQueue createQueue(int size);
void insertNode(tQueue *q, tNode n);
tNode removeNode(tQueue *q);


int main(){
    int v, w, i = 0;
    tQueue q;
    tNode node, node1, node2;
    scanf("%d", &W); //Leitura da capacidade da mochila
    scanf("%d", &nItems); //Leitura do número de itens
    items = (tItem *)malloc(nItems*sizeof(tItem)); //Alocação de espaço para os itens
    
    //Leitura do valor e peso de cada item
    i = 0;
    while(scanf("%d %d", &v, &w) != EOF){
        items[i].id = i+1;
        items[i].v = v;
        items[i++].w = w;
    }
    
    printf("Mochila lida\n");
    printf("Capacidade: %d\n", W);
    printf("Itens:\n");
    for(i = 0; i < nItems; i++) printf("id = %d v = %d w = %d\n", items[i].id, items[i].v, items[i].w);
    printf("\n");
    
    //Ordena os itens em ordem decrescente de valor/peso
    qsort(items, nItems, sizeof(tItem), compItem);
    
    printf("Itens reordenados:\n");
    for(i = 0; i < nItems; i++) printf("id = %d v = %d w = %d\n", items[i].id, items[i].v, items[i].w);
    printf("\n");
    
    //Aloca espaço e inializa melhor solução global e valor da melhor solução global
    globalBestSol = (int *)malloc(nItems*sizeof(int));
    for(i = 0; i < nItems; i++) globalBestSol[i] = 0;
    globalLb = 0;
    
    //Cria fila vazia
    q = createQueue(2*nItems);
    
    printf("Fila vazia criada.\n\n");

    //Criação do nó raiz da árvore
    node.id = nodeCount++;
    node.sol = (int *)malloc(nItems*sizeof(int));
    for(i = 0; i < nItems; i++) node.sol[i] = 0; //Nenhum item na mochila no início
    node.solW = 0;
    node.solV = 0; //A solução parcial está vazia, portanto seu valor e peso são 0
    node.nextItem = 0; //O primeiro item a ser considerado é o de índice 0 no vetor
    setNodeUb(&node); //Calcula o limitante superior na raiz
    insertNode(&q, node); //Insere o nó raiz na fila
    printf("Nó raiz criado.\n\n");
    
    //Enquanto existirem nós ativos continuamos a busca
    while(q.size != 0){
        //Cada passo da busca consiste em explorar o próximo nó
        node = removeNode(&q);
        printf("############################\n");
        printf("Nó %d:\n", node.id);
        printf("ub: %d\n", node.ub);
        printf("Próximo item: %d\n", node.nextItem);
        printf("ID próximo item: %d\n", items[node.nextItem].id);
        printf("Valor sol. parcial: %d, peso sol. parcial: %d\n", node.solV, node.solW);
        printf("Solução parcial: ");
        for(i = 0; i < nItems; i++)
            if(node.sol[i])
                printf("%d ", items[i].id);
        printf("\n");
        printf("############################\n\n");
        
        //Podas por limitante e inviabilidade
        if(node.ub > globalLb  && node.solW <= W){
            if(node.solV > globalLb){
                globalLb = node.solV;
                for(i = 0; i < nItems; i++){
                    globalBestSol[i] = node.sol[i];
                }
            }
            
            //Poda por "otimalidade" (não existem mais itens a considerar)
            if(node.nextItem < nItems){
                
                //Criação do primeiro filho do nó
                node1.id = nodeCount++;
                node1.sol = (int *)malloc(nItems*sizeof(int));
                memcpy(node1.sol, node.sol, nItems*sizeof(int));
                node1.sol[node.nextItem] = 1;
                node1.solW = node.solW+items[node.nextItem].w;
                node1.solV = node.solV+items[node.nextItem].v;
                node1.nextItem = node.nextItem+1;
                setNodeUb(&node1);
                insertNode(&q, node1);
                
                //Criação do segundo filho do nó
                node2.id = nodeCount++;
                node2.sol = (int *)malloc(nItems*sizeof(int));
                memcpy(node2.sol, node.sol, nItems*sizeof(int));
                node2.sol[node.nextItem] = 0;
                node2.solW = node.solW;
                node2.solV = node.solV;
                node2.nextItem = node.nextItem+1;
                setNodeUb(&node2);
                insertNode(&q, node2);
            }else{
                printf("Nó %d podado por \"otimalidade\".\n\n", node.id);
                free(node.sol);
            }
        }else{
            if(node.ub > globalLb){
                printf("Nó %d podado por inviabilidade.\n\n", node.id);
            }else{
                printf("Nó %d podado por limitante.\n\n", node.id);
            }
            free(node.sol);
        }
    }
    printf("Valor da solução ótima: %d\n", globalLb);
    printf("Solução ótima: ");
    for(i = 0; i < nItems; i++){
        if(globalBestSol[i]) printf("%d ", items[i].id);
    }printf("\n");
    
    free(globalBestSol);
}


int compItem(const void* item1, const void* item2){
    tItem i1 = *(tItem*)item1, i2 = *(tItem*)item2;
    if(fabs(i1.v/i1.w - i2.v/i2.w) < 0.000001) return 0;
    else if(i1.v/i1.w > i2.v/i2.w) return -1;
    else return 1;
}

int compNode(const void* node1, const void* node2){
    tNode n1 = *(tNode*)node1, n2 = *(tNode*)node2;
    return n2.ub-n1.ub;
}


//Função para calcular o limitante como descrito nos slides
/*int setNodeUb(tNode *n){
    return n->ub = n->solV+(items[n->nextItem].v/items[n->nextItem].w)*(W-(n->solW));
}*/

//Função melhor para calcular o limitante
int setNodeUb(tNode *n){
    int i = n->nextItem,  ub = n->solV, w = n->solW;
    while(i < nItems && w+items[i].w <= W){
        w += items[i].w;
        ub += items[i++].v;
    }
    ub += (int)((items[i].v/items[i].w)*(W-w));
    n->ub = ub;
    return ub;
}

tQueue createQueue(int size){
    tQueue q;
    q.size = 0;
    q.maxSize = size;
    q.nodes = (tNode *)malloc(size*sizeof(tNode));
    return q;
}

void insertNode(tQueue *q, tNode n){
    int i, j, max = q->maxSize;
    tNode *q2, temp;
    //Se a fila está cheia, dobramos a capacidade da fila
    if(q->size == max){
        q2 = (tNode *)malloc(2*max*sizeof(tNode));
        for(i = 0; i < max; i++){
            q2[i] = q->nodes[i];
        }
        free(q->nodes);
        q->nodes = q2;
        q->maxSize = 2*max;
    }
    //O nó é inserido na posição adequada na fila
    i = q->size;
    q->nodes[i] = n;
    while(i > 0 && compNode(&n, &(q->nodes[i-1])) < 0){
        q->nodes[i] = q->nodes[i-1];
        q->nodes[i-1] = n;
        i--;
    }
    q->size += 1;
    return;
}


tNode removeNode(tQueue *q){
    int i;
    tNode res = q->nodes[0]; //O primeiro nó é removido
    //Os demais nós são deslocados para o início
    for(i = 0; i < q->size-1; i++){
        q->nodes[i] = q->nodes[i+1];
    }
    q->size -= 1;
    return res; 
}
