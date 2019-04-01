#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "inform.h"

void ShowMenu(){
	printf("\n\n");
	printf("=========Welcome to Leeds University=========\n");
	printf("||      1.View the whole university        ||\n");
	printf("||     2.Find GPS system to find road      ||\n");
	printf("||        3.Exit the system                ||\n");
	printf("=============================================\n");
	printf("\n\n");
}

void Exit(){
	printf("\nThank you for using the system!\n");
	printf("Press 'Enter' to exit...\n\n");
	getchar();
	exit(0);
}

void Info(){
	printf("\nPlease input 'load 'map.plt'' in Gnuplot.\n\n");
}
