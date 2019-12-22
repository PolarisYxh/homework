// Assignment_2.cpp
/*
 * 姓名:黄博  学号SY1706237
 * 主要思路：
 *     遍历：利用栈结构，通过深度优先搜索遍历路径
 *     定界：每一个最短路径值更小的可行解确定了新的下界
 *     剪枝：先利用Dijkstra算法计算每个城市到目的城市的最短路径和最小花费，当算法运行到某个城市后，
 *          计算在栈里的城市的路径长度 + 这个城市到目的城市的最短路径，以及在栈里的城市的路径花费 + 这个城市到目的地的最小花费，
 *          与当前最优的可行解以及约束条件进行比较，从而达到剪枝的目的
 */


#include <iostream>
#include <fstream>
#include <deque>
#include <time.h>

using namespace std;

#define MAX_NODE 60 // 最大节点数
#define MAX_INT 9999 // 定义最大整数
#define MAX_COST 1500 // 定义最大花费

int n1, n2; // 分别表示矩阵的行和列
deque<int> queueMinPath; // 记录已得到的最短路径
int minPath; // 记录最短路径长度
int costOfMinPath; // 记录最短路径的花费

int main(int argc, char* argv[]) {

    clock_t startTime, endTime;
    startTime = clock();

    cout << endl << "程序开始运行" << endl << endl;

    int** readTxtToArrayWithoutKnowRowOrColumn(const char* strPath); // 把txt文件读进二维数组
    void findPathWithDFS(int **m1, int **m2, int fn, int tn); // 深度优先

    int pIn[MAX_INT] = { 0 }; // 记录某个城市是否在当前路径

    int** m1 = 0, **m2 = 0; // 分别保存m1.txt和m2.txt的矩阵

    cout << "从txt文件读取数据（请把txt文件和可执行文件放在同一路径下）：" << endl << endl;

    m1 = readTxtToArrayWithoutKnowRowOrColumn("m1.txt");

    m2 = readTxtToArrayWithoutKnowRowOrColumn("m2.txt");

    cout << "行数: " << n1 << ", 列数: " << n2 << endl << endl;

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (m1[i][j] == MAX_INT) {
                m2[i][j] = MAX_INT;
            }
        }
    }

    minPath = MAX_INT;
    findPathWithDFS(m1, m2, 0, n1 - 1);

    cout << "满足条件的最短路径长度为: " << minPath << endl << endl;
    cout << "满足条件的最短路径的花费为: " << costOfMinPath << endl << endl;
    cout << "最短路径为: " << endl << endl;
    for (int is = 0; is < queueMinPath.size(); is++) {
        cout << "\t" << queueMinPath[is] + 1;
    }
    cout << endl << endl;

    cout << "程序运行结束" << endl << endl;
    endTime = clock();
    cout << "总共耗时: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " 秒" << endl << endl;

    cout << "按 <Enter> 即可退出程序" << endl;
    getchar();

    return 0;
}

void findPathWithDFS(int **m1, int **m2, int fn, int tn) {
    int calculateShortestByDijkstra(int **m1, int fn, int tn); // 根据a矩阵计算从fn到tn的最短距离或者最小花费
    int p1[MAX_NODE] = { 0 }, c1[MAX_NODE] = { 0 }; // 分别保存各个城市到目的地的最短路径和最小花费
    int pMin = MAX_INT, cNow = MAX_INT; // 分别记录当前到的路径的最小路径长度和当前花费

    cout << "先用Dijkstra算法求出每个城市到目的城市的最短路径和最小花费" << endl << endl;
    // 各个城市到达目的城市的最短路径
    for (int i = 0; i < n1; i++) {
        p1[i] = calculateShortestByDijkstra(m1, i, n1 - 1);
    }
    // 各个城市到达目的城市的最小花费
    for (int i = 0; i < n1; i++) {
        c1[i] = calculateShortestByDijkstra(m2, i, n1 - 1);
    }

    cout << "再用分枝定界算法求满最大花费不超过" << MAX_COST << "的最短路径" << endl << endl;
    deque<int> stackPathNode;
    stackPathNode.push_back(fn);
    int nPath[MAX_NODE] = { 0 };
    nPath[fn] = 1;
    int lastOut = -1;
    int tag = 0; // 标记是否找到下一个城市
    int pathLengthNow = 0; // 当前已经走到的路径长度
    int pathCostNow = 0; // 当前已经走到的路径的花费
    int nNow;
    while (!stackPathNode.empty()) { // 栈为空
        nNow = stackPathNode.back();
        for (int i = 0; i < n1; i++) {
            if (nPath[i] == 1 || i <= lastOut || nPath[i] == 1)
                continue;
            if (m1[nNow][i] < MAX_INT) {
                // 根据当前能够获取的最短路径长度和最小花费确定是否剪枝
                if (pathLengthNow + p1[i] >= minPath || pathCostNow + c1[i] > MAX_COST) {
                    // 当前路径的最优解没有已有的可行解好，或者当前路径的最小花费超过 MAX_COST
                    continue;
                }
                if (pathLengthNow + m1[nNow][i] >= minPath || pathCostNow + m2[nNow][i] > MAX_COST){
                    continue;
                }
                if (i == tn) {
                    // 找到一条更好的路径，如下
                    minPath = pathLengthNow + m1[nNow][i];
                    costOfMinPath = pathCostNow + m2[nNow][i];
                    pathLengthNow = minPath;
                    pathCostNow = costOfMinPath;
                    stackPathNode.push_back(i);
                    queueMinPath = stackPathNode;
                    break;

                }
                else {
                    // 当前城市有下一个城市可以寻得最优解，下一个城市入栈
                    tag = 1;
                    stackPathNode.push_back(i);
                    nPath[i] = 1;
                    pathLengthNow += m1[nNow][i];
                    pathCostNow += m2[nNow][i];
                    lastOut = -1;
                    break;
                }
            }

        }

        if (tag == 0) {
            // 当前城市没有下一个城市可以寻得最优解，当前城市出栈
            lastOut = stackPathNode.back();
            stackPathNode.pop_back();
            if (stackPathNode.empty()) {
                break;
            }
            nNow = stackPathNode.back();
            nPath[lastOut] = 0;
            pathLengthNow -= m1[nNow][lastOut];
            pathCostNow -= m2[nNow][lastOut];
        }
        tag = 0;
    }
}

