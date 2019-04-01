#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "structure.h"
#include "inform.h"
#include "readfile.h"
#include "buildgraph.h"
#include "shortpath.h"

int main(int argc,char *argv[]){
	LGraph Graph;
	Table T;
	ids s;
	newn n;
	read_file();
	oldnew(n);
	load(s);
	Graph = BuildGraph(n);
	DrawMap(n,s,Graph);
	int choice = 0;
	ShowMenu();
	while(1){
		printf("Please select(From 1 to 3): ");
		scanf("%i",&choice);
		if(choice == 1){
			ViewGraph(Graph);
			Info();
		}
		else if(choice == 2){
			int start,end;
			printf("\nPlease input the start point (0-2118): ");
			scanf("%i",&start);
			if(start >= 0 && start <= 2118){
				InitTable(start,Graph,T);
				Dijkstra_1(Graph,T);
				printf("Please input the end point (0-2118): ");
				scanf("%i",&end);
				if(end >= 0 && end <= 2118){
					FILE *fp1;
					fp1 = fopen("short.out","w");
					PrintOut_1(n,end,T,fp1);
					printf("\nThe total length is %lf.\n",T[end].Dist);
					fclose(fp1);
				}
				else
					printf("End ERROR!!!\n");
			}
			else
				printf("Start ERROR!!!\n");
		}
		else if(choice == 3){
			DestroyGraph(Graph);
			Exit();
			break;
		}
		else 
			printf("Please input again!\n");
	}
	return 0;
}
