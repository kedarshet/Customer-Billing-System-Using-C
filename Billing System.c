//                                              IMPORTING REQUIRED FILES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<conio.h>
#include<windows.h>//                   AS IT IS RUNNED IN WINDOWS 
//                                              ALL FUNCTIONS
void create_customer();
void display();
void edit_customer();
void create_item();
void update_item();
int bill(int k);
int customer_exists();
int exist(char new[11]);
char existcb(char new[11]);
int existi(char new[11]);
int indexOf(FILE *fptr, char *new,int *line, int *col);
int indexOf2(FILE *fptr, const char *new, int *line, int *col);
int indexOfi(FILE *fptr,char *n,int *line, int *col);
int indexOfi2(FILE *fptr, char *newi,int *line, int *col);
int indexOfi4(FILE *fptr,char *i,int *line, int *col);
int indexOf2b(FILE *fptr, const char *NEW, int *line, int *col);
int existi2(char i[8],int k);
void item_name(int line);
void item_quantity(int line);
void item_price(int line);
//                                          DEFINING VARIABLES ANG STRUCTURES                                            
#define MAX 256
#define BUFFER_SIZE 1000
struct custo
{
	char mobileno[51];
	char customername[50];
}custo;
struct item
{
	char productno[8];
	char productname[10];
	int quantity;
	float price;
}item;
struct bll
{
	char no[8];
	char name[10];
	int quan;
	float pric;
}bll[1000];

