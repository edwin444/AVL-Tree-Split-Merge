#include<stdio.h>
#include<stdlib.h>

#define COUNT 5

int p = 0;
struct node                            //This is the structure definition
{ 
        int data;
        int height;
        struct node* left;
        struct node* right;
        struct node* parent;
        
}*header,*header1,*new_node,*prev,*prevptr,*current,*pos;


int Switch = 0;

//for traversing tree to find the location to insert node.
int heightHelper(struct node *x)
{
    if (x == NULL)
    {
        return -1;
    }
    else
    {
        return x->height;
    }
}

void inorder(struct node * ptr,int *a)
{
      int x = 0;
      if (ptr==NULL)
          return;
      inorder(ptr->left,a);
      //printf("%d(p=%d)(H=%d)|",ptr->data,ptr->parent==NULL ? 0:ptr->parent->data,ptr->height);
      
      *(a+p) = ptr->data;
      p+=1;
      inorder(ptr->right,a);
}
void preorder(struct node* ptr)
{
      if (ptr==NULL)
          return;
   
      printf("%d|",ptr->data);
      preorder(ptr->left);
      preorder(ptr->right);

}
void postorder(struct node* ptr){
      if (ptr==NULL)
          return;
      postorder(ptr->left);
      postorder(ptr->right);
      printf("%d|",ptr->data);

}

void print2DUtil(struct node *root, int spaces) 
{ 
    if (root == NULL) 
        return; 
    spaces += COUNT; 
    print2DUtil(root->right, spaces); 
    printf("\n"); 
    for (int i = COUNT; i < spaces; i++) 
    {
        printf(" ");
    } 
    printf("%d\n", root->data); 
    print2DUtil(root->left, spaces); 
} 
int balance_factor(struct node *ptr){
      int lh,hr;
      
      if (ptr==NULL)
      	return 0;
      if (ptr->left==NULL)
        lh=0;
      else
        lh=ptr->left->height+1;
       
      if (ptr->right==NULL)
        hr=0;
      else
        hr=ptr->right->height+1;
      
      
      return (lh-hr);           //here we check the height of the left and right sub trees and subtract it.    
}

int hyt(struct node *ptr)
{
      int lh,hr;
      
      if (ptr==NULL)
      	return 0;
      if (ptr->left==NULL)
        lh=0;
      else
        lh=ptr->left->height+1;
       
      if (ptr->right==NULL)
        hr=0;
      else
        hr=ptr->right->height+1;
      
      
      if (lh>hr)         //here to find height we check whether left of right sub trees height is the greatest and assign that as height.
                         //but we are assigning heights to these nodes during the insertion stage from leaf to the root node by using function 
                          //recursion stack
          return lh;
      return hr;      

}

struct node* rightrotate(struct node *ptr)
{ 
          if (ptr==NULL)
            return NULL;
             struct node * temp;
           temp=ptr->left;

           if (ptr->parent!=NULL)
           {
               //we also need to change where parent of earlier ptr pointed to
                if (ptr == ptr->parent->left)
                {
                    ptr->parent->left = temp;
                }
                else if (ptr == ptr->parent->right)
                {
                    ptr->parent->right = temp;
                }
           }
          

           //fixing parents
           temp->parent = ptr->parent;
           if (temp->right!=NULL)
           {
               temp->right->parent = ptr;
           }
            ptr->parent = temp;

           ptr->left=temp->right;
           temp->right=ptr;

           
           // printf("temp->right: %d\n",temp->right->data);
           //now we need to update the heights
           
           ptr->height=hyt(ptr);
           temp->height=hyt(temp);
           //printf("***\n");
           //inorder(temp);
           //printf("\n");
           //inorder(temp->parent);
           //printf("***\n");
           return temp;
}
struct node* leftrotate(struct node * ptr)
{          
           //printf("the value of 15: %d\n",ptr->data);
           //inorder(ptr);
           //printf("\n");
            if (ptr==NULL)
            return NULL;
           struct node * temp;
           temp=ptr->right;