int** readTxtToArrayWithoutKnowRowOrColumn(const char* strPath) { // 把txt文件读进二维数组
    int** a = new int*[MAX_NODE];
    for (int i = 0; i < MAX_NODE; i++) {
        a[i] = new int[MAX_NODE];
    }
    int nTmp = 0;
    n1 = 0;
    n2 = 0;
    ifstream is(strPath);
    if (!is) {
        cout << "open file error!" << endl;
    }
    else {
        char p;
        int num;
        int j = 0;
        while (is.get(p)) { // 判断是否到达文末
            do {
                if (p == '\n') {
                    n1++; // 统计行数
                    if (n2 == 0) {
                        n2 = nTmp; // 实际上只统计了第一行的列数
                    }
                    j = 0;
                    // cout << endl; // 一行之后输出一个回车符
                }
            } while (isspace((int)p) && is.get(p));
            if (!is)
                break;
            nTmp++; // 统计列数
            is.putback(p); // 如果前面读入的不是空格或者回车符，则把刚才读入的字符返回文件流
            is >> num;
            // cout << num << "\t";
            a[n1][j++] = num;
        }
    }
    is.close();
    return a;
}

int calculateShortestByDijkstra(int **m1, int fn, int tn) { // 根据距离矩阵计算从fn到tn的最短距离或者最小花费

    if (fn == tn) {
        return 0;
    }

    int p[MAX_NODE] = { 0 }; // 记录当前路径长度
    int pt[MAX_NODE] = { 0 }; // 记录当前路径是否是最短路径，1表示是

    for (int i = 0; i < MAX_NODE; i++) {
        if (i != fn)
            p[i] = MAX_INT;
    }

    p[fn] = 0; // nf到nf的路径为0
    pt[fn] = 1; // 当前nf到nf的路径是最短路径

    for (int i = 0; i < n1 - 1; i++) { // 求n个节点中1个节点到另一个节点的最短路径最多需要n-1步
        for (int j = 0; j < n1; j++) {
            if (pt[j] != 1) {
                // 还没有求出第nf第j个节点的最短路径
                for (int k = 0; k < n1; k++) {
                    // 计算nf到第j个节点的路径
                    if (pt[k] == 1) {
                        // k是已经求出最短路径的节点
                        if (m1[k][j] < MAX_INT) {
                            // 如果k到j有路径
                            if ((p[k] + m1[k][j]) < p[j]) {
                                p[j] = p[k] + m1[k][j];
                            }
                        }
                    }

                }
            }
        }

        int tmp = MAX_INT;
        for (int j = 0; j < n1; j++) {//找最小值
            if (pt[j] != 1) {
                if (p[j] < tmp) {
                    tmp = p[j];
                }
            }
        }

        for (int j = 0; j < n1; j++) {
            if (pt[j] != 1) {
                if (p[j] == tmp) {
                    pt[j] = 1;
                    if (j == tn) {
                        return p[j];
                    }
                }
            }
        }
    }
    return -1;
}
