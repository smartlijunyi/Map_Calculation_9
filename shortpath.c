#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "structure.h"
#include "buildgraph.h"
#include "readfile.h"
#include "shortpath.h"

void DrawMap(newn n,ids s,LGraph Graph){
	FILE *fp;
	int i = 0;
	fp = fopen("map.out","w");
	for(i = 0; i < 2344; i++){
		int m = s[i].node1;
		double m0 = get_lon(n,m);
		double m1 = get_lat(n,m);
		int x = s[i].node2;
		double n0 = get_lon(n,x);
		double n1 = get_lat(n,x);
		fprintf(fp,"%lf %lf \n",m0,m1);
		fprintf(fp,"%lf %lf \n\n\n\n",n0,n1);
	}
	fclose(fp);
}

void InitTable(Vertex Start,LGraph Graph,Table T){
	int i;
	for(i = 0; i < Graph->Nv; i++){
		T[i].Known = 0;
		T[i].Dist = INFINITY;
		T[i].Path = NotAVertex;
	}
	T[Start].Dist = 0;
}

Vertex FindMin_1(LGraph Graph,Table T){
	Vertex MinV1,V;
	double minDist = INFINITY;
	for(V = 0; V < Graph->Nv; V++){
		if(T[V].Known == 0 && T[V].Dist < minDist){
			minDist = T[V].Dist;
			MinV1 = V;
		}
	}
	if(minDist < INFINITY)
		return MinV1;
	else
		return NotAVertex;
}

void Dijkstra_1(LGraph Graph,Table T){
	Vertex V;
	PtrToAdjVNode Ptr;
	while(1){
		V = FindMin_1(Graph,T);
		if(V == NotAVertex)
			break;
		T[V].Known = 1;
		for(Ptr = Graph->G[V].FirstEdge; Ptr; Ptr = Ptr->Next){
			if(T[Ptr->AdjV].Known == 0 && T[V].Dist + Ptr->Weight < T[Ptr->AdjV].Dist){
				T[Ptr->AdjV].Dist = T[V].Dist + Ptr->Weight;
				T[Ptr->AdjV].Path = V;
			}
		}
	}
}

void PrintOut_1(newn n,Vertex E,Table T,FILE *fp){
	if(T[E].Path != NotAVertex){
		PrintOut_1(n,T[E].Path,T,fp);
		printf("-> ");
	}
	printf("%i ",E);
	fprintf(fp,"%lf %lf \n",get_lon(n,E),get_lat(n,E));
}

void ViewGraph(LGraph Graph){
	PtrToAdjVNode p;
	printf("View the adjacent list: \n");
	for(int i = 0; i < 2119; i++){
		p = Graph->G[i].FirstEdge;
		while(p){
			printf(" (%i -> %i) ",Graph->G[i].newid,Graph->G[p->AdjV].newid);
			p = p->Next;
		}
		printf("\n");
	}
}

void DestroyGraph(LGraph Graph){
	int i;
	PtrToAdjVNode p,q;
	for(i = 0; i < Graph->Nv; i++){
		p = Graph->G[i].FirstEdge;
		if(p != NULL){
			q = p->Next;
			free(p);
			p = q;
		}
	}
	Graph->Nv = 0;
	Graph->Ne = 0;
}
