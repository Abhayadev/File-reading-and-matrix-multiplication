#include <stdio.h> 
#include <stdlib.h> 


struct node//Defining data type for the nodes that stores ech integer of matrix
{
    int val;
    struct node *next;
    struct node *cross;
};

struct node** fill_matrix(FILE * p)//Function to create the matrix using linkedlist when input file pointer is given 
{   
   
    char c;
    int val;
    fscanf(p,"%d",&val);
    struct node * temp;
    struct node * new_node = (struct node *)malloc(sizeof(struct node));
    new_node->val=val;
    struct node* row_pointer =new_node;
    struct node* temp_pointer;
    struct node** matrix_pointer = (struct node **)malloc(sizeof(struct node*));
    *matrix_pointer=new_node;  
    temp=new_node;
    while(free)//Loop to make the nodes successively
    {    
        if( fscanf(p,"%c",&c)==EOF)
            break; 

        if ( c == ',')
        {    
            fscanf(p,"%d",&val); 
            struct node* new_node1 = (struct node *)malloc(sizeof(struct node));
            new_node1->val = val;
            temp->next=new_node1;
            temp=new_node1;
            if(temp_pointer!=NULL)
            {
                temp_pointer->cross=new_node1;
                temp_pointer=temp_pointer->next;
            }    
        } 
        else if( c == ';')
        {   
            fscanf(p,"%d",&val);
            struct node* new_node2 = (struct node *)malloc(sizeof(struct node));
            new_node2->val = val;
            temp_pointer=row_pointer;
            temp_pointer->cross=new_node2;
            row_pointer=new_node2;
            temp_pointer=temp_pointer->next;
            temp=new_node2;

        }        
    }
    return matrix_pointer; 
}  


void print_list(struct node **head,FILE*p)//Function to print the matrix when the head
                                          // pointer to the matrix is given as input
{   
    struct node* temp1 = *head;
    struct node* temp2 = *head;
    while(temp2!=NULL)
    {
        if(temp1!=NULL)
        {
            fprintf(p,"%d\t", temp1->val);
            temp1 = temp1->next;
        }
        else
        {
            fprintf(p,"\n");
            temp2=temp2->cross;
            if(temp2!=NULL)
            {       
                temp1=temp2;
                fprintf(p,"%d\t", temp1->val);
                temp1 = temp1->next;
            }    
        }
    }    

}

int validity(struct node**head,FILE*p)//Function to check the validity of the matrix
{
    int i=0;
    int j=0;
    int k=0;
    struct node*temp1=*head;
    struct node*tempx=*head;
    struct node*temp2=(*head)->cross;
    while(tempx->cross!=NULL)
    {  
        if(tempx->cross!=NULL)
        {
            if(temp1!=NULL)
            { 
                temp1 = temp1->next;
                i++;
            }
            else if(temp1==NULL)
            {
                temp1=tempx->cross;
                tempx=temp1;
            };
        }
      if(temp2!=NULL)
      { 
        temp2 = temp2->next;
        j++;
      }
      else if(temp2==NULL)
      {
        temp2=tempx->cross;

      };
   
      if(j!=i)//Checks the number of elements in consecutive rows are not equal 
      {
          fprintf(p,"\n");
          fprintf(p,"The matrix is invalid\n");
          break;
      }  
    }
    if(j==i)
    {
        fprintf(p,"\n");
        fprintf(p,"Matrix is valid\n");
    }
    //k = i%j;
    return k;   
}

void multiply(struct node**head1,struct node**head2,FILE*p)//Function to multiply two matrices
{   
    int i;
    int j=0;
    struct node*temp1=*head1;
    struct node*temp2=*head2;
    struct node*tempx1=*head1;
    struct node*tempx2=*head2;
    struct node*tempxs=*head2;
    while(tempx1!=NULL)
    {   
        if(temp1!=NULL && temp2!=NULL)
        {
            i=(temp1->val)*(temp2->val);
            j=i+j;//Adds up after each multiplication between elements 
            temp1=temp1->next;
            temp2=temp2->cross;
        }
      
        else if(tempx2==NULL)
        {
            tempx2=tempxs;
            tempx1=tempx1->cross;
            temp2=tempx2;
            temp1=tempx1;
             fprintf(p,"\n");
             i=0;
             j=0;
        }
        else if( temp2==NULL)
        {  
           fprintf(p,"%d\t",j);
           temp1=tempx1;
           temp2=tempx2->next; 
           tempx2=tempx2->next;
           i=0;
           j=0;
        }

    }
    
}

 void check_square(struct node**head,FILE*p)//Function to check if the matrix is a square matrix
 {
     struct node*temp=*head;
     do
     {   
         if(temp->next!=NULL)//Pointer temp traverses by moving horizontally and vertically 
                             //through nodes 
         {
            temp=temp->next;
         }
         if(temp->cross!=NULL)
         {
            temp=temp->cross;
         }
     }while(temp->cross!=NULL && temp->next!=NULL );

    if(temp->cross==NULL && temp->next==NULL )//If temp reaches the last element of the last row we can conclude 
                                              //that the matrix is a square matrix
    {
        fprintf(p,"The matrix is a square matrix\n");
    }
    else
    {
        fprintf(p,"The matrix is not a square matrix\n");
    }

 }
   void main() 
   {
    char c; 
    int  a;
    int  b;
    FILE *ptr1 = fopen("input_1.txt", "r"); 
    FILE *ptr2 = fopen("input_2.txt", "r"); 
    FILE *ptr3 = fopen("output.txt", "w"); 
    struct node** head1 = fill_matrix(ptr1);
    struct node** head2 = fill_matrix(ptr2);
    a = validity(head1,ptr3);
    check_square(head1,ptr3);
    printf("\n");
    fprintf(ptr3,"\n");
    if(a==0)//a=0 if the first matrix is valid
    {
        print_list(head1,ptr3);
    }
    b = validity(head2,ptr3);
    check_square(head2,ptr3);
    fprintf(ptr3,"\n");

    if(b==0)//b=0 if the second matrix is valid
    {
        print_list(head2,ptr3);
    }
    fprintf(ptr3,"\n");
    fprintf(ptr3,"The matrix obtained after the multiplication of above two matrices are\n");
    fprintf(ptr3,"\n");
    multiply(head1,head2,ptr3);
    printf("\n");
    fprintf(ptr3,"\n");
    fclose(ptr1); 
    fclose(ptr2); 
   }