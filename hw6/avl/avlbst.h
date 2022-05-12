#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "../bst/bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* insertHelper additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{  

public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(1)
{
	// initialize height to 1 for calculation convenience
}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	if (this == NULL) {
		return 0;
	}

	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{

public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);

	Node<Key, Value>* insertHelper(Node<Key, Value> *node, const std::pair<Key, Value> &keyValuePair);
	Node<Key, Value>* removeHelper(Node<Key, Value> *node, const Key &key);

	Node<Key, Value>* rotateRight(Node<Key, Value> *node);
	Node<Key, Value>* rotateLeft(Node<Key, Value> *node);
	int height(Node<Key, Value> *node);
	Node<Key, Value>* findMin(Node<Key, Value> *node);
	int clacBalance(Node<Key, Value> *node);
	 

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    this->mRoot = insertHelper(this->mRoot, keyValuePair);
}

// Helper for Insert

template<class Key, class Value>
Node<Key, Value>* AVLTree<Key, Value>::insertHelper(Node<Key, Value> *node, const std::pair<Key, Value> &keyValuePair) {
    if(node == NULL){ // base case
        return new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    }

    if(keyValuePair.first > node->getKey()){
        node->setRight(insertHelper(node->getRight(), keyValuePair)); 
    } else if(keyValuePair.first < node->getKey()){
        node->setLeft(insertHelper(node->getLeft(), keyValuePair));
    } else {
        node->setValue(keyValuePair.second); // existed, update value
    }

	// update height
    //static_cast<AVLNode<Key, Value>* >(node)->setHeight(1 + max(height(node->getLeft()), height(node->getRight())) );  

    int balance = clacBalance(node);

    if(balance > 1) {
        if(clacBalance(node->getLeft()) >= 0) {
            return rotateRight(node);
        } else {
            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }
    } else if(balance < -1) {
        if(clacBalance(node->getRight()) <= 0) {
            return rotateLeft(node);
        } else {
            node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }
    }
    return node;
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
 this->mRoot = removeHelper(this->mRoot, key);
}

// Helper for Remove

template<class Key, class Value>
Node<Key, Value>* AVLTree<Key, Value>::removeHelper(Node<Key, Value> *node, const Key &key) {
    if(node == NULL) return NULL;

    Node<Key, Value>* target;
    if(key > node->getKey()) {
        node->setRight(removeHelper(node->getRight(), key));
        target = node;
    } else if(key < node->getKey()) {
        node->setLeft(removeHelper(node->getLeft(), key));
        target = node;
    } else {
        if(node->getLeft() == NULL) {
            target = node->getRight();
            node->setRight(NULL);
        } else if(node->getRight() == NULL) {
            target = node->getLeft();
            node->setLeft(NULL);
        } else {
            Node<Key, Value>* min = findMin(node->getRight());
            min->setRight(removeHelper(node->getRight(), min->getKey()));
            min->setLeft(node->getLeft());
            node->setLeft(NULL);
            node->setRight(NULL);
            target = min;
        }
    }

    if(target == NULL) return NULL;


    int balance = clacBalance(target);
    if(balance > 1) {									// Left > Right
        if(clacBalance(target->getLeft()) >= 0) {
            return rotateRight(target);
        } else {
            target->setLeft(rotateLeft(target->getLeft()));
            return rotateRight(target);
        }
    } else if(balance < -1) {							// Right > Left
        if(clacBalance(target->getRight()) >= 0) {
            return rotateLeft(target);
        } else {
            target->setRight(rotateRight(target->getRight()));
            return rotateLeft(target);
        }
    }

    return target;
}

// Used in Common

int max(int a, int b)  
{
    return (a > b)? a : b;  
}  

template<class Key, class Value>
int AVLTree<Key, Value>::height(Node<Key, Value> *node) {
    if(node == NULL)  return 0;

    return max(height(node->getLeft()), height(node->getRight())) + 1;
}

template<class Key, class Value>
int AVLTree<Key, Value>::clacBalance(Node<Key, Value> *node) {
    return height(node->getLeft()) - height(node->getRight());
}

template<class Key, class Value>
Node<Key, Value>* AVLTree<Key, Value>::rotateLeft(Node<Key, Value> *node) {
    Node<Key, Value>* n = node->getRight();
    node->setRight(n->getLeft());
    n->setLeft(node);

    // update height 
    /*
    static_cast<AVLNode<Key, Value>* >(node)->setHeight(1 + max(height(node->getLeft()),  
                       											height(node->getRight())) );
    static_cast<AVLNode<Key, Value>* >(n)->setHeight(1 + max(height(n->getLeft()),  
                       											height(n->getRight())) );
    */
    return n;
}

template<class Key, class Value>
Node<Key, Value>* AVLTree<Key, Value>::rotateRight(Node<Key, Value> *node) {
    Node<Key, Value>* n = node->getLeft();
    node->setLeft(n->getRight());
    n->setRight(node);

    // update height
    /*
    static_cast<AVLNode<Key, Value>* >(node)->setHeight(1 + max(height(node->getLeft()),  
                       											height(node->getRight())) );
    static_cast<AVLNode<Key, Value>* >(n)->setHeight(1 + max(height(n->getLeft()),  
                       											height(n->getRight())) );
	*/
    return n;
}

template<class Key, class Value>
Node<Key, Value>* AVLTree<Key, Value>::findMin(Node<Key, Value> *node) {
    if(node == NULL)
        return NULL;

    if(node->getLeft() != NULL)
    {
        return findMin(node->getLeft());
    }

    return node;
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
