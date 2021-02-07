#include <iostream>
#include <memory>

typedef int Status;
#define STATUS_OK 1
#define STATUS_ERROR 0

template<typename T>
struct Node {
    std::shared_ptr<const T> data;
    std::unique_ptr<Node<T>> next;
};

template<class T>
class CircularLinkList {
public:
    CircularLinkList();
    ~CircularLinkList();

    CircularLinkList(const CircularLinkList&) = delete;
    CircularLinkList& operator=(const CircularLinkList&) = delete;

    Status GetElem(int idx,std::shared_ptr<const T>& data);
    Status ListInsert(int idx,std::shared_ptr<const T> data);
    Status ListDelete(int idx,std::shared_ptr<const T>& data);
    Status ListDeleteAll();

    bool Empty() {
        return _circular_link_list->next.get() == _circular_link_list;
    }
    int ListSize() {
        return _list_size;
    }
 
private:
    void InitList();
    Node<T> *_circular_link_list;
    int _list_size;
};

template<typename T>
void CircularLinkList<T>::InitList() {
    _circular_link_list = new Node<T>;
    _circular_link_list->next.reset(_circular_link_list);
    _list_size = 0;
}

template<typename T>
CircularLinkList<T>::CircularLinkList() {
    InitList();
}

template<typename T>
Status CircularLinkList<T>::ListInsert(int idx,std::shared_ptr<const T> data) {
    if(idx>_list_size) return STATUS_ERROR;
    Node<T> *p = _circular_link_list;
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); 
        cnt++;
    }
    std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>();
    node->data = data;
    node->next = std::move(p->next);
    p->next = std::move(node);
    _list_size++;
    return STATUS_OK;
}

template<typename T>
Status CircularLinkList<T>::GetElem(int idx,std::shared_ptr<const T>& data) {
    if(Empty()) return STATUS_ERROR;
    Node<T> *p = _circular_link_list;
    int cnt = 0;
    while(cnt<=idx) {
        p = p->next.get(); 
        cnt++;
    }
    data = p->data;
    return STATUS_OK;
}

template<typename T>
Status CircularLinkList<T>::ListDelete(int idx,std::shared_ptr<const T>& data) {
    if(Empty()) return STATUS_ERROR;
    Node<T> *p = _circular_link_list;
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); 
        cnt++;
    }
    data = p->next->data;
    p->next = std::move(p->next->next);
    _list_size--;
    return STATUS_OK;
}

template<typename T>
Status CircularLinkList<T>::ListDeleteAll() {
    _circular_link_list->next = nullptr;
    InitList();
    return STATUS_OK;
}

template<typename T>
CircularLinkList<T>::~CircularLinkList() {
    _circular_link_list->next = nullptr;
    _circular_link_list = nullptr;
}

int main() {
    CircularLinkList<int> L;
    std::shared_ptr<const int> res;
    for(int i=0;i<10;i++) {
        L.ListInsert(i,std::move(std::make_shared<int>(i)));
        L.GetElem(i,res);
        std::cout<<*res<<std::endl;
    }
    std::cout<<L.Empty()<<std::endl;
    std::cout<<L.ListSize()<<std::endl;
    // for(int i=0;i<10;i++) {
    //     L.ListDelete(0,res);
    //     std::cout<<*res<<std::endl;
    // }
    L.ListDeleteAll();
    std::cout<<L.Empty()<<std::endl;
    std::cout<<L.ListSize()<<std::endl;
}
