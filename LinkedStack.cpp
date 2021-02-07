#include <iostream>
#include <memory>

using Status = int;
#define STATUS_OK 1
#define STATUS_ERROR 0

template<typename T>
struct Node {
    std::shared_ptr<const T> data;
    std::unique_ptr<Node<T>> next;
};

template<class T> 
class LinkedStack {
public:
    LinkedStack():_link_list_head(std::make_unique<Node<T>>()),_link_list_size(2) {}
    ~LinkedStack() = default;

    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    void Push(const T& data);
    Status Pop(std::shared_ptr<const T>& data);

private:
    Status ListInsert(int idx,std::shared_ptr<const T> data);
    Status ListDelete(int idx,std::shared_ptr<const T>& data);

    int GetListSize() { return _link_list_size-2; }

    std::unique_ptr<Node<T>> _link_list_head;
    int _link_list_size;
};

template<typename T>
void LinkedStack<T>::Push(const T& data) {
    std::shared_ptr<const T> data_p = std::make_shared<const T>(data);
    ListInsert(0,data_p); 
}

template<typename T>
Status LinkedStack<T>::Pop(std::shared_ptr<const T>& data) {
    if(GetListSize()==0) return STATUS_ERROR;
    ListDelete(0,data);
    return STATUS_OK;
}

template<typename T>
Status LinkedStack<T>::ListInsert(int idx,std::shared_ptr<const T> data) {
    if(idx<0 || idx>_link_list_size-2) return STATUS_ERROR;
    Node<T> *p = _link_list_head.get();
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); cnt++;
    }
    auto new_node_ptr = std::make_unique<Node<T>>();
    new_node_ptr->next = std::move(p->next);
    new_node_ptr->data = data;
    p->next = std::move(new_node_ptr);
    _link_list_size++;
    return STATUS_OK;
}

template<typename T>
Status LinkedStack<T>::ListDelete(int idx,std::shared_ptr<const T>& data) {
    if(idx<0 || idx>_link_list_size-3) return STATUS_ERROR;
    Node<T> *p = _link_list_head.get();
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); cnt++;
    }
    data = p->next->data;
    p->next = std::move(p->next->next);
    return STATUS_OK;
}

int main() {
    LinkedStack<int> LST;
    for(int i=0;i<10;i++) {
        LST.Push(i);
    }
    std::shared_ptr<const int> res;
    for(int i=0;i<10;i++) {
        LST.Pop(res);
        std::cout<<*res<<std::endl;
    }
}
