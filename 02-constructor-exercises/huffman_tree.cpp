#include <iostream>
using namespace std;

struct Node { // node = char + value + 2 links
    char ch;
    int value;
    Node* left;
    Node* right;

    Node(char c, int v, Node* l = nullptr, Node* r = nullptr) {
        ch = c;
        value = v;
        left = l;
        right = r;
    }

    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
};

int main() {
    
    // text "aaaaabbb": 'a' appears 5 times, 'b' appears 3 times
    Node* leaf_a = new Node('a', 5);
    Node* leaf_b = new Node('b', 3);
    
    // root's value is the sum of children value 
    Node* root = new Node('\0', leaf_a->value + leaf_b->value, leaf_a, leaf_b);

    cout << "root value: " << root->value << ", 'a' value: " << root->left->value << ", 'b' value: " << root->right->value << endl;
    cout << "   (" << root->value << ")" << endl;
    cout << "  " << "/" << "   " << "\\" << endl;
    cout << root->left->ch << "(" << root->left->value << ") "<< root->right->ch << "(" << root->right->value << ")"<< endl;
    
    cout << "root is leaf: " << root->isLeaf() << endl; // 0
    cout << "a is leaf: " << root->left->isLeaf() << endl; // 1
    
    // left link = 0, right = 1
    cout << root->left->ch << " = 0" << endl;
    cout << root->right->ch << " = 1" << endl;  

    delete leaf_a;
    delete leaf_b;
    delete root;

    return 0;
}