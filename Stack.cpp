/*
.cpp implementation of the Stack class in Stack.h
*/

#include "Arduino.h"
#include "Stack.h"

Stack::Stack() {
 _top = -1;
 _size = 20;
 _stack[_size];
}

void Stack::push(float data) {
 if (!isFull()) {
   _stack[++_top] = data;
 }
}

float Stack::pop() {
 if (!isEmpty()) {
   return _stack[_top--];
 }
}

float Stack::peek() {
  return _stack[_top];
}

boolean Stack::isEmpty() {
 return _top == -1;
}

boolean Stack::isFull() {
 return _top == _size - 1;
}
