#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 10

void create(int N)
{
  float Matrix[MAXN][MAXN];
  float Row_Sum[MAXN],Column_Sum[MAXN];
  float E,max,sum;
  int flag,k,j,i;

 do{
 flag=1;
  for( k=1; k<=N; k++){
   for(j=1; j<=N; j++){

    max=Column_Sum[j];

    if(Row_Sum[k]>max){
     max=Row_Sum[k];
    }
   

    if(max==0){
     E = (float)rand();
    }else if(k==N){
     E = (1-Column_Sum[j]);
    }else if(j==N){
     E = (1-Row_Sum[k]);
    }else if(max!=0){
     E =  ((float)rand()/(float)(1-max));
    }
 
    Matrix[k][j] = E;
    Row_Sum[k] += E;  
    Column_Sum[j] +=E;
   }
  }

  for( i=0; i<N; i++){
   sum=0;
   for( j=0; j<N; j++){
    sum += Matrix[i][j];
   }

   if(sum !=1.0){
    flag=0; 
   }
  } 

  for( j=0; j<N; j++){
   sum=0;
   for( i=0; i<N; i++){
    sum += Matrix[i][j];
   }

   if(sum!=1.0){
    flag=0;
   }
  } 

 }while(flag==0); 

  printf("%d\n",N);
  for(j=0; j<N; j++){
   for( i=0; i<N; i++){
    printf("%f ", Matrix[j][i]);
   }
   printf("\n");
  }

}

void check()
{
  
  
  int N;
  float Matrix[MAXN][MAXN];
  int flag,i,j;
  float sum;
  scanf("%d", &N);
  flag=1;

  for(j=0; j<N; j++){
   for( i=0; i<N; i++){
     scanf("%f", &Matrix[j][i]);
   }
  } 


 for(i=0; i<N; i++){
  sum=0;
  for(j=0; j<N; j++){
   sum += Matrix[i][j];
  }

  if(sum==1.0){
   printf("ROW %d YES\n",i+1);
  }else{
   printf("ROW %d NO\n",i+1);
   flag=0;
  }
 }

 for(j=0; j<N; j++){
  sum=0;
  for(i=0; i<N; i++){
   sum += Matrix[i][j];
  }
  if(sum==1.0){
   printf("COLUMN %d YES\n",j+1);
  }else{
   printf("COLUMN %d NO\n",j+1); 
   flag=0;
  }
 }

 if(flag==1){
  printf("MARKOV YES\n");
 }else{
  printf("MARKOV NO\n");
 }

}

int main(int argc, const char* argv[])
{ 
 int number; 

 if (argc<2){
   return 0;
  }

  if( strcmp("-check",argv[1]) == 0){
   check();s
  }else if(strcmp("-create",argv[1]) == 0){
   if(argc<3){
    printf("I dont have a number..\n");
   }else{
 
    number = atoi(argv[2]);

    if(number<MAXN){
     create(number);
    }else{
     printf("Wrong\n");
    }
   } 
  }else{
   return 1;
  }

return 0;

}


