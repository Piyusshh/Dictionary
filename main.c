#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define ws 20

struct row_list_node
{
    char char_var;
    struct word_list_node *link_right;
    struct row_list_node *link_down;
};

struct word_list_node
{
    char word[ws];
    struct word_list_node *next;
};


struct MRU_node
{
    char char_var[ws];
    int freq;
    struct MRU_node *next;
};


void print_full_dictionary(struct row_list_node *row) // to print full dictionary with all rows and coloumns...
{
    struct row_list_node *r;
    r = row;
    
    while(r != NULL)
    {
        printf("%c :-",r->char_var);
        print_word_list(r);
        printf("\n");

        r = r->link_down;
    }
}

void print_word_list(struct row_list_node *row)   // to pprint the word list of every indexing node
{
    struct row_list_node *r;
    r = row;
    struct word_list_node *w;          // To capture the first node of word list which is of another type
    w = r->link_right;

    while(w != NULL)
    {
        printf("%s, ",w->word);
        w = w->next;
    }
}



void print_row_list(struct row_list_node *row)
{
    struct row_list_node *r;
    r = row;
    if (r == NULL)
    {
        printf("Your Index List is empty\n\n");
    }
    else
    {
        while(r != NULL)
        {
            printf("%c\n",r->char_var);
            r = r->link_down;
        }
        
    }
}

void create_row_list(struct row_list_node **row,char word[])
{
    char temp_var = 'a';
    char temp_var1 = 'A';
    struct row_list_node *r;
    r = *row;                                    // r will contain the value stored at address stored at row.
    int i;

    for(i=0; i<26; i++)
    {
        struct row_list_node *temp1;
        temp1 = (struct row_list_node*)malloc(sizeof(struct row_list_node));
        temp1->char_var = temp_var1;
        temp_var1++;
        temp1->link_right = NULL;
        temp1->link_down = NULL;
        if(*row == NULL)
        {
            r = temp1;
            *row = r;
        }
        else
        {
            while(r->link_down != NULL)
            {
                r = r->link_down;
            }
            r->link_down = temp1;
        }
        
    }

    i = 0;

    for(i=0; i<26; i++)
    {
        struct row_list_node *temp;
        temp = (struct row_list_node*)malloc(sizeof(struct row_list_node));
        temp->char_var = temp_var;
        temp_var++;                                // for increasing alphabets
        temp->link_right = NULL;
        temp->link_down = NULL;
        if(*row == NULL)                           //check wheather the list is empty 
        {
            r = temp;
            *row = r;
        }
        else
        {
            while(r->link_down != NULL)
            {
                r = r->link_down;
            }
            r->link_down = temp;
        }
        
    }

    
}


void insert_at_word_list(struct row_list_node **row, char str[])
{
    int length;
    int found = 0;
    struct row_list_node *r;
    r = *row;
    struct word_list_node *w,*temp;
    w = r->link_right;

    int i;
    
    if(r->link_right == NULL)
    {
        temp = (struct word_list_node*)malloc(sizeof(struct word_list_node));
        length = strlen(str);
        for(i=0; i<length; i++)
        {
            temp->word[i] = str[i];
        }
        temp->word[i] = '\0';
        temp->next = NULL;
        r->link_right = temp;
        *row = r;        
    }
    else                                       // reapeted waord wala part kaam nhi kar rha matlab else waala part me koi issue hai.
    {
        found = 0;
        temp = (struct word_list_node*)malloc(sizeof(struct word_list_node));
        length = strlen(str);
        for(i=0; i<length; i++)
        {
            temp->word[i] = str[i];
        }
        temp->word[i] = '\0';
        temp->next = NULL;

        while (w->next != NULL)
        {
            if (strcmp(w->word,str)==0)
            {
                found = 1;
                printf("%s -- Already Exists. \n\n",w->word);
            }
            w = w->next;
        }
        if(found == 0)
        {
            w->next = temp;
        }
        
        /* Error one
        //temp->next = r->link_right;   //basically insert at start.
        //r->link_right = temp;


        par isko isliye nhi kar sakte kyunki isse fir reapted words nhi catch kar paayenge during insertion.....
        */
    }
    
}


