#include<stdio.h>
#include<iostream>
#include<map>



namespace ariel{
        template <typename T>
    
    class BinaryTree{
        struct Node
        {
            int inst;
            Node *left;
            Node *right;
            Node *parent;
            T theValue;
            Node(const T& val):theValue(val){
                theValue=val;
               left=nullptr;
               right = nullptr;
               parent=nullptr;
                inst=0;
            }
           
        };
        

        public:
        Node *root;
        std::map<T,Node*> leafs;

    BinaryTree<T>& add_root(T p){
        
        if(!root){
             
            Node * x = new Node(p);
            x->theValue =p;
            x->inst++;
            root = x;
            leafs[p]=x;
        }
        else{
            
            leafs.erase(root->theValue);
           
            root->theValue=p;
           
            leafs[p]=root;           
        
        }     
        
        return *this;
    }


        
    BinaryTree<T>& add_left(T p ,T a){ // p =  9 a =1
        if(!root){
            throw std::invalid_argument("no root added");
        }
        Node * x = leafs.at(p);
        
        if(x->left){
            
            Node * temp = x->left;
            leafs.erase(temp->theValue);
            
            temp->theValue=a;
            
            leafs[a]=temp;
            
            
        }
        else{
            Node * e = new Node(a);
            e->theValue=a;
            x->left=e;            
            e->parent=x;
            leafs[a]=e;     
        }
        
        
      
        return *this;
    }
        
    
    BinaryTree<T>& add_right(T p,T a){   
        if(!root){
            throw std::invalid_argument("no root added");
        }
        Node * x =  leafs.at(p);
        if(x->right){
           Node * temp = x->right;
            leafs.erase(temp->theValue);
            temp->theValue=a;
            leafs[a]=temp;
            
        }
        else{
            Node * e = new Node(a);
            x->right=e;
            e->parent=x;
            leafs[a]=e;
                    
        }
        
        return *this;

    }
        BinaryTree(Node * ro=nullptr):root(ro){
            
            
        }
        BinaryTree(const BinaryTree<T>& tree){
                root = DeepCopy(tree.root,nullptr);

        }
        BinaryTree( BinaryTree<T>&& tree)noexcept{
                root = DeepCopy(tree.root,nullptr);

        }
        Node * DeepCopy(Node * node, Node * parent){
            Node * temp = new Node(node->theValue);
            if(node->left){
                temp->left = DeepCopy(node->left,temp);
            }
            if(node->right){
                temp->right = DeepCopy(node->right,temp);
            }
            if(parent){
                temp->parent=parent;
            }
            
            leafs[temp->theValue]=temp;
            return temp;


        }
        void RecursiveDelete(Node * node){
                if(node->left){
                    RecursiveDelete(node->left);
                }
                if(node->right){
                    RecursiveDelete(node->right);
                }
                node->parent=nullptr;
                delete node;

        }
        BinaryTree<T>& operator=(const BinaryTree<T>& tree){
          if(this!=&tree){
              if(root){
                RecursiveDelete(root);
                leafs.clear();
                root=nullptr;
                
            }
            root=DeepCopy(tree.root,nullptr);
          }
            
            
            
            return *this;
        }
        BinaryTree<T>& operator=( BinaryTree<T>&& tree)noexcept{
            
            return *this;
        }
        ~BinaryTree(){
           for(auto& x:leafs){
               x.second->left=nullptr;
               x.second->right=nullptr;
               x.second->parent=nullptr;
                delete x.second;
                x.second=nullptr;
            }
        }
        
        
        


        	

	class iterator_pos {

	  private:
        Node *CurrentIndex;
        Node *P;
        size_t index;
       
    public:
        iterator_pos(size_t uy=0,Node * x = 0):CurrentIndex(x),index(uy){
            if(!CurrentIndex){
                return;
            }
            P=nullptr;
            while(CurrentIndex->right||CurrentIndex->left){
                            if(!CurrentIndex->left&&CurrentIndex->right){
                                P=CurrentIndex;
                                CurrentIndex=CurrentIndex->right;
                         }
                            while(CurrentIndex->left){
                                P=CurrentIndex;
                                CurrentIndex=CurrentIndex->left;
                            }
                        }       
            
            
        }
        bool operator!=(const iterator_pos& it) const{
            
            return CurrentIndex!=it.CurrentIndex;
        }
        bool operator==(const iterator_pos& it) const{
            
            return CurrentIndex==it.CurrentIndex;
        }

        iterator_pos& operator ++(){
            if(CurrentIndex->left!=P&&CurrentIndex->left&&CurrentIndex->right!=P){
                        while(CurrentIndex->left){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->left;
                        }
                    }
            else if(CurrentIndex->right!=P&&CurrentIndex->right){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->right;
                        while(!CurrentIndex->left&&CurrentIndex->right){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->right;
                        }
                                        
                        while(CurrentIndex->left){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->left;
                        }
                    }            
            else{        
                        if(!CurrentIndex->parent){
                            CurrentIndex=nullptr;
                            return *this;
                        }           
                        P = CurrentIndex;
                        CurrentIndex = CurrentIndex->parent;
                            if(CurrentIndex->right && CurrentIndex->right!=P){
                            ++*this;
                            }
                        
                    }
            return *this;
        }
        iterator_pos operator ++(int){
            
            iterator_pos it = *this;
            ++*this;
            return it;
        }

