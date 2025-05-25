#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// グラフ構造体（隣接リスト表現）
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* adjList[MAX_VERTICES];
    int numVertices;
} Graph;

// 新しいノードを作成
Node* create_node(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// グラフを初期化
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    
    return graph;
}

// エッジを追加（無向グラフ）
void add_edge(Graph* graph, int src, int dest) {
    // src -> dest
    Node* newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
    
    // dest -> src（無向グラフの場合）
    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// DFS実装（再帰版）
void dfs_recursive(Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    
    Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            dfs_recursive(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// DFS実装（スタック版）
void dfs_iterative(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    int stack[MAX_VERTICES];
    int top = -1;
    
    // スタックに開始頂点をプッシュ
    stack[++top] = startVertex;
    
    while (top >= 0) {
        int currentVertex = stack[top--];
        
        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
            printf("%d ", currentVertex);
            
            // 隣接する頂点をスタックに追加
            Node* temp = graph->adjList[currentVertex];
            while (temp != NULL) {
                if (!visited[temp->vertex]) {
                    stack[++top] = temp->vertex;
                }
                temp = temp->next;
            }
        }
    }
}

// キュー構造体（BFS用）
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool is_empty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("キューが満杯です\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (is_empty(q)) {
        printf("キューが空です\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// BFS実装
void bfs(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue* q = create_queue();
    
    visited[startVertex] = true;
    enqueue(q, startVertex);
    
    printf("BFS traversal: ");
    
    while (!is_empty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        Node* temp = graph->adjList[currentVertex];
        
        while (temp) {
            int adjVertex = temp->vertex;
            
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    
    printf("\n");
    free(q);
}

// 最短経路を求めるBFS
void shortest_path_bfs(Graph* graph, int start, int end) {
    bool visited[MAX_VERTICES] = {false};
    int parent[MAX_VERTICES];
    int distance[MAX_VERTICES];
    Queue* q = create_queue();
    
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
        distance[i] = -1;
    }
    
    visited[start] = true;
    distance[start] = 0;
    enqueue(q, start);
    
    while (!is_empty(q)) {
        int currentVertex = dequeue(q);
        
        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                parent[adjVertex] = currentVertex;
                distance[adjVertex] = distance[currentVertex] + 1;
                enqueue(q, adjVertex);
                
                if (adjVertex == end) {
                    break;
                }
            }
            temp = temp->next;
        }
    }
    
    if (distance[end] != -1) {
        printf("最短距離（%dから%d）: %d\n", start, end, distance[end]);
        printf("経路: ");
        
        int path[MAX_VERTICES];
        int pathIndex = 0;
        int current = end;
        
        while (current != -1) {
            path[pathIndex++] = current;
            current = parent[current];
        }
        
        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("頂点%dから%dへの経路が存在しません\n", start, end);
    }
    
    free(q);
}

// グラフを表示
void print_graph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjList[v];
        printf("頂点 %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    Graph* graph = create_graph(6);
    
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 5);
    add_edge(graph, 3, 5);
    
    printf("グラフの隣接リスト:\n");
    print_graph(graph);
    printf("\n");
    
    bool visited[MAX_VERTICES] = {false};
    
    printf("DFS（再帰版）: ");
    dfs_recursive(graph, 0, visited);
    printf("\n");
    
    printf("DFS（反復版）: ");
    dfs_iterative(graph, 0);
    printf("\n");
    
    bfs(graph, 0);
    printf("\n");
    
    shortest_path_bfs(graph, 0, 5);
    
    return 0;
}
