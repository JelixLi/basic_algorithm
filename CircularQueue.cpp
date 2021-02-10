#include <iostream>
#include <memory>
#include <vector>

using Status = int;
#define STATUS_OK 1
#define STATUS_ERROR 0

template<class T>
class CircularQueue {
public:
    CircularQueue(int capacity);
    ~CircularQueue() = default;

    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    Status Enqueue(T& data);
    Status Dequeue(std::shared_ptr<const T>& data);
private:
    bool Empty() { return front==rear; }
    bool Full() { return front==((rear+1)%_circular_queue.size()); }
    std::vector<std::shared_ptr<const T>> _circular_queue;
    int front;
    int rear;
};

template<typename T>
CircularQueue<T>::CircularQueue(int capacity):front(0),rear(0) {
    _circular_queue.resize(capacity+1);
}

template<typename T>
Status CircularQueue<T>::Enqueue(T& data) {
    if(Full()) return STATUS_ERROR;
    _circular_queue[rear] = std::make_shared<const T>(data);
    rear = (rear+1)%_circular_queue.size();
    return STATUS_OK;
}

template<typename T>
Status CircularQueue<T>::Dequeue(std::shared_ptr<const T>& data) {
    if(Empty()) return STATUS_ERROR;
    data = _circular_queue[front];
    front = (front+1)%_circular_queue.size();
    return STATUS_OK;
}

int main() {
    CircularQueue<int> CQ(10);
    for(int i=0;i<10;i++) {
        CQ.Enqueue(i);
    }
    std::shared_ptr<const int> res;
    for(int i=0;i<10;i++) {
        CQ.Dequeue(res);
        std::cout<<*res<<std::endl;
    }
}
