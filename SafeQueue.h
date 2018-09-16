#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <QObject>
#include <condition_variable>
#include <queue>

template <class T>
class SafeQueue {
private:
  std::condition_variable has_work;
  std::mutex mu_queue;
  std::queue<T> item_queue;
  unsigned int size;
public:
  SafeQueue<T>() {
    size = 0;
  }
  void push_item(T data);
  T pop_item();
  unsigned int get_size();
};

template<class T>
inline void SafeQueue<T>::push_item(T data)
{
  std::unique_lock<std::mutex> lock(mu_queue);
  bool was_empty = item_queue.empty();
  item_queue.push(data);
  size++;
  lock.unlock();
  if (was_empty) {
    has_work.notify_one();
  }
}

template<class T>
inline T SafeQueue<T>::pop_item()
{
  std::unique_lock<std::mutex> lock(mu_queue);
  while (item_queue.empty()) {
    has_work.wait(lock);
  }
  T p = item_queue.front();
  item_queue.pop();
  size--;
  return p;
}

template<class T>
inline unsigned int SafeQueue<T>::get_size()
{
  std::unique_lock<std::mutex> lock(mu_queue);
  int temp = size;
  lock.unlock();
  return temp;
}
#endif
