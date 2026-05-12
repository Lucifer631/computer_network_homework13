#include <stdio.h>
#include <string.h>

#define MAX_NET 5   // 最大网络数量（题目中N1-N5共5个）
#define NAME_LEN 10 // 网络名称长度

// 路由表条目结构体
typedef struct {
    char dest[NAME_LEN];   // 目的网络（N1/N2/N3/N4/N5）
    int hop;               // 跳数
    char nextHop[NAME_LEN];// 下一跳
} Route;

// RIP路由更新核心函数
void updateRIP(Route r1[], Route r2[]) {
    // 遍历R2发来的所有路由条目
    for (int i = 0; i < MAX_NET; i++) {
        // RIP规则：收到邻居路由，跳数+1
        int newHop = r2[i].hop + 1;
        char newNext[] = "R2";

        // 遍历R1路由表，查找对应目的网络
        for (int j = 0; j < MAX_NET; j++) {
            if (strcmp(r1[j].dest, r2[i].dest) == 0) {
                // 规则1：直连路由（跳数0）不修改
                if (r1[j].hop == 0) {
                    break;
                }
                // 规则2：新跳数更小 → 更新；下一跳是R2 → 强制更新
                if (newHop < r1[j].hop || strcmp(r1[j].nextHop, newNext) == 0) {
                    r1[j].hop = newHop;
                    strcpy(r1[j].nextHop, newNext);
                }
                break;
            }
        }
    }
}

// 打印路由表
void printRoute(Route table[], const char* name) {
    printf("===== %s =====\n", name);
    for (int i = 0; i < MAX_NET; i++) {
        printf("目的网络：%s\t跳数：%d\t下一跳：%s\n",
               table[i].dest, table[i].hop, table[i].nextHop);
    }
    printf("\n");
}

int main() {
    // 初始化 R1 原始路由表（第30题题目给定）
    Route R1[MAX_NET] = {
        {"N1", 1, "直连"},
        {"N2", 0, "直连"},
        {"N3", 5, "R3"},
        {"N4", 6, "R4"},
        {"N5", 7, "R5"}
    };

    // 初始化 R2 发来的路由表（第30题题目给定）
    Route R2[MAX_NET] = {
        {"N1", 2, ""},
        {"N2", 1, ""},
        {"N3", 3, ""},
        {"N4", 7, ""},
        {"N5", 3, ""}
    };

    // 打印更新前的路由表
    printRoute(R1, "R1更新前路由表");

    // 执行RIP更新算法
    updateRIP(R1, R2);

    // 打印更新后的路由表
    printRoute(R1, "R1更新后路由表");

    return 0;
}
