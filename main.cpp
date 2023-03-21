#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

class product
{
   int pno;
   char name[50];
   float price,qty,tax,dis;
   
   public:

   void create_product()
   {
      cout<<"\nPlease Enter The Product No. of The Product ";
      cin>>pno;
      cout<<"\n\nPlease Enter The Name of The Product ";
      gets(name);
      cout<<"\nPlease Enter The Price of The Product(in Rs) ";
      cin>>price;
      cout<<"\nPlease Enter The Discount (%) ";
      cin>>dis;
   }

   void show_product()
   {
      cout<<"\nThe Product No. of The Product : "<<pno;
      cout<<"\nThe Name of The Product : ";
      puts(name);
      cout<<"\nThe Price of The Product(in Rs) : "<<price;
      cout<<"\nDiscount (%): "<<dis;
   }

   int retpno()
   {
      return pno;
   }

   float retprice()
   {
      return price;
   }

   char* retname()
   {
      return name;
   }

   int retdis()
   {
      return dis;
   }

};

fstream fp;
product pr;

void write_product()
{
   fp.open("Shop.dat",ios::out|ios::app);
   pr.create_product();
   fp.write((char*)&pr,sizeof(product));
   fp.close();
   cout<<"\n\nThe Product Has Been Created ";
   getch();
}

void display_all()
{
   system("CLS");
   cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
   fp.open("Shop.dat",ios::in);

   while(fp.read((char*)&pr,sizeof(product)))
   {
      pr.show_product();
      cout<<"\n\n====================================\n";
      getch();
   }
   fp.close();
   getch();
}

void admin_menu();
product A,B;

void AppendData()
   {
      fstream fapp;
      fapp.open("Shop.dat",ios::binary|ios::app);
      if (!fapp)
         {
         cout<<"\File could not be opened";
         getch();
         admin_menu();
         }
      system("CLS");
      pr.create_product();
      fapp.write((char *)&pr,sizeof(pr));
      fapp.close();
      cout<<"\n\n\tThe Product has been appended";
      getch();
   }

void InsertRecord()
   {
      fstream fin,fout;
      fin.open("Shop.dat",ios::binary|ios::in);
      fout.open("Temp.dat",ios::binary|ios::out);
      if (!fin || !fout)
         {
         cout<<"\File could not be opened";
         getch();
         admin_menu();
         }
      system("CLS");
      B.create_product();

      while(!fin.eof())
         {  fin.read((char*)&A,sizeof(A));
            if (A.retpno() > B.retpno())
               {
                  fout.write((char*)&B,sizeof(B));
                  fout.write((char*)&A,sizeof(A));
                  break;
               }
           else
               {
                  fout.write((char*)&A,sizeof(A));
               }
         }

      while(fin.read((char*)&A,sizeof(A)))
         fout.write((char*)&A,sizeof(A));

      fin.close();
      fout.close();
      cout<<"\n\n The Product has been inserted....";
      getch();
      remove("Shop.dat");
      rename("Temp.dat","Shop.dat");
   }


void display_sp(int n)
{
   int flag=0;
   fp.open("Shop.dat",ios::in);

   while(fp.read((char*)&pr,sizeof(product)))
   {
      if(pr.retpno()==n)
      {
         system("CLS");
         pr.show_product();
         flag=1;
      }
   }

   fp.close();
   if(flag==0)
   cout<<"\n\nProduct does not exist";
   getch();
}


void modify_product()
{
   int no,found=0;
   system("CLS");
   cout<<"\n\n\tTo Modify ";
   cout<<"\n\n\tPlease Enter The Product No. of The Product";
   cin>>no;
   fp.open("Shop.dat",ios::in|ios::out);

   while(fp.read((char*)&pr,sizeof(product)) && found==0)
   {
      if(pr.retpno()==no)
      {
         pr.show_product();
         cout<<"\nPlease Enter The New Details of Product"<<endl;
         pr.create_product();
         int pos=-1*sizeof(pr);
         fp.seekp(pos,ios::cur);
         fp.write((char*)&pr,sizeof(product));
         cout<<"\n\n\t Product Updated";
         found=1;
      }
   }
   fp.close();
   if(found==0)
   cout<<"\n\n Product Not Found ";
   getch();
}


