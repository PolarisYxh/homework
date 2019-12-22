#include <iostream>
#include <string.h>
#include <fstream>
 
using namespace std;
const int maxn=55;
const int INF=9999999;
int minDist[maxn][maxn]; //用于存放使用Floyd算法求解的最短距离和最小花费
int minCost[maxn][maxn];
 
int dist[maxn][maxn]; //原始数据的最短距离和最小花费
int cost[maxn][maxn];
 
bool visit[maxn]; //标记结点是否被访问的数组
int path_list[maxn]; //标记当前路径的数组
int length_path=0; //标记当前路径数组的长度
 
int best_list[maxn]; //用于存放最好的路径
int bestlength=0; //用于存放最好的路径的总距离长度
int bestcost=0;//用于存放最好的路径的花费
int bestlistlength=0;//用于存放最好路径经过城市的个数，即best_list的长度
 
void init()
{
    memset(dist,0,sizeof(dist));
    memset(cost,0,sizeof(cost));
    memset(path_list,0,sizeof(path_list));
 
    path_list[0]=0;//当前路径中只有第一个城市，A城市，即为0号城市
    length_path=1;//当前路径长度为
 
    best_list[0]=0; //设置最好的路径为0-49，距离为9999，花费为15，路径长度为2
    best_list[1]=49;
    bestlength=9999;
    bestcost=15;
    bestlistlength=2;
 
    for(int i=0; i<maxn; i++) //设置所有节点都未被访问过
    {
        visit[i]=false;
    }
    visit[0]=true;//设置0号节点已被访问
 
    //读取文件中的数据
    ifstream file("m1.txt");
 
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            file>>dist[i][j];
        }
    }
//    cout<<"m1_data"<<endl;
//    for(int i=0; i<50; i++)
//    {
//        for(int j=0; j<50; j++)
//        {
//            cout<<dist[i][j]<<" ";
//        }
//        cout<<endl;
//    }
 
    file.close();
 
    ifstream file2("m2.txt");
 
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            file2>>cost[i][j];
        }
    }
//    cout<<"m2_data"<<endl;
//    for(int i=0; i<50; i++)
//    {
//        for(int j=0; j<50; j++)
//        {
//            cout<<cost[i][j]<<" ";
//        }
//        cout<<endl;
//    }
 
    file2.close();
 
    for(int i=0; i<maxn; i++) //对Floyd求最小化距离和花费进行初始化
    {
        for(int j=0; j<maxn; j++)
        {
            minDist[i][j]=dist[i][j];
            minCost[i][j]=cost[i][j];
        }
    }
}
void floyd() //利用Floyd算法求解多源最短路，其中有用的之后0-48号节点分别到第49号节点的距离
{
    for(int k=0; k<50; k++)
    {
        for(int i=0; i<50; i++)
        {
            for(int j=0; j<50; j++)
            {
                if(i==47&&j==49&&k==48)
                    int c=0;
                if(minDist[i][j]>minDist[i][k]+minDist[k][j])
                {
                    minDist[i][j]=minDist[i][k]+minDist[k][j];
                }
                if(minCost[i][j]>minCost[i][k]+minCost[k][j])
                {
                    minCost[i][j]=minCost[i][k]+minCost[k][j];
                }
            }
        }
    }
    for(int i=0;i<50;i++)
    {
        cout<<minDist[i][49]<<" ";
        
    }
    cout<<endl;
    for(int i=0;i<50;i++)
    {
        cout<<minCost[i][49]<<" ";
    }
}
 
void dfs(int p) //开始深搜一棵50*50叉树
{
    int length=0; //记录当前距离长度
    int mycost=0; //记录当前花费
    for(int i=1; i<length_path; i++)
    {
        length+=dist[path_list[i-1]][path_list[i]];
        mycost+=cost[path_list[i-1]][path_list[i]];
    }
    if(p!=49)
    {
        length+=minDist[p][49];//当前的最短路径，当前路径为0-p点真正走过的路径，
        //并加上p点到49点的最短路径（Floyd计算出的）
        mycost+=minCost[p][49];
    }
    if(length>bestlength || mycost>1500) //剪枝条件
        return;
    if(p==49)//搜索到最后一个节点即需要更新最优路径
    {
        for(int i=0; i<length_path; i++)
        {
            best_list[i]=path_list[i];
        }
 
        bestlength=length;
        bestcost=mycost;
        bestlistlength=length_path;
 
//        cout<<"cost="<<bestcost<<endl;
//        cout<<"length="<<bestlength<<endl;
//        for(int i=0;i<bestlistlength;i++)
//        cout<<best_list[i]<<" ";
//        cout<<endl;
        return;
    }
 
    for(int i=1; i<50; i++)
    {
        if(!visit[i]) //剪枝条件
        {
            visit[i]=true;
            path_list[length_path++]=i;
            dfs(i);
            //path_list[length_path--]=-1;
            length_path--;
            visit[i]=false;
        }
    }
}
 
int main()
{
    init();
    floyd();
//    for(int i=0;i<50;i++)
//    {
//        for(int j=0;j<50;j++)
//        {
//            cout<<minDist[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    for(int i=0;i<50;i++)
//    {
//        for(int j=0;j<50;j++)
//        {
//            cout<<minCost[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    dfs(0);
    cout<<"最小距离长度="<<bestlength<<endl;
    cout<<"最小花费="<<bestcost<<endl;
    cout<<"最短路径为："<<endl;
    for(int i=0; i<bestlistlength; i++)
    {
        if(i==bestlistlength-1)
            cout<<best_list[i]<<endl;
        else
        cout<<best_list[i]<<"->";
    }
 
    return 0;
}
 
 
//GCN,UAV