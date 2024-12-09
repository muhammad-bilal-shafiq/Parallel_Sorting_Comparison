#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<omp.h>
#include<time.h>

int size=100;
int n=100, m=100, o=100;
int *A, *B, *C;

int messageA(){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=204; j++)
		{
		    if(i==3 && j==5)
		    {
		        printf("\n\t\t\t\t\t\t\t\t\t S    O    R    T    I    N    G       A    L    G    O    R    I    T    H    M    S ");
		        continue;
		    }
		    
			else if(i==3 && j>=5 || i == 3 && j<=5)
		    printf(" ");
		    
			else
		    printf("*");
	
		}
		printf("\n");
	}

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



int message(){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=204; j++)
		{
		    if(i==3 && j==5)
		    {
		        printf("\n\t\t\t\t\t\t\t\t\t\tH    E    A    P        S    O    R    T  ");
		        continue;
		    }
		    
			else if(i==3 && j>=5 || i == 3 && j<=5)
		    printf(" ");
		    
			else
		    printf("*");
	
		}
		printf("\n");
	}

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


void heapify(int a[], int n, int i){
	int max = i;
	int left = 2*i;
	int right = 2*i+1;
        int temp;
	
	if(left<n && a[left] > a[max]){
		max = left;
	}
	
	if(right<n && a[right] > a[max]){
		max = right;
	}
	
	if(max!=i){
                 temp = a[i];
                 a[i] = a[max];
                 a[max] = temp;
		//swap(a[i], a[max]);
		heapify(a, n, max);
	}
}

void display(int a[], int n){
n=10;
	for(int i=0; i<n; i++){
            printf("%d ", a[i]);
	}
       //printf("\n\n");
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


void *heapSort(void* arr){

	int i, temp;
       int* a= arr; 


	for(i=n/2-1; i>=0; i--){
		heapify(a, n, i);
	}
	
	for(i=n-1; i>=0; i--){
                 temp = a[0];
                 a[0] = a[i];
                 a[i] = temp;
	//	swap(a[0], a[i]);
		heapify(a, i, 0);
	}
        
       printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
	display(a, n);
 
}

void heapS(int a[], int n){
	int i, temp;
 

	for(i=n/2-1; i>=0; i--){
		heapify(a, n, i);
	}
	
	for(i=n-1; i>=0; i--){
                 temp = a[0];
                 a[0] = a[i];
                 a[i] = temp;
	//	swap(a[0], a[i]);
		heapify(a, i, 0);
	}

}

void threads(){
FILE* fptr;
ms("\tP t h r e a d s");

double start, stop;

   pthread_t t1;
start=clock(); 

       pthread_create(&t1, NULL, heapSort, (void*)A);

        pthread_join(t1, NULL);
stop=clock();

double time = (double)(stop-start)/CLOCKS_PER_SEC;
printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);


fptr = fopen("HeapTime.txt", "a");
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

   heapS(B, m);

    printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
    display(B, m);
   }
}
stop = omp_get_wtime(); 
double time;
time = stop-start;
printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(stop-start));


fptr = fopen("HeapTime.txt", "a");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "\nOPENMP:\n%f", time); 
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
void clrscr(void)
{
    system("clear");
}


int main(){

messageA();

printf("\n\t\t\t\t\t\t\t\t\t\tPress Any Key to Continue");  
getchar();

clrscr();
	message();

FILE* fptr;

 C = (int*) malloc(size*sizeof(int));
  randArray(C);
 printf("\t\t\t\t\t\t\t\t\t\t    Generating Array Randomly: \n\n");
displayA(C, size);


	ms("S e r i a l  E x e c u t i o n");

double start, stop;

       
start=clock();
heapS(C, o);
    printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
display(C, o);
stop=clock();
double time = (double)(stop-start)/CLOCKS_PER_SEC;

printf("\n\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);

   fptr = fopen("HeapTime.txt", "w");
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
