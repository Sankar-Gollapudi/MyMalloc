//#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "mymalloc.h"

//#include "mymalloc.h"
int getTime(){
	struct timeval tv;
        struct timezone tz;
        gettimeofday(&tv,&tz);
	return tv.tv_usec;
}
int test1(){
	int startTime =getTime();
	for(int counter=0;counter<120;counter++){
          	char* charptr = malloc(1);
        	free(charptr);
        }
	int finalTime = getTime();
	return abs(finalTime-startTime);
}
int test2(){
	int startTime = getTime();
	char* ptrArr [120];
	for (int i=0;i<120;i++){
		ptrArr[i]=malloc(1);
	}
	for (int i=0;i<120;i++){
		free(ptrArr[i]);
	}
	int finalTime = getTime();
	return abs(finalTime-startTime);
}

int test3(){
	int startTime = getTime();

	char * ptrArray[120];
	int occupiedMem[120] = {0};
	int currPtr = 0;

	for(int counter=0; counter<120; counter++) {
		if((currPtr<120&&rand() % 2 == 0)||currPtr==0)
		{
//			printf("memory allocated at position %d.\n",currPtr);
			ptrArray[currPtr] = malloc(1);
			occupiedMem[currPtr] = 1;
			currPtr++;
        	}
		else
		{
			currPtr--;
//			printf("Memory free at position %d.\n", currPtr);
			free(ptrArray[currPtr]);
			occupiedMem[currPtr]=0;
        	}
    	}

//	printf("Memory allocation complete.\n");

	for(int counter=0;counter<120;counter++) {
		if(occupiedMem[counter] == 1) {
			free(ptrArray[counter]);
		}
	}


	int endTime = getTime();
	return abs(endTime-startTime);

}


int test4(){
	int startTime = getTime();
	int* arr1;
	int* arr2;
	for(int i=0; i<50; i++){
		arr1 = malloc(2040);
		arr2 = malloc(2040);
		free(arr1);
		free(arr2);
	}
	int endTime = getTime();
	return abs(endTime-startTime);
}

int test5(){
	int startTime = getTime();
	int* a;
	char* c;
	double* d;
	for(int i=0; i<25; i++){
		a=malloc(4);
		c=malloc(1);
		d=malloc(8);
		free(c);
		free(a);
		free(d);

	}
	int endTime = getTime();
	return abs(endTime-startTime);
}


int main(int argc, char* argv[]){
	int sum=0;
	for(int i=0;i<1;i++){
		sum+=test1();
	}
	double avg=sum/50.0;
	printf("The average time taken to run test 1 was %f ms\n",avg);

	sum = 0;
	for(int i=0;i<50;i++){
		sum+=test2();
	}
	avg=sum/50.0;
        printf("The average time taken to run test 2 was %f ms\n",avg);

        sum=0;
        for(int i=0;i<50;i++){
                sum+=test3();
        }
        avg=sum/50.0;
        printf("The average time taken to run test 3 was %f ms\n",avg);

	sum=0;
        for(int i=0;i<50;i++){
                sum+=test4();
        }
        avg=sum/50.0;
        printf("The average time taken to run test 4 was %f ms\n",avg);

	sum=0;
        for(int i=0;i<50;i++){
                sum+=test5();
        }
        avg=sum/50.0;
        printf("The average time taken to run test 5 was %f ms\n",avg);


}