#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#define MAX 50


void ccolor(int clr){

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);

}

char query[MAX],name[MAX];
FILE *fp, *ft, *pt;
int i,n,ch,l,found;
int x,y,a;
COORD coord = {0,0};
void gotoxy(int x,int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
struct contact
{

    long ph;

    char name[MAX],add[MAX],email[MAX];

} list;
void encrypt()
{
	fp = fopen("contact.txt", "r");
    if(fp == NULL)
        return 0;
    pt = fopen("pass.txt", "w");
    if(pt == NULL)
        return 0;
    ch = fgetc(fp);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, pt);
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(pt);
    remove("contact.txt");
	rename("pass.txt","contact.txt");
}
void decrypt()
{
	fp = fopen("contact.txt", "r");
    if(fp == NULL)
        return 0;
    pt = fopen("pass.txt", "w");
    if(pt == NULL)
        return 0;
    ch = fgetc(fp);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch, pt);
        ch = fgetc(fp);
    }
    fclose(fp);
    fclose(pt);
    remove("contact.txt");
	rename("pass.txt","contact.txt");
}
void add_contacts()
{
	ccolor(55);
         system("cls");

        fp=fopen("contact.txt","a");
for (;;)

        {
            fflush(stdin);

			system("cls");
			box();
			gotoxy(36,5);printf("ADD CONTACTS");

			gotoxy(21,24);printf(" To exit enter blank space in the Name");
            gotoxy(22,9);printf("Name (Use identical):");

            gotoxy(22,12);printf("Phone:");

            gotoxy(22,15);printf("address:");

            gotoxy(22,18);printf("email address:");

            gotoxy(22,10);scanf("%[^\n]",&list.name);

            if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)

                break;
            fflush(stdin);

            gotoxy(22,13);scanf("%ld",&list.ph);

            fflush(stdin);

            gotoxy(22,16);scanf("%[^\n]",&list.add);

            fflush(stdin);

            gotoxy(22,19);gets(list.email);

            fwrite(&list,sizeof(list),1,fp);
    	}
        	fclose(fp);
        system("cls");
        box();
        uploading();
}
void view_list()
{
	ccolor(55);

		system("cls");
    	gotoxy(30,1);printf("LIST OF CONTACTS");
    	gotoxy(20,4);printf("%c",176);
    	gotoxy(20,5);printf("%c",176);


    	for(x=15;x<=60;x++)
   		{
    		gotoxy(x,2);printf("%c",176);
   		}


        for(i=97; i<=122; i=i+1)
		{
			fp=fopen("contact.txt","r");
            fflush(stdin);
			found=0;

            while(fread(&list,sizeof(list),1,fp)==1)

            {


                if(list.name[0]==i || list.name[0]==i-32)

                {

                    printf("\n\t       %c   Name: %s\n\t       %c   Phone: %ld\n\t       %c   Address: %s\n\t       %c   Email: %s\n\t       %c",
					176,list.name,176,list.ph,176,list.add,176,list.email,176);
                    found++;


                }
            }

            if(found!=0)
            {

                printf("\n\t       %c   ======================= [%c]-(%d)",176,i-32,found);


            }
          fclose(fp);

        }

		getch();

}
void search()
{
	
	 system("cls");
	 ccolor(55);
   		 do

      	{

	
		            found=0;
					box();
					gotoxy(21,24);printf(" To exit enter blank space in the Name");
		           gotoxy(34,4);printf("CONTACT SEARCH");
		           gotoxy(22,9);printf("ENTER LETTER/NAME: ");
		
		            fflush(stdin);
		
		            scanf("%[^\n]",&query);
		            
		            l=strlen(query);
		            
		            if(stricmp(query,"")==0 || stricmp(query," ")==0)
		                break;
		
		            fp=fopen("contact.txt","r");
		
		            system("cls");
		
		    		for(x=15;x<=60;x++)
		   				{
		    				gotoxy(x,2);printf("%c",176);
		   				}
		
		
		            printf("\n\t       %c\tSearch result for '%s'",176,query);
		            printf("\n\t       %c",176);
		
		            while(fread(&list,sizeof(list),1,fp)==1)
		
		            {
		
		                for(i=0; i<=l; i++)
		
		                    name[i]=list.name[i];
		
		                name[l]='\0';
		
		                if(stricmp(name,query)==0)
		
		                {
		
		                    printf("\n\t       %c   Name: %s\n\t       %c   Phone: %ld\n\t       %c   Address: %s\n\t       %c   Email: %s\n\t       %c",
							176,list.name,176,list.ph,176,list.add,176,list.email,176);
		
		                    found++;
		
		                    if (found%4==0)
		
		                    {
		
		                        printf("\n\t       %cPress any key to continue...",176);
		
		                        getch();

                    		}

	                	}		

            		}

            if(found==0)
            	printf("\n\t       %c  No match found!",176);

            else
            {
            	printf("\n\t       %c",176);
            	printf("\n\t       %c  %d match(s) found!",176,found);
			}

            fclose(fp);
            printf("\n\t       %c  Try again?\t[1] Yes\t",176);

            scanf("%d",&ch);
            system("cls");

        }
        while(ch==1);
    


}
void modify_contacts()
{
	ccolor(55);
	
        fp=fopen("contact.txt","r");

        ft=fopen("temp.txt","w");
		
for(;;)
{
	system("cls");
	gotoxy(21,24);printf(" To exit enter blank space in the Name");

        fflush(stdin);

        box();

        gotoxy(36,5);printf("EDIT CONTACTS");
        gotoxy(22,7);printf("Enter the name of contact to edit:");
        gotoxy(22,8);scanf("%[^\n]",name);
        
        

        while(fread(&list,sizeof(list),1,fp)==1)

        {

            if(stricmp(name,list.name)!=0)

                fwrite(&list,sizeof(list),1,ft);

        }

        fflush(stdin);
        if(stricmp(name,"")==0 || stricmp(name," ")==0)
					break;
        

        gotoxy(22,9);printf("Editing '%s'\n\n",name);

        gotoxy(22,11);printf("Name (Use identical):");

        gotoxy(43,11);scanf("%[^\n]",&list.name);

        fflush(stdin);

        gotoxy(22,12);printf("Phone:");

        gotoxy(28,12);scanf("%ld",&list.ph);

        fflush(stdin);

        gotoxy(22,13);printf("address:");

        gotoxy(30,13);scanf("%[^\n]",&list.add);

        fflush(stdin);

        gotoxy(22,14);printf("email address:");

        gotoxy(36,14);gets(list.email);

        printf("\n");

        fwrite(&list,sizeof(list),1,ft);
        
}
		fclose(fp);

        fclose(ft);

        remove("contact.txt");

        rename("temp.txt","contact.txt");
		system("cls");
        box();
        updating();

}

