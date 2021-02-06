#include <iostream>
#include <memory>

using Status = int;
#define STATUS_OK 1
#define STATUS_ERROR 0

template<typename T>
struct Node {
    std::shared_ptr<const T> data;
    std::unique_ptr<Node<T>> next;
// public:
//     ~Node() {
//         std::cout<<"deconstruct"<<std::endl;
//     }
};

template<typename T>
class LinkList {
public:
    LinkList():_link_list_head(std::make_unique<Node<T>>()),_link_list_size(2) {}
    ~LinkList() = default;

    LinkList(const LinkList&) = delete;
    LinkList& operator=(const LinkList&) = delete;

    Status GetElem(int idx,std::shared_ptr<const T>& data);
    Status ListInsert(int idx,std::shared_ptr<const T> data);
    Status ListDelete(int idx,std::shared_ptr<const T>& data);
    Status ListDeleteAll();

    int GetListSize() { return _link_list_size-2; }

private:
    std::unique_ptr<Node<T>> _link_list_head;
    int _link_list_size;
};

template<typename T>
Status LinkList<T>::GetElem(int idx,std::shared_ptr<const T>& data) {
    if(idx<0 || idx>_link_list_size-3) return STATUS_ERROR;
    Node<T> *p = _link_list_head->next.get();
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); cnt++;
    }
    data = p->data;
    return STATUS_OK;
}

template<typename T>
Status LinkList<T>::ListInsert(int idx,std::shared_ptr<const T> data) {
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
Status LinkList<T>::ListDelete(int idx,std::shared_ptr<const T>& data) {
    if(idx<0 || idx>_link_list_size-3) return STATUS_ERROR;
    Node<T> *p = _link_list_head.get();
    int cnt = 0;
    while(cnt<idx) {
        p = p->next.get(); cnt++;
    }
    data = p->next->data;
    p->next = std::move(p->next->next);
}

template<typename T>
Status LinkList<T>::ListDeleteAll() {
    _link_list_head->next = nullptr;
    _link_list_size = 2;
}

int main() {
    LinkList<int> L;
    std::shared_ptr<const int> res;
    for(int i=0;i<10;i++) {
        L.ListInsert(i,std::move(std::make_shared<int>(i)));
        L.GetElem(i,res);
        std::cout<<*res<<std::endl;
    }
    // for(int i=0;i<10;i++) {
    //     L.ListDelete(0,res);
    //     std::cout<<*res<<std::endl;
    // }
    L.ListDeleteAll();
}
