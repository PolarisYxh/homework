import numpy as np

class shortest:
    def __init__(self,lenth_m,value_m):
        self.m1=lenth_m
        self.m2=value_m
        self.size_m1=np.size(m1,0)
        self.size_m2=np.size(m2,0)
        self.floydlenth=lenth_m
        self.minlenth=self.dij(np.size(m1,0),m1)#每个点到终点的最短距离列表
        self.minvalue=self.dij(np.size(m2,0),m2)#每个点到终点的最小花费列表
        self.visloc=np.zeros(self.size_m1)
        self.bestlen=9999
        self.bestvalue=9999
        self.pathllist=[1]
        self.bestlist=[1]


    def argmin(self,l,vis):
        min=9999
        minloc=9999
        for i in range(0,np.size(l,0)):
            if(vis[i]!=1 and l[i]<min):
                minloc=i
                min=l[i]
        return minloc
                    
    def dij(self,start,m):#m1是距离矩阵，判断城市间是否相通
        vislenloc=np.zeros(np.size(m,0))
        lenth=np.empty(np.size(m,0))
        lenth[:]=9999
        lenth[start-1]=0
        while(1):
            lenloc=self.argmin(lenth,vislenloc)
            if(lenloc==9999):
                break

            vislenloc[lenloc]=1
            for i in range(0,lenloc+1):
                if(self.m1[i][lenloc]<9999 and vislenloc[i]==0):
                    if(m[i][lenloc]+lenth[lenloc]<lenth[i]):
                        lenth[i]=m[i][lenloc]+lenth[lenloc]
        print(lenth)
        return lenth

    def floyd(self):
        x=np.size(self.floydlenth,0)
        for k in range(0,x):
            for i in range(0,x):
                for j in range(0,x):
                    self.floydlenth[i][j]=min(self.floydlenth[i][j],self.floydlenth[i][k]+self.floydlenth[k][j])
        print(self.floydlenth)

    def dfs(self,start,lenth,value): 
        lendic={}
        if(start==self.size_m1-1 and self.bestlen>lenth):
            self.bestlen=lenth
            self.bestvalue=value
            self.bestlist=self.pathllist[:]#按值拷贝
            return
        for i in range(0,self.size_m1):
            if(self.m1[start][i]<9999 and self.visloc[i]==0):
                lendic.update({i:lenth+self.m1[start][i]+self.minlenth[i]})
        if not lendic:
            return
        dic=sorted(lendic.items(),key=lambda item:item[1])                     #排序[(1,5),(2,8)...]
        minlimit=dic[0][1]
        if(value+self.minvalue[start]>=1500 or minlimit>self.bestlen):
            return

        for s in dic:
            i=s[0]
            self.visloc[i]=1
            self.pathllist.append(i+1)
            self.dfs(i,lenth+self.m1[start][i],value+self.m2[start][i])
            self.pathllist.pop()
            self.visloc[i]=0
        
        



if __name__ == "__main__":
    m1 = np.loadtxt('.\\m1.txt',dtype=int)
    m2=np.loadtxt('.\\m2.txt',dtype=int)
    print(m1,'\n',m2)
    lenval=shortest(m1,m2)
    lenval.visloc[0]=1
    lenval.dfs(0,0,0)
    print("最短路径：")
    print(lenval.bestlist)
    print("最短路程：%d"%lenval.bestlen)
    print("最短路径花费：%d"%lenval.bestvalue)