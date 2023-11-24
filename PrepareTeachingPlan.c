#include <stdio.h>
#include <stdlib.h>

typedef char *VertexType; /* 用顶点下标表示顶点,为整型 */
typedef char *DataType;   /* 顶点存储的数据类型设为字符型 */
typedef _Bool WeightType; /* 边的权值设为布尔值 */

typedef struct Graph {
    DataType *_data;
    int _vertex_num;
    int _edge_num;
    WeightType **_gmatrix;
} Graph;

typedef struct Edge {
    int _from;
    int _to;
    WeightType _weight;
} Edge;

Graph *createNoEdgeGraph(int vertex_num, DataType *data)
{
    Graph *new_graph = (Graph *)malloc(sizeof(Graph));
    new_graph->_vertex_num = vertex_num;
    new_graph->_edge_num = 0;
    new_graph->_gmatrix = (WeightType **)malloc(sizeof(WeightType *) * vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        new_graph->_gmatrix[i] = (WeightType *)malloc(sizeof(WeightType) * vertex_num);
    }
    return new_graph;
}

void insertEdge(Graph *graph, Edge *edge)
{
    graph->_edge_num++;
    if (graph->_gmatrix[edge->_from][edge->_to] == edge->_weight && edge->_weight != 0) {
        fprintf(stderr, "Edge is existed\n");
        return;
    } else
        graph->_gmatrix[edge->_from][edge->_to] = edge->_weight;
}


int main(void)
{

    return 0;
}