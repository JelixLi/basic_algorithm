#include <iostream>
#include <memory>
#include <vector>

using Status=int;
#define STATUS_OK 1
#define STATUS_ERROR 0

template<typename T>
struct Node {
    std::shared_ptr<const T> data;
    int cur;
};

template<typename T>
class StaticLinkList {
public:
    StaticLinkList(int capacity);
    ~StaticLinkList() = default;

    StaticLinkList(const StaticLinkList&) = delete;
    StaticLinkList& operator=(const StaticLinkList&) = delete;

    Status GetElem(int idx,std::shared_ptr<const T>& data);
    Status ListInsert(int idx,std::shared_ptr<const T> data);
    Status ListDelete(int idx,std::shared_ptr<const T>& data);
    Status ListDeleteAll();

    bool Empty() {
        int size = _static_list.size();
        return _static_list[size-1].cur == size-1;
    }

    bool Full() {
        return _static_list[0].cur == 0;
    }

private:
    int _alloc_node();
    void InitStaticLinkList(int capacity);
    std::vector<Node<T>> _static_list;
};

template<typename T>
void StaticLinkList<T>::InitStaticLinkList(int capacity) {
    _static_list.resize(capacity+2);
    int size = _static_list.size();
    for(int i=0;i<size-2;i++) {
        _static_list[i].cur = i+1;
    }
    _static_list[size-2].cur = 0;
    _static_list[size-1].cur = size-1;
}

template<typename T>
StaticLinkList<T>::StaticLinkList(int capacity) {
    InitStaticLinkList(capacity);
}

template<typename T>
int StaticLinkList<T>::_alloc_node() {
    int alloced_node = _static_list[0].cur;
    _static_list[0].cur = _static_list[alloced_node].cur;
    return alloced_node;
}

template<typename T>
Status StaticLinkList<T>::ListInsert(int idx,std::shared_ptr<const T> data) {
    if(idx<0 || idx>_static_list.size()-2 || Full()) return STATUS_ERROR;
    int p = _static_list.size()-1;
    int cnt = 0;
    while(cnt<idx) {
        p = _static_list[p].cur;
        cnt++;
    }  
    int new_node = _alloc_node();
    _static_list[new_node].cur =  _static_list[p].cur;
    _static_list[p].cur = new_node;
    _static_list[new_node].data = data;
    return STATUS_OK;
}

template<typename T>
Status StaticLinkList<T>::GetElem(int idx,std::shared_ptr<const T>& data) {
    if(idx<0 || idx>=_static_list.size()-2 || Empty()) return STATUS_ERROR;
    int p = _static_list[_static_list.size()-1].cur;
    int cnt = 0;
    while(cnt<idx) {
        p = _static_list[p].cur;
        cnt++; 
    }
    data = _static_list[p].data;
    return STATUS_OK;
}

template<typename T>
Status StaticLinkList<T>::ListDelete(int idx,std::shared_ptr<const T>& data) {
    if(idx<0 || idx>=_static_list.size()-2 || Empty()) return STATUS_ERROR;
    int p = _static_list.size()-1;
    int cnt = 0;
    while(cnt<idx) {
        p = _static_list[p].cur;
        cnt++; 
    }
    int deleted_node = _static_list[p].cur;
    _static_list[p].cur = _static_list[deleted_node].cur;
    data = _static_list[deleted_node].data;
    _static_list[deleted_node].data.reset();
    return STATUS_OK;   
}

template<typename T>
Status StaticLinkList<T>::ListDeleteAll() {
    InitStaticLinkList(0);
}

int main(int argc,const char* argv[]) {
    StaticLinkList<int> L(10);
    std::shared_ptr<const int> res;
    for(int i=0;i<10;i++) {
        L.ListInsert(i,std::move(std::make_shared<int>(i)));
        L.GetElem(i,res);
        std::cout<<*res<<std::endl;
    }
    std::cout<<L.Full()<<std::endl;
    // for(int i=0;i<10;i++) {
    //     L.ListDelete(0,res);
    //     std::cout<<*res<<std::endl;
    // }
    L.ListDeleteAll();
    std::cout<<L.Empty()<<std::endl;
}
