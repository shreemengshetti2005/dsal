#include <iostream>
using namespace std;

class avl{
    public:
    avl*left,*right;
    int Key,height;
    string val;
    
    avl(int key,string meaning):left(NULL),right(NULL),Key(key),val(meaning),height(1){}

};
  
  int getheight(avl*root){
     if(!root) return 0;

     return root->height;
  }

  int isbalanced(avl*root){
    return getheight(root->left)-getheight(root->right);
  }

  avl*leftrotation(avl*root){
      if(!root) return NULL;

      avl*child=root->right;

      avl*childleft=child->left;

      child->left=root;

      root->right=childleft;

      root->height=1+max(getheight(root->left),getheight(root->right));

      child->height=1+max(getheight(root->left),getheight(root->right));

      return child;
  }

  avl*rightrotation(avl*root){
      if(!root) return NULL;

      avl*child=root->left;

      avl*childright=child->right;

      child->right=root;

      root->left=childright;

      root->height=1+max(getheight(root->left),getheight(root->right));

      child->height=1+max(getheight(root->left),getheight(root->right));

      return child;
  }

   avl*insert(avl*root,int key,string mean){
       avl*newnode=new avl(key,mean);

       if(!root) return newnode;

       if(root->Key<key){
         root->right=insert(root->right,key,mean);
       }
       else if(root->Key>key){
        root->left=insert(root->left,key,mean);
       }
       else{
        return root;
       }

       //update root height: 

       root->height=1+max(getheight(root->left),getheight(root->right));
       int balance=isbalanced(root);

       //Now balance the tree according to conditions;

       if(balance>1 && root->left->Key > key){   //LL , right rotation
           return rightrotation(root);
       }
       else if( balance <-1 && root->right->Key < key){   //RR and left rotation
        return leftrotation(root);
       }

       else if( balance >1 && root->left->Key < key){ 
          root->left=leftrotation(root->left);
          return rightrotation(root);
       }

       else if( balance <-1 && root->right->Key > key){ 
          root->right=rightrotation(root->right);
          return leftrotation(root);
       }
       else {
        return root;
       }
   }

   void inorder(avl*root){
     if(! root) return;
     inorder(root->left);
    cout<<"{"<<root->Key<<"->"<<root->val<<"} ";
    inorder(root->right);
   }

int main(){
    avl*root=NULL;

    root=insert(root,10,"labra");
    root=insert(root,20,"Husky");
    root=insert(root,60,"bull");
    root=insert(root,40,"germaan");
    
    cout<<"Ascending order: \n";
    inorder(root);
}