void create_Dict (struct row_list_node *row, char word[])
{
    struct row_list_node *r;
    r = row;

    while(word[0] != r->char_var)   // after this we will reach the [correct index]....
    {
        r = r->link_down;
    }
    /* r is the correct index in the list*/

    insert_at_word_list(&r,word);   // passing the word list and strng to be inserted  

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int length_of_word_list(struct word_list_node *word) //here the right link is passed.
{
    int count = 0;
    struct word_list_node *w;
    w = word;
    while(w != NULL)
    {
        count++; 
        w = w->next; 
    }
    return count;
}

struct word_list_node* swap(struct word_list_node* ptr1, struct word_list_node* ptr2) 
{ 
    struct word_list_node* tmp = ptr2->next; 
    ptr2->next = ptr1; 
    ptr1->next = tmp; 
    return ptr2; 
} 

void bubble_sort(struct word_list_node **head,int count)
{
    struct word_list_node** h; 
    int i, j, swapped; 
  
    for (i = 0; i <= count; i++) 
    { 
  
        h = head; 
        swapped = 0; 
  
        for (j = 0; j < count - i - 1; j++) 
        { 
  
            struct word_list_node* p1 = *h; 
            struct word_list_node* p2 = p1->next; 
  
            //if (p1->data > p2->data)
            if(strcmp(p1->word,p2->word)>0) 
            { 
                /* update the link after swapping */
                *h = swap(p1, p2); 
                swapped = 1; 
            } 
  
            h = &(*h)->next; 
        } 
  
        /* break if the loop ended without any swap */
        if (swapped == 0) 
            break; 
    } 
}



void bubble_sort_dictionary(struct row_list_node **row)
{
    int length = 0;
    struct row_list_node *r;
    r = *row;
    while (r != NULL)
    {
        length = length_of_word_list(r->link_right);
        bubble_sort(&r->link_right,length);
        r = r->link_down;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_punctuation(char str[])
{
    int i = 0;   // for old string
    int j = 0;   // for new string
    while(str[i] != '\0')
    {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='a' && str[i]<='z'))
        {
            str[j] = str[i];
            i++;
            j++;
        }
        else
        {
            i++;
        }
        
    }
    str[j] = '\0'; 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// function to find out middle element 
struct word_list_node* middle(struct word_list_node* start, struct word_list_node* last) 
{ 
    if (start == NULL) 
    {
        return NULL;
    }
         
    struct word_list_node* slow = start; 
    struct word_list_node* fast = start -> next; 
  
    while (fast != last) 
    { 
        fast = fast -> next; 
        if (fast != last) 
        { 
            slow = slow -> next; 
            fast = fast -> next; 
        } 
    } 
  
    return slow; 
}



int binarySearch(struct word_list_node *head, char search_str[]) 
{ 
    struct word_list_node *start = head; 
    struct word_list_node *last = NULL; 
    int retval = 0;
    int found = 0;
  
    while (last != start && found == 0)
    { 
        // Find middle 
        struct word_list_node *mid = middle(start, last); 
  
        // If middle is empty 
        if (strcmp(mid->word,search_str) != 0) 
        {
            retval = 0;   // not found
        }
             
        // If value is present at middle 
        if (strcmp(mid->word,search_str) == 0) 
        {
            retval =1;
            found = 1;
        }
  
        // If value is more than mid 
        else if (strcmp(mid->word,search_str) > 0) 
        {
            last = mid;
            
        } 
  
        // If the value is less than mid. 
        else
        {
            start = mid->next;
        } 
  
    }  
  
    // value not present 
    return retval; 
}




void search_in_dictionary_binary(struct row_list_node *row,char search_str[])
{
    struct row_list_node *r;
    r = row;

    int found;

    while(r->char_var != search_str[0])
    {
        r = r->link_down;
    }
    //now i have recahed the correct word location
    printf("The Index to be searched is %c\n",r->char_var);
    found = binarySearch(r->link_right,search_str);
    if (found == 1)
    {
        printf(" \"%s\" spellled correctly...........\n\n",search_str);
    }
    else if(found == 0)
    {
        printf(" \"%s\" spelled wrongly...........\n\n");
    }
    
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int linear_search(struct word_list_node *link_right, char search_str[])
{
    int found = 0;
    int retval;
    struct word_list_node *temp;
    temp = link_right;
    while((temp != NULL)&&(found == 0))
    {
        if(strcmp(temp->word,search_str) == 0)
        {
            found = 1;
            retval = 1;
        }
        else 
        {
            retval = 0;
        }
        temp = temp->next;

    }

    return retval;
}


void search_in_dictionary_linear(struct row_list_node *row,char search_str[])
{
    int found;
    struct row_list_node *r;
    r = row;

    while(r->char_var != search_str[0])
    {
        r = r->link_down;
    }
    /*now i have recahed the correct word location*/
    printf("The Index to be searched is %c\n",r->char_var);
    
    found = linear_search(r->link_right,search_str);
    if (found == 1)
    {
        printf(" \"%s\" spellled correctly\n\n",search_str);
    }
    else
    {
        printf(" \"%s\" spelled wrongly\n\n");
    }
    
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
int search_in_mru(struct MRU_node *mru, char str[])
{
    struct MRU_node *temp;
    temp = mru;
    int found = 0;
    int retval = 0;
    while(temp != NULL && (found == 0))
    {
        if(strcmp(temp->char_var,str) == 0)
        {
            found = 1;
            retval = 1;

        }
        temp = temp->next;
    }

    return retval;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char str[ws];
    char str1[ws];   // for reading from user input file.
    struct MRU_node *mru = NULL;
    char search_str[ws];
    struct row_list_node *row = NULL;
    char word[20];

    int choice;
    int flag = 1;

    FILE *fp;   // for reading from dictionary file
    FILE *fp1;  // for reading from user input
    FILE *fp2;  // for writing into new file
    FILE *fp3; // for reading from new file for searching.
    FILE *fp4;
    char ch1[20];
    fp = fopen("dictionary.txt","r");
    fp1 = fopen("input.txt","r");
    

    
    printf("****************************************************Welcome**************************************************************\n");
    while (flag == 1)
    {
        printf("Select any Option\n");
        printf("1. Create Dictionary Index list\n");
        printf("2. Print Dictionary Row list\n");
        printf("3. Print Full Dictionary\n");
        printf("4. Create Full Dictionary\n");
        printf("5. Sort The Full Dictionary\n");
        printf("6. Remove All punctuations from user input\n");
        printf("7. Direct From Dictionary:- Search for the spelled and misspleed words\n");
        printf("8. First from MRU:- Search for the speled and misspelled words\n");
        printf("10. Exit\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1: create_row_list(&row,word);           // passing the row_list and the string which needs to added to the dictionary... 
                    break;
            case 2: print_row_list(row);
                    break;

            case 3: print_full_dictionary(row);
                    break;

            case 4: while(fscanf(fp,"%s",str) != EOF)
                    {
                        //printf("enter the string\n");
                        //scanf("%s",str);
                        create_Dict (row,str);
                
                    }
                    
                    // fclose(fp);
                    
            case 5: bubble_sort_dictionary(&row);
                    break;

            case 6: fp2 = fopen("new_input.txt","w");  // after removing all the punctuations;
                    while(fscanf(fp1,"%s",str1) != EOF)
                    {
                        remove_punctuation(str1);
                        fprintf(fp2,"%s ",str1);
                    } 
                    fclose(fp2);
                    break;

            case 7: fp3 = fopen("new_input.txt","r");
                    while(fscanf(fp3,"%s",search_str) != EOF)
                    {
                        search_in_dictionary_linear(row,search_str);
                    }
                    fclose(fp3);
                    break;

            case 8: fp4 = fopen("new_input.txt","r");
                    while(fscanf(fp4,"%s",search_str) != EOF)
                    {
                        search_in_dictionary_binary(row,search_str);
                    }
                    fclose(fp4);
                    break;

            case 10: printf("______________________________________Thank You______________________________________________________\n\n");
                    flag = 0;
                    fclose(fp);
                    fclose(fp1);
                    break;
            default: printf("Please Enter A Valid Choice\n\n\n"); 
                     break;   
        }
    }


   /* 
    FILE *fp;
    fp = fopen("a.txt","r");

    if(fp == NULL)
    {
        printf("Dictionary File Failed to open\n");
    }
    else
    {
        printf("The File is now opened\n");

        while(fgets(word,ws,fp) != NULL);  // buffer, size of buffer, file pointer
        {
            printf("%d\n", word);

            //void create_dict(row,word);
        }
        
        fclose(fp);  //closing the file
        printf("The File has been Succesfully Closed\n");

        print_row_list(row);
    }
    */
   
   


   return 0;


    
}






/*
int main()
{
    int i=0;
    char ch;
    char str[20];
    FILE *fp;
    fp = fopen("a.txt","r");
    if(fp == NULL)
    {
        printf("failed to open\n");
    }
    else
    {
        ch = fgetc(fp);
        while(ch != NULL)
        {
            i = 0;
            while(ch != ' ')
            {
                
                str[i] = ch;
                i++;
                ch = fgetc(fp);
            }
            ch = fgetc(fp);

            printf("%s\n",str);
        }
    }

    fclose(fp);
    
}

*/