/* 
* Ray Che 
* COEN 12 Project, Spring Quarter 2016
* Santa Clara University

This program creates a binary tree ADT and contains functions for retriving data within the tree, updating the tree, and destroying the tree. 
*/

// Include header files. "tree.h" is local. 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

// Define the contents of each leaf
struct tree {
	int data; 
	struct tree *parent; 
	struct tree *left; 
	struct tree *right; 
}; 

// Prototype detach function
void detach(struct tree *child); 

/* This function creates and allocates memory for a binary tree ADT and returns a pointer to the new tree. This function has a run time of O(1).*/
struct tree *createTree(int data, struct tree *left, struct tree *right){
	struct tree *root=malloc(sizeof(struct tree)); 
	assert(root!=NULL); 
	
	// Inserts data and sets pointers to parent and children
	root->data=data; 
	root->parent=NULL;
	
    // Detaches left from parent and attaches to new root
	detach(left);  
	root->left=left;
	if(left!=NULL){
		left->parent=root; 
	}
	
    // Detaches right from parent and attaches to new root
	detach(right); 
	root->right=right; 
	if(right!=NULL){
		right->parent=root; 
	}

	return root; 
}

/* This function deallocates memory for the tree passed to the function. This function has a run time of O(n). */
void destroyTree(struct tree *root){
	// Traverses recursively until it reaches the end of the tree, then returns and frees
	if (root==NULL){
		return; 
	}

	destroyTree(root->left); 
	destroyTree(root->right); 

	free(root); 

	return; 
}

/* This function returns the data contained within the root of the subtree. This function has a run time of O(1). */
int getData(struct tree *root){
	assert(root!=NULL); 
	
	return root->data; 
}

/* This function returns the left subtree from the root of the subtree passed to the function. This function has a run time of O(1). */
struct tree *getLeft(struct tree *root){
	assert(root!=NULL); 

	return root->left; 
}

/* This function returns the right subtree from the root of the subtree passed to the function. This function has a run time of O(1). */
struct tree *getRight(struct tree *root){
	assert(root!=NULL); 

	return root->right; 
}

/* This function returns the parent tree of the root of the the subtree passed to the function. This function has a run time of O(1). */
struct tree *getParent(struct tree *root){
	assert(root!=NULL); 

	return root->parent; 
}

/* This function updates the left subtree of the subtree passed to the function. This function has a runtime of O(1). */
void setLeft(struct tree *root, struct tree *left){
	assert(root!=NULL && left!=NULL);
    
    // Case for if the left child is null
	if(root->left!=NULL){
		root->left->parent=NULL;
	}
    
    // Set root's left child pointer to left, detach, then set left's child pointer to root
	root->left=left;
	detach(left); 
	left->parent=root;  
	return; 
}

/* This function updates the right subtree of the subtree passed to the function. This function has a runtime of O(1). */
void setRight(struct tree *root, struct tree *right){
	assert(root!=NULL && right!=NULL);
    
    // Case for if the right child is null
	if(root->right!=NULL){
		root->right->parent=NULL;
	}
    
    // Set root's right child pointer to right, detach, then set right's child pointer to root
	root->right=right; 
	detach(right); 
	right->parent=root;  
	return; 
}

/* This function detaches a child from its parent. This function has a runtime of O(1). */
void detach(struct tree *child){
    // Checks if the child is null
	if(child==NULL || child->parent==NULL){
		return; 
	}
	
    // Checks whether you are freeing the left or right child
	if (child->parent->left->data==child->data){
		child->parent->left=NULL; 
	}	
	else if (child->parent->right->data==child->data){
		child->parent->right=NULL;
	}
    
	child->parent=NULL; 

	return;  
}
