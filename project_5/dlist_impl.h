#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include <iostream>
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const{
        return (!first);
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node *np = new node;
    np->op = op;
    np->prev = NULL;

    if(isEmpty()){
        np->next = NULL;
		first = last = np;
    } else {
		np->next = first;
        first->prev = np;
        first = np;
    }

}

template <class T>
void Dlist<T>::insertBack(T *op){
    node *np = new node;
    np->op = op;
    np->next = NULL;

    if(isEmpty()){
		np->prev = NULL;
        first = last = np;
    } else {
		np->prev = last;
        last->next = np;
        last = np;
    }

}

template <class T>
T* Dlist<T>::removeFront(){
    if (isEmpty()){
        emptyList e;
        throw e;
    }

    T *result = first->op;
	
	if (first == last){
		delete first;
		first = last = NULL;
	} else {
		node *victim = first;
		first = victim->next;
		delete victim;
		first->prev= NULL;
	}
    return result;
}

template <class T>
T* Dlist<T>::removeBack(){
	T *result = last->op;
    if (isEmpty()){
        emptyList e;
        throw e;
    }
	if (first == last){
		
		delete last;
		first = last = NULL;
	} else {
		node *victim = last;
		last = victim->prev;
		delete victim;
		last->next = NULL;
	}
    return result;
}

template <class T>
Dlist<T>::Dlist() : first(NULL), last(NULL) {}

template <class T>
void Dlist<T>::removeAll(){
    while (!isEmpty()){
        delete removeFront();
    }
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    if (!l.isEmpty()){
        node *np = l.first;
        while (np) {
            T *newelt = new T(*np->op);
            insertBack(newelt);
            np = np->next;
        }
    }
}

template <class T>
Dlist<T>::Dlist(const Dlist &l) : first(NULL), last(NULL) {
    copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist &l){
    if(this != &l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}

#endif