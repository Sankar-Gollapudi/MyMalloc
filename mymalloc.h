//if the macro MYMALLOC_H has not been defined,
//we define it here, so it cannot be defined again
#ifndef MYMALLOC_H
#define MYMALLOC_H

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

//after defining MYMALLOC_H, we set a macro so that when calling malloc()
//and free, users will run our version instead
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

//end the if statement
#endif