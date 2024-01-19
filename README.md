Memgrind is to stress test the malloc and free functions and use a custom time class to compute how much time each process takes
Memtest tests to make sure there aren't any incorrect bytes throughout the stack array.

8 bytes of metadata for each block of malloced data, first 4 bytes are used to store an int that is either 0/1 for free or occupied
Second 4 bytes is used to store an int that contains the number of bytes in the block total. Sum of stored bytes should equal 4096.

Malloc/Free never look at user data, only the function managed metadata.
