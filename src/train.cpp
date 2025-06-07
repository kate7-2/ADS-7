// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;

  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);
}

void Train::addCar(bool light) {
  Car* newCar = new Car(light);  // Используем конструктор

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  resetOperationCounter();
  if (!first) return 0;

  Car* current = first;

  countOp++;
  if (!current->light) {
    current->light = true;
    countOp++;
  }

  current = current->next;
  countOp++;

  int length = 1;
  while (true) {
    countOp++;
    if (current->light) {
      current->light = false;
      countOp++;
      break;
    }
    current = current->next;
    countOp++;
    length++;
  }

  countOp++;
  if (!first->light) {
    return length;
  }

  return getLength();
}

int Train::getOpCount() const { return countOp; }

void Train::resetOperationCounter() { countOp = 0; }
