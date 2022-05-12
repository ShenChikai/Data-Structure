### 1000 insertions.
### AVL:0.613278 seconds
### Splay: 0.328643 seconds
### Splay expensive: 35

# Question 1
## This is tested on 1000 strings with length of 9 characters with r = 10
## However, the 9 char strings are originally generated in order, and were randomly scattered again.

# Question 2
## It took AVLTree 0.613278 seconds to perform 1000 insertions.
### Divided by 1000, per operation took 0.00061 seconds for AVLTREE.
## It took SplayTree 0.328643 seconds to perform 1000 insertions.
### Divided by 1000, per operation took 0.00033 seconds for AVLTREE.
## Yes, the time expense should depend on parameters, the input, greatly.
## SplayTree is almost twice faster than AVLTree here, since AVLTree needs to maintain the balance of the tree each time a new node is inserted, and with the total amount of nodes became really large, this time-consuming factor is greatly magnified.
## Unlike AVLTree, SplayTree requires no balance of the tree and saves the memory that AVLTree used to keep track of the height member for each node. Instead, SplayTree reshapes itself based on lookups, inserts, and deletions.



# Question 3
## Previously when using 100 strings of length 3 characters, the runtime of both type of trees are actually very close.
## However, from this specific case, we can see that SplayTree is almost twice faster than AVLTree, and that is because SplayTree requires no balance information and is thus more memory-efficient than AVLTree. 
## This is also affected by the form of data we are dealing with. For real-time applications, AVL Tree is better than Splay tree, but for non-real time applications, Splay tree has better average running time.
## Another factor could be that Splay tree is more efficient in tree merging and splitting.

# Question 4
## Unsorted List
### Store all the pair data in an Unsorted List will make the runtime decent if the size of the List is initialized to be greater than the amount of input data, because every insert will just ends up being a push_back operation to the list which has constant runtime. However, if the size is initialized to be not enough, resizing the list will eat up most of the runtime as it requires to copy everything prior to a new larger list once the data exceeds the size of the list.

## Sorted list
### Store all the pair data in a Sorted List will make the runtime extremely slow, because every insert has one specific sorted place to go, and before insertion, the list must perform a shift to create a space for the new data to be stored. Same as unsorted list, resizing the list will eat up most of the runtime. 

## Binary search tree, non-rotating variety
### Store all pair data in a non-rotating BST should have normal runtime for a BST if the data are randomized enough, and there is no extreme case such that the BST becomes essentially a linked list. The non-rotating BST can esaily lose balance and become similar some linked lists structre, and is very limited compared to AVLTree and SplayTree which adapt to different situations.

## Hash Table, with universal hash function
### Store all pair data in a Hash Table should have pretty good runtime as all the insert operation does here is just hashing the key of the pair to some index (assume the universal hash function is good enough that collision rarely happens, and if happened, it could be taken care by chaining or probing.) However, if one is to use probing, it does requires the table to be half empty and of size of a prime number.
