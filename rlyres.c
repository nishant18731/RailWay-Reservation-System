#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("_");
    printf("\n");
    printf("\nSelect an option");
    printf("\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");
    printf("\n\nEnter choice:");
    scanf( "%d", &choice );
    return choice;

}
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
    }
    else
    {
        fclose(fp);
    }
}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=1;i<=80;i++)
        printf("_");
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    printf("\n\n\n\n");
    fclose(fp);

}
void view_all_bookings()
{
    int i;
    printf("TICKET NO CLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\tADDRESS\n");
    for(i=1;i<=80;i++)
        printf("_");
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1 )
        {
            printf("%d\t  %c\t%s\t\t",pr.ticketno,pr.p_class,pr.p_name);
            printf("%c\t%d\t%s\t%s\n",pr.gender,pr.age,pr.mob_no,pr.p_address);
        }
    fclose(fp);

}
int check_train_no(char *trainno)
{
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
      if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }

    }
    fclose(fp);
    return 0;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
       if( isdigit(*p_mob)==0)
        return 0;
       p_mob++;
    }
    return 1;
}
Passenger* get_passenger_details()
{
    int i;
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;


    //Input Passanger Name
    printf("Enter passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    int valid;


    //Input Passanger Gender
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.gender!='M'&& psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!Gender should be M or F(in uppercase)!");
            valid=0;
            getch();
            gotoxy(19,2);
            printf("\t\t\t");
            gotoxy(19,2);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,3);


    //Input Train Number
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!Invalid Train No!");
            getch();
            gotoxy(20,3);
            printf("\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,4);


    //Input travelling class
    printf("Enter travelling class(First AC:F,Second AC:S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.p_class!='F'&& psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!travellingclass should be F or S(in uppercase)!");
            valid=0;
            getch();
            gotoxy(48,4);
            printf("\t\t\t");
            gotoxy(48,4);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,5);


    //Input Passanger Address
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.p_address,20,stdin);
    pos=strchr(psn.p_address,'\n');
    *pos='\0';
    if(strcmp(psn.p_address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }



    //Input Passanger Age
    printf("Enter age:");
    do
    {
        valid=1;
       // fflush(sdtin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age<0 || psn.age>=130)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,7);


    //Passanger Mobile Number
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!Invalid Mobile No!");
            getch();
            gotoxy(21,7);
            printf("\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}
int get_booked_ticket_count(char *train_no,char tc)
{
        FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
        if(fp==NULL)
            return 0;
        Passenger pr;
        int count=0;
        while(fread(&pr,sizeof(pr),1,fp)==1)
        {
            if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
                ++count;
        }
        fclose(fp);
        return count;

}
int last_ticket_no()
{

        FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
        if(fp==NULL)
            return 0;
        Passenger pr;
        fseek(fp,-1L*sizeof(pr),SEEK_END);
        fread(&pr,sizeof(pr),1,fp);
        fclose(fp);
        return pr.ticketno;
}
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats in train no %s in class %c are full!",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no();
    p.ticketno=ticket_no+1;
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return p.ticketno;

}
int accept_ticket_no()
{
    printf("Enter a valid ticket no:");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelled Input...!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Ticket number should be positive");
            getch();
            valid=0;
            gotoxy(25,1);
            printf("\t\t\t\t");
            gotoxy(25,1);
            textcolor(YELLOW);
        }

    }while(valid==0);
    return ticket_no;
}
void view_ticket(int ticket_no)
{
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return ;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.p_address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }

    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of the ticket no %d found",ticket_no);
    }
    fclose(fp);
}
char *accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid ;
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!Invalid Mobile No!");
            getch();
            gotoxy(27,1);
            printf("\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }


    }while(valid==0);
        clrscr();
        return mob_no;
}
int *get_ticket_no(char *p_mob_no)
{
    int count=0;
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            ++count;
        }

    }
    if(!count)
    {
        fclose(fp);
        return NULL;
    }

    int *p=(int*)malloc((count+1)*sizeof(int));
    rewind(fp);
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
          *(p+i)=pr.ticketno;
          i++;
        }

    }
    *(p+i)=-1;
    fclose(fp);
    return p;

}
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("SOrry!No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for the mobile number %s",pmob_no);
    int i;
    printf("\n\nTICKET NUMBERS\n");
    printf("\n--------------------------------------------------------------------------------\n");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("%d\n",*(pticket_no+i));
    }

    textcolor(WHITE);
    printf("\nPress any key to go back to main screen");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}
char *accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!!");
            getch();
            textcolor(YELLOW);
            return NULL;

        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Erro!Invalid Train No!");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;

}
void view_booking(char *train_no)
{
    int found=0,i;
    FILE *fp=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return ;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1; i<=80;i++)
    {
        printf("-");

    }
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(train_no,pr.train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of booking in train no %s found",train_no);
    }
    textcolor(WHITE);
    printf("\n\nPreass any key to continue!");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}

int cancel_train(char *train_no)
{
    int result;
    FILE *fp1=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nFile not present!");
        return -1;
    }
    FILE *fp2=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)!=0)
        {

            fwrite(&pr,sizeof(pr),1,fp2);
        }
        else
        {
            found=1;
        }

    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat");
    }

    else
    {
        result=remove("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat","D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo booking done yet!");
        return -1;
    }
    FILE *fp2=fopen("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }

    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat");
    }
    else
    {
        result=remove("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\temp.dat","D:\\C Project\\Cproject\\Railway Reservation System\\projectfile\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}