int main()
{        //                                            INTRO / LOGIN  PAGE
	char ch,password[10],new[11],q[10]="kedars";
	int s,y=0,w=1,i,n,o=0;int k=0;
    system("cls");
	w:printf("\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("--------------------------------------------    WELCOME   -------------------------------------------------------------\n");
    printf("\t---------------------------\n");
    printf("\t|Please Select an Option: |\n");
    printf("\t---------------------------\n");
	printf("\t01. LOGIN\n");
	printf("\t02. EXIT\n\n");
	printf("\tPlease Enter an Option: ");
	scanf("%d",&s);
    switch(s)
	{           //                                     LOGIN WITH PASSWORD
    //                                                  PASSWORD: kedars
	        case 1: printf("\tEnter Password:\t");
            for(i=0;i<6;i++)
            {
                ch = getch();
                password[i] = ch;
                ch = '*' ;
                printf("%c",ch);
            }
            password[i]='\0';
            if(strcmp(password,q))
            {
                printf("\n\t");
                printf("Wrong Password Please Try Again");
                printf("\n\n");
                goto w;
            }
            system("cls");
            printf("\n\n\t"); 
            for(int ii=0; ii<80; ii++)
            {
                printf("\xdb");
            }
            printf("\n\t LOADING PLEASE WAIT... \n");
            for(int ii=0; ii<3; ii++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\n\t Enter Any Key To Proceed");
            fflush(stdin);
            getch();
            system("cls");
            printf("\n\t");
            printf("Access Granted\n\n\n");
            q:system("cls");
            //                                               MAIN MENU
            printf("\n\t----------------------------\n");
            printf("\tPlease Select an Option: \n");
            printf("\t----------------------------\n");
		    printf("\t01.ADMIN\n");
		    printf("\t02.BILLING\n");
		    printf("\t03.EXIT\n");
		    printf("\tPlease Enter an Option: ");
		    scanf("%d",&y);
		    switch(y)
		        {  //                                       ADMIN MENU 
                  case 1:
                    system("cls");
                    printf("\t----------------------------\n");
                    printf("\tPlease Select an Option: \n");
                    printf("\t----------------------------\n");
    		        printf("\t01.CREATE CUSTOMER\n");
	    	        printf("\t02.DISPLAY CUSTOMER\n");
		            printf("\t03.CREATE/EDIT/REMOVE ITEM\n");
		            printf("\t04.DISPLAY ITEM\n");
		            printf("\t05.MAIN MENU\n\n");
		            printf("\tPlease Enter an Option: ");
		            scanf("%d",&o);
		            switch(o)
		            {
        		        case 1:create_customer();
        			        goto q;
  			            case 2:edit_customer();
  			                goto q;
                        case 3:create_item();
        			        goto q;
                        case 4:display();
                            goto q;     
                        case 5: goto q;
                        default : printf("\tError\n");
				            goto q;
        		} 
                //                                BILLING SECTION
            case 2: system("cls");
                    bill(k);
                    printf("\n\t Enter Any Key To Proceed");
                    fflush(stdin);
                    getch();
                    goto q;
                    break;
               //                                    EXIT 
            case 3: system("cls");
                    printf("\n\tExiting...\n");
                    break;
            default : 
                    goto w;  
	        }

    case 2 : system("cls");
             printf("\n\tExiting...\n");
             break;
    default : 
            goto w;    
    }
}

void create_customer()
{     //                                        CREATE CUSTOMER DETAILS
	int i=0;int n=0;char new[11];
	FILE *fp;
	fp=fopen("CUSTOMER_DETAILS.txt","a");
	if(fp==NULL)
	{
		printf("Error\n");
	}
	else {
	    printf("\n\tEnter Mobile Number: ");
	    scanf("%s",custo.mobileno); 
        strcpy(new,custo.mobileno);
        switch(exist(new))
        {
	    case 1 :printf("\tEnter Customer Name: ");
	            scanf("%s",custo.customername);
	            printf("\n");
    	        fprintf(fp,"\n%s|%s",custo.mobileno,custo.customername);
                printf("\tCustomer Record is Created\n\n");
                    break;           
        case 2:printf("\tCustomer Already Exists\n");
                break; 
        default : printf("\tError\n");
                break;               
        }
    }
	fclose(fp);
	
}
int exist(char new[11])
{//                                         CHECKS FOR CUSTOMER EXISTANCE
    FILE *fptr;
    int line, col;
    fptr = fopen("CUSTOMER_DETAILS.txt", "r");
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("SORRY for the Inconvenience\n");
        exit(EXIT_FAILURE);
    }
    indexOf(fptr, new, &line, &col);
    fclose(fptr);
    if (line == -1){
        return 1;}
    else{
        return 2;}
        
}
int indexOf(FILE *fptr, char *new,int *line, int *col)
{
    char str[1000];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str,1000, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, new);
        if (pos != NULL){
            *col = (pos - str);
            break;
        }
    }
    if (*col == -1){
        *line = -1;}
    return *col;
}
void edit_customer(){
    //                                              DISPLAYS CUSTOMER DETAILS
    int i=0;int n=0;char new[11];int yn=0,yna=0;
	FILE *fp;
	fp=fopen("CUSTOMER_DETAILS.txt","a");
	if(fp==NULL)
	{
		printf("Error\n");
	}
	else {
	    aa: printf("\n\tEnter Mobile Number: ");
	    scanf("%s",custo.mobileno); 
        strcpy(new,custo.mobileno);
        switch(exist(new)){
	    case 1 : printf("\tNo account exist.\n\tDo you want to create new??\n");
               printf("\t----------------------------\n");
                printf("\tPlease Select an Option: \n");
                printf("\t----------------------------\n");
                printf("\t1.YES\n");
                printf("\t2.NO\n");
                printf("\tPlease Enter an Option: ");
                scanf("%d",&yn);
                switch (yn)
                {
                case 1: create_customer();
                    break;
                
                default:
                    break;
                }break;
        case 2: printf("\tDisplaying Details\n\n");
                printf("\t----------------------------\n");
                printf("\tMobile__No|Customer___Name\n");
                customer_exists(new);    
                printf("\n\t Enter Any Key To Proceed");
                fflush(stdin);
                getch();
                system("cls");
                break;
        default:
                break;
                     
    }}
	fclose(fp);
	
}
int customer_exists(char new[11])
{ //                                      CHECKING FOR CUSTOMER IN FILE
    FILE *fptr;
    int line, col;
    fptr = fopen("CUSTOMER_DETAILS.txt", "r");
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }
    indexOf2(fptr, new, &line, &col);
    fclose(fptr);
    FILE *file = fopen("CUSTOMER_DETAILS.txt", "r");
    int count = 0;
    if ( file != NULL )
    {   
        char lne[256];
        while (fgets(lne, sizeof lne, file) != NULL)
        {   
            if (count == line)
            {
                printf("\t%s\n", lne);
                printf("\t----------------------------\n\n");
                fclose(file);
            }   
            else{
                count++;}   
        }   
        fclose(file);
    }   
}

