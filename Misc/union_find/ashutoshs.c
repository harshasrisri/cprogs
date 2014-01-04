#include <stdio.h>
int NODES=0, *lookup_table;

void connect(int n1, int n2){
	int base1 = lookup_table[n1], base2 = lookup_table[n2], i;

	if(base1==-1 && base2==-1)//if both new
		lookup_table[n1]=lookup_table[n2]=n2;//create new list
	else if(base1==-1 && base2!=-1)//if first new
		lookup_table[n1]=base2;
	else if(base1!=-1 && base2==-1)//if second new
		lookup_table[n2]=base1;
	else if(base1!=base2)//if none new and in different lists
		for(i=0; i<NODES; i++)
			if(lookup_table[i]==base1)
				lookup_table[i]=base2;
}

void process_input(){
	while(1){
		char string[100];
		int n1=0, n2=0;
		int i=0;	
		fgets(string, 100, stdin);
		if(string[0]=='-')
			return;
		for(i=0; string[i]!='\0'; i++)
			if(string[i]==','){
				string[i]=' ';
				break;
			}
		sscanf(string, "%d %d",&n1, &n2);
		connect(n1,n2);
	}
}
void init(){
	int i=0;
	scanf(" %d ", &NODES);
	lookup_table= malloc(sizeof(int)* NODES);
	for(i=0; i<NODES; i++)
		lookup_table[i]=-1;
}
void process_queries(){
	while(1){
		char string[100];
		int n1=0, n2=0;
		int i=0;	
		fgets(string, 100, stdin);
		if(feof(stdin))
			return;	
		for(i=0; string[i]!='\0'; i++)
			if(string[i]==','){
				string[i]=' ';
				break;
			}
		sscanf(string, "%d %d",&n1, &n2);
		printf("%d", (lookup_table[n1]==lookup_table[n2])&&(lookup_table[n2]!=-1));
	}
}

int main (){
	init();
	process_input();
	process_queries();
}