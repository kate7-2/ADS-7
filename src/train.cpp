// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  auto createNewCar = [light]() { return new Car{light, nullptr, nullptr}; };

  auto initFirstCar = [this, &createNewCar]() { first = createNewCar(); };

  auto addSecondCar = [this, &createNewCar]() {
    Car* newCar = createNewCar();
    first->next = newCar;
    first->prev = newCar;
    newCar->prev = first;
    newCar->next = first;
  };

  auto insertNewCar = [this, &createNewCar]() {
    Car* newCar = createNewCar();
    Car* last = first->prev;

    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  };

  if (!first) {
    initFirstCar();
  } else if (!first->next) {
    addSecondCar();
  } else {
    insertNewCar();
  }
}
int Train::getOpCount() { return countOp; }

int Train::getLength() {
  countOp = 0;
  Car* tempObj;
  while (true) {
    tempObj = first;
    unsigned int countCar = 1;
    if (!tempObj->light) {
      tempObj->light = true;
    }
    tempObj = tempObj->next;
    countOp += 2;
    while (!tempObj->light) {
      tempObj = tempObj->next;
      countOp += 2;
      countCar++;
    }
    tempObj->light = false;
    if (!first->light) {
      return countCar;
    }
  }
}

Train::~Train() {
  auto destroyCars = [this]() {
    if (!this->first) return;

    auto* current = this->first->next;
    auto* stop = this->first;

    while (current != stop) {
      auto* nextCar = current->next;
      delete current;
      current = nextCar;
    }

    delete stop;
    this->first = nullptr;
  };

  destroyCars();
}
