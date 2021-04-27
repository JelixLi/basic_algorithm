#include <iostream>
#include <memory>
#include <string>
#include <stack>

struct Node {
    char data;
    Node *left,*right;
    Node():left(NULL),right(NULL) {}
};

Node* BuildTree(std::string tree_str) {
    if(tree_str.size()==0) return NULL;
    std::stack<Node**> sk;
    Node *T = NULL;
    Node **p = &T;
    int idx = 0;
    while(idx<tree_str.size()) {
        while(idx<tree_str.size() && tree_str[idx]!='#') {
            *p = new Node();
            (*p)->data = tree_str[idx];
            sk.push(p);
            p = &((*p)->left);
            ++idx;
        }
        if(!sk.empty()) {
            p = sk.top();
            sk.pop();
            p = &((*p)->right);
        }
        ++idx;
    }
    return T;
}

std::string Preorder_traversal_recursive(Node *T) {
    if(T==NULL) return "";
    std::string s(1,T->data);
    s += Preorder_traversal_recursive(T->left);
    s += Preorder_traversal_recursive(T->right);
    return s;
}

std::string Preorder_traversal(Node *T) {
    std::stack<Node*> sk;
    Node *p = T;
    std::string s;
    while(p || !sk.empty()) {
        while(p) {
            s.push_back(p->data);
            sk.push(p);
            p = p->left;
        }
        if(!sk.empty()) {
            p = sk.top();
            sk.pop();
            p = p->right;
        }
    }
    return s;
}

std::string Midorder_traversal_recursive(Node *T) {
    if(T==NULL) return "";
    std::string s;
    s += Midorder_traversal_recursive(T->left);
    s.push_back(T->data);
    s += Midorder_traversal_recursive(T->right);
    return s;
}

std::string Midorder_traversal(Node *T) {
    std::stack<Node*> sk;
    Node *p = T;
    std::string s;
    while(p || !sk.empty()) {
        while(p) {
            sk.push(p);
            p = p->left;
        }
        if(!sk.empty()) {
            p = sk.top();
            sk.pop();
            s.push_back(p->data);
            p = p->right;
        }
    }
    return s;
}

std::string Postorder_traversal_recursive(Node *T) {
    if(T==NULL) return "";
    std::string s;
    s += Postorder_traversal_recursive(T->left);
    s += Postorder_traversal_recursive(T->right);
    s.push_back(T->data);
    return s;
}

std::string Postorder_traversal(Node *T) {
    std::stack<Node*> sk;
    Node *p = T;
    std::string s;
    Node *pre = NULL;
    while(p || !sk.empty()) {
        while(p) {
            sk.push(p);
            p = p->left;
        }
        if(!sk.empty()) {
            p = sk.top();
            if(p->right==pre || p->right==NULL) {
                sk.pop();
                s.push_back(p->data);
                pre = p;
                p = NULL;
            } else {
                p = p->right;
            }
        }
    }
    return s;
}

int main() {
    // std::string tree_str = "ABC##D##E##";
    std::string tree_str = "ABC##D##E#F##";
    Node *tree = BuildTree(tree_str);
    std::cout<<Preorder_traversal_recursive(tree)<<std::endl;
    std::cout<<Preorder_traversal(tree)<<std::endl;
    std::cout<<Midorder_traversal_recursive(tree)<<std::endl;
    std::cout<<Midorder_traversal(tree)<<std::endl;
    std::cout<<Postorder_traversal_recursive(tree)<<std::endl;
    std::cout<<Postorder_traversal(tree)<<std::endl;
}
