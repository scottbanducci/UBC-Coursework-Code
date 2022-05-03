#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  /* your code here */
  if (p==NULL && head_ == NULL){
    Node* newNode =  new Node(ndata);
    newNode->next = NULL;
    newNode->prev = NULL;
    length_++;
    head_= newNode;
    return newNode;
  }

  if (p==NULL && head_ != NULL){
    Node *newNode =  new Node(ndata);
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    newNode->prev = NULL;
    length_++;
    return newNode;
  }

  if (p->next ==NULL){
    Node* nodeObjectForNData = new Node(ndata);
    p->next = nodeObjectForNData;
    nodeObjectForNData->prev = p;
    nodeObjectForNData->next = NULL;
    length_++;
    return nodeObjectForNData;
  }

    Node* tempNode = p->next;
	  Node* nodeObjectForNData = new Node(ndata);
	  p->next = nodeObjectForNData;
    nodeObjectForNData->prev = p;
	  nodeObjectForNData->next = tempNode;
    tempNode->prev = nodeObjectForNData;
    length_++;
    return nodeObjectForNData;
  
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  /* your code here */
  if (p!=NULL && q!=NULL && p->next != q && q->next != p && p != q) {
    if (p->prev == NULL && q->next !=NULL){
      head_ = q;
      Node* tempNode1 = p->next;
      Node* tempNode2 = q->prev;
      Node* tempNode3 = q->next;
      
      q->next = tempNode1;
      q->prev = NULL;
      p->next = tempNode3;
      p->prev = tempNode2;

      tempNode1->prev = q;
      tempNode2->next = p;
      tempNode3->prev = p;
      return;
    }
    if (p->prev == NULL && q->next ==NULL){
      head_ = q;
      Node* tempNode1 = p->next;
      Node* tempNode2 = q->prev;
      
      q->next = tempNode1;
      q->prev = NULL;
      p->next = NULL;
      p->prev = tempNode2;

      tempNode1->prev = q;
      tempNode2->next = p;
      return;
    }

    if (p->prev != NULL && q->next ==NULL){
      Node* tempNode1 = p->next;
      Node* tempNode2 = p->prev;
      Node* tempNode3 = q->prev;
      
      q->next = tempNode1;
      q->prev = tempNode2;
      p->next = NULL;
      p->prev = tempNode3;

      tempNode1->prev = q;
      tempNode2->next = q;
      tempNode3->next = p;
      return;
    }
    if (q->prev != NULL && p->next ==NULL){
      Node* tempNode1 = q->next;
      Node* tempNode2 = q->prev;
      Node* tempNode3 = p->prev;
      
      p->next = tempNode1;
      p->prev = tempNode2;
      q->next = NULL;
      q->prev = tempNode3;

      tempNode1->prev = p;
      tempNode2->next = p;
      tempNode3->next = q;
      return;
    }

    if (q->prev == NULL && p->next !=NULL){
      head_ = p;
      Node* tempNode1 = q->next;
      Node* tempNode2 = p->prev;
      Node* tempNode3 = p->next;
      
      p->next = tempNode1;
      p->prev = NULL;
      q->next = tempNode3;
      q->prev = tempNode2;

      tempNode1->prev = p;
      tempNode2->next = q;
      tempNode3->prev = q;
      return;
    }
    if (q->prev == NULL && p->next ==NULL){
      head_ = p;
      Node* tempNode1 = q->next;
      Node* tempNode2 = p->prev;
      
      p->next = tempNode1;
      p->prev = NULL;
      q->next = NULL;
      q->prev = tempNode2;

      tempNode1->prev = p;
      tempNode2->next = q;
      return;
    }
    if (p->prev != NULL && q->prev !=NULL && p->next != NULL && q->next != NULL){
      Node* tempNode1 = p->prev;
      Node* tempNode2 = p->next;
      Node* tempNode3 = q->prev;
      Node* tempNode4 = q->next;  
      
      p->next = tempNode4;
      p->prev = tempNode3;
      q->next = tempNode2;
      q->prev = tempNode1;

      tempNode1->next = q;
      tempNode2->prev = q;
      tempNode3->next = p;
      tempNode4->prev = p;
      return;
    }

  }
  if(p!=NULL && q!=NULL && (p->next == q || q->next == p)) {
    if (p->prev == NULL && q->next !=NULL){
      head_ = q;
      Node* tempNode1 = q->next;

      q->next = p;
      q->prev = NULL;
      p->prev = q;
      p->next = tempNode1;

      tempNode1->prev = p;
      return;
    }
    if (q->prev == NULL && p->next !=NULL){
      head_ = p;
      Node* tempNode1 = p->next;

      p->next = q;
      p->prev = NULL;
      q->prev = p;
      q->next = tempNode1;

      tempNode1->prev = q;
      return;
    }
    if (p->next == NULL && q->prev != NULL){
      head_ = q;
      Node* tempNode1 = q->prev;

      q->next = NULL;
      q->prev = p;
      p->prev = tempNode1;
      p->next = q;

      tempNode1->next = p;
      return;
    }
    if (q->next == NULL && p->prev != NULL){
      Node* tempNode1 = p->prev;

      p->next = NULL;
      p->prev = q;
      q->prev = tempNode1;
      q->next = p;

      tempNode1->next = q;
      return;
    }
     if (p->next == NULL && q->prev == NULL){
      head_ = p;

      q->next = NULL;
      q->prev = p;
      p->prev = NULL;
      p->next = q;
      return;

    }
     if (q->next == NULL && p->prev == NULL){
      head_ = q;

      p->next = NULL;
      p->prev = q;
      q->prev = NULL;
      q->next = p;
      return;
    }
    if (q->next != NULL && q->prev !=NULL && p->next == q && p->prev != NULL){
      Node* tempNode1 = p->prev;
      Node* tempNode2 = q->next;
      
      p->next = tempNode2;
      p->prev = q;
      q->prev = tempNode1;
      q->next = p;

      tempNode1->next = q;
      tempNode2->prev = p;
      return;
    }
    if (q->next == p && q->prev !=NULL && p->next != NULL && p->prev != NULL){
      Node* tempNode1 = q->prev;
      Node* tempNode2 = p->next;
      

      q->next = tempNode2;
      q->prev = p;
      p->prev = tempNode1;
      p->next = q;

      tempNode1->next = p;
      tempNode2->prev = q;
      return;
    }

  }

}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  // Node* next1 = head_;
  // if (head_ != NULL){
  // for (Node* temp = next1->next; temp!=NULL; temp=temp->next){
  //   delete next1;
  //   next1 = temp;
  //   length_--;
  // }
  // head_ = NULL;
  // }
  if (head_ == NULL) {
    return;
  }

  Node *curr = head_;
  Node *next = head_;
  while (curr != NULL) {
    next = curr->next;
    delete curr;
    curr = next;
  }
  head_ = NULL;
  curr = NULL;
  next = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* ****THIS CODE WAS ORIGINAL, IT WORKED BUT TA PROVIDED THE 5-LINE APPROACH USED****
    Node *newNode = new Node(other.head_->data);
    length_++;
    head_ = newNode;
    newNode->prev=NULL;

    Node *nextTarget = other.head_->next;

    Node *newNodeNext = new Node(nextTarget->data);
    head_->next = newNodeNext;
    length_++;
    newNodeNext->prev = head_;
    newNodeNext->next = NULL;

  while (nextTarget->next != NULL){
    Node* newNode1 = new Node(nextTarget->next->data);
    newNodeNext->next = newNode1;
    length_++;
    newNode1->prev = newNodeNext;

    newNodeNext = newNode1;
    newNodeNext->next = NULL;
    nextTarget = nextTarget->next;
  }
  */
  Node* curr = head_;
  Node* otherCurr = other.head_;
  while(otherCurr != NULL){
    curr = insertAfter(curr, otherCurr->data);
    otherCurr = otherCurr->next;
  }

}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  largestDistance();
  Node *curr = head_;
  for (int i = 0; i < length_; i++) {
    Node *nextBlock;
    double distance = 1000;
    Node *inner = curr->next;
    for (int j = i + 1; j < length_; j++) {
      double tempDistance = 0;
      tempDistance = curr->data.distanceTo(inner->data);
      if (tempDistance < distance) {
      distance = tempDistance;
      nextBlock = inner;
      }
      inner = inner->next;
    }
    swap(curr->next, nextBlock);
    curr = curr->next;
  }
}

//   Node *curr = head_;
//   Node *next = head_;
//   while (curr != NULL) {
//   double tempDistance = 1000;
//   Node *nextBlock = curr;
//     while (next != NULL) {
//     Node *next = curr->next;
//     double distance = curr->data.distanceTo(next->data);
//     if (distance < tempDistance) {
//       tempDistance = distance;
//       nextBlock = curr;
//     }
//     swap(next, nextBlock);
//     next = next->next;
//   }
//     curr = curr->next;
//   }
// }

void Chain::largestDistance() {
  Node *curr = head_;
  Node *leftBlock = curr;
  double distance = 0;
  for (int i = 0; i < length_; i++) {
    double tempDistance = 0;
    Node *inner = head_;
    for (int j = 0; j < length_; j++) {
      if (inner != NULL) {
        tempDistance += inner->data.distanceTo(curr->data);
      } 
      if (tempDistance > distance) {
      distance = tempDistance;
      leftBlock = curr;
    }
    inner = inner->next;
    }
    curr = curr->next;
  }
    swap(head_, leftBlock);
}




