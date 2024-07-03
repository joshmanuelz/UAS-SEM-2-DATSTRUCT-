#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int key;
    char name[31];
    int bf;
    int height;
    node* left;
    node* right;
};

node* createnode(int key, char name[]){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->key = key;
    strcpy(newnode->name, name);
    newnode->bf = 0;
    newnode->height = 1;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int getmax(int a, int b){
    return a > b ? a:b;
}

int getheight(node* nodes){
    if(!nodes)return NULL;
    return nodes->height;
}

int setheight(node* nodes){
    if(!nodes)return NULL;
    return getmax(getheight(nodes->left), getheight(nodes->right)) + 1;
}

int setbf(node* nodes){
    if(!nodes)return NULL;
    return getheight(nodes->left) - getheight(nodes->right);
}

node* updatenode(node* nodes){
    if(nodes==NULL)return NULL;
    nodes->bf = setbf(nodes);
    nodes->height = setheight(nodes);
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
    //perform rotate
    pivot->right = nodes;
    nodes->left = rightchild;

    nodes = updatenode(nodes);
    pivot = updatenode(pivot);
    return pivot;
}

node* rotate(node* nodes){
    if(!nodes)return nodes;
    //klw left heavy
    else if(nodes->bf > 1){
        if(nodes->left->bf >= 0){
            return rightrotate(nodes);
        }
        else if(nodes->left->bf < 0){
            nodes->left = leftrotate(nodes->left);
            return rightrotate(nodes);
        }
    }//klw right heavy
    else if(nodes->bf < -1){
        //right right
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

node* insertnode(node* nodes, node* newnode){
    if(!nodes) return newnode;
    else if(newnode->key < nodes->key){
        nodes->left = insertnode(nodes->left, newnode);
    }
    else if( newnode->key > nodes->key){
        nodes->right = insertnode(nodes->right, newnode);
    }
    else if(newnode->key == nodes->key){
        printf("Node Duplicated\n");
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
    }
    else{
        if(!nodes->right && !nodes->left){
            free(nodes);
            nodes = NULL;
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
    if(nodes == NULL)return NULL;
    return rotate(updatenode(nodes));
}

node* searchnode(node* nodes, int key){
    if(!nodes)return nodes;
    else if(key < nodes->key){
        return searchnode(nodes->left, key);
    }
    else if(key > nodes->key){
        return searchnode(nodes->right, key);
    }
    else{
        return nodes;
    }
}

void printinorder(node* nodes){
    if(nodes){
        printinorder(nodes->left);
        printf("ID: %d, Name: %s, BF: %d, Height: %d\n", nodes->key, nodes->name, nodes->bf, nodes->height);
        printinorder(nodes->right);
    }
}

int main(){
    struct node* root = NULL;
    int key, amount, searchkey;
    char name[31], deletename[31];

    printf("How many students ? "); scanf("%d", &amount);
    for(int i = 0; i < amount; i++){
        printf("What is the name of student ? "); scanf("%s", name);
        printf("What is the ID of student ? "); scanf("%d", &key);
        root = insertnode(root, createnode(key, name));
    }
    printinorder(root);
    printf("\n");
    printf("Who do you want to delete? ");scanf("%s", deletename);
    root = deletenode(root, deletename);
    printinorder(root);

    printf("Who do you want to Search? ");scanf("%d", &searchkey);
    node* result = searchnode(root, searchkey);
    if(result){
        printf("%d is found !\n", searchkey);
    }else{
        printf("%d is not found int this tree !\n", searchkey);
    }




    return 0;
}