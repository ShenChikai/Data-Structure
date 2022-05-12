#include <vector>
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

template <typename T>
  class MinHeap {
     public:
       MinHeap (int dd);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

       ~MinHeap ();

       int add (T data, int priority);
         /* adds the data to the heap, with the given priority. 
            multiple identical datas can be in the heap simultaneously. 
            Returns the number of times add has been called prior to this
            call (for use with the update function).*/

       const T & peek () const;
         /* returns the element with smallest priority.  
            If two elements have the same priority, use operator< on the 
            T data, and return the one with smaller data.*/

       void remove ();
         /* removes the element with smallest priority, with the same tie-breaker
            as peek. */

       void update (int nth, int priority);
         /* finds the nth item (where nth is 0-based) that has ever been added 
            to the heap (the node that was created on the nth call to add), 
            and updates its priority accordingly. */

       bool isEmpty ();
         /* returns true iff there are no elements on the heap. */

       void bubbleUp(int index);

       void trickleDown(int index);

       void swa(int i, int j);

       int getPrio(T data);

       int getNth(T data);

       int geth(string word, string target);

       T peekDoublet(string target);

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
      

      struct item
      {
        item(const T& d, int p, int n);
        T data;
        int prio;
        int nth;
      };

      vector<item*> v;   // vecotr of pointers to items
      int size;            // size of heap
      int d;               // d-ary
      int addTimes;
  };

template <typename T>
MinHeap<T>::item::item(const T& d, int p, int n) : data(d), prio(p), nth(n){

}

template <typename T>
MinHeap<T>::MinHeap(int dd) {
  this->size = 0;
  this->d = dd;
  this->addTimes = -1;      // first time ++ will be 0
} 

template <typename T>
MinHeap<T>::~MinHeap() {
  for (int i = 0; i < this->size; i++) {
   delete this->v[i];
  } 
} 

template <typename T>
int MinHeap<T>::add(T data, int priority) {
  //Returns the number of times add has been called prior to this
  //call (for use with the update function).
  this->addTimes++;

  item* temp = new item(data, priority, this->addTimes);

  this->v.push_back(temp);

  this->bubbleUp(this->size);
  size++;

  return this->addTimes;
} 

template <typename T>
const T& MinHeap<T>::peek() const {
  // If two elements have the same priority, use operator< on the 
  // T data, and return the one with smaller data.
  item* temp = this->v[0];                    // find smallest
  int index = 0;

  for (int i = 0; i < this->size; i++) {
    if (this->v[i]->prio == temp->prio) {     // if two items have equal prio
      if (this->v[i]->data < temp->data) {    // if data at i < data at temp
        index = i;
      }
    }
  }  

  temp = NULL;

  return this->v[index]->data;
} 

template <typename T>
void MinHeap<T>::remove() {
  item* temp = this->v[this->size - 1];       // find smallest
  int remove = this-> size - 1;               // the end of the vector

  for (int i = this->size - 1; i >= 0; i--) {
    if (this->v[i]->prio == temp->prio) {     // if two items have equal prio
      if (this->v[i]->data < temp->data) {    // if data at i < data at temp
        remove = i;
      }
    }
  }

  this->swa(0, remove);

  temp = NULL;
  delete this->v[remove];                     // this wont get deleted by destructor since size--
  this->v.erase(this->v.begin() + remove);    // erase from vector

  this->size--;

  this->trickleDown(0);

} 

template <typename T>
void MinHeap<T>::update(int nth, int priority) {
  int index;
  bool nExist = false;    // check if n exist or not

  for (int i = 0; i < this->size; i++) {
    if (this->v[i]->nth == nth) { 
      this->v[i]->prio = priority; 
      index = i;
      nExist = true;
    }
  }

  if (nExist) {
    this->swa(index, this->size - 1); // put nth added item to the end
    this->bubbleUp(this->size - 1);
  } 

}

template <typename T>
bool MinHeap<T>::isEmpty() {
  if (size <= 0) {
    return true;
  }
  return false;
}  

template <typename T>
void MinHeap<T>::bubbleUp(int index) {
  int parent = (index - 1) / this->d; 
  
  if (index > 0 && this->v[index]->prio < this->v[parent]->prio) {      // parent exist && parent < child
    this->swa(index, parent);
    this->bubbleUp(parent);
  }
}  

template <typename T>
void MinHeap<T>::trickleDown(int index) {
  int left = (index * d) + 1;   // keep track of the left most child
  int child = left;             // index of child used to do comparison
  int smallChild = child;       // target smallest child

  if (child < this->size) {               // child exist

    for (int i = 0; i < d; i++) {
      if (left + i < size) {
        if (this->v[child]->prio > this->v[left + i]->prio) {  // find smallest child
          smallChild = left + i;
          child = left + i;
        } 
      } else {
        break;
      }
    }

    if (this->v[smallChild]->prio < this->v[index]->prio) {
      this->swa(index, smallChild);
      this->trickleDown(smallChild);
    }
  }
}

template <typename T>
void MinHeap<T>::swa(int i, int j) {
  item* temp;
  temp = this->v[i];
  this->v[i] = this->v[j];
  this->v[j] = temp;
  temp = NULL;
}

template <typename T>
int MinHeap<T>::getPrio(T data) {
  int priority = -1;
  for (int i = 0; i < this->size; i++) {
    if (this->v[i]->data == data) { 
      priority = this->v[i]->prio; 
      break;
    }
  }
  return priority;
}

template <typename T>
int MinHeap<T>::getNth(T data) {
  int n = -1;
  for (int i = 0; i < this->size; i++) {
    if (this->v[i]->data == data) { 
      n = this->v[i]->nth; 
      break;
    }
  }
  return n;
}

template <typename T>
int MinHeap<T>::geth(string word, string target) {
  int h = 0;
  for(int i = 0; i < (int) word.length(); i++) {
    if(word[i] != target[i]){
      h++;
    }
  }
  return h;
}

template <typename T>
T MinHeap<T>::peekDoublet(string target) {
  item* temp = this->v[0];   // move with smallest f-value
  int swaIdx = 0;
  string cao = temp->data;

  for (int i = 0; i < this->size; i++) {
    if (this->v[i]->prio == temp->prio) {     // if two items have equal prio
        // smallest h-value
      if (this->geth(target, this->v[i]->data) < this->geth(target, temp->data)) {
        temp = this->v[i];
        swaIdx = i;
      } else if (geth(target, this->v[i]->data) == geth(target, temp->data)) {
          //operator<(str1, str2), where str1 and str2 are fully-capitalized
        string temptemp = temp->data;
        string tempthis = this->v[i]->data;
        for (int j = 0; j < (int) temptemp.size(); j++) {   // get to upper case
          temptemp[j] = toupper(temptemp[j]);
        }
        for (int k = 0; k < (int) tempthis.size(); k++) {
          tempthis[k] = toupper(tempthis[k]);
        }

        if (tempthis < temptemp) {
          temp = this->v[i];
          swaIdx = i;
        }
      }
    }
  }  

  cao = temp->data;
  temp = NULL;
  swa(0, swaIdx);

  return cao;
} 