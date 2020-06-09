#include<iostream>
using namespace std;
struct node{
    int data;
    struct node *left;
    struct node *right;
};
struct node *root;
struct node *head, *tail = NULL;
struct node* createNode(int data){
    struct node *temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
void  convertToLink(struct node *node) {
    if(node == NULL)
        return;
     convertToLink(node->left);
    if(head == NULL) {
        head = tail = node;
    }
    else {
        tail->right = node;
        node->left = tail;
        tail = node;
    }
     convertToLink(node->right);
}
void display() {
    struct node *current = head;
    if(head == NULL) {
        cout<<"List is empty\n";
        return;
    }
    cout<<"generated doubly linked list: \n";
    while(current != NULL) {
        cout<<"\t"<<current->data;
        current = current->right;
    }
    cout<<"\n";
}
int main()
{
    root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    convertToLink(root);
    display();

    return 0;
}
