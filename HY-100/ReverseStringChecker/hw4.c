#include <stdio.h>   
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 250

int main(int argc, const char *argv[]){

 char str1[MAX],str2[MAX],tmp,tmp2;
 int j=0,i=0;
 int stringlen1,stringlen2,a=0;

  FILE *fp1;
  FILE *fp2;

  fp1 = fopen(argv[1],"r");
  fp2 = fopen(argv[2],"r");


 for(i=0; i<MAX;i++){
  str1[i]='\0';
  str2[i]='\0';
 }
 

 while((fgets(str1,MAX,fp1)!=NULL)&&(fgets(str2,MAX,fp2)!=NULL)){
    

 for(i=0; i<MAX;i++){
  if(str1[i]!=' ' && str1[j]!='\n' && str1[i]!='\0'){
   str1[i]=toupper(str1[i]);
  }

  if(str2[i]!=' ' && str2[j]!='\n' && str2[i]!='\0'){
   str2[i]=toupper(str2[i]);
  }
 }


 stringlen1= strlen(str1);

 for(i=0; i<stringlen1; i++){
   for(j=i+1; j<(stringlen1-1); j++){
     if(str1[i]<str1[j]){
       tmp=str1[j];
       str1[j]=str1[i];
       str1[i]=tmp;
     }
   }
 }  
 
 stringlen2= strlen(str2);

 for(i=0; i<stringlen2; i++){
   for(j=i+1; j<(stringlen2-1); j++){
     if(str2[i]<str2[j]){
       tmp=str2[j];
       str2[j]=str2[i];
       str2[i]=tmp;
     }
   }
 }
   
  i=strcmp(str1,str2);
  if(i==0){
   printf("TRUE\n");
  }else{
   printf("FALSE\n");
  }
 
 for(i=0; i<MAX;i++){
  str1[i]='\0';
  str2[i]='\0';
 }
 
}

 if((fgets(str1,MAX,fp1)==NULL)&&(fgets(str2,MAX,fp2)!=NULL)){
  printf("TRAILING LINES IN %s\n",argv[2]);
 }else if((fgets(str1,MAX,fp1)==NULL)&&(fgets(str2,MAX,fp2)!=NULL)){
  printf("TRAILING LINES IN %s\n", argv[1]);
 }


fclose(fp1);
fclose(fp2);

return 0;
}  
