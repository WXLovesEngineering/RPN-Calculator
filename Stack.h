/*
My personal Stack class definition
Date: 2025 04 21
*/

#ifndef Stack_h
#define Stack_h

#include "Arduino.h"

class Stack {
   public:
     Stack();
     void push(float data);
     float pop();
     float peek();
     boolean isFull();
     boolean isEmpty();
   private:
     int8_t _top;
     uint8_t _size;
     float _stack[];
};

#endif
