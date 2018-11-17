//Kevin Shannon
//Templated Linked List Data Structure

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include "Node.h"

template <class T>
class LinkedList {
  friend class Node<T>;
  protected:
    Node<T>* head;
    Node<T>* tail;
    int size;
  public:
    LinkedList();
    ~LinkedList();
    void Append(T data);
    bool Contains(T data);
    T Retrieve(int index);
    void Empty();
    int Length();
};

//LinkedList methods

template <class T>
LinkedList<T>::LinkedList() {
  head = NULL;
  tail = NULL;
  size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
  Empty();
}

template <class T>
void LinkedList<T>::Append(T data) {
  if(head == NULL && tail == NULL) {
    Node<T>* temp = new Node<T>(data, NULL);
    head = tail = temp;
  } else {
    Node<T>* temp = new Node<T>(data, NULL);
    tail->setNext(temp);
    tail = temp;
  }
  size++;
}

template <class T>
bool LinkedList<T>::Contains(T data) {
  Node<T>* current = head;
  while(current != NULL) {
    if(current->getData() == data)
      return true;
    current = current->getNext();
  }
  return false;
}

template <class T>
T LinkedList<T>::Retrieve(int index) {
  Node<T>* current = head;
  for(int i = 0; i < index; i++)
    current = current->getNext();
  return current->getData();
}

template <class T>
void LinkedList<T>::Empty() {
  while(head != NULL) {
    Node<T>* current = head->getNext();
    head->setNext(NULL);
    delete head;
    head = current;
  }
  size = 0;
}

template <class T>
int LinkedList<T>::Length() {
  return size;
}

#endif
