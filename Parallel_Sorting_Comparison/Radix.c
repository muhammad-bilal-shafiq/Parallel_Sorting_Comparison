#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<omp.h>
#include<time.h>

int Size=100;
int *A, *B, *C;
int n=100; 
int m=100; 
int o=100;


int message(){
	
	int i, j;
	for(i=1;i<=3;i++)
	{
		for(j=1; j<=204; j++)
		{
		    if(i==3 && j==5)
		    {
		        printf("\n\t\t\t\t\t\t\t\t\t\tR    A    D    I    X        S    O    R    T  ");
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


int max_element(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

void SF(int array[], int size, int sd){ //sort acc to sig. fig
  int output[size + 1];
  int max = (array[0] / sd) % 10;

  for (int i = 1; i < size; i++) {
    if (((array[i] / sd) % 10) > max)
      max = array[i];
  }
  int count[max + 1];

  for (int i = 0; i < max; ++i)
    count[i] = 0;

  for (int i = 0; i < size; i++)
    count[(array[i] / sd) % 10]++;
    

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    output[count[(array[i] / sd) % 10] - 1] = array[i];
    count[(array[i] / sd) % 10]--;
  }

  for (int i = 0; i < size; i++)
    array[i] = output[i];
}

void *radixsort(void *a) {
 	int *array=a; 
  int max = max_element(array, n);


  for (int sd = 1; max / sd > 0; sd *= 10)
    SF(array, n, sd);
}

void radix_sort(int array[], int size) {
 	
  int max = max_element(array, size);


  for (int sd = 1; max / sd > 0; sd *= 10)
    SF(array, size, sd);
}

void printArray(int array[], int size) {
size = 10;
  for (int i = 0; i < size; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void threads(){ 
FILE* fptr;

  ms("\tP t h r e a d s");

	double start, stop;
	
  	
  	pthread_t t2;
  	
  	start=clock();
  	pthread_create(&t2, NULL, radixsort, (void*)A);
    
    pthread_join(t2, NULL);
    stop=clock();
 printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
	printArray(A, n);

	printf("\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);


double time = (double)(stop-start)/CLOCKS_PER_SEC;

fptr = fopen("RadixTime.txt", "a");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "\nPTHREADS:\n%f", time); 

fclose(fptr);
}

void openmp(){ 
FILE* fptr;
fflush(stdout);
	ms("\tO p e n M P");
fflush(stdout);

  	
  	double start, stop;
  	start = omp_get_wtime(); 
  	#pragma omp parallel sections num_threads(8)
  	
  	{ 
  		#pragma omp section
		  { 
		  	radix_sort(B,m); 
		  	printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
		  	printArray(B, m);
		  	
			  }	
	  }
	stop = omp_get_wtime();
	printf("\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(stop-start));
double time = stop-start;
fptr = fopen("RadixTime.txt", "a");
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

    for(int i=0; i<100; i++){
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


int main() {
message();
	FILE* fptr;

	 C = (int*) malloc(Size*sizeof(int));
  	randArray(C);

 printf("\t\t\t\t\t\t\t\t\t\t    Generating Array Randomly: \n\n");
displayA(C, Size);
fflush(stdout);
ms("S e r i a l  E x e c u t i o n");
fflush(stdout);
	
	double start, stop;

	start=clock();
	radix_sort(C, o);
   printf("\n\n\t\t\t\t\t\t\t\t\t\tSorted Array:     ");
printArray(C, o);

	stop=clock();
	printf("\t\t\t\t\t\t\t\t\t\tTime Taken:       %lf seconds.\n",(double)(stop-start)/CLOCKS_PER_SEC);
double time = (double)(stop-start)/CLOCKS_PER_SEC;

 fptr = fopen("RadixTime.txt", "w");
if(fptr == NULL){
printf("\nError, file not created!");
exit(1);
}

fprintf(fptr, "Serial:\n%f", time); 

	fclose(fptr);

	A = (int*) malloc(Size*sizeof(int));
 	randArray(A);
 	
	threads(); 
	
	B = (int*) malloc(Size*sizeof(int));
 	randArray(B);
	openmp(); 
}
