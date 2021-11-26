#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct movies
{
	int charss;
 	char *name;
 	int year;
 	float money;
	struct movies *next;
} movies;

movies *head;
movies *tail;



void add_queue(const movies *p){
	movies *new_movies;

	new_movies= (movies*)malloc(sizeof(movies));
	if(new_movies==NULL){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	*new_movies = *p;
	new_movies->next =NULL;
	if(head==NULL){
		head = tail=new_movies;}
	else{
		tail->next = new_movies;
		tail= new_movies;
		tail->next= NULL;
	}
}


void show_stack(void){
	movies *p;

	p = head;
	while(p != NULL){
 		        
    printf("%s %d %.2f\n",p->name, p->year, p->money);
    p = p->next;
	}

}


void delete_movie(FILE *fp,char* tmp, int len){
  
int characters;

	movies *p; 	
	p=head;

fp = fopen("movies.dat","wb");

while(p!=NULL){

	 if(strcmp(tmp,p->name) != 0){
  characters = strlen(p->name);

fwrite(&characters,sizeof(int),1,fp);
fwrite(p->name,sizeof(char),characters,fp);
fwrite(&p->year,sizeof(int),1,fp);
fwrite(&p->money,sizeof(float),1,fp);

	
	}
p = p->next;
	
}

 fclose(fp);
}


void add_insert(FILE *fp,char *mv,int date,float money,int characters){
		
	movies *n;


	fp=fopen("movies.dat","ab+");
	fseek(fp,0,SEEK_END);

fwrite(&characters,sizeof(int),1,fp);
fwrite(mv,sizeof(char),characters,fp);
fwrite(&date,sizeof(int),1,fp);
fwrite(&money,sizeof(float),1,fp);

fclose(fp);

}

void after(int yr){

	movies *p;

	p=head;
	while(p!=NULL){
		
		if(p->year>=yr){

		printf( "%s %d %.2f\n",p->name,p->year,p->money);
		}
	p=p->next;
	}
}

void add_money(FILE *fp,char* mv,float chains){

	int characters;
	
	movies *p;
	p=head;
	fp=fopen("movies.dat","wb");


	while(p!=NULL){

		if(strcmp(mv,p->name)==0){
			p->money=p->money+chains;

		}
	 characters = strlen(p->name);

	fwrite(&characters,sizeof(int),1,fp);
	fwrite(p->name,sizeof(char),characters,fp);
	fwrite(&p->year,sizeof(int),1,fp);
	fwrite(&p->money,sizeof(float),1,fp);

	p=p->next;
	}


fclose(fp);
}


int main(int argc,char *argv[])
{

movies n; 

int characters,yr;
char* mv;
float chains;

FILE *fp;
fp=fopen("movies.dat","rb");

head = NULL;

while(!feof(fp)){


if(fread(&n.charss,sizeof(int),1,fp) >0){
n.name = malloc(sizeof(char)*n.charss);
fread(n.name,sizeof(char),n.charss,fp);
fread(&n.year,sizeof(int),1,fp);
fread(&n.money,sizeof(float),1,fp);

add_queue(&n);
}

}

fclose(fp);


 	if( strcmp("--insert",argv[1]) == 0){
	

        n.name=argv[2];
        n.year=atoi(argv[3]);
        n.money=atof(argv[4]);


	characters = strlen(n.name);
	mv = malloc(sizeof(char)*(characters));
 	strcpy(mv,n.name);


	add_insert(fp,mv,n.year,n.money,characters);

       }else if( strcmp("--list-all",argv[1]) == 0){

		if(head != NULL){
			show_stack();
		}
	
	}else if( strcmp("--reset",argv[1]) == 0){
		
		fopen("movies.dat","wb");

	}else if( strcmp("--delete",argv[1]) == 0){
		
	  characters = strlen(argv[2]);
	  mv = malloc(sizeof(char)*(characters));
 	  strcpy(mv,argv[2]);


               delete_movie(fp, mv,characters);

	}else if( strcmp("--list-after",argv[1]) == 0){
	
	yr=atoi(argv[2]);
	after(yr);
		
	}else if( strcmp("--add",argv[1]) == 0){

		 characters = strlen(argv[2]);
		  mv = malloc(sizeof(char)*(characters));
 		  strcpy(mv,argv[2]);
		  chains = atof(argv[3]);

 		add_money(fp,mv,chains);
	}

return 0;
}
















