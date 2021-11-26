#include <iostream>
#include <memory>

template<typename KT,typename VT>
struct Node {
    KT key;
    VT val;
    std::shared_ptr<Node<KT,VT>> left,right;
    int height;
};

template<typename KT,typename VT>
class AVLTree {
public:
    AVLTree():tree(nullptr) {}

    void Insert(KT key,VT val) {
        tree = _Insert(tree,key,val);
    }

    void Delete(KT key) {
        tree = _Delete(tree,key);
    }

    VT Get(KT key) {
        std::shared_ptr<Node<KT,VT>> node = _Get(tree,key);
        if(node == nullptr) {
            throw "key not exist";
        }
        return node->val;
    }

    int Height() {
        return _Height(tree);
    }

    void InOrderPrint() {
        _InOrderPrint(tree);
    }

private:
    std::shared_ptr<Node<KT,VT>> tree;

    void _InOrderPrint(std::shared_ptr<Node<KT,VT>> node) {
        if(node != nullptr) {
            _InOrderPrint(node->left);
            std::cout<<node->key<<std::endl;
            _InOrderPrint(node->right);
        }
    }

    std::shared_ptr<Node<KT,VT>> _Get(std::shared_ptr<Node<KT,VT>> node,KT key) {
        if(node != nullptr) {
            if(key == node->key) return node;
            if(key > node->key) return _Get(node->right,key);
            else return _Get(node->left,key);
        }
        return nullptr;
    }

    std::shared_ptr<Node<KT,VT>> _Insert(std::shared_ptr<Node<KT,VT>> node,KT key,VT val) {
        if(node == nullptr) {
            node = std::make_shared<Node<KT,VT>>();
            node->key = key;
            node->val = val;
        } else if(key > node->key) {
            node->right = _Insert(node->right,key,val);
            if(_Height(node->right) - _Height(node->left) == 2) {
                if(key > node->right->key) node = _L_Rotate(node);
                else if(key < node->right->key) node = _RL_Rotate(node);
            }
        } else if(key < node->key) {
            node->left = _Insert(node->left,key,val);
            if(_Height(node->left) - _Height(node->right) == 2) {
                if(key < node->left->key) node = _R_Rotate(node);
                else if(key > node->left->key) node = _LR_Rotate(node);
            }
        } else if(key == node->key) {
            node->key = key;
            node->val = val;
        }
        node->height = std::max(_Height(node->left),_Height(node->right)) + 1;
        return node;
    }

    std::shared_ptr<Node<KT,VT>> _Delete(std::shared_ptr<Node<KT,VT>> node,KT key) {
        if(node != nullptr) {
            if(key == node->key) {
                if(node->left!=nullptr && node->right!=nullptr) {
                    if(_Height(node->left) > _Height(node->right)) {
                        std::shared_ptr<Node<KT,VT>> pre = _Max(node->left);
                        node->key = pre->key;
                        node->left = _Delete(node->left,pre->key);
                    } else {
                        std::shared_ptr<Node<KT,VT>> post = _Min(node->right);
                        node->key = post->key;
                        node->right = _Delete(node->right,post->key);
                    }
                } else {
                    if(node->left != nullptr) node = node->left;
                    else if(node->right != nullptr) node = node->right;
                    else return nullptr;
                }
            } else if(key > node->key) {
                node->right = _Delete(node->right,key);
                if(_Height(node->left) - _Height(node->right) == 2) {
                    if(_Height(node->left->right) > _Height(node->left->left)) {
                        node = _LR_Rotate(node);
                    } else {
                        node = _R_Rotate(node);
                    }
                }
            } else if(key < node->key) {
                node->left = _Delete(node->left,key);
                if(_Height(node->right) - _Height(node->left) == 2) {
                    if(_Height(node->right->left)>_Height(node->right->right)) {
                        node = _RL_Rotate(node);
                    } else {
                        node = _L_Rotate(node);
                    }
                }
            }
            node->height = std::max(_Height(node->left),_Height(node->right)) + 1;
            return node;
        }
        return nullptr;
    }

    std::shared_ptr<Node<KT,VT>> _Max(std::shared_ptr<Node<KT,VT>> node) {
        if(node != nullptr) {
            while(node->right != nullptr) node = node->right;
            return node;
        }
        return nullptr;
    } 

    std::shared_ptr<Node<KT,VT>> _Min(std::shared_ptr<Node<KT,VT>> node) {
        if(node != nullptr) {
            while(node->left != nullptr) node = node->left;
            return node;
        }
        return nullptr;
    }
    
    int _Height(std::shared_ptr<Node<KT,VT>>& node) {
        return node == nullptr? 0 : node->height;
    }

    std::shared_ptr<Node<KT,VT>> _R_Rotate(std::shared_ptr<Node<KT,VT>>& node) {
        std::shared_ptr<Node<KT,VT>> L = node->left;
        node->left = L->right;
        L->right = node;

        node->height = std::max(_Height(node->left),_Height(node->right)) + 1;
        L->height = std::max(_Height(L->left),_Height(L->right)) + 1; 

        return L;
    }

    std::shared_ptr<Node<KT,VT>> _L_Rotate(std::shared_ptr<Node<KT,VT>>& node) {
        std::shared_ptr<Node<KT,VT>> R = node->right;
        node->right = R->left;
        R->left = node;

        node->height = std::max(_Height(node->left),_Height(node->right)) + 1;
        R->height = std::max(_Height(R->left),_Height(R->right)) + 1; 

        return R;
    }

    std::shared_ptr<Node<KT,VT>> _RL_Rotate(std::shared_ptr<Node<KT,VT>>& node) {
        node->right = _R_Rotate(node->right);
        return _L_Rotate(node);
    }

    std::shared_ptr<Node<KT,VT>> _LR_Rotate(std::shared_ptr<Node<KT,VT>>& node) {
        node->left = _L_Rotate(node->left);
        return _R_Rotate(node);
    }
};

int main() {
    AVLTree<int,int> tree;
    for(int i=0;i<10;i++) {
        tree.Insert(i,i);
    }
    for(int i=0;i<5;i++) {
        tree.Delete(i);
    }
    for(int i=5;i<10;i++) {
        std::cout<<tree.Get(i)<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<tree.Height()<<std::endl;
    std::cout<<std::endl;
    tree.InOrderPrint();
}
