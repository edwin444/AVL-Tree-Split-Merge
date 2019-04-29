#include<stdio.h>
#include <string.h> 
#include "avlTrees.h"
#include <time.h>


void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
int maxDepth(struct node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left); 
       int rDepth = maxDepth(node->right); 
  
       /* use the larger one */
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}  
void randomize (int arr[], int n) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap(&arr[i], &arr[j]); 
    } 
} 
int main()
{
    while (1)
    {
        printf("\n\t\t---------------MENU-----------------\n");
        printf("\n\t\tSplit AVL tree -->1");
        printf("\n\t\tMerge ABL trees-->2");
        printf("\n\t\tWrite Files-->3");
        printf("\n\t\tExit-->4");
        printf("\n\n");

        int ch;
        printf("\nEnter the choice: ");
        scanf("%d",&ch);

        if (ch==1)
        {
            //innitialization code
            int x;
            char c;
            float key;
            char arr1[50];
            struct node* header = NULL;

            printf("Enter the file name: ");
            scanf("%s",arr1);


            FILE *fp; 
            fp = fopen(arr1, "r"); 
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n") ; 
                while(fscanf(fp, "%d,%c", &x, &c)!=EOF) 
                { 
                    //printf("%d\n",x);
                    
                    header = insert(header,x);
                } 
                
                
                // Closing the file using fclose() 
                fclose(fp) ; 
                
                printf("Data successfully read from file\n"); 
                printf("Enter the value of key to be used for splitting: ") ;
                scanf("%f",&key); 


                //innitializing split procedure
                struct node ** arr = (struct node **)malloc(sizeof(struct node *));
                for (int i=0;i<2;i++)
                {
                    arr[i]=(struct node*)malloc(sizeof(struct node));
                }


        

                AVLTreeSplit(header,key,&arr[0],&arr[1]);


                printf("\n-------------------\n");
                printf("\nThe first Tree\n");
                printf("\n-------------------\n");
                print2DUtil(arr[0],0);
                printf("\n-------------------\n");
                printf("\nThe second Tree\n");
                printf("\n-------------------\n");
                print2DUtil(arr[1],0);
                printf("\n-------------------\n");

            

                int a2[10000];
                p=0;
                inorder(arr[0],a2);

                fp = fopen("outputTreeT.txt", "a"); 
                int i;
                for (i=0;i<key;i++)
                {
                    //printf("%d",a1[i]);
                    fprintf(fp, "%d ", a2[i]);
                }
                fclose(fp);



                int a3[10000];
                p=0;
                inorder(arr[1],a3);

                fp = fopen("outputTreeU.txt", "a"); 
                for (i=0;i<10000-key;i++)
                {
                    //printf("%d",a1[i]);
                    fprintf(fp, "%d ", a3[i]);
                }
                fclose(fp);
            }
        }
        else if(ch==2)
        {
            //innitialization code
            struct node* header = NULL;
            struct node* header1 = NULL;

            //file read innitializtion 
            int x;
            char c;
            float key;
            char arr1[50];
            char arr2[50];

            printf("\nEnter the file name storing tree T: ");
            scanf("%s",arr1);
            
            //file for Tree T
            FILE *fp; 
            fp = fopen(arr1, "r"); 
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n") ; 
                while(fscanf(fp, "%d,%c", &x, &c)!=EOF) 
                { 

                    header = insert(header,x);
                } 
                // Closing the file using fclose() 
                fclose(fp); 
                printf("\nData successfully read from file\n"); 
            }


            printf("Height of the merged Trees: %d\n",heightHelper(header)-1);

            //file for Tree U

            printf("\nEnter the file name storing tree T: ");
            scanf("%s",arr2);

            fp = fopen(arr2, "r"); 
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n") ; 
                while(fscanf(fp, "%d,%c", &x, &c)!=EOF) 
                { 
                    //printf("%d\n",x);
                    
                    header1 = insert(header1,x);
                } 
                
                
                // Closing the file using fclose() 
                fclose(fp) ; 
                
                printf("\nData successfully read from file\n"); 
            }
            
            printf("Height of the merged Trees: %d\n",heightHelper(header1)-1);
            //initializing merge procedure
            struct node* newHeader = AVLTreeMerge(header,header1);

            printf("\n-------------------\n");
            printf("\nThe Merged Tree\n");
            printf("\n-------------------\n");
            print2DUtil(newHeader,0);
            printf("\n");
            
            int a1[10000];

            p = 0;
            inorder(newHeader,a1);
            
            fp = fopen("outputMerged.txt", "a"); 
            int i;
            for (i=0;i<10000;i++)
            {
                //printf("%d",a1[i]);
                fprintf(fp, "%d ", a1[i]);
            }
            fclose(fp);

            //newHeader is the new Header
            printf("Height of the Tree T: %d\n",maxDepth(header)-1);
            printf("Height of the Tree U: %d\n",maxDepth(header1)-1);
            printf("Height of the merged Trees: %d\n",maxDepth(newHeader)-1);


        
        }
        else if(ch==3)
        {
            //writing split.txt
            FILE *fp; 
            fp = fopen("split.txt", "w"); 
        
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n"); 
                int i; 
                int arr[10000];
                for (i=0;i<10000;i++)
                {
                    arr[i] = i+1;
                }
                randomize(arr,10000);

                for (int i=0;i<10000;i++)
                {
                    fprintf(fp, "%d ", arr[i]);
                }

                printf("The file is now written with 10000 values.\n");
                fclose(fp) ;
            }

            fp = fopen("treeT.txt", "w"); 
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n");
                int i; 
                int arr[5000];
                for (i=0;i<5000;i++)
                {
                    arr[i] = i+1;
                }
                randomize(arr,5000);

                for (int i=0;i<5000;i++)
                {
                    fprintf(fp, "%d ", arr[i]);
                }
                printf("The file is now written with 5000 values.\n");
                fclose(fp) ;
            }

            fp = fopen("treeU.txt", "w"); 
            if ( fp == NULL ) 
            { 
                printf( "Given file name does not exist - failed to open." ); 
            } 
            else
            { 
                printf("The file is now opened.\n");
                int i; 
                int arr[5000];
                for (i=0;i<5000;i++)
                {
                    arr[i] = i+10000;
                }
                randomize(arr,5000);

                for (int i=0;i<5000;i++)
                {
                    fprintf(fp, "%d ", arr[i]);
                }
                printf("The file is now written with 5000 values.\n");
                fclose(fp) ;
            }


        }
        else
        {
            printf("\nExiting the loop...\n");
            exit(0);
        }
    }

    return 0;         

}