#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

// HELPER FUNCTIONS HERE...
template <class T>
void deletenode(node<T>* a)
{
    node<T>* traverse=a;
    if (traverse!=NULL)
    {
        deletenode(traverse->left);
        deletenode(traverse->right);
        delete traverse;
    }
}



template <class T>
BST<T>::BST(){
    root = NULL;
}

template <class T>
BST<T>:: ~BST()
{
   //node<T>* traverse=root;
    deletenode(root);

}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
    int heightl=1;
    int heightr=1;
    if (p==NULL)
    {
        return 0;
    }
    node<T>* ps=p;
    if (ps!=NULL)
    {
    if (ps->left!=NULL)
    {
        heightl=1+height(ps->left);
    }
    if (ps->right!=NULL)
    {
        heightr=1+height(ps->right);
    }
    }
    return max(heightr,heightl);
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    if(p==NULL)
    {
        return 0;
    }
    int left=height(p->left);
    int right=height(p->right);
    return (left-right);
}

template <class T>
void BST<T> :: fixHeight(node<T>* p)
{
    p->height=height(p);
    // node<T>* a=p;
    // while (a!=NULL)
    // {
    //     fixHeight(a->left);
    //     fixHeight(a->right);
    //     a->height=height(a);
    // }
}



// template <class T>
// node<T>* fix(node<T>* p)
// {
//     node<T>* a=p;
//     while (a!=NULL)
//     {
//         fix(a->left);
//         fix(a->right);
//         a->height=height(a);
//     }
//     return a;
// }

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
   //   if(p==NULL)
   //  {
   //      return NULL;
   //  }
   //  if(p->right==NULL && p->left==NULL)
   //  {
   //      return p;
   //  }
   // node<T>* temp=p->right;
   // node<T>* temp2=temp->left;
   // temp->left=p;
   // p->right=temp2;
   // fixHeight(p);
   // fixHeight(temp);
   // return temp;
    return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p)
{
    return p;
   //  if(p==NULL)
   //  {
   //      return NULL;
   //  }
   //  if(p->right==NULL && p->left==NULL)
   //  {
   //      return p;
   //  }
   // node<T>* temp=p->left;
   // node<T>* temp2=temp->right;
   // temp->right=p;
   // p->left=temp2;
   // //root aur temp badalte sirf
   // fixHeight(p);
   // fixHeight(temp);
   // return temp;
}
// template <class T>
// node<T>* fix(node<T>* p)
// {
//     node<T>* a=p;
//     while (a!=NULL)
//     {
//         fix(a->left);
//         fix(a->right);
//         a->height=height(a);
//     }
//     return a;
// }
template <class T>
node<T>* BST<T> :: balance(node<T>* p){  
    // //cout<<p->key<<endl;
    // //fix heights first
    // //p=fix(p);
    // if (p==NULL) {
    //     return NULL;
    // }
    // p->left=balance(p->left);
    // p->right=balance(p->right);
    // //balance(p);
    // int  bfactor=balanceFactor(p);
    // if(abs(bfactor)>1)
    // {
        
    //     if(bfactor>1)//left left case or left right case
    //     {
    //         //cout<<"idhar aata"<<endl;
    //         if (balanceFactor(p->left)>=0)//llc
    //         {
    //             return rotateright(p);
    //         }
    //         else if (balanceFactor(p->left)<0)//lrc
    //         {
    //             p->left=rotateleft(p->left);
    //             return rotateright(p);
    //         }
    //     }
    //     if (bfactor<-1)//right right case or right left ase
    //     {
    //   //      cout<<"idhar bhi aata"<<endl;
    //         if (balanceFactor(p->right)<=0)//rrc
    //         {
    //             return rotateleft(p);
    //         }
    //         else if (balanceFactor(p->right)>0)//rlc
    //         {
    //             p->right=rotateright(p->right);
    //             return rotateleft(p);
    //         }

    //     }
        
    // }
    //p->left=balance(p->left);
    //p->right=balance(p->right);
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations. //4 cases
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    node<T>* traverse=p;
    if(traverse!=NULL)
    {
        if (traverse->key<=k)
        {
            p->right=insertHelper(value, k, traverse->right);
        }
        else
        {
            p->left=insertHelper(value, k, traverse->left);
        }
    }
    
   
    traverse=new node<T>(k, value);
    if(p==NULL)
    {
        p=traverse;

    }
    return (p);
}
// takes key ​ k ​ as input and returns pointer to the node that has the matching key.
// Returns ​ NULL​ if ​ k ​ does not exist in the tree
template<class T>
node<T>* BST<T> :: search(T key){
    node<T>* traverse=root;
    while (traverse!=NULL)
    {
        if (traverse->key>key)
        {
            traverse=traverse->left;
        }
        else if (traverse->key<key)
        {
            traverse=traverse->right;
        }
        else
        {
            return traverse;
        }
    }
        return NULL;
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    if (p!=NULL)
    {
        node<T>* traverse=p;
        while (traverse->left!=NULL)
        {
            traverse=traverse->left;
        }
        return traverse;

    }
    else
    return NULL;
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    if (p==NULL)
    {
        return NULL;
    }
    if (p->left ==NULL)
    {
        node<T>* righ=NULL;
        if(p->right!=NULL)
        {
            righ=p->right;
        }
     //   cout << "removing " << p->key << endl;
        delete p;
        p=righ;
        //fixHeight(p);
        return (p); //isko balance tu error ata
    }
    if (p->left->left==NULL)
    {
        node<T>* righ=NULL;
        if(p->left->right!=NULL)
        {
            righ=p->left->right;
        }
        delete p->left;
        p->left=righ;
        //fixHeight(p->left);
        //fixHeight(p);
        return (p);

    }
    p->left=removemin(p->left);
    return (p);

    // This function recursively finds the min node and deletes it.
}
// template<class T>
// void level_traversal(node<T>* root) 
// {
//     Queue<T>* b; 
//     node<T>* traverse= root;
//     while (traverse!=NULL)
//     {
//         cout<<"ID: "<<traverse->id<<"     latest data: "<<traverse->latest_data<<endl;
//         for (int i=0; i< traverse->child.size(); i++)
//         {
//             b.enqueue(traverse->child[i]);
//         }
//         if (b.isEmpty())
//             return;
        
//         traverse=b.dequeue();
//     }
// }

template<class T>
void PreOrder(node<T>* root) {
    if (root != NULL) {
        cout << root->key << ", ";
        inOrder(root->left);
        inOrder(root->right) ;
    }
}

template<class T>
void BST<T>::delete_node(T k){
    //PreOrder(root);
    root = remove(root, k);
    
    

}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{

    //three cases
    if(p==NULL)
    {
        return NULL;
    }
    if (p->key == k) {
        node<T>* traverse=findmin(p->right);
        if (!traverse)
            return NULL;
        p->key=traverse->key;
        p->value=traverse->value;
        p->right=removemin(p->right);
    }
    if (findmin(p)->key==k)
        p = removemin(p);
    //reach node
    if(k>p->key)
    {
        p->right=remove(p->right,k);
    }
    else if (k<p->key)
    {
        p->left=remove(p->left,k);
    }
    
       
 //   This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
