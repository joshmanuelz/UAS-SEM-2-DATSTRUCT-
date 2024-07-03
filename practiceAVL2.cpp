#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int key;
    char name[31];
    int bf;
    int height;
    node* left;
    node* right;
};

node* createnode (int key, char name[]){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->key = key;
    strcpy(newnode->name, name);
    newnode-> bf = 0;
    newnode->height = 1;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int getmax(int a, int b){
    return a>b ? a:b;
}

int getheight(node* nodes){
    if(!nodes)return NULL;
    return nodes->height;
}

int setheight(node* nodes){
    if(!nodes)return NULL;
    return getmax(getheight(nodes->left), getheight(nodes->right))+1;
}

int setbf(node* nodes){
    if(!nodes)return NULL;
    return getheight(nodes->left) - getheight(nodes->right);
}

node* updatenode(node* nodes){
    if(nodes==NULL)return NULL;
    nodes->height = setheight(nodes);
    nodes->bf = setbf(nodes);
    return nodes;
}

node* leftrotate(node* nodes){
    node* pivot = nodes->right;
    node* leftchild = pivot->left;
    //perform rotate
    pivot->left = nodes;
    nodes->right = leftchild;

    nodes = updatenode(nodes);
    pivot = updatenode(pivot);
    return pivot;
}

node* rightrotate(node* nodes){
    node* pivot = nodes->left;
    node* rightchild = pivot->right;
    //rorate
    pivot->right = nodes;
    nodes->left = rightchild;

    nodes = updatenode(nodes);
    pivot = updatenode(pivot);
    return pivot;
}

node* rotate(node* nodes){
    if(!nodes)return nodes;
    else if(nodes->bf > 1){
        if(nodes->left->bf >= 0){
            return rightrotate(nodes);
        }
        else if(nodes->left->bf < 0){
            nodes->left = leftrotate(nodes->left);
            return rightrotate(nodes);
        }
    }
    else if(nodes->bf < -1){
        if(nodes->right->bf <= 0){
            return leftrotate(nodes);
        }
        else if(nodes->right->bf > 0){
            nodes->right = rightrotate(nodes->right);
            return leftrotate(nodes);
        }
    }
    return nodes;
}

node* insertnode (node* nodes, node* newnode){
    if(!nodes)return newnode;
    else if(newnode->key < nodes->key){
        nodes->left = insertnode(nodes->left, newnode);
    }
    else if(newnode->key > nodes->key){
        nodes->right = insertnode(nodes->right, newnode);
    }
    else if(newnode->key == nodes->key){
        printf("Duplicated key\n");
        return nodes;
    }
    return rotate(updatenode(nodes));
}

node* deletenode(node* nodes, char name[]){
    if(!nodes)return nodes;
    else if(strcmp(nodes->name, name) > 0){
        nodes->left = deletenode(nodes->left, name);
    }
    else if(strcmp(nodes->name, name) < 0){
        nodes->right = deletenode(nodes->right, name);
    }else{
        if(!nodes->left && !nodes->right){
            free(nodes);
            return NULL;
        }
        else if(!nodes->right){
            node* temp = nodes->left;
            free(nodes);
            return temp;
        }
        else if(!nodes->left){
            node* temp = nodes->right;
            free(nodes);
            return temp;
        }
        else{
            node* prede = nodes->left;
            while(prede->right){
                prede = prede->right;
            }
            strcpy(nodes->name, prede->name);
            nodes->key = prede->key;
            nodes->left = deletenode(nodes->left, prede->name);
        }
    }
    if(!nodes)return NULL;
    return rotate(updatenode(nodes));
}

node* printinoder (node* nodes){
    if(nodes){
        printinoder(nodes->left);
        printf("Key: %d, Name: %s, BF: %d, Height: %d\n", nodes->key, nodes->name, nodes->bf, nodes->height);
        printinoder(nodes->right);
    }
}

int main(){
    struct node* root = NULL;
    root = insertnode(root, createnode(123, "Amel"));
    root = insertnode(root, createnode(156, "Brian"));
    root = insertnode(root, createnode(169, "Cekitot"));
    printinoder(root);
    printf("\n");
    root = deletenode(root, "cekitot");
    printinoder(root);

    
    return 0;
}