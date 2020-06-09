#include <iostream>
using namespace std;
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* newNode(int data)
{
    struct Node* node = new Node;
    node->data = data;
    node->left = NULL;
    node->right =NULL;
    return (node);
}
void mirror(struct Node* node)
{
    if(node == NULL)
        return;
    else
    {
        struct Node* temp;
        mirror(node->left);
        mirror(node->right);
        temp = node->left;
        node->left = node-> right;
        node->right = temp;
    }
}
void inorder(struct Node* node)
{
    if(node == NULL)
        return;
    inorder(node->left);
    cout<<node->data<< " ";
    inorder(node->right);
}
int main(){
    struct Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    cout << "Inorder traversal tree is" << endl;
    inorder(root);
    mirror(root);
    cout << "\nInorder traversal of the mirror tree is \n";
    inorder(root);

    return 0;
}
