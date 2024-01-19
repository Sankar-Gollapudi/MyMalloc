#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(){

        printf("Starting\n");
        int* arr1 = malloc(4080);
//      int* a = malloc(9);
//      intb = malloc(9);
//      intc = malloc(9);
        free(arr1);
        int* arr2[256];
        for(int i=0;i<256;i++){
                arr2[i] = malloc(2);
        }
        printf("Loop 1 finished.");
        for(int i=0;i<256;i++){
        free(arr2[i]);
        //free(arr2[1]);
        }
        for(int i=0;i<256;i++){
                arr2[i] = malloc(2);
        }
        for(int i=0;i<256;i++){
                free(arr2[i]);
        }
        printf("going to allocate 4080 now\n");
        arr1 = malloc(4080);
        printf("going to free 4080 now\n");
        free(arr1);
        printf("going to allocate 4088 now\n");
        arr1 = malloc(4088);
        printf("going to free 4088 now\n");
        free(arr1);
        
        return 0;
}