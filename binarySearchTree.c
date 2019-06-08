#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;

struct node* findRightMost(struct node*);
struct node* findLeftMost(struct node*);
struct node* parentRight(struct node*);
struct node* parentLeft(struct node*);


int main(){

    insertData(10);
    insertData(20);
    insertData(5);
    insertData(45);
    insertData(7);
    insertData(3);
    insertData(1);
    insertData(4);
    postOrder(root);
    printf("\n");
    deleteNode(5);
    postOrder(root);
    printf("\n");


    return 0;
}

void insertData(int data){

    struct node* p;
    p = (struct node*) malloc(sizeof(struct node));
    p->data = data;
    p->left = NULL;
    p->right = NULL;

    
    struct node* parent = root;
    

    if(root == NULL){
        root = p;
    }else{
        struct node* t;
        t = root;
        while(t){
            parent = t;
            // printf("parent value: %d\n", t->data);
            if(t->data > p->data){
                t = t->left;
            }else{
                t = t->right;
            }
        }
        if(parent->data > p->data){
            parent->left = p;
        }else{
            parent->right = p;
        }
    }
}

void postOrder(struct node* tree){
    if(tree != NULL){
        postOrder(tree->left);
        postOrder(tree->right);
        printf("%d->", tree->data);
    }else{
        return;
    }
}

void deleteNode(int data){

    
    struct node* parent = root;
    struct node* t;
    t = root;
    struct node* current = root;
        
    while(t){
        parent = t;
        current = t;
        if(t->right->data == data){
            current = t->right;
            break;
        }else if(t->left->data == data){
            current = t->left;
            break;
        }else if(t->data < data){
            if(t->right != NULL){
                t = t->right;
            }else{
                printf("Not found\n");
                break;
            }
        }else if(t->data > data){
            if(t->left != NULL){
                t = t->left;
            }else{
                printf("Not found\n");
                break;
            }
            
        }else{
            printf("Not found\n");
            break;
        }
    }

    if(current->left == NULL && current->right == NULL){
        if(parent->left == NULL && parent->right != NULL){
            parent->right = NULL;
            free(current);
        }else if(parent->right == NULL && parent->left != NULL){
            parent->left = NULL;
            free(current);
        }
    }else if((current->left != NULL && current->right == NULL) || (current->left == NULL && current->right != NULL)){
        if(current == parent->right){
            if(current->left == NULL && current->right != NULL){
                parent->right = current->right;
                free(current);
            }else if(current->left != NULL && current->right == NULL){
                parent->right = current->left;
                free(current);
            }
        }else if(current == parent->left){
            if(current->left == NULL && current->right != NULL){
                parent->left = current->right;
                free(current);
            }else if(current->left != NULL && current->right == NULL){
                parent->left = current->left;
                free(current);
            }
        }
    }else if(current->left != NULL && current->right != NULL){
        if(current == parent->left){
            struct node* rMost = findRightMost(current->left);
            current->data = rMost->data;
            if(current->left->right != NULL){
                struct node* parentR = parentRight(current->left);
                parentR->right = NULL;
            }
            free(rMost);
            
        }else if(current == parent->right){
            struct node* lMost = findLeftMost(current->right);
            current->data = lMost->data;
            if(current->right->left != NULL){
                struct node* parentL = parentLeft(current->right);
                parentL->left = NULL;
            }
            free(lMost);
        }
        
    }
}


struct node* findRightMost(struct node *node){
    
    if(node->right == NULL){
        
        return node;
    }else{
        
        findRightMost(node->right);
    }
}

struct node* findLeftMost(struct node *node){
    
    if(node->left == NULL){
        
        return node;
    }else{
        
        findLeftMost(node->left);
    }
}

struct node* parentRight(struct node* node){
    if(node->right->right == NULL){
        
        return node;
    }else{
        
        parentRight(node->right);
    }
}

struct node* parentLeft(struct node* node){
    if(node->left->left == NULL){
        
        return node;
    }else{
        
        parentLeft(node->left);
    }
}

