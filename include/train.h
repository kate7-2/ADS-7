// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;

    Car(bool l) : light(l), next(nullptr), prev(nullptr) {}
  };
  Car* first;
  int countOp;
  void cleanup();
  Car* getLastCar() const;
 public:
  Train();
  ~Train();
  Train(const Train&) = delete;
  Train& operator=(const Train&) = delete;

  void addCar(bool lightState);
  int getLength();
  int getOpCount() const;
  void resetOperationCounter();
};
#endif  // INCLUDE_TRAIN_H_
