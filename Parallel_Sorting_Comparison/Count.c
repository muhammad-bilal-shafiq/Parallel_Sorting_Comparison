#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<omp.h>
#include<time.h>

int size=100;
int n=100, m=100, o=100;
int *A, *B, *C;

int message(){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=204; j++)
		{
		    if(i==3 && j==5)
		    {
                   
		        printf("\n\t\t\t\t\t\t\t\t\t\tC    O    U    N    T        S    O    R    T  ");
		        continue;
		    }
		    
			else if(i==3 && j>=5 || i == 3 && j<=5)
		    printf(" ");
		    
			else
		    printf("*");
	
		}
		printf("\n");
	}
//printf("\n");
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=204; j++)
		{
		    if(i==3 && j==5)
		    {
		        printf("\n ");
		        continue;
		    }
		    
			else if(i==3 && j>=5 || i == 3 && j<=5)
		    printf(" ");
		    
			else
		    printf("*");
	
		}
		printf("\n");
	}
}

int ms(const char* s){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=102; j++)
		{
			 if(i==2 && j==2)
		    {
			printf("\t\t\t\t\t\t\t\t\t\t  %s \t\t\t\t  ",s);
		        continue;
		    }
		    
			else if(i==2 && j>=2 || i == 2 && j<=2)
		    printf(" ");
		    
			else
		    printf(" -");
		}
		printf("\n");
	}
}

int p;
 int n;
void display(int a[], int n){
n=10;
	for(int i=0; i<n; i++){
            printf("%d ", a[i]);
	}
}

int getMax(int a[], int n) {  
   int max = a[0];  
   for(int i = 1; i<n; i++) {  
      if(a[i] > max)  
         max = a[i];  
   }  
   return max; 
  }
void countSort(int a[], int n)  
{  
   int output[n+1];  
   int max = getMax(a, n);  
   int count[max+1]; 
  
  
  for (int i = 0; i <= max; ++i)   
  {  
    count[i] = 0;
  }  
    
  for (int i = 0; i < n; i++) 
  {  
    count[a[i]]++;  
  }  
  
   for(int i = 1; i<=max; i++)   
      count[i] += count[i-1];  
  

  for (int i = n - 1; i >= 0; i--) {  
    output[count[a[i]] - 1] = a[i];  
    count[a[i]]--;   
}  
  
   for(int i = 0; i<n; i++) {  
      a[i] = output[i];   
   }  
}  

void* countS(void *arr)  
{  
int *a=arr;
  
 int output[n+1];  
   int max = getMax(a, n);  
   int count[max+1]; 
  
  
  for (int i = 0; i <= max; ++i)   
  {  
    count[i] = 0;
  }  
    
  for (int i = 0; i < n; i++) 
  {  
    count[a[i]]++;  
  }  
  
   for(int i = 1; i<=max; i++)   
      count[i] += count[i-1];  
  

  for (int i = n - 1; i >= 0; i--) {  
    output[count[a[i]] - 1] = a[i];  
    count[a[i]]--;   
}  
  
   for(int i = 0; i<n; i++) {  
      a[i] = output[i];   
   }  
}  
void threads(){
FILE* fptr;

ms("\tP t h r e a d s");


double start, stop;


   pthread_t t1;
start=clock();
       pthread_create(&t1, NULL, countS, (void*)A);

        pthread_join(t1, NULL);
     printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
	display(A, n);
stop=clock();
printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);

double time = (double)(stop-start)/CLOCKS_PER_SEC;

fptr = fopen("CountTime.txt", "a");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "\nPTHREADS:\n%f", time); 

fclose(fptr);

//pthread_exit(NULL);
}


void openmp(){
FILE* fptr;
ms("\tO p e n M P");


double start, stop;


start = omp_get_wtime(); 

#pragma omp parallel sections num_threads(8)
{

  #pragma omp section
   {

   countSort(B, m);

     printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
    display(B, m);
   }
}
stop = omp_get_wtime(); 

printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(stop-start));


double time = stop-start;
fptr = fopen("CountTime.txt", "a");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "\nOpenMP:\n%f", time); 
fclose(fptr);

}

int randArray(int *r){
// r = (int*) malloc(100*sizeof(int));

srand(time(0));

    for(int i=0; i<size; i++){
       r[i]=rand()%100 + 1;
     }


return *r;
}
void displayA(int a[], int n){

      printf("\t\t\t");
	for(int i=0; i<50; i++){
            printf("%d ", a[i]);
	}
        printf("\n\t\t\t");
	for(int i=50; i<n; i++){
            printf("%d ", a[i]);
	}
       printf("\n\n");
}

int main(){
	message();

FILE* fptr;

 C = (int*) malloc(size*sizeof(int));
  randArray(C);

 printf("\t\t\t\t\t\t\t\t\t\t    Generating Array Randomly: \n\n");
displayA(C, size);

ms("S e r i a l  E x e c u t i o n");
double start, stop;

start=clock();
countSort(C, o);
   printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
display(C, o);
stop=clock();
printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);

double time = (double)(stop-start)/CLOCKS_PER_SEC;
 fptr = fopen("CountTime.txt", "w");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "Serial:\n%f", time); 

	fclose(fptr);



 A = (int*) malloc(size*sizeof(int));
  randArray(A);
threads();

 B = (int*) malloc(size*sizeof(int));
  randArray(B);
       openmp();
	
}
