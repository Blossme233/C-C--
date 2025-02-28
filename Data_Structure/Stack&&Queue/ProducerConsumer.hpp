/****************************************************************/
/*                    ProducerConsumer Class                    */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/
#pragma once

#include <string>

const int SIZE = 20;

class ProducerConsumer
{
private:
  int queueFront; //the index in queue[] that will be dequeued next
  int queueEnd; //the index in queue[] that was most recently enqueued
  int counter = 0; //changed
  std::string queue[SIZE];

public:
  ProducerConsumer();
  bool isEmpty();
  bool isFull();
  void enqueue(std::string item);
  void dequeue();
  std::string peek();
  int queueSize();   //changed
  int getQueueFront() { return queueFront; }
  int getQueueEnd() { return queueEnd + 1; }
  std::string* getQueue() { return queue; }

};
