#include <iostream>
#include <cstring>  
#include <cstdio> 
#include <algorithm>
using namespace std;  
  
#define inf 65535  
#define MAXN 10  
  
typedef struct MGraph{  
    string vexs[10];//顶点信息  
    int arcs[10][10];//邻接矩阵  
    int vexnum, arcnum;//顶点数和边数  
}MGraph;  
  
int LocateVex(MGraph G, string u)//返回顶点u在图中的位置  
{  
    for(int i=0; i<G.vexnum; i++)  
        if(G.vexs[i]==u)  
            return i;  
    return -1;  
}  
  
  
//弗洛伊德算法求每一对顶点间的最短路径  
//p[v][w][i]表示当前求得的顶点v到顶点w的最短路径中的第i+1个顶点，也是打印最短路径的关键  
//D[v][w]表示当前求得的顶点v到顶点w的最短路径的长度  
void FLOYD(MGraph G, int p[MAXN][MAXN][MAXN], int D[][MAXN])  
{  
    int u, v, w, i, j;  
      
    for(v=0; v<G.vexnum; v++)  
        for(w=0; w<G.vexnum; w++)  
        {  
            D[v][w]=G.arcs[v][w];  
            for(u=0; u<G.vexnum; u++)  
                p[v][w][u]=-1;  
            if(D[v][w] < inf)  
            {  
                p[v][w][0]=v;  
                p[v][w][1]=w;  
            }  
        }  

        for(u=0; u<G.vexnum; u++)  
            for(v=0; v<G.vexnum; v++)  
                for(w=0; w<G.vexnum; w++)  
                    if(D[v][u] < inf && D[u][w] < inf && D[v][u]+D[u][w] < D[v][w])  
                    {  
                        //更新D  
                        D[v][w]=D[v][u]+D[u][w];  
                        //更新p，从v到w的路径是从v到u，再从u到w的所有路径  
                        for(i=0; i<G.vexnum; i++)  
                        {  
                            if(p[v][u][i]!=-1)  
                                p[v][w][i]=p[v][u][i];  
                            else  
                                break;  
                        }  
                        for(j=1; j<G.vexnum; j++)//j从1开始而不是从0开始，因为从v到u的路径最后一个顶点是u, 而从u到w的路径第一个顶点是u，只需打印u一次即可  
                        {  
                            if(p[u][w][j]!=-1)  
                                p[v][w][i++]=p[u][w][j];  
                            else  
                                break;  
                        }  
                          
                    }  
                    
}  

string start;
//读入文件
void read(char a[],MGraph &G){
	FILE *fp = fopen(a,"r+");
	char name[10],name2[10]; 
	int num;
	int cnt = 0;
	char dian[10];
	fscanf(fp,"%s",dian);
	//读入各点 
	for(int i = 0; i < strlen(dian); i++){
		G.vexs[cnt++] = dian[i];
	}
	fscanf(fp,"%s",dian);
	start = dian;   

    int i,j,k;  
    G.vexnum = cnt;//点数 
	for( i=0; i<G.vexnum; i++)  
        for(j=0; j<G.vexnum; j++)  
            G.arcs[i][j] = inf; //邻接矩阵 
    int s = 0;
    //读入两两点名称和其间距
	while (fscanf(fp, "%s%s%d", name, name2, &num) == 3){
		i=LocateVex(G, name);
        j=LocateVex(G, name2);  
        G.arcs[i][j] = num;  
        s++;
	}
	G.arcnum = s;	
}
	
struct node {
	string s;
	int n;
};
node a[100];
int ans = 0;
bool cmp(node a,node b){
	return a.n < b.n;
}
int main(int argv, char *args[])
{  
    MGraph g;  
    int p[MAXN][MAXN][MAXN];  
    int D[MAXN][MAXN];  
 	read(args[1],g);//读入文件 
    for(int  i=0; i<g.vexnum; i++)  
        g.arcs[i][i]=0; //初始化 
   	FLOYD(g, p, D); //调用弗洛伊德算法
    int i;
    for(i = 0; i<g.vexnum; i++){
    	if(g.vexs[i] == start)
		break;
	}
    for(int j = 0; j < g.vexnum-1; j++){  
        if(i != j)  
        {  
            if(D[i][j] != inf)  
            {  
                for(int k=0; k<g.vexnum; k++)  
                {  
                    if(p[i][j][k]!=-1)  
                    	a[ans].s += g.vexs[p[i][j][k]];
                    else  
                        break;  
                }  
                a[ans].s += "_";
				a[ans++].n = D[i][j]; 
            }    
        }  
    }  
	sort(a,a+ans,cmp);//排序 
	for(int i = 0; i < ans; i++){
		cout << a[i].s << a[i].n << endl;
	}  
  return 0;
}