           if (ptr->parent!=NULL)
           {
               //we also need to change where parent of earlier ptr pointed to
                if (ptr == ptr->parent->left)
                {
                    ptr->parent->left = temp;
                }
                else if (ptr == ptr->parent->right)
                {
                    ptr->parent->right = temp;
                }
           }

           //fixing parents
           temp->parent = ptr->parent;
           if (temp->left!=NULL)
           {
               temp->left->parent = ptr;
           }
           
           ptr->parent = temp;
           //printf("Value of 16: %d\n",temp->left->data);
           ptr->right=temp->left;
           //printf("Value of 16: %d\n",temp->left->data);
           temp->left=ptr;
           //now we need to update the heights
           
           ptr->height=hyt(ptr);
           temp->height=hyt(temp);
           
           return temp;
}

struct node* LL(struct node * ptr)
{
           ptr=rightrotate(ptr);
           return ptr;


}
struct node * RR(struct node * ptr)
{
         ptr=leftrotate(ptr);
         return ptr;
}
struct node * LR(struct node* ptr)
{

           ptr->left=leftrotate(ptr->left);
           ptr=rightrotate(ptr);
           return ptr;

}
struct node* RL(struct node* ptr)
{

           ptr->right=rightrotate(ptr->right);
           ptr=leftrotate(ptr);
           return ptr;
}


struct node * insert(struct node  *ptr,int data1)
{
            if (ptr==NULL)         //this is used to create a node once we reach NULL and insert as a leaf .
            {
                 new_node=(struct node *)malloc(sizeof(struct node));
                 new_node->data=data1;
                 new_node->right=NULL;
                 new_node->left=NULL;
                 new_node->parent=NULL;
                 ptr=new_node;
                
                 
            }
            else if (data1<ptr->data)
                 { 
                       ptr->left=insert(ptr->left,data1); 
                       if (ptr->left!=NULL)   
                            ptr->left->parent = ptr;              //first it inserts into the binary seach tree such that the resultant tree is BST
                       if (balance_factor(ptr)==2)           //now it has to check if the given BST is balance or not 
                       {                                     //if not balanced then we balance it also we are updating heights from leaf to root
                           if (ptr->left->data>data1)
                               ptr=LL(ptr);            //first case
                           else
                               ptr=LR(ptr);            //third case
                       }
                 }
                       
            else 
                 {
                        
                        ptr->right=insert(ptr->right,data1);
                        if (ptr->right!=NULL)
                            ptr->right->parent = ptr;
                        if (balance_factor(ptr)==-2)
                        {
                           if (ptr->right->data<data1)
                               ptr=RR(ptr);         //second case
                           else
                               ptr=RL(ptr);          //fourth case
                        }
                 }
                 ptr->height=hyt(ptr);   //note: here before the new_node is returned its current height from the leaf to root nodes are assigned
                                         //but the heights are also updated in the rotation process  in the rotate functions.
                 return ptr;         //this will store the nodes from root to leaf in program stack such that the leaf to root hyts get updated 
                                   //and balanced
            

}
struct node * get_left_most_node(struct node * ptr)    //utility function to get the left most node from the given node ptr
{

         if (ptr->left==NULL)
            return ptr;
         else
            get_left_most_node(ptr->left);
}

struct node * deleteNode(struct node  *ptr,int data1)   //this data1 is the data of the node to be deleteNoded.
{           struct node * temp;
            if (ptr==NULL)         //this is used to create a node once we reach NULL and insert as a leaf .
            {
                 return ptr;
            }
            if (data1<ptr->data)
            {
                ptr->left=deleteNode(ptr->left,data1);
            }
            else if (data1>ptr->data)
            {
                ptr->right=deleteNode(ptr->right,data1);
            }
                
