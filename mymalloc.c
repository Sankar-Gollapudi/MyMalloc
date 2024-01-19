//Dhruv Rai and Sankar  Gollapudi
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mymalloc.h"
//rounds up to nearest multiple of 8 using bitwise operators
#define ROUNDUP8(x) (((x) + 7) & (-8))

//creating a global array with memory as well as the # of chunks
//(because we have a minimum 8 byte requirement per "chunk")
#define MEMLENGTH 512
static double memory[MEMLENGTH];

//setting up functions for modularity that will be used often
//by code to avoid repetition

//returns a boolean describing whether or not the chunk following the header
//is free or allocated
bool static isFree(void* head){return *(((int*)head) + 1) == 0;}

//returns chunk size bytes in an int
int static getChunkSize(void* head){return *((int*)head);}

//returns an int pointer to the next chunk of memory
int *getNextChunk(void* head){return ((int*)head) + (*(int*)head)/4 ;}

//sets the current block as allocated (not free)
void static setAllocated(void* head){*(((int*)head) + 1) = 1;}

//set the chunk size of the current header block
void static setChunkSize(void* head, size_t size){*((int*) head) = size + 8;}

//set the free parameter of the current block to free
void static setFree(void* head){*(((int*) head) + 1) = 0;}

void* mymalloc(size_t size, char* file, int line){
    //if the size is 0 then we return an error
    if(size == 0){
	fprintf(stderr, "Can't allocate 0 bytes File: %s, Line: %d\n", file, line);

        return NULL;
    }
    //round up the size to the nearest multiple of 8
    //minimum chunk size
    size = ROUNDUP8(size);

    //in 8 byte metadata: first 4 bytes is an integer representing chunk size, and last 4 bytes is 0 = free or 1 = occupied
    int* head = (int*)memory;

    //if chunkSize=0 and is free, then initialize
    if (getChunkSize(head) == 0 && isFree(head))
    {
            *head = (MEMLENGTH*8); //set chunk size to max length because our chunk size is going to include
            //header for easier traversal when using free
            setFree(head); //mark chunk as free
    }
    //go through each header until a header with enough bytes and is free=0 is found, or until end of memory
    int byteNumber=0;
    int origSize;
    void* finalPtr;




    //traverse until the byte we are on exceeds the size of the array
    while(byteNumber < (MEMLENGTH*8)){
            if(size <= getChunkSize(head)-8 && isFree(head)){

		origSize = getChunkSize(head);
                //adding 8 to account for header bytes
                setChunkSize(head, size);
                setAllocated(head);
                finalPtr = (void*)(head + 2);

                if(origSize > getChunkSize(head)){

                    setChunkSize(getNextChunk(head), origSize-getChunkSize(head)-8);
                    setFree(getNextChunk(head));
                }
                return finalPtr;
            }
            else{
                byteNumber += getChunkSize(head);
                head = getNextChunk(head);
            }
    }
    fprintf(stderr, "Error: insufficient memory File: %s, Line: %d\n", file, line);
    return NULL;
}


void myfree(void* ptr, char* file, int line){
    int shift;
    int byteNumber=0;
    int*prevChunkSizeAdd=(int*)memory;
    int* chunkSizeAdd=(int*)memory;
    while(byteNumber<=(MEMLENGTH*8)-8){
            if((void*)(chunkSizeAdd+2)==ptr){
                if(*(chunkSizeAdd+1)==0){
                    fprintf(stderr, "Double Free File: %s, Line: %d\n", file, line);
                    return;
                }
                else{
                    *(chunkSizeAdd+1)=0;



                    if((byteNumber+(*chunkSizeAdd))<MEMLENGTH*8 && *(chunkSizeAdd+(*chunkSizeAdd/4)+1)==0){

			            *chunkSizeAdd = *chunkSizeAdd + *(chunkSizeAdd+(*chunkSizeAdd/4));
                    }


                    if (prevChunkSizeAdd!=chunkSizeAdd && *(prevChunkSizeAdd+1) == 0){

			            *prevChunkSizeAdd = *prevChunkSizeAdd + *chunkSizeAdd;
                    }
                    return;
                }
            }
            else{
                shift = (*chunkSizeAdd)/4; //divide by 4 because pointer is of type int
                prevChunkSizeAdd=chunkSizeAdd;
                chunkSizeAdd = chunkSizeAdd + shift;//+2 because 2 ints is a bytes
                byteNumber = byteNumber+ (shift*4);
            }
    }
    fprintf(stderr, "Bad Pointer! File: %s, Line: %d\n", file, line);
    return;
}