void delete_product()
{
   int no,flag=0;
   system("CLS");
   cout<<"\n\n\n\tDelete Record";
   cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
   cin>>no;
   fp.open("Shop.dat",ios::in|ios::out);
   fstream fp2;
   fp2.open("Temp.dat",ios::out);
   fp.seekg(0,ios::beg);

   while(fp.read((char*)&pr,sizeof(product)))
   {
      if(pr.retpno()==no)
      {
         flag=1;
         pr.show_product();
      }

      if(pr.retpno()!=no)
      {
         fp2.write((char*)&pr,sizeof(product));
      } 
   }

   fp2.close();
   fp.close();
   remove("Shop.dat");
   rename("Temp.dat","Shop.dat");
   if(flag==1)
   cout<<"\n\n\tThe following product has been deleted ..";
   else
   cout<<"\n\n\tProduct not found..";
   getch();
}


void menu()
{
   system("CLS");
   fp.open("Shop.dat",ios::in);

   if(!fp)
   {
      cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
      cout<<"\n\n\n Program is closing ....";
      getch();
      exit(0);
   }
   cout<<"\n\n\t\tProduct MENU\n\n";
   cout<<"====================================================\n";
   cout<<"P.NO.\t\tNAME\t\tPRICE\n";
   cout<<"====================================================\n";

   while(fp.read((char*)&pr,sizeof(product)))
   {
      cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
   }
   fp.close();
}


void place_order()
{
   int order_arr[50],quan[50],c=0;
   float amt,damt,total=0;
   char ch='Y';
   menu();
   cout<<"\n============================";
   cout<<"\n PLACE YOUR ORDER";
   cout<<"\n============================\n";

   do{
      cout<<"\n\nEnter The Product Number Of The Product : ";
      cin>>order_arr[c];

      cout<<"\nQuantity in number : ";
      cin>>quan[c];
      c++;
      cout<<"\nDo You Want To Order Another Product ? (y/n)";
      cin>>ch;
   }while(ch=='y' ||ch=='Y');

   cout<<"\n\nThank You For Placing The Order";getch();system("CLS");
   cout<<"\n\n********************************INVOICE************************\n";
   cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount After Discount\n";
   
   for(int x=0;x<=c;x++)
   {
      fp.open("Shop.dat",ios::in);
      fp.read((char*)&pr,sizeof(product));
      while(!fp.eof())
      {
         if(pr.retpno()==order_arr[x])
         {
            amt=pr.retprice()*quan[x];
            damt=amt-(amt*pr.retdis()/100);
            cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()
            <<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
            total+=damt;
         }
         fp.read((char*)&pr,sizeof(product));
      }
      fp.close();
   }
   cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
   getch();
}

void intro()
{
   system("CLS");
   cout<<"\t\t\t\t AJR SUPER MARKET \n\n\n";

   cout<<"\t\t\t\t  BILLING \n\n\n";
   getch();
   
}


void admin_menu()
{
   system("CLS");
   char ch2;
   cout<<"\n\n\n\tADMIN MENU";
   cout<<"\n\n\t1.CREATE PRODUCT";
   cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
   cout<<"\n\n\t3.SEARCH PRODUCT ";
   cout<<"\n\n\t4.MODIFY PRODUCT";
   cout<<"\n\n\t5.DELETE PRODUCT";
   cout<<"\n\n\t6.APPEND DATA";
   cout<<"\n\n\t7.INSERT PRODUCT";
   cout<<"\n\n\t8.BACK TO MAIN MENU";
   cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
   cin>>ch2;

   switch(ch2)
   {
      case '1': system("CLS");;
                  write_product();
                  break;

      case '2': display_all();
                  break;

      case '3': int num;
                  system("CLS");;
                  cout<<"\n\n\tPlease Enter The Product No. ";
                  cin>>num;
                  display_sp(num);
                  break;

      case '4': modify_product();
                  break;

      case '5': delete_product();
                  break;

      case '6':AppendData();
                  break;

      case '7': InsertRecord();
                  break;

      case '8':  menu();
                  break;

      default:cout<<"Wrong option!!! Enter again!!!";
            admin_menu();
   }
}


void main()
{
   char ch;
   intro();
   do{
      system("CLS");
      cout<<"\n\n\n\tMAIN MENU";
      cout<<"\n\n\t01. CUSTOMER";
      cout<<"\n\n\t02. ADMINISTRATOR";
      cout<<"\n\n\t03. EXIT";
      x:
      cout<<"\n\n\tPlease Select Your Option (1-3) ";
      cin>>ch;

      switch(ch)
      {
         case '1': system("CLS");;
                     place_order();
                     getch();
                     break;

         case '2': admin_menu();
                     break;

         case '3': exit(0);
                     break;

         default :cout<<"\tWrong option!!! Enter again!!!";
         goto x;
      }

   }while(ch!=3);
   getch();
}