void remove_contact()
{
	  fp=fopen("contact.txt","r");

        ft=fopen("temp.txt","w");

	
	for(;;)
	{
		
		ccolor(55);
	 	system("cls");
        fflush(stdin);
        gotoxy(21,24);printf(" To exit enter blank space in the Name");
		box();
		gotoxy(32,5);printf("DELETE A CONTACT");
		gotoxy(22,11);printf("Enter the name of contact to delete: ");
        gotoxy(22,12);scanf("%[^\n]",name);
        

      
        while(fread(&list,sizeof(list),1,fp)!=0)

            if (stricmp(name,list.name)!=0)

                fwrite(&list,sizeof(list),1,ft);
                
        if(stricmp(name,"")==0 || stricmp(name," ")==0)
		        break;
                
        
	}
		fclose(fp);
		
        fclose(ft);

        remove("contact.txt");
        rename("temp.txt","contact.txt");
        system("cls");
        box();
        updating();
        
}
void box()
{

   for(x=20;x<=60;x++)
   {

    gotoxy(x,3);printf("%c",176);
    gotoxy(x,25);printf("%c",176);

   }
   for( y=3;y<=25;y++)
   {

       gotoxy(20,y);printf("%c",176);
       gotoxy(60,y);printf("%c",176);

   }
}
void loader()
{

   for(x=20;x<=60;x++)
   {
   	Sleep(20);
    gotoxy(x,3);printf("%c",176);
    gotoxy(x,25);printf("%c",176);

   }
   for( y=3;y<=25;y++)
   {
   		Sleep(20);
       gotoxy(20,y);printf("%c",176);
       gotoxy(60,y);printf("%c",176);

   }
}
void menu()
{
	box();
	gotoxy(39,5);printf("MENU");
	gotoxy(35,8);printf(" [1]Add New");
	gotoxy(36,11);printf("[2]List");
	gotoxy(36,14);printf("[3]Modify");
	gotoxy(36,17);printf("[4]Search");
	gotoxy(36,20);printf("[5]Delete");
	gotoxy(36,23);printf("[6]Exit");
}
void welcome()
{	
	gotoxy(22,15);printf("WELCOME TO CONTACT MANAGEMENT SYSTEM\n\n\n\t\t");system("pause");

}
void loading()
{
	int i;
	for ( i=15;i<=100;i+=5)
	{	
		system("cls");
		ccolor(55);
		gotoxy(32,15);printf("%d %% Loading...\n",i);Sleep(100);
	}
	
}
void updating()
{
	int i;
	for ( i=15;i<=100;i+=5)
	{	
		ccolor(55);
		gotoxy(30,11);printf("%d %% Updating data...\n",i);Sleep(150);
	}
	
}
void uploading()
{
	int i;
	for ( i=15;i<=100;i+=5)
	{	
		ccolor(55);
		gotoxy(30,11);printf("%d %% Uploading data...\n",i);Sleep(150);
	}
	
}
int main()
{
	system("title  Contact Management System");
	system("mode con: cols=80 lines=30");

	loading();
	welcome();
	main:ccolor(55);
	system("cls");
	menu();
	switch(getch())
	{
	case '1':
		decrypt();
		add_contacts();
		encrypt();
		goto main;
		break;
	case '2':
		decrypt();
		view_list();
		encrypt();
		goto main;
		break;
    case '3':
    	decrypt();
    	modify_contacts();
    	encrypt();
    	goto main;
    	break;
    case '4':
    	decrypt();
    	search();
    	encrypt();
    	goto main;
		break;
    case '5':
    	decrypt();
    	remove_contact();
    	encrypt();
    	goto main;
    	break;
    case '6':
    	system("cls");
    	decrypt();
    	encrypt();
    	box();
    	gotoxy(35,12);printf("THANK YOU!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    	break;
    default:
    	system("cls");
        gotoxy(32,15);printf("Invalid choice\n\n\n");
        break;

    }



}


