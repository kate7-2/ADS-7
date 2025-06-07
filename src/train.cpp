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
    return new Car(light);
  };

  auto linkToEmptyList = [this](Car* car) {
    this->first = car;
    car->next = car;
    car->prev = car;
  };

  auto appendToExistingList = [this](Car* car) {
    auto* tail = this->first->prev;
    tail->next = car;
    car->prev = tail;
    car->next = this->first;
    this->first->prev = car;
  };

  Car* newNode = createNewCar(lightState);

  if (this->first == nullptr) {
    linkToEmptyList(newNode);
  } else {
    appendToExistingList(newNode);
  }
}

int Train::getLength() {
  resetOperationCounter();

  auto calculate = [this]() -> int {
    if (!this->first) return 0;

    auto* ptr = this->first;
    bool initialLightState = ptr->light;

    if (!initialLightState) {
      ptr->light = true;
      this->countOp++;
    }

    int counter = 1;
    ptr = ptr->next;
    this->countOp++;

    auto detectLight = [this, &counter](auto* p) {
      while (!p->light) {
        p = p->next;
        counter++;
        this->countOp += 2;
      }
      p->light = false;
      this->countOp++;
      return p;
    };

    ptr = detectLight(ptr);

    if (!this->first->light) {
      return counter;
    }

    return -1;
  };

  int result = calculate();
  return result != -1 ? result : getLength();
}

int Train::getOpCount() const { return countOp; }

void Train::resetOperationCounter() { countOp = 0; }
