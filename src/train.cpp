// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() { cleanup(); }

void Train::cleanup() {
  if (!first) return;

  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);

  first = nullptr;
}

Train::Car* Train::getLastCar() const {
  if (!first) return nullptr;
  return first->prev;
}

void Train::addCar(bool lightState) {
    auto createNewCar = [](bool light) {
        return new Car(light);  // Явный вызов конструктора
    };

    auto linkToEmptyList = [this](Car* car) {
        this->first = car;
        car->next = car;
        car->prev = car;
    };

    auto appendToExistingList = [this](Car* car) {
        Car* tail = this->first->prev;
        tail->next = car;
        car->prev = tail;
        car->next = this->first;
        this->first->prev = car;
    };

    Car* newNode = createNewCar(lightState);
    if (!this->first) {
        linkToEmptyList(newNode);
    } else {
        appendToExistingList(newNode);
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
