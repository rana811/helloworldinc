#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *left, *right;

    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
	}
};
void printDLL(Node* &head)
{
    Node* curr = head;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->right;
    }
}
void convert(Node* root, Node* &head)
{
    if (root == nullptr)
        return;
    convert(root->left, head);
    Node* right = root->right;
    root->right = head;
    if (head != nullptr)
        head->left = root;

    head = root;
    convert(right, head);
}
void reverse(Node*& head)
{
    Node* prev = nullptr;
    Node* current = head;

    while (current)
    {
        swap(current->left, current->right);
        prev = current;
        current = current->left;
    }

    if (prev != nullptr)
        head = prev;
}
void convert(Node* root)
{
    Node* head = nullptr;
    convert(root, head);
    reverse(head);
    printDLL(head);
}

int main()
{
    Node* root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);

    convert(root);

    return 0;
}
