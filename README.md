# heapSort

Here I tried to show a different approach to Heap Sort.
I was driven by the pseudocode from CLRS Introduction to Algorithms, third edition and by the fact that I couldn't find 
any elegant solution on the web about this Algorithm.
The algorithms performs less recursice calls, by checking if the node is in order i.e. max heapify condion holds.
By performing one recursive call less, the system saves on stack space and thus far a CPU cycles.  
My language of choice was C, since it really shows the depth of the working process underneath.
This code also works with I/O files. For that particular case, the user must take care of the stack/heap space in advance.

To be compiled with:
gcc -std=c99 -O3 heapSort.c -o heapSort -lm

Any sugestions, ideas, contribtions are much appreciated.

- Ivan

