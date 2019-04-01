#define MaxVertexNum 3950
#define INFINITY 65535
#define NotAVertex -1

typedef int Vertex;         
typedef double WeightType;        
typedef int DataType;
typedef double LonValue;
typedef double LatValue;        

typedef struct ENode{
   	Vertex V1, V2;      
	WeightType Weight; 
}ENode,*PtrToENode;

typedef PtrToENode Edge;




typedef struct AdjVNode *PtrToAdjVNode; 

struct AdjVNode{
   	Vertex AdjV;        
	WeightType Weight; 
	PtrToAdjVNode Next;    
};

struct Vnode{
	PtrToAdjVNode FirstEdge;
	DataType Data;
	LonValue lon;
	LatValue lat;
	Vertex newid;            
}; 

typedef struct Vnode AdjList[MaxVertexNum];   

typedef struct GNode{  
	int Nv;     
    	int Ne;     
    	AdjList G;  
}GNode,*PtrToGNode;

typedef PtrToGNode LGraph; 

struct LinkInfo{
	int node1;
	int node2;
	double length;
};

typedef struct LinkInfo ids[3000];

struct NewID{
	int newid;
	int oldid;
	double lon;
	double lat;
};

typedef struct NewID newn[3950];

struct TableEntry{
	int Known;
	double Dist;
	int Path;
};

typedef struct TableEntry Table[3950];
