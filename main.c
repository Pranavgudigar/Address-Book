/* Name : Pranav C
   Date : 08/07/2025
   Description : Address Book.
                 The Address Book project is a C language-based console application that allows users to manage contact information such as names, mobile numbers, and email addresses. 
                 It provides full operations — Add, List, Search, Delete, Edit and Save — on contact entries.
                 This project demonstrates the use of structures, file handling, string manipulation, and input validation in C. 
                 The contact data is stored persistently in a file, allowing the user to retain data even after the program exits. */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int match[100],match_count=0;   //Global variables are used during search operations to store the indices of matched contacts.
//Structure  definition
struct Contact_data   // Structure to store contact data
{
    char name[25];
    char mobile_number[25];
    char email_id[25];
};
// Structure to hold entire address book
struct Addressbook
{
    struct Contact_data contact_list[100];
    int contact_count;
};
// Function to validate if email has only lowercase letters and valid symbols

int islwrcseandvalid(char *email_id)
{  
    int len=strlen(email_id);     //length of email id
    int i=0;
    if(email_id[i] >= 'a'&& email_id[i] <= 'z')  //Checking 1st character of email id is small letter or not
    {
        i++;
        while(email_id[i]!='\0')
        {
            if(email_id[i] >= '0' && email_id[i] <= '9' || email_id[i] == '.' || email_id[i] == '@' || email_id[i] >= 'a' || email_id[i] <= 'z')
            {
                i++;
            }
            
        }
    }
    if(len==i)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// Function to check if email ends with ".com"
int endswthgmailcom(char *email_id)
{
    int i=0;
    int len1=strlen(email_id);   //length of email id
    int m=len1-1;    
    char com[]="moc.";           
    int len=strlen(com);         //length of .com
    while(com[i]!='\0')
    {
        if(email_id[m]==com[i])
        {
            m--;
        }
        i++;
    }
    if(i==len)
    {
	    return 1;
    } 
    else 
    {
        return 0;
    }
}
// Function to check exactly one '@' symbol in email
int attheratemail(char *email_id)
{
    int i=0; 
    int temp=0;
    while(email_id[i]!='\0')
    {
        if(email_id[i] =='.'&& i>0 && email_id[i-1] == '@')    //checking the '@' before and after 1 character be there 
        {
            return 0;
        }
        else if(email_id[i]=='@')
        {
            temp=temp+1; 
        }
        i++;
    }
    if(temp==1)
    {
        return 1;  // Return true if exactly one '@'

    }
    else
    {
        return 0;
    }
}
// Function to check if email contains only one dot '.'
int dotemail(char *email_id)
{
    int i=0;
    int temp=0;
    while(email_id[i]!='\0')
    {
        if(email_id[i]=='.')
        {
            temp=temp+1;
        }
        i++;
    }
    if(temp==1)
    {
        return 1;   // Return true if exactly one '.'

    }
    else
    {
        return 0;
    }
}
//Function to check number is valid or not 
int valid_mobile_number(char *mobile_number)
{
    int len=strlen(mobile_number);
    if(len==10)
    {
        for(int i=0; mobile_number[i] != '\0';i++)
        {
            if(!isdigit(mobile_number[i]))
            {
                return 0;    // Return false if not a digit
            }
        }
        return 1;
    }
    return 0;
}
//Function to check the number is unique or not
int is_mobile_unique(struct Addressbook *var, const char *mobile) 
{
    for (int i = 0; i < var->contact_count; i++) 
    {
        if (strcmp(var->contact_list[i].mobile_number, mobile) == 0) 
        {
            return 0; // Not unique
        }
    }
    return 1; // Unique
}
// Function to add new contact to address book
void add_contact(struct Addressbook *var)
{
    struct Contact_data new_data;
    char name[25];
    char mobile_number[25];
    char email_id[25];
    printf("Enter the name : ");
    scanf(" %[^\n]",new_data.name);   // Read full line including spaces
    while (1) 
    {
        printf("Enter mobile number: ");
        scanf("%s", new_data.mobile_number);
 
        if (!valid_mobile_number(new_data.mobile_number))
        {
            printf("Invalid mobile number, should be 10 digits.\n"); 
        } 
        else if(is_mobile_unique(var, new_data.mobile_number))  // Unique number, proceed
        {
            break;
        }
        else
        {
            printf("Mobile number already exists! Enter a different number.\n");
        }
    }
    printf("Enter the email id : ");   
    scanf(" %[^\n]",new_data.email_id);  // Read email ID

    while(!islwrcseandvalid(new_data.email_id) || !endswthgmailcom(new_data.email_id) || !attheratemail(new_data.email_id) || !dotemail(new_data.email_id))
    {
        printf("invalid repeat again\n");
        scanf("%[^\n]",new_data.email_id);
        getchar();
    }
    var->contact_list[var->contact_count]=new_data;  // Store new contact
    var->contact_count++;  //Increase count
    printf("Contact added successfully.\n");
}
// Function to display all contacts
void list_contact(struct Addressbook *var)
{
    for(int i=0; i<var->contact_count; i++)
    {
        const char *strline = "---------------------------------------------------------------------";
        printf("%s\n", strline);
        printf("contact %d : \n", i+1);
        printf("Name : %s\n", var->contact_list[i].name);
        printf("Mobile Number : %s\n", var->contact_list[i].mobile_number);
        printf("Email ID : %s\n", var->contact_list[i].email_id);
        printf("%s\n", strline);
    }
    return;
}
void search_name();
void search_mobile_number();
void search_email_id();
// Function to search contact by name, number, or email
int search_contact(struct Addressbook *var)
{
    char search[20];
    int choice;
    int found=0;
    printf("\n1.Search by name\n");
    printf("2.Search by mobile number\n");
    printf("3.Search by email id\n");
    printf("Choose the choice : ");
    scanf("%d", &choice);
    switch(choice) 
    {
        case 1:
                printf("Enter the name : ");
                scanf(" %[^\n]", search);
                for(int i=0; i<var->contact_count;i++)
                {
                    if(strcmp(var->contact_list[i].name,search)==0)
                    {
                        match[match_count++]=i;
                        printf("%d %s %s %s",match_count,var->contact_list[i].name,var->contact_list[i].mobile_number,var->contact_list[i].email_id);
                        printf(" contact found\n");
                        found=1;
                        
                    }
                }
                if(!found)
                {
                    printf("contact is not found\n");
                }
                break;
        case 2:
                printf("Enter the  mobile number : ");
                scanf(" %[^\n]",search);
                for(int i=0; i<var->contact_count;i++)
                {
                    if(strcmp(var->contact_list[i].mobile_number,search)==0)
                    {
                        match[match_count++]=i;
                        printf("%d %s %s %s",match_count,var->contact_list[i].name,var->contact_list[i].mobile_number,var->contact_list[i].email_id);
                        printf(" contact found\n");
                        found=1;
                    }
                }
                if(!found)
                {
                    printf("contact is not found\n");
                }
                break;
        case 3:
                printf("Enter the email id : ");
                scanf(" %[^\n]",search);
                for(int i=0; i<var->contact_count;i++)
                {
                    if(strcmp(var->contact_list[i].email_id,search)==0)
                    {
                        match[match_count++]=i;
                        printf("%d %s %s %s",match_count,var->contact_list[i].name,var->contact_list[i].mobile_number,var->contact_list[i].email_id);
                        printf(" contact found\n");
                        found=1;
                    }
                }
                if(!found)
                {
                    printf("contact is not found\n");
                }
                break;
        default:
                printf("Invalid input");
                break;
    }
}
// Function to delete contact after search
void delete_contact(struct Addressbook *var)
{
    int delete;
    search_contact(var);  // First search contact
    printf("Enter number to delete : ");
    scanf("%d", &delete);
    if (delete < 1 || delete > match_count) 
    {
        printf("Delete not happen.\n");
        return;
    }
    int delposition = match[delete - 1];
    for (int k = delposition; k < var->contact_count - 1; k++)
    {
        var->contact_list[k] = var->contact_list[k + 1];  // Shift contacts
    }
    var->contact_count--;  // Reduce count
    printf("Deleted the serial number %d Contact successfully.\n", delete);
}
// Function to edit a contact
void edit_contact(struct Addressbook *var)
{
    search_contact(var);  // First search
    int select,serial_num;
    printf("Select the contact serial number to edit : ");
    scanf("%d", &select);
    if(select < 1 || select > match_count)
    {
        printf("Edit not happen.\n");
        return;
    }
    serial_num = match[select - 1];
    printf("What do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Mobile number\n");
    printf("3. Email ID\n");
    char edit[20];
    int choice;
    printf("Choose the choice : ");
    scanf("%d", &choice);  // Read the choice from user
    switch(choice)
    {
        case 1:
                printf("Enter the new number : ");
                scanf(" %[^\n]", edit);
                strcpy(var->contact_list[serial_num].name,edit); // Edit name 
                printf("Successfully edited the contact\n");
                break;
             
        case 2:
                printf("Enter the new mobile number : ");
                scanf(" %[^\n]", edit);
                while(!valid_mobile_number(edit))
                {
                    printf("Invalid mobile number. Enter again : ");
                    scanf(" %[^\n]", edit);
                }
                strcpy(var->contact_list[serial_num].mobile_number,edit);  // Edit mobile number
                printf("Successfully edited the contact\n");
                break;
                
        case 3:
                printf("Enter the new email id : ");
                scanf(" %[^\n]", edit);
                while(!islwrcseandvalid(edit) || !endswthgmailcom(edit) || !attheratemail(edit) || !dotemail(edit))
                {
                    printf("Invalid email id. Enter again : ");
                    scanf(" %[^\n]", edit);
                }
                strcpy(var->contact_list[serial_num].email_id,edit);  // Edit email id
                printf("Successfully edited the contact\n");
                break;               
    }
}
// Function to save all contacts to file
void save_contact(struct Addressbook *var)
{
    FILE *fp;
    fp=fopen("contacts.csv","w");  // Open file for writing
    if(fp==NULL)
    {
        printf("File not opened\n");
    }
    fprintf(fp,"%d\n",var->contact_count);  // Write contact count

    for(int i=0;i<var->contact_count;i++)
    {
        fprintf(fp,"%s,%s,%s\n",var->contact_list[i].name,var->contact_list[i].mobile_number,var->contact_list[i].email_id);  // Write each contact
    }
    fclose(fp);  // Close file
    printf("Contact saved successfully (^_^)\n");
}
// Function to load contacts from file
void load(struct Addressbook *var)
{
    FILE *fp;
    fp=fopen("contacts.csv","r");  // Open file to read
    if(fp==NULL)
    {
        printf("File not opened\n");
        return;
    }
    fscanf(fp,"%d\n",&var->contact_count);  // Read contact count
    for(int i=0;i<var->contact_count;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",var->contact_list[i].name,var->contact_list[i].mobile_number,var->contact_list[i].email_id);  // Read each contact
    }
    fclose(fp);  // Close file
}
void load();
void add_contact();
void list_contact();
int search_contact();
void delete_contact();
void edit_contact();
void save_contact();
// Main function with menu-driven interface
int main()
{
    struct Addressbook var;
    load(&var);
    int choice;
    do
    {
        printf("1.Add contact\n");
        printf("2.List contact\n");
        printf("3.Search contact\n");
        printf("4.Delete contact\n");
        printf("5.Edit contact\n");
        printf("6.Save contact\n");
        printf("7.Exit\n");
        printf("Choose the choice : ");
        scanf("%d", &choice);                // Read the choice from the user
    
        switch(choice)
        {
            case 1:
                    printf("Add contact\n");  // Add contact
                    add_contact(&var);
                    break;
            case 2:
                    printf("List contact\n");  // List contacts
	                list_contact(&var);
	                break;
	        case 3:
                    printf("Search contact\n");  // Search contact
	                search_contact(&var);
		            break;	       
		    case 4: 
                    printf("Delate contact\n");  // Delete contact
	                delete_contact(&var);
	                break;
	        case 5: 
                    printf("Edit contact\n");  // Edit contact
	                edit_contact(&var);
	                break;
	        case 6: 
                    printf("Save contact\n");  // Save contact to file
	                save_contact(&var);
		            break;
	        case 7:
                    printf("Exit");
		            break;
            default:
                    printf("Invalid input");
                    return 0;
        }
    }while (choice!=7);  // Repeat until exit
}