        T* operator ->() const{
            
            return &CurrentIndex->theValue;
        }
        T& operator *() const{
            return CurrentIndex->theValue;
        }
        int size(){
            return index;
        }
        
    };
    
    class iterator_in {

	  private:
        Node *CurrentIndex;
        Node *P;
        size_t index;
       
    public:
        iterator_in(size_t uy=0,Node * x = nullptr):CurrentIndex(x),index(uy){
            P=CurrentIndex;
            if(!CurrentIndex){return;}
            while(CurrentIndex->left){
                
                P=CurrentIndex;
                CurrentIndex=CurrentIndex->left;
            }    
            
            
        }
        bool operator!=(const iterator_in& it) const{
            return CurrentIndex!=it.CurrentIndex;
        }
        bool operator==(const iterator_in& it) const{
            
            return CurrentIndex==it.CurrentIndex;
        }
        

        iterator_in& operator ++(){ //do it
            if((CurrentIndex->left!=P && CurrentIndex->left) && CurrentIndex->right!=P){
                        
                        while(CurrentIndex->left){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->left;
                        }
                    }
            else if(CurrentIndex->right!=P&&CurrentIndex->right){
                      
                        P=CurrentIndex;
                        CurrentIndex=CurrentIndex->right;
                        while(CurrentIndex->left){
                            P=CurrentIndex;
                            CurrentIndex=CurrentIndex->left;
                        }
                    }            
            else{
                        
                        if(!CurrentIndex->parent){
                            
                            CurrentIndex=nullptr;
                            return *this;
                        }
                        
                        P = CurrentIndex;
                        CurrentIndex = CurrentIndex->parent;
                        if((CurrentIndex->right&&CurrentIndex->right==P)){
                                ++*this;
                               
                        }
                    }
                
            return *this;
        }
        iterator_in operator ++(int){
            
            iterator_in it = *this;
            ++*this;
            return it;
        }

        T* operator ->() const{
            
            return &CurrentIndex->theValue;
        }
        T& operator *()const{
            return CurrentIndex->theValue;
        }
        int size(){
            return index;
        }
        
    };
    
    class iterator_pre {

	  private:
        Node *CurrentIndex;
        Node *P;
        size_t index;
       
    public:
        iterator_pre(size_t uy = 0 ,Node * x = nullptr):CurrentIndex(x),index(uy){    
            
            P=CurrentIndex;
        }
        bool operator!=(const iterator_pre& it) const{
            if(!CurrentIndex){return false;}
            return CurrentIndex!=it.CurrentIndex;
        }
        bool operator==(const iterator_pre& it) const{
            
            return CurrentIndex==it.CurrentIndex;
        }
        

        iterator_pre& operator++(){
               
            if(CurrentIndex->right!=P && CurrentIndex->left!=P && CurrentIndex->left){              
                        P=CurrentIndex;
                        CurrentIndex=CurrentIndex->left;
                        }
            else if(CurrentIndex->right!=P && CurrentIndex->right){
                        P=CurrentIndex;
                        CurrentIndex=CurrentIndex->right;
                        }
            else if(!CurrentIndex->parent){
                        CurrentIndex =nullptr;
                        }
            else{
                        P=CurrentIndex;
                        CurrentIndex=CurrentIndex->parent;
                        ++*this;
                        }
            return *this;
        }
         iterator_pre operator++(int){
            
            iterator_pre it = *this;
            ++*this;
            return it;
        }

        T* operator ->()const{
            
            return &CurrentIndex->theValue;
        }
        T& operator *()const{
            return CurrentIndex->theValue;
        }
        int size(){
            return 0;
        }
        
    };
        friend std::ostream& operator<<(std::ostream& a,  const BinaryTree<T>& c){
            return a;
        }
        
        iterator_in begin_inorder(){
                return iterator_in{leafs.size(),root};
        }

        iterator_in end_inorder(){
            

            return iterator_in{0,nullptr};
        }

       iterator_pre begin_preorder(){
           
        return iterator_pre{leafs.size(),root};
        }

        iterator_pre end_preorder(){
           
        return iterator_pre{};
        }

        iterator_pos begin_postorder(){
            
        return iterator_pos{leafs.size(),root};
        }

        iterator_pos end_postorder(){
        return iterator_pos{0,nullptr};
        }
        iterator_in begin(){
           return iterator_in{leafs.size(),root};
        }

        iterator_in end(){
            return iterator_in{0,nullptr};
        }
};
    }