            else
            {
                  if (ptr->left==NULL)
                  {      
                         temp=ptr->right;
                         if (temp!=NULL)
                         {
                             temp->parent = ptr->parent;
                             //printf("temp->parent: %d,ptr->parent: %d\n",temp->parent->data,ptr->parent->data);
                         }
                         
                         free(ptr);
                         return temp;
                  }
                  else if (ptr->right==NULL)
                  {
                  
                         temp=ptr->left;
                         if (temp!=NULL)
                         {
                             temp->parent = ptr->parent;
                             //printf("temp->parent: %d,ptr->parent: %d\n",temp->parent->data,ptr->parent->data);
                         }
                         free(ptr);
                         return temp;
                 }
                 temp=get_left_most_node(ptr->right);
                 ptr->data=temp->data;
                 ptr->right=deleteNode(ptr->right,temp->data);
             }
             ptr->height=hyt(ptr);  //update height
             
             if (ptr==NULL)
                 return ptr;
              
             ptr->height=hyt(ptr);  //update height
             
             
              
                      
            if (balance_factor(ptr)==2)           //now it has to check if the given BST is balance or not 
            {                                     //if not balanced then we balance it also we are updating heights from leaf to root
                 if (balance_factor(ptr->left)>=0)
                 {
                       return LL(ptr);            //first case
                               
                 }
                 else
                 {
                       return LR(ptr);            //third case
                               
                 }
            }
             
        
             
                        
                       
            if (balance_factor(ptr)==-2)
            {
                 if (balance_factor(ptr->right)<=0)
                 {
                       return RR(ptr);
                                               //second case
                 }
                 else
                 {
                       return RL(ptr);          //fourth case
                              
                 }
             }
             
                
             return ptr;          
}


void balanceRight(struct node* N)
{
    struct node* M = N->left;
    if (heightHelper(M->right) > heightHelper(M->left))
    {
        struct node* temp = leftrotate(M);
    }
    struct node * headSub = rightrotate(N);
}
void balanceLeft(struct node* N)
{
    struct node* M = N->right;
    if (heightHelper(M->left) > heightHelper(M->right))
    {
        struct node* temp = rightrotate(M);
    }
    struct node* headSub = leftrotate(N);
    //inorder(N);
}

//we pass the header as in case the header node gets rotated the 
//new header node should be assigned its value..
struct node* rebalance(struct node* current)
{

    if (heightHelper(current->left) > heightHelper(current->right) + 1)
    {
        balanceRight(current);
    }
    if (heightHelper(current->right) > heightHelper(current->left) + 1)
    {
        balanceLeft(current);
    }

    
    //adjusting height of current
    current->height = heightHelper(current->left) >= heightHelper(current->right) ? heightHelper(current->left)+1: heightHelper(current->right)+1; 
    
    if (current->parent == NULL)
    {
        return current;
    }
    else
    {
        struct node* temp = rebalance(current->parent);
        return temp;
    }
    
}

struct node* extractRight(struct node** header)
{
    if (*header == NULL)
    {
        return NULL;
    }

    current = *header;
    prev = NULL;
    while (current!=NULL)
    {
        prev = current;
        current = current->right;
    }
    struct node* rightMost = (struct node*)malloc(sizeof(struct node));
    rightMost->left = NULL;
    rightMost->parent = NULL;
    rightMost->right = NULL;
    rightMost->data = prev->data;
    struct node * temp = deleteNode(*header,prev->data);
    *header = temp; 
    return rightMost;
}
struct node* extractLeft(struct node** header)
{
    if (*header == NULL)
    {
        return NULL;
    }

    current = *header;
    prev = NULL;
    while (current!=NULL)
    {
        prev = current;
        current = current->left;
    }
    //printf("Entered..\n");
    struct node* leftMost = (struct node*)malloc(sizeof(struct node));
    leftMost->left = NULL;
    leftMost->parent = NULL;
    leftMost->right = NULL;
    leftMost->data = prev->data;
    //printf("Entered..\n");
    struct node * temp = deleteNode(*header,prev->data);
    *header = temp; 
    //inorder(header);
    return leftMost;
}

