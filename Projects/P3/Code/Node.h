//Kevin Shannon
//Templated Node Data Structure

#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
  protected:
    T data;
    Node<T>* next;
  public:
    Node(T data, Node<T>* next);
    ~Node();
    void setData(T data);
    void setNext(Node<T>* next);
    T getData();
    Node<T>* getNext();
};

//Node methods

template <class T>
Node<T>::Node(T data, Node<T>* next) {
  this->data = data;
  this->next = next;
}

template <class T>
Node<T>::~Node() {
  delete next;
}

template <class T>
void Node<T>::setData(T data) {
  this->data = data;
}

template <class T>
void Node<T>::setNext(Node<T>* next) {
  this->next = next;
}

template <class T>
T Node<T>::getData() {
  return data;
}

template <class T>
Node<T>* Node<T>::getNext() {
  return next;
}

#endif