int indexOf2(FILE *fptr, const char *NEW, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, NEW);
        if (pos != NULL)
        {
            *col = (pos - str);
            break;
        }
    }
    if (*col == -1)
        *line = -1;
    return *col;
}

void create_item()
{	//                                      CREATES ITEM
    int in=0,ynn=0;char newi[8];
	FILE *fp,*fp2,*fp3,*fp4;
	fp=fopen("INUM.txt","a");
	if(fp==NULL)
	{
		printf("Error\n");
	}else{
    fclose(fp);
	printf("\n");
	printf("\tEnter Product Code(7-digit): ");
	scanf("%s",item.productno);
    strcpy(newi,item.productno);
    switch (existi(newi))
    {
    case 1 :fp2=fopen("INAME.txt","a");
	    fp=fopen("INUM.txt","a");
	    fp3=fopen("IQ.txt","a");
	    fp4=fopen("IP.txt","a");
        printf("\tEnter Product Name: ");
	    scanf("%s",item.productname);
	    printf("\tEnter Quantity: ");
	    scanf("%d",&item.quantity);
	    printf("\tEnter Price: ");
	    scanf("%f",&item.price);
	    printf("\n");
	    fprintf(fp,"%s\n",item.productno);
	    fprintf(fp2,"%s\n",item.productname);
	    fprintf(fp3,"%d\n",item.quantity);
	    fprintf(fp4,"%.2f\n",item.price);
    	printf("\tRecord is Created\n\n");
        fclose(fp);
        fclose(fp2);
	    fclose(fp3);
	    fclose(fp4);
        break;
    case 2 :  printf("\tITEM EXIST,DO YOU WANT TO UPDATE THE STOCK:\n");
              printf("\t----------------------------\n");
              printf("\t1.YES\n");  
              printf("\t2.NO\n");
              printf("\tENTER your Choice: ");
              scanf("%d",&ynn);
              switch (ynn)
              {
              case 1:
                    update_item(newi);  
                    printf("\tRecord is Updated\n\n");
                  break;
              case 2:break;
              default:
                  break;
              }
         break; 
    default:
        break;}}
}
int existi(char newi[8])
{//                                                  CHECK EXISTENCE OF ITEM
    FILE *fptr;
    int line, col;
    fptr = fopen("INUM.txt", "r");
    if (fptr == NULL)
    {
        printf("Unable to process.\n");
        printf("SORRY for the Inconvenience\n");
        exit(EXIT_FAILURE);
    }
    indexOfi(fptr, newi, &line, &col);
    fclose(fptr);
    if (line==-1){
        return 1;}
    else{
        return 2;}
        
}
int indexOfi(FILE *fptr,char *newi,int *line, int *col)
{
    char str[1000];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str,1000, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, newi);
        if (pos != NULL){
            *col = (pos - str);
            break;
        }
    }
    if (*col == -1){
        *line = -1;}
    return *col;
}
void update_item(char newi[8])
{   //                                          UPDATING ITEM DETAILS
    FILE *fptr,*fptr2,*fptr3,*fptr4;    
    int line, col,y3;
    fptr=fopen("INUM.txt","r");
	if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("SORRY for the Inconvenience\n");
        exit(EXIT_FAILURE);
    }
    indexOfi2(fptr, newi, &line, &col);
    fclose(fptr);
    line=line+1;
    printf("\t----------------------------\n");
    printf("\tPLEASE SELECT THE TYPE YOU WANT TO UPDATE:\n");
    printf("\t----------------------------\n");
    printf("\t1.NAME\n");  
    printf("\t2.QUANTITY\n");
    printf("\t3.PRICE\n");
    printf("\tENTER your Choice: ");
    scanf("%d",&y3);
    switch (y3)
    {
    case 1: item_name(line);
        break;
    case 2: item_quantity(line);
        break;
    case 3: item_price(line);
        break;
    default:
        break;
    }
    
}
int indexOfi2(FILE *fptr, char *newi,int *line, int *col)
{
    char str[1000];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str,1000, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, newi);
        if (pos != NULL){
            *col = (pos - str);
            break;
        }
    }
    if (*col == -1){
        *line = -1;}
    return *col,*line;
}
void item_name(int line)
{//                                               UPDATING NAME
    char s[1000],f[100]="INAME.txt",c;
    FILE *fptr, *f1ptr;
    int d=line,temp=1;
    fptr=fopen(f,"r");
    f1ptr=fopen("temp.txt","w");
    printf("\tEnter Name to be replaced with: ");
    scanf("%s",s);
    while((c=getc(fptr))!=EOF){
        if(c=='\n'){
            temp++;
            putc(c,f1ptr);}
        else if(temp==d){
            fputs(s,f1ptr);
            while((c=getc(fptr))!='\n');
                putc(c,f1ptr);
            temp++;}
        else if (temp!=d){
            putc(c,f1ptr);
        }
    }
    fclose(fptr);
    fclose(f1ptr);
    char ch, source_file[20]="temp.txt", target_file[20]="INAME.txt";
    FILE *source, *target;
    source = fopen(source_file, "r");
    if( source == NULL )
    {
      printf("\t\t\t\tNOT UPDATED...\n");
      exit(EXIT_FAILURE);
   }
    target = fopen(target_file, "w");
    if( target == NULL )
    {
      fclose(source);
      printf("\t\t\t\tNOT UPDATED...\n");
      exit(EXIT_FAILURE);
    }
    else
    {
        while( ( ch = fgetc(source) ) != EOF )
            fputc(ch, target);
        printf("\n\tITEM NAME UPDATED SUCCESSFULLY.\n");
    }
   fclose(source);
   fclose(target);
   remove("temp.txt");
}
void item_quantity(int line)
{//                                                 UPDATNG QUANTITY
    char s[1000],f[100]="IQ.txt",c;
    FILE *fptr, *f1ptr;
    int d=line,temp=1;
    fptr=fopen(f,"r");
    f1ptr=fopen("temp.txt","w");
    printf("\tEnter Quantity to be updated: ");
    scanf("%s",s);
    while((c=getc(fptr))!=EOF){
        if(c=='\n'){
            temp++;
            putc(c,f1ptr);}
        else if(temp==d){
            fputs(s,f1ptr);
            while((c=getc(fptr))!='\n');
            putc(c,f1ptr);
            temp++;}
        else if (temp!=d){
            putc(c,f1ptr);
        }
    }
    fclose(fptr);
    fclose(f1ptr);
    char ch, source_file[20]="temp.txt", target_file[20]="IQ.txt";
    FILE *source, *target;
    source = fopen(source_file, "r");
    if( source == NULL )
    {
      printf("\t\t\t\tNOT UPDATED...\n");
      exit(EXIT_FAILURE);
   }
    target = fopen(target_file, "w");
 
   if( target == NULL )
   {
      fclose(source);
      printf("\t\t\t\tNOT UPDATED...\n");
      exit(EXIT_FAILURE);
   }
   else{ while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
   printf("\n\tITEM QUANTITY UPDATED SUCCESSFULLY.\n");}
   fclose(source);
   fclose(target);
   remove("temp.txt");
}
void item_price(int line)
{//                                                 UPDATING PRICE
    char s[1000],f[100]="IP.txt",c;
    FILE *fptr, *f1ptr;
    int d=line,temp=1;
    fptr=fopen(f,"r");
    f1ptr=fopen("temp.txt","w");
    printf("\tEnter Price to be updated with: ");
    scanf("%s",s);
    while((c=getc(fptr))!=EOF){
        if(c=='\n'){
            temp++;
            putc(c,f1ptr);}
        else if(temp==d){
            fputs(s,f1ptr);
            while((c=getc(fptr))!='\n');
            putc(c,f1ptr);
            temp++;}
        else if (temp!=d){
            putc(c,f1ptr);
        }
    }
    fclose(fptr);
    fclose(f1ptr);
    char ch, source_file[20]="temp.txt", target_file[20]="IP.txt";
    FILE *source, *target;
    source = fopen(source_file, "r");
    if( source == NULL )
    {
      printf("\t\t\t\tNOT UPDATED...................\n");
      exit(EXIT_FAILURE);
   }
    target = fopen(target_file, "w");
 
   if( target == NULL )
   {
      fclose(source);
      printf("\t\t\t\tNOT UPDATED................\n");
      exit(EXIT_FAILURE);
   }
   else{ while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
   printf("\n\tITEM PRICE UPDATED SUCCESSFULLY..............\n");}
   fclose(source);
   fclose(target);
   remove("temp.txt");
}
void display()
{//                                     DISPLAYS EXISTING ITEMS
	FILE *fp,*fp2,*fp3,*fp4;    
    fp=fopen("INUM.txt","r");
	fp2=fopen("INAME.txt","r");
	fp3=fopen("IQ.txt","r");
	fp4=fopen("IP.txt","r");   
    char buffer[1000],buffer2[1000],buffer3[1000],buffer4[1000];
    int totalRead = 0;int totalRead2 = 0;int totalRead3 = 0;int totalRead4 = 0;
    if(fp == NULL ||fp2 == NULL || fp3 == NULL ||fp4 == NULL)
    {
        printf("\terror.\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("\tINUMBER\t\tNAME\t\tQUANTITY\tPRICE\n");
        while(fgets(buffer, 1000, fp) != NULL && fgets(buffer2, 1000, fp2) != NULL && fgets(buffer3, 1000, fp3) != NULL && fgets(buffer4, 1000, fp4) != NULL)
        {
            totalRead = strlen(buffer);totalRead2 = strlen(buffer2);totalRead3 = strlen(buffer3);totalRead4 = strlen(buffer4);
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];
            buffer2[totalRead2 - 1] = buffer2[totalRead2 - 1] == '\n' ? '\0' : buffer2[totalRead2 - 1];
            buffer3[totalRead3 - 1] = buffer3[totalRead3 - 1] == '\n' ? '\0' : buffer3[totalRead3 - 1];
            buffer4[totalRead4 - 1] = buffer4[totalRead4 - 1] == '\n' ? '\0' : buffer4[totalRead4 - 1];
            printf("\t%s\t\t%s\t\t%s\t\t%s\n", buffer,buffer2,buffer3,buffer4);}
        }
        fclose(fp);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
}
int bill(int k)
{//                                                         BILLING PART
    char i[10];float sum=0;char new[11];
    printf("\n\tEnter PRODUCT NUMBER(0-Checkout): ");
    scanf("%s",i);
    if (strcmp("0",i))
    {
        existi2(i,k);
    }
    else
    {   edit_customer();
        float dis;
        printf("\tWANNA ADD DISCOUNT(add in %% 0 for NO): ");
        scanf("%f",&dis);
        printf("\n\t------------------------------------------------------\n");
        printf("\tINUMBER\t\tNAME\t\tQUANTITY\tPRICE\n");
        printf("\t------------------------------------------------------\n");
        for (int o= 0; o<k; o++)
        {
            printf("\t%s\t\t%s\t\t%d\t\t%.2f\n",bll[o].no,bll[o].name,bll[o].quan,bll[o].pric);
        }
        for (int oo= 0; oo<k;oo++)
        {
                sum+=bll[oo].pric;
        }
        printf("\n\t------------------------------------------------------\n");
        printf("\t\t\t\tTOTAL(tax exclusive) :  %.2f\n",sum);
        float tax=sum*18/100;dis=sum*dis/100;sum=sum+tax-dis;
        printf("\t\t\t\tTAX:\t\t\t%.2f\n",tax);
        printf("\t\t\t\t-------------------------------\n");
        printf("\t\t\t\tDISCOUNT:\t\t%.2f\n",dis);
        printf("\t\t\t\t-------------------------------\n");
        printf("\t\t\t\tTOTAL(Tax Inclusive) :  %.2f\n",sum);
        printf("\t\t\t\t-------------------------------\n");
    }
}
int existi2(char i[8],int k)
{
    FILE *fptr;
    int line, col;
    fptr = fopen("INUM.txt", "r");
    if (fptr == NULL)
    {
        printf("Unable to process.\n");
        printf("SORRY for the Inconvenience\n");
        exit(EXIT_FAILURE);
    }
    indexOfi4(fptr, i, &line, &col);
    fclose(fptr);
    if(line==-1){printf("\tItem does not Exist.\n");}
    else
    {
        FILE *fp2 = fopen("INAME.txt", "r");
        FILE *fp3 = fopen("IQ.txt", "r");
        FILE *fp4 = fopen("IP.txt", "r");
        printf("\tENTER QUANTITY: ");
        int qq=0;
        scanf("%d",&qq);
        int count = 0;
        if ( fp2 != NULL )
        {   
            char lne[256];
            while (fgets(lne, sizeof lne, fp2) != NULL)
            {   
                if (count == line)
                {   
                    char llne[100];
                    for(int hh=0;lne[hh]!='\n' ;hh++)
                    {
                        llne[hh]=lne[hh];
                    }
                    strcpy(bll[k].no,i);
                    strcpy(bll[k].name,llne);                
                    fclose(fp2);
                }   
                else
                {
                    count++;
                }   
            }
        }
        if ( fp4 != NULL )
        {   
            int count = 0;float pp=0;
            char lne[256];
            while (fgets(lne, sizeof lne, fp4) != NULL)
            {   
                if (count == line)
                {   
                    sscanf(lne,"%f",&pp);                
                    pp=pp*qq;
                    bll[k].quan=qq;
                    bll[k].pric=pp;
                    fclose(fp4);
                    break;
                }   
                else
                {
                    count++;
                }   
            }
        }      
        if ( fp3 != NULL )
        {   
            int count = 0;
            int pp;
            char lne[256];
            while (fgets(lne, sizeof lne, fp3) != NULL)
            {   
                if (count == line)
                {   
                    sscanf(lne,"%d",&pp);                
                    //pp=pp-qq;
                    fclose(fp3);
                    break;
                }   
                else
                {
                count++;
                }   
            }
        }
        fclose(fp2);
        fclose(fp3);
    }
    return bill(k+1);
}
int indexOfi4(FILE *fptr,char *i,int *line, int *col)
{
    char str[1000];
    char *pos;
    *line = -1;
    *col  = -1;
    while ((fgets(str,1000, fptr)) != NULL)
    {
        *line += 1;
        pos = strstr(str, i);
        if (pos != NULL)
        {
            *col = (pos - str);
            break;
        }
    }
    if (*col == -1)
    {
        *line = -1;
    }
    return *col;
}