//merge T and U
struct node* Merge_with_root(struct node *header,struct node *header1,struct node* root)
{
    //find the largest node of first tree
    root->left = header;
    root->right = header1;
    if (root->left!=NULL)
    {
        root->left->parent = root;
    }
    if (root->right!=NULL)
    {
        root->right->parent = root;
    }
    
    //adjust height of prev node
    root->height = heightHelper(root->left) >= heightHelper(root->right) ? heightHelper(root->left) + 1: heightHelper(root->right) + 1;
    //returns new root of merged trees
    return root; 
}
struct node* AVLTreeMergeWithRoot(struct node *header,struct node* header1,struct node* root)
{
    //special case ie if no root passed 
    if (root == NULL)
    {   
        return NULL;
    }
    
    if ((heightHelper(header) - heightHelper(header1) <= 1) && (heightHelper(header)-heightHelper(header1)>=-1))
    {      
        struct node* newRoot = Merge_with_root(header,header1,root);
        return newRoot;
    }
    else if(heightHelper(header) > heightHelper(header1))
    {
        
        struct node* R = AVLTreeMergeWithRoot(header->right,header1,root);

        if (Switch == 1)
        {
            return R;
        }
        //header is the parent before we went to header->right when the recursive calls return.
        header->right = R;
        R->parent = header;
        header->height = heightHelper(header->left)>=heightHelper(header->right)? heightHelper(header->left)+1: heightHelper(header->right)+1;
        struct node* newHeader = rebalance(header);
        //returning the new header of the merged trees 

        Switch = 1;
        return newHeader;
    }
    else if(heightHelper(header) < heightHelper(header1))
    {
        //here the tree with the larger values have greater height
        struct node* R = AVLTreeMergeWithRoot(header,header1->left,root);
        if (Switch == 1)
        {
            return R;
        }
        
        header1->left = R;
        R->parent = header1;

        //recalulate height of header1
        header1->height = heightHelper(header1->left)>=heightHelper(header1->right)? heightHelper(header1->left)+1: heightHelper(header1->right)+1;
        struct node* newHeader = rebalance(header1);
        //returning the new header of the merged trees 
        Switch = 1;
        return newHeader;
    }
}

struct node* AVLTreeMerge(struct node* header,struct node* header1)
{
    if (heightHelper(header) >= heightHelper(header1))
    {
        struct node* rightMost = extractRight(&header);
        if (rightMost == NULL)
        {
            //case when header is NULL
            return header1;
        }
        else
        {
            struct node* newMergedHeader = AVLTreeMergeWithRoot(header,header1,rightMost);
            return newMergedHeader;
        }
    }
    else
    {
        //case when the right tree has greater height
        struct node* leftMost = extractLeft(&header1);
        if (leftMost == NULL)
        {
            //case when header1 is NULL then return the other tree
            return header;
        }
        else
        {
            struct node* newMergedHeader = AVLTreeMergeWithRoot(header,header1,leftMost);
            return newMergedHeader;
        }
    }
}

void AVLTreeSplit(struct node *Root,float x,struct node **R1,struct node** R2)
{
    if (Root == NULL)
    {
        *R1 = NULL;
        *R2 = NULL;
        return;
    }
    if (x <= Root->data)
    {
        AVLTreeSplit(Root->left,x,R1,R2);
        if (Root->right!=NULL)
        {
            Root->right->parent = NULL;
        }
        Switch = 0;
        struct node* R3 = AVLTreeMergeWithRoot(*R2,Root->right,Root);
        R3->parent = NULL;
        //(R1,R3)
        *R2 = R3;
        return;
    }
    else if (x > Root->data)
    {

        AVLTreeSplit(Root->right,x,R1,R2);
        if (Root->left!=NULL)
        {
            Root->left->parent = NULL;
        }
        //make switch to zero before calling R3
        Switch = 0;
        struct node* R3 = AVLTreeMergeWithRoot(Root->left,*R1,Root);

       
        R3->parent = NULL;
        //(R1,R3)
        *R1 = R3;
        return;
    }
}

