#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include "../bst/bst.h"

/**
* A templated binary search tree implemented as a Splay tree.
*/
template <class Key, class Value>
class SplayTree : public BinarySearchTree<Key, Value>
{

	void zig(Node<Key, Value>* x);
    void zig_zig(Node<Key, Value>* x);
    void zig_zag(Node<Key, Value>* x);

    void splay(Node<Key, Value> *x);

public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods.
	SplayTree();
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& x);
	int report() const;

	Node<Key, Value>* look(const Key& x);
	int sizen(Node<Key, Value> *root);

private:
	/* You'll need this for problem 5. Stores the total number of inserts where the
	   node was added at level strictly worse than 2*log n (n is the number of nodes
	   including the added node. The this->mRoot is at level 0). */
	int badInserts;

	/* Helper functions are encouraged. */
};

/*
--------------------------------------------
Begin implementations for the SplayTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() : badInserts(0) { }

template<typename Key, typename Value>
int SplayTree<Key, Value>::report() const {
	return badInserts;
}

// Helper zig, zigzig, zigzag

template<typename Key, typename Value>
void SplayTree<Key, Value>::zig(Node<Key, Value> *x)
{
    Node<Key, Value> *p = x -> getParent();
    if (p -> getLeft() == x)
    {
        //Node<Key, Value> *A = x -> getLeft();
        Node<Key, Value> *B = x -> getRight();
        //Node<Key, Value> *C = p -> getRight();
        
        x -> setParent(NULL);
        x -> setRight(p);
        
        p -> setParent(x);
        p -> setLeft(B);
        
        if (B != NULL) B -> setParent(p);
    }
    else
    {
        //Node<Key, Value> *A = p -> getLeft();
        Node<Key, Value> *B = x -> getLeft();
        //Node<Key, Value> *C = x -> getRight();
        
        x -> setParent(NULL);
        x -> setLeft(p);
        
        p -> setParent(x);
        p -> setRight(B);
        
        if (B != NULL) B -> setParent(p);
    }
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::zig_zig(Node<Key, Value> *x)
{
    Node<Key, Value> *p = x -> getParent();
    Node<Key, Value> *q = p -> getParent();
    if (p -> getLeft() == x)
    {
        //Node<Key, Value> *A = x -> getLeft();
        Node<Key, Value> *B = x -> getRight();
        Node<Key, Value> *C = p -> getRight();
        //Node<Key, Value> *D = q -> getRight();
        
        x -> setParent(q -> getParent());
        x -> setRight(p);
        
        p -> setParent(x);
        p -> setLeft(B);
        p -> setRight(q);
        
        q -> setParent(p);
        q -> setLeft(C);
        
        
        if (x -> getParent() != NULL)
        {
            if (x -> getParent() -> getLeft() == q) x -> getParent() -> setLeft(x);
            else x -> getParent() -> setRight(x);
        }
        
        if (B != NULL) B -> setParent(p);
        
        if (C != NULL) C -> setParent(q);
    }
    else
    {
        //Node<Key, Value> *A = q -> getLeft();
        Node<Key, Value> *B = p -> getLeft();
        Node<Key, Value> *C = x -> getLeft();
        //Node<Key, Value> *D = x -> getRight();
        
        x -> setParent(q -> getParent());
        x -> setLeft(p);
        
        p -> setParent(x);
        p -> setLeft(q);
        p -> setRight(C);
        
        q -> setParent(p);
        q -> setRight(B);
        
        if (x -> getParent() != NULL)
        {
            if (x -> getParent() -> getLeft() == q) x -> getParent() -> setLeft(x);
            else x -> getParent() -> setRight(x);
        }
        
        if (B != NULL) B -> setParent(q);
        
        if (C != NULL) C -> setParent(p);
    }
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::zig_zag(Node<Key, Value> *x)
{
    Node<Key, Value> *p = x -> getParent();
    Node<Key, Value> *q = p -> getParent();
    if (p -> getRight() == x)
    {
        //Node<Key, Value> *A = p -> getLeft();
        Node<Key, Value> *B = x -> getLeft();
        Node<Key, Value> *C = x -> getRight();
        //Node<Key, Value> *D = q -> getRight();
        
        x -> setParent( q -> getParent() );
        x -> setLeft(p);
        x -> setRight(q);
        
        p -> setParent(x);
        p -> setRight(B);
        
        q -> setParent(x);
        q -> setLeft(C);
        
        if (x -> getParent() != NULL)
        {
            if (x -> getParent() -> getLeft() == q) x -> getParent() -> setLeft(x);
            else x -> getParent() -> setRight(x);
        }
        
        if (B != NULL) B -> setParent(p);
        
        if (C != NULL) C -> setParent(q);
    }
    else
    {
        //Node<Key, Value> *A = q -> getLeft();
        Node<Key, Value> *B = x -> getLeft();
        Node<Key, Value> *C = x -> getRight();
        //Node<Key, Value> *D = p -> getRight();
        
        x -> setParent( q -> getParent() );
        x -> setLeft(q);
        x -> setRight(p);
        
        p -> setParent(x);
        p -> setLeft(C);
        
        q -> setParent(x);
        q -> setRight(B);
        
        if (x -> getParent() != NULL)
        {
            if (x -> getParent() -> getLeft() == q) x -> getParent() -> setLeft(x);
            else x -> getParent() -> setRight(x);
        }
        
        if (B != NULL) B -> setParent(q);
        
        if (C != NULL) C -> setParent(p);
    }
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *x)
{
    while (x -> getParent() != NULL)
    {
        Node<Key, Value> *p = x -> getParent();
        Node<Key, Value> *q = p -> getParent();

        if (q == NULL) zig(x);
        else if (q -> getLeft() == p && p -> getLeft() == x) zig_zig(x);
        else if (q -> getRight() == p && p -> getRight() == x) zig_zig(x);
        else zig_zag(x);
    }
    this -> mRoot = x;
}

template<typename Key, typename Value>
int SplayTree<Key, Value>::sizen(Node<Key, Value> *root) {
	if (this->mRoot == NULL) return 0;

	int count = 1;
    if (root->getLeft() != NULL) {
       count += sizen(root->getLeft());
    }
    if (root->getRight() != NULL) {
        count += sizen(root->getRight());
    }
    return count;
}


/**
* Insert function for a x value pair. Finds location to insert the node and then splays it to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if (this->mRoot == NULL)
    {
        this->mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        this->badInserts = 0;
        return;
    }

    Node<Key, Value> *curr = this->mRoot;

    while (curr != NULL)
    {
        if (keyValuePair.first < curr -> getKey())
        {
            if (curr -> getLeft() == NULL)
            {
                Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
                curr -> setLeft(newNode);
                newNode -> setParent(curr);
                // node was added at level strictly worse than 2*log n
                int level = 1;
                Node<Key, Value> *levelPtr = newNode;
                while (levelPtr != this->mRoot) {
                	level++;
                	levelPtr = levelPtr->getParent();
                }
                if ( level > 2 * log2(this->sizen(this->mRoot)) ) {
                	this->badInserts++;
                }
                // Done updating Bad Insert
                splay(newNode);
                return;
            }
            else curr = curr -> getLeft();
        }
        else if (keyValuePair.first > curr -> getKey())
        {
            if (curr -> getRight() == NULL)
            {
                Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
                curr -> setRight(newNode);
                newNode -> setParent(curr);
                // node was added at level strictly worse than 2*log n
                int level = 1;
                Node<Key, Value> *levelPtr = newNode;
                while (levelPtr != this->mRoot) {
                	level++;
                	levelPtr = levelPtr->getParent();
                }
                if ( level > 2 * log2(this->sizen(this->mRoot)) ) {
                	this->badInserts++;
                }
                // Done updating Bad Insert
                splay(newNode);
                return;
            }
            else curr = curr -> getRight();
        }
        else
        {
            splay(curr);
            return;
        }
    }
}

/**
* Remove function for a given x. Finds the node, reattaches pointers, and then splays the getParent()
* of the deleted node to the top.
*/

