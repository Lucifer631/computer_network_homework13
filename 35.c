#include <stdio.h>
#include <limits.h>

// 宏定义
#define MAX_NODE 20    // 最大节点数（路由器/交换机数量）
#define INF INT_MAX    // 无穷大（表示不可达）

// 全局邻接矩阵存储图
int graph[MAX_NODE][MAX_NODE];
// 节点总数
int node_num = 0;

// 初始化图：所有边设为不可达
void initGraph() {
    for (int i = 0; i < MAX_NODE; i++) {
        for (int j = 0; j < MAX_NODE; j++) {
            graph[i][j] = INF;
        }
    }
}

// Dijkstra算法：src为源节点，计算到所有节点的最短路径
void dijkstra(int src) {
    // dist[i]：源节点到i的最短距离
    int dist[MAX_NODE];
    // path[i]：i的前驱节点（用于回溯路径）
    int path[MAX_NODE];
    // visited[i]：节点i是否已确定最短路径
    int visited[MAX_NODE] = {0};

    // 初始化
    for (int i = 0; i < MAX_NODE; i++) {
        dist[i] = graph[src][i];
        path[i] = (dist[i] != INF) ? src : -1;
    }
    dist[src] = 0;    // 源节点到自身距离为0
    visited[src] = 1; // 标记源节点已处理

    // 遍历剩余所有节点
    for (int i = 1; i < MAX_NODE - 1; i++) {
        // 步骤1：找到未访问的距离最小的节点
        int min = INF;
        int u = -1;
        for (int j = 0; j < MAX_NODE; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 无可达节点，退出
        visited[u] = 1;

        // 步骤2：松弛操作，更新最短路径
        for (int v = 0; v < MAX_NODE; v++) {
            if (!visited[v] && graph[u][v] != INF
                && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }

    // 输出结果
    printf("\n===== 从源节点 %d 出发的最短路径 =====\n", src);
    for (int i = 0; i < MAX_NODE; i++) {
        if (dist[i] == INF) {
            printf("节点 %d：不可达\n", i);
            continue;
        }
        if (i == src) continue;

        printf("节点 %d：最短路径长度 = %d，路径：", i, dist[i]);
        // 回溯路径
        int stack[MAX_NODE], top = 0;
        int cur = i;
        while (cur != -1) {
            stack[top++] = cur;
            cur = path[cur];
        }
        // 逆序输出
        for (int j = top - 1; j >= 0; j--) {
            printf("%d", stack[j]);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }
}

// 解析输入的三元组 (a,b,weight)，构建无向图
void inputGraph() {
    int a, b, weight;
    char ch;
    printf("请输入图的三元组，格式：(r1,r2,weight) (r3,r4,weight) ...\n");
    printf("输入完成后按回车结束：\n");

    // 循环读取所有三元组
    while (1) {
        // 跳过非'('字符
        while ((ch = getchar()) != '(' && ch != '\n');
        if (ch == '\n') break;

        // 读取三元组数值
        scanf("%d,%d,%d", &a, &b, &weight);
        // 跳过')'
        getchar();

        // 构建无向图（双向连通）
        graph[a][b] = weight;
        graph[b][a] = weight;

        // 更新最大节点数
        if (a > node_num) node_num = a;
        if (b > node_num) node_num = b;
    }
}

int main() {
    initGraph();
    inputGraph();

    int src;
    printf("请输入源节点（起点）：");
    scanf("%d", &src);

    dijkstra(src);
    return 0;
}
