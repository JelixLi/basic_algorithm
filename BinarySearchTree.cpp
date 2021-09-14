#include <iostream>
#include <memory>
#include <string>

using namespace std;

template<class K,class T>
struct Node {
    Node(K key,T item):key(key),item(item) {}
    K key;
    T item;
    shared_ptr<Node<K,T>> left;
    shared_ptr<Node<K,T>> right;
};

template<class K,class T>
class BST {
public:
    BST() = default;

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void Insert(K key,T item) {
        Insert_Impl(this->tree,key,item);
    }

    void Delete(K key) {
        tree = Delete_Impl(this->tree,key);
    }

    T GetMaxItem() {
        return (*GetMaxItem_Impl(tree)).item;
    }

    T GetMinItem() {
        return (*GetMinItem_Impl(tree)).item;
    }

    void DeleteMax() {
        tree = DeleteMax_Impl(tree);
    }

    void DeleteMin() {
        tree = DeleteMin_Impl(tree);
    }

    bool Exist(K key) {
        return Exist_Impl(tree,key);
    }

    T Get(K key) {
        return (*Get_Impl(tree,key)).item;
    }

private:
    shared_ptr<Node<K,T>> tree;

    bool Exist_Impl(shared_ptr<Node<K,T>>& tree,K key) {
        if(tree == nullptr) return false;
        if(tree->key == key) return true;
        if(tree->key > key) return Exist_Impl(tree->right,key);
        else return Exist_Impl(tree->left,key);
    }

    shared_ptr<Node<K,T>> Get_Impl(shared_ptr<Node<K,T>>& tree,K key) {
        if(tree == nullptr) return nullptr;
        if(tree->key == key) return tree;
        if(tree->key > key) return Get_Impl(tree->right,key);
        else return Get_Impl(tree->left,key); 
    }

    shared_ptr<Node<K,T>> DeleteMax_Impl(shared_ptr<Node<K,T>>& tree) {
        if(tree->right == nullptr) return tree->left;
        tree->right = DeleteMax_Impl(tree->right);
        return tree;
    }

    shared_ptr<Node<K,T>> DeleteMin_Impl(shared_ptr<Node<K,T>>& tree) {
        if(tree->left == nullptr) return tree->right;
        tree->left = DeleteMin_Impl(tree->left);
        return tree;
    }

    shared_ptr<Node<K,T>> GetMaxItem_Impl(shared_ptr<Node<K,T>>& tree) {
        if(tree->right == nullptr) return tree;
        return GetMaxItem_Impl(tree->right);
    }

    shared_ptr<Node<K,T>> GetMinItem_Impl(shared_ptr<Node<K,T>>& tree) {
        if(tree->left == nullptr) return tree;
        return GetMinItem_Impl(tree->left);
    }

    void Insert_Impl(shared_ptr<Node<K,T>>& tree,K& key,T& item) {
        if(tree == nullptr) {
            tree = make_shared<Node<K,T>>(key,item);
            return;
        }
        if(tree->key == key) {
            tree->item = item;
            return;
        }
        if(tree->key < key) {
            Insert_Impl(tree->right,key,item);
        } else {
            Insert_Impl(tree->left,key,item);
        }
    }

   shared_ptr<Node<K,T>> Delete_Impl(shared_ptr<Node<K,T>>& tree,K& key) {
       if(tree == nullptr) return nullptr;
       if(tree->key > key) tree->left = Delete_Impl(tree->left,key);
       else if(tree->key < key) tree->right = Delete_Impl(tree->right,key);
       else {
           if(tree->left == nullptr) return tree->right;
           if(tree->right == nullptr) return tree->left;
           shared_ptr<Node<K,T>> p = GetMinItem_Impl(tree->right);
           tree->key = p->key;
           tree->item = p->item;
           tree->right = DeleteMin_Impl(tree->right);
       }
       return tree;
   }

};

int main() {
    BST<int,int> T;
    for(int i=0;i<100;i++) {
        T.Insert(i,i);
    }
    for(int i=0;i<100;i++) {
        cout<<T.Exist(i)<<endl;
    }
    for(int i=0;i<100;i++) {
        cout<<T.Get(i)<<endl;
    }
    cout<<T.GetMaxItem()<<endl;
    cout<<T.GetMinItem()<<endl;
    T.DeleteMax();
    T.DeleteMin();
    cout<<T.GetMaxItem()<<endl;
    cout<<T.GetMinItem()<<endl;
    for(int i=1;i<25;i++) {
        T.Delete(i);
    }
    for(int i=75;i<99;i++) {
        T.Delete(i);
    }
    cout<<T.GetMaxItem()<<endl;
    cout<<T.GetMinItem()<<endl;
}