// Helper for remove

template<typename Key, typename Value>
Node<Key, Value>* findSubMax(Node<Key, Value> *sRoot)
{
    Node<Key, Value> *curr = sRoot;
    while (curr -> getRight() != NULL) curr = curr -> getRight();
    return curr;
}

template<typename Key, typename Value>
Node<Key, Value>* findSubMin(Node<Key, Value> *sRoot)
{
    Node<Key, Value> *curr = sRoot;
    while (curr -> getLeft() != NULL) curr = curr -> getLeft();
    return curr;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::look(const Key& x) {
	Node<Key, Value> *ret = NULL;
    Node<Key, Value> *curr = this -> mRoot;
    Node<Key, Value> *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        if (x < curr -> getKey()) curr = curr -> getLeft();
        else if (x > curr -> getKey()) curr = curr -> getRight();
        else {
            ret = curr;
            break;
        }
    }

    if (ret != NULL) splay(ret);
    else if (prev != NULL) splay(prev);
    return ret;
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& x)
{
	Node<Key, Value> *removing = look(x);
    if (removing == NULL)
    {
        return;
    }
    Node<Key, Value> *L = removing -> getLeft();
    Node<Key, Value> *R = removing -> getRight();
    if (L == NULL && R == NULL)
    {
        this -> mRoot = NULL;
    }
    else if (L == NULL)
    {
        Node<Key, Value> *M = findSubMin(R);
        splay(M);
    }
    else if (R == NULL)
    {
        Node<Key, Value> *M = findSubMax(L);
        splay(M);
    }
    else
    {
        Node<Key, Value> *M = findSubMax(L);
        splay(M);
        M -> setRight(R);
        R -> setParent(M);
    }
    delete removing;
}

/*
------------------------------------------
End implementations for the SplayTree class.
------------------------------------------
*/

#endif
