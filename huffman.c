/* 

* Ray Che
* COEN 12 Project, Spring Quarter 2016
* Santa Clara University

This program takes a file input, counts the number of occurences of characters in the file, and inserts them into a priority queue. It then uses the priority queue to generate a huffman tree, which it then uses with huffman coding in order to compress the file input. 
*/

// Include header files. "tree.h" and "pack.h" are local.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

// Define macros for determining position of parent and children
#define p(x) (((x)-1)/2) // Parent
#define l(x) ((x)*2+1) // Left child
#define r(x) ((x)*2+2) // Right Child

// Declare global variables
int count=0, counts[257];
struct tree *leaves[257]; 
struct tree *heap[257];

// Prototype functions
void countChar(char *fname);
void insert(struct tree *t);
struct tree *delete();
void heapSort();
void print(struct tree *t);

/* Main function of the program. Takes in file name as arguement. */
int main(int argc, char *argv[]){
    // Returns error if improper amount of files passed into the program
	if(argc==2){
		printf("The name of the file is missing!\n"); 
		return 0; 
	}

    // Calls countChar and passes file 1
	countChar(argv[1]);
    
    struct tree *t;
    int i;
    
    // Takes counts and initializes leaves and inserts into heap. This loop has a run time of O(n).
    for(i=0; i<256; i++){
        if(counts[i]!=0){
            t=createTree(counts[i], NULL, NULL);
            assert(t!=NULL);
            leaves[i]=t;
            insert(t);
        }
        else{
            leaves[i]=NULL;
        }
    }
    
    // Adds the end-of-file marker
    leaves[256]=createTree(0, NULL, NULL);
    assert(leaves[256]!=NULL);
    insert(leaves[256]);

    struct tree *x, *y, *tree;
    int data;
    
    // Generates the huffman tree while there is more than 1 tree in the heap. This loop has a run time of O(n).
    while(count>1){
        x=delete();
        y=delete();
        data=getData(x)+getData(y);
        tree=createTree(data, x, y);
        assert(tree!=NULL);
        insert(tree);
    }
    
    // Prints out each unique character present in the file, its count, as well as the corresponding binary. This loop as a run time of O(n).
    for(i=0; i<257; i++){
        if(leaves[i]!=NULL){
            if(isprint(i)!=0){ // Checks if the character is printable
                printf("'%c': %d: ", i, counts[i]);
            }
            else{
                printf("%03o: : %d: ", i, counts[i]);
            }
            print(leaves[i]);
            printf("\n");
        }
    }
    
    // Calls pack to compress the file
    pack(argv[1], argv[2], leaves);

	return 0; 
}

/* This function opens the passed file and counts the occurences for each unique character in the file. This function has a run time of O(n). */
void countChar(char *fname){
	FILE *fp=fopen(fname, "r"); 
	assert(fp!=NULL); 

	int c;

    // Inserts the counts in the corresponding ASCII slot of the counts array
	while((c=fgetc(fp))!=EOF){
		counts[c]++;
	}

	fclose(fp);
	return; 
}

/* This function inserts the passed subtree into the heap and calls heapSort to maintain heap order. This function has a run time of O(n).  */
void insert(struct tree *t){
    assert(t!=NULL);
    
    heap[count++]=t;
    
    heapSort(count-1);

    return;
}

/* This function returns and deletes the minimum value. This function has a run time of O(1). */
struct tree *delete(){
    return heap[--count];
}

/* This function recursively sorts the heap to ensure proper heap order. This function has a run time of O(n). */
void heapSort (int x){
    struct tree *parent, *temp;
    
    if(x!=0){
        parent=heap[p(x)];
        if(getData(heap[x])>getData(parent)){ // Swap values if greater than parent
            temp=heap[x];
            heap[x]=parent;
            heap[p(x)]=temp;
        }
        heapSort(p(x));
    }
    return;
}

/* This function recursively traverses the passed tree and prints out the binary value associated with the path from the root to the initial "t". This function has a run time of O(n). */
void print (struct tree *t){
    assert(t!=NULL);
    
    if(getParent(t)==NULL){ // Return when root is reached
        return;
    }
    print(getParent(t));
    if(t==getLeft(getParent(t))){ // Print "0" if left child, 1 if right child
        printf("0");
    }
    else{
        printf("1");
    }
    return;
}

