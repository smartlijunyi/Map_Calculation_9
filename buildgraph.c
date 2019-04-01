#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "structure.h"
#include "readfile.h"
#include "buildgraph.h"

LGraph CreateGraph(int Nodenum){ 
	Vertex V;
	LGraph Graph;
     	Graph = (LGraph)malloc(sizeof(struct GNode)); 
	Graph->Nv = Nodenum;
	Graph->Ne = 0;
        for (V=0; V<Graph->Nv; V++)
       		Graph->G[V].FirstEdge = NULL;
        return Graph; 
}

void InsertEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
     
    	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    	NewNode->AdjV = E->V2;
    	NewNode->Weight = E->Weight;
    	
    	
    	NewNode->Next = Graph->G[E->V1].FirstEdge;
    	Graph->G[E->V1].FirstEdge = NewNode;
         
    	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    	NewNode->AdjV = E->V1;
    	NewNode->Weight = E->Weight;
    	
    	
    	NewNode->Next = Graph->G[E->V2].FirstEdge;
    	Graph->G[E->V2].FirstEdge = NewNode;
}

void load(ids s){
	int i = 0;
	FILE *fp;
	fp = fopen("linkinfo.txt","r");
	while( i < 2344 ){
		fscanf(fp,"%i%i%lf",&s[i].node1,&s[i].node2,&s[i].length);
		i++;
	}
	fclose(fp);
}

void oldnew(newn n){
	int i = 0;
	FILE *fp;
	fp = fopen("nodeinfo.txt","r");
	while( i < 3941 ){
		fscanf(fp,"%i%i%lf%lf",&n[i].newid,&n[i].oldid,&n[i].lon,&n[i].lat);
		i++;
	}
}

int findid(newn n,int oldid){
	int newid;
	for(int i = 0; i < 3941; i++){
		if( oldid == n[i].oldid ){
			newid = n[i].newid;
			break;
		}
	}
	return newid;
}

double get_lon(newn n,int id){
	int i = 0;
	double lon;
	for(i = 0; i < 3941; i++){
		if( id == n[i].oldid || id == n[i].newid){
			lon = n[i].lon;
			break;
		}
	}
	return lon;
}

double get_lat(newn n,int id){
	int i = 0;
	double lat;
	for(i = 0; i < 3941; i++){
		if( id == n[i].oldid || id == n[i].newid){
			lat = n[i].lat;
			break;
		}
	}
	return lat;
}

LGraph BuildGraph(newn n){
	LGraph Graph;
	Edge E;
	Vertex V;
    	int Nv, i;
    	Nv = 3941;
     	Graph = CreateGraph(Nv);
    	FILE *fp1,*fp2; 
     	fp1 = fopen("nodeinfo.txt","r");
	fp2 = fopen("linkinfo.txt","r");
	Graph->Ne = 2344;
    	if ( Graph->Ne != 0 ) { 
        	E = (Edge)malloc(sizeof(struct ENode));  
        	for (i = 0; i < Graph->Ne; i ++) {
        	int a,b;
        	double c;
            		fscanf(fp2,"%i%i%lf",&a,&b,&c);
            		E->V1 = findid(n,a);
            		E->V2 = findid(n,b);
            		E->Weight = c;
            		
            		InsertEdge(Graph,E);
        	}
    	} 
 
    	for (V = 0; V < Graph->Nv; V++) 
 		fscanf(fp1,"%i%i%lf%lf",&(Graph->G[V].newid),&(Graph->G[V].Data),&(Graph->G[V].lon),&(Graph->G[V].lat));
 	fclose(fp1);
 	fclose(fp2);
 	return Graph;
}
