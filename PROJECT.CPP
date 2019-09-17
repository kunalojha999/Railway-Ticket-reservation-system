//**************************************************************
//                 HEADER FILES USED IN PROJECT
//**************************************************************
#include<stdio.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
//**************************************************************
//                 CLASS USED IN PROJECT
//**************************************************************

class ticket
{
private:
int trainno;
int noofpassangers;
int pnr;
int distance;
char from[30];
char to[30];
char trainname[30];
char passanger1[20],passanger2[20],passanger3[20] ,passanger4[20];
int fare;
void assignpnr()
{
randomize();
pnr=random(3000-2000+1)+2000;
}
void assignfare()
{randomize();
fare=random(2000-1000+1)+1000;
}
void assigndistance()
{randomize();
distance=random(10000-900+1)+900;
}
public:
void choosetrain();
void createticket();
void showticket();
int returnpnr()
{
return(pnr);
}
};
void ticket::choosetrain()
{
cout<<"train no      train name"<<"\n";
cout<<"  2305      kranti express"<<"\n";
cout<<"  2607      rajdhani express"<<"\n";
cout<<"  2777      shatabdi express"<<"\n";
cout<<"  2997      sialdah mail"<<"\n";
cout<<"select train no:";
cin>>trainno;
switch(trainno)
{case 2305:
strcpy(trainname,"kranti express");
break;
case 2607:
strcpy(trainname,"rajdhani express");
break;
case 2777:
strcpy(trainname,"shatabdi express");
break;
case 2997:
strcpy(trainname,"sialdah mail");
break;
}}
void ticket::createticket()
{
int i,j;
cout<<"enter boarding station:";
gets(from);
cout<<"enter destination station:";
gets(to);
cout<<"enter no of passangers (between 1 to 4):";
cin>>noofpassangers;
for(i=0;i<noofpassangers;i++)
{
if(i==0)
{cout<<"enter name of passanger"<<i+1<<":";
gets(passanger1);}
else if(i==1)
{cout<<"enter name of passanger"<<i+1<<":";
gets(passanger2);}
else if(i==2)
{cout<<"enter name of passanger"<<i+1<<":";
gets(passanger3);}
else if(i==3)
{cout<<"enter name of passanger"<<i+1<<":";
gets(passanger4);}
}
assignpnr();
assignfare();
assigndistance();
choosetrain();
clrscr();
cout<<"the ticket has following specifications"<<"\n";
showticket();
}
void  ticket::showticket()
{int i,j;
cout<<"pnr:"<<pnr<<"\n"<<"fare:"<<fare<<"\n"<<"distance:"<<distance<<"\n";
cout<<"boarding station:";
puts(from);
cout<<"destination station:";
puts(to);
cout<<"train no:"<<trainno<<"\n";
cout<<"train name:";
puts(trainname);
cout<<"no of passangers:"<<noofpassangers;
cout<<"\n";
for(i=0;i<noofpassangers;i++)
{
if(i==0)
{cout<<"passanger"<<i+1<<":";
puts(passanger1);
cout<<"\n";}
else if(i==1)
{cout<<"passanger"<<i+1<<":";
puts(passanger2);
cout<<"\n";}
if(i==2)
{cout<<"passanger"<<i+1<<":";
puts(passanger3);
cout<<"\n";}
if(i==3)
{cout<<"passanger"<<i+1<<":";
puts(passanger4);
}
}
cout<<"\n";
}




//**************************************************************
//                 MAIN FUNCTION OF PROGRAM
//**************************************************************

void main()
{
void bookticket();
void searchticket();
void cancelticket();
void showallticket();
int i,j,ch;
char pass[5];
clrscr();
for(i=0;i<3;i++)
{
cout<<"enter password:";
for(j=0;j<5;j++)
{
pass[j]=getch();
cout<<"*";
}
pass[j]='\0';
if(strcmp(pass,"comp1")==0)
{
clrscr();
cout<<"correct password";
delay(500);
clrscr();
break;}
else if(i<2)
{cout<<"\n";
cout<<"incorrect password";
delay(500);
clrscr();
cout<<"try again";
delay(500);
clrscr();
continue;
}
else
{
clrscr();
cout<<"you have exceeded your tries";
delay(500);
exit(0);
}
}




//**************************************************************
//                    MAIN MENU OF PROJECT
//**************************************************************

cout<<"                 TICKET RESERVATION AND TICKET CHECKING SYSTEM           "<<"\n";
cout<<"\n";
cout<<"MENU"<<"\n";
cout<<"1.Book ticket"<<"\n";
cout<<"2.Search existing ticket"<<"\n";
cout<<"3.Cancel ticket"<<"\n";
cout<<"4.show all ticket"<<"\n";
cout<<"select option:";
cin>>ch;
switch(ch)
{
case 1:
bookticket();
break;
case 2:
searchticket();
break;
case 3:
cancelticket();
break;
case 4:
showallticket();
break;
default:
cout<<"incorrect option";
delay(500);
}
}
//**************************************************************
//                 FUNCTION TO BOOK TICKET
//**************************************************************
void bookticket()
{
clrscr();
ticket t2;
ofstream filout;
char ans='y';
filout.open("ticket.dat",ios::binary);
while(ans=='y')
{
clrscr();
t2.createticket();
filout.write((char*)&t2,sizeof(t2));
cout<<"book another ticket?";
cin>>ans;}
filout.close();
}
//**************************************************************
//      FUNCTION TO DISPLAY DETAILS OF A PARTICULAR TICKET
//**************************************************************
void searchticket()
{
clrscr();
int n,flag=0;
ticket t1;
cout<<"enter pnr no of ticket you want to search";
cin>>n;
ifstream filin;
filin.open("ticket.dat",ios::binary);
while(filin)
{
filin.read((char*)&t1,sizeof(t1));
if(t1.returnpnr()==n)
{
t1.showticket();
delay(500);
flag=1;
break;
}}
if(flag==0)
cout<<"ticket not found";
delay(500);
filin.close();
}
//**************************************************************
//                 FUNCTION TO CANCEL TICKET
//**************************************************************
void cancelticket()
{
clrscr();
char found='f';
int n;
ticket t1,t2;
ofstream filout;
ifstream filin;
cout<<"enter pnr no of ticket you want to cancel";
cin>>n;
filin.open("ticket.dat",ios::binary);
filout.open("temp.dat",ios::binary);
while(filin)
{
filin.read((char*)&t1,sizeof(t1));
if(t1.returnpnr()==n)
{
t1.showticket();
cout<<"\n";
cout<<"ticket cancelled";
delay(500);
found='t';
}
else
filout.write((char*)&t1,sizeof(t1));
}
if(found=='f')
cout<<"ticket not found";
delay(500);
filin.close();
filout.close();
remove("ticket.dat");
rename("temp.dat","ticket.dat");
}

//**************************************************************
//                 FUNTION TO SHOW ALL TICKETS
//**************************************************************
void showallticket()
{
clrscr();
ticket t1;
ifstream filin;
filin.open("ticket.dat",ios::binary);
while(filin)
{
filin.read((char*)&t1,sizeof(t1));
t1.showticket();
}
filin.close();
}
