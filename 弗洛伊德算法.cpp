#include <iostream>
#include <cstring>  
#include <cstdio> 
#include <algorithm>
using namespace std;  
  
#define inf 65535  
#define MAXN 10  
  
typedef struct MGraph{  
    string vexs[10];//������Ϣ  
    int arcs[10][10];//�ڽӾ���  
    int vexnum, arcnum;//�������ͱ���  
}MGraph;  
  
int LocateVex(MGraph G, string u)//���ض���u��ͼ�е�λ��  
{  
    for(int i=0; i<G.vexnum; i++)  
        if(G.vexs[i]==u)  
            return i;  
    return -1;  
}  
  
  
//���������㷨��ÿһ�Զ��������·��  
//p[v][w][i]��ʾ��ǰ��õĶ���v������w�����·���еĵ�i+1�����㣬Ҳ�Ǵ�ӡ���·���Ĺؼ�  
//D[v][w]��ʾ��ǰ��õĶ���v������w�����·���ĳ���  
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
                        //����D  
                        D[v][w]=D[v][u]+D[u][w];  
                        //����p����v��w��·���Ǵ�v��u���ٴ�u��w������·��  
                        for(i=0; i<G.vexnum; i++)  
                        {  
                            if(p[v][u][i]!=-1)  
                                p[v][w][i]=p[v][u][i];  
                            else  
                                break;  
                        }  
                        for(j=1; j<G.vexnum; j++)//j��1��ʼ�����Ǵ�0��ʼ����Ϊ��v��u��·�����һ��������u, ����u��w��·����һ��������u��ֻ���ӡuһ�μ���  
                        {  
                            if(p[u][w][j]!=-1)  
                                p[v][w][i++]=p[u][w][j];  
                            else  
                                break;  
                        }  
                          
                    }  
                    
}  

string start;
//�����ļ�
void read(char a[],MGraph &G){
	FILE *fp = fopen(a,"r+");
	char name[10],name2[10]; 
	int num;
	int cnt = 0;
	char dian[10];
	fscanf(fp,"%s",dian);
	//������� 
	for(int i = 0; i < strlen(dian); i++){
		G.vexs[cnt++] = dian[i];
	}
	fscanf(fp,"%s",dian);
	start = dian;   

    int i,j,k;  
    G.vexnum = cnt;//���� 
	for( i=0; i<G.vexnum; i++)  
        for(j=0; j<G.vexnum; j++)  
            G.arcs[i][j] = inf; //�ڽӾ��� 
    int s = 0;
    //�������������ƺ�����
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
 	read(args[1],g);//�����ļ� 
    for(int  i=0; i<g.vexnum; i++)  
        g.arcs[i][i]=0; //��ʼ�� 
   	FLOYD(g, p, D); //���ø��������㷨
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
	sort(a,a+ans,cmp);//���� 
	for(int i = 0; i < ans; i++){
		cout << a[i].s << a[i].n << endl;
	}  
  return 0;
}

