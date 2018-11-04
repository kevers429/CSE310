//Kevin Shannon
//Templated Linked List Data Structure

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <class T>
class LinkedList {
  friend class Node<T>;
  protected:
    Node<T>* head;
    Node<T>* tail;
    int size;
    T id;
  public:
    LinkedList();
    ~LinkedList();
    void Append(T data);
    bool Exists(T data);
    Node<T>* Find(T data);
    int IndexOf(T data);
    T RetrieveFront();
    T RetrieveEnd();
    T Retrieve(int index);
    T getID();
    void setID(T id);
    void Empty();
    int Length();
};

//LinkedList methods

template <class T>
LinkedList<T>::LinkedList() {
  head = NULL;
  tail = NULL;
  size = 0;
  id = -1;
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
bool LinkedList<T>::Exists(T data) {
  Node<T>* current = head;
  while(current != NULL) {
    if(current->getData() == data) {
      return true;
    }
    current = current->getNext();
  }
  return false;
}

template <class T>
Node<T>* LinkedList<T>::Find(T data) {
  Node<T>* current = head;
  while(current != NULL) {
    if(current->getData() == data)
    return current;
    current = current->getNext();
  }
  return NULL;
}

template <class T>
int LinkedList<T>::IndexOf(T data) {
  Node<T>* current = head;
  int count = 0;
  while(current != NULL) {
    if(current->getData() == data)
    return count;
    current = current->getNext();
    count++;
  }
  return -1;
}

template <class T>
T LinkedList<T>::RetrieveFront() {
  return head->getData();
}

template <class T>
T LinkedList<T>::RetrieveEnd() {
  return tail->getData();
}

template <class T>
T LinkedList<T>::Retrieve(int index) {
  Node<T>* current = head;
  for(int i = 0; i < index; i++)
  current = current->getNext();
  return current->getData();
}

template <class T>
T LinkedList<T>::getID() {
  return id;
}

template <class T>
void LinkedList<T>::setID(T id) {
  this->id = id;
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
