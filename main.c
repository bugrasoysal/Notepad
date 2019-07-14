#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

FILE *fp;//DOSYA ACMA
char name[20];
enum ozelkarakter //OZEL KARAKTERLER
{
    NONE = 0,
    SPACE=32,
    BACKSPACE = 8,
    ENTER = 13,
    TAB = 9,
    ESCAPE = 27,
    ARROW = 224,
    ARROW_UP = 72,
    ARROW_DOWN = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77


};
typedef struct node{ //CIFT YONLU BAGLI list OLUSTURMA

   char *data;

   struct  node * next;
   struct  node * prev;

}list;

int a=1;
int x=0;
int y=1;
int total_ch=0;
list *head=NULL;
list *tail=NULL;
list *newNode=NULL;
list *temp=NULL;
list *iter=NULL;



struct edit{ //CIKIS DATASI

	int esc;
	int space;
	int backspace;
	int f1;

}data;


int is_special(int key) //OZEL KARAKTER OLDUGUNUN SORULMASI
{
	if (key != ARROW && key != BACKSPACE && key != ENTER && key != TAB && key != ESCAPE && key!=SPACE )
		return 0;
	else return 1;
}

int read () //KLAVYEDEN KARAKTER OKUMA
{
    if (_kbhit())
	{
		return _getch();
	}
	else return -1;
}
void input () //KLAVYEDEN KARAKTER OKUYUP EKLE FONKSIYONUNA GONDERME
{
    int key = read();
    if (key != -1)
	{
      if (!is_special(key))
		{
			add(key);

		}
      else
		{
			special_key_fonc(key);
		}

	}

}
void add(char *info){ //listYE ELEMAN EKLEME

   iter=head;

   if(head==NULL)
   {
     newNode=malloc(sizeof(list));
     newNode->data=info;
     newNode->next=NULL;
     newNode->prev=NULL;
     head=newNode;
     tail=newNode;

   if(x!=80)
    x++;
   else{
    x=1;
    y++;
   }
  total_ch++;
    if(info==' '){
        printf("%c",info);
        gotoxy(x,y);
    }
    else
        writeScreen();

    }


else if((((y-1)*80)+x)!=total_ch)
{
    int i=1;
    if(y>1){
    for(i=1;i<((((y-1)*80)+x));i++)
        iter=iter->next;
    }
    else
    {
    for(i=1;i<x;i++)
        iter=iter->next;
    }
    newNode=malloc(sizeof(list));
    newNode->data=info;
    newNode->next=iter->next;
    iter->next=newNode;
    newNode->next->prev=newNode;
    newNode->prev=iter;

    if(x!=80)
        x++;
    else{
        x=1;
        y++;

    }
    total_ch++;

     if(info==' '){
       printf("%c",info);
     }
     else
        writeScreen();

     gotoxy(x+1,y);


}

else
{
    newNode= malloc(sizeof(list));
    newNode->data=info;
    newNode->next=NULL;
    newNode->prev=tail;
    tail->next=newNode;
    tail=newNode;
    if(x!=80)
        x++;
    else{
        x=1;
        y++;

    }
    total_ch++;

    if(info==' '){
        printf("%c",info);
        gotoxy(x,y);
    }
    else
        writeScreen();

    }

}

void backspace() //LYSTEDEN ELEMAN SYLME
{
iter=head;
    if(newNode->data==' ')
        {
        int i=0;
        while(newNode->data==' ' && i<80)
        {

            temp=newNode;
            tail = tail->prev;
            tail->next = NULL;
            newNode=tail;
            free(temp);


   if(x>0){
   x--;
   }
   else if (x==0 && y>1)
   {
   x=79;
   y--;

   }
   if(total_ch>0)
       total_ch--;
    i++;
   }
   gotoxy(x,y);
}
else{
if(head==NULL){
    system("cls");
}
else{



if(newNode->prev == NULL)
{
    temp=newNode;
    head->prev= NULL;
    tail->next=NULL;
    head=NULL;
    tail=NULL;
    free(temp);

   if(x>0){
   x--;
   }
   else if (x==0 && y>1)
   {
   x=79;
   y--;

   }
   if(total_ch>0)
       total_ch--;


}
else if((((y-1)*80)+x)!=total_ch)
{
    int i=2;
    if(y>1){
    for(i=1;i<((((y-1)*80)+x));i++)
        iter=iter->next;
    }
    else
    {
    for(i=2;i<x;i++)
        iter=iter->next;
    }
    temp=iter->next;
    iter->next=temp->next;
    iter->next->prev=iter;
    free(temp);
   if(x>0){
   x--;
   }
   else if (x==0 && y>1)
   {
   x=79;
   y--;

   }
   if(total_ch>0)
       total_ch--;

    }
else
{
    temp=newNode;
    tail = tail->prev;
    tail->next = NULL;
    newNode=tail;
    free(temp);


   if(x>0){
   x--;
   }
   else if (x==0 && y>1)
   {
   x=79;
   y--;

   }
   if(total_ch>0)
       total_ch--;

}

}


    writeScreen();
    gotoxy(x+1,y);

}
}

void special_key_fonc(int key) //OZEL KARAKTER FONKSIYONLARI
{

	if(key==ARROW)
	{
    switch (_getch()) {
    case ARROW_UP:
        arrowu();
        break;
    case ARROW_DOWN:
        arrowd();
        break;
    case ARROW_LEFT:
         arrowl();
        break;
    case ARROW_RIGHT:
         arrowr();
        break;
		}}
    if(key==BACKSPACE){
        backspace();
        data.backspace=1;
    }
    if(key==TAB)
		tab();
    if(key==ESCAPE)
        data.esc=1;
    if(key==ENTER)
	    enter();
    if(key==SPACE)
        space();



}

void arrowl() //SOL OK
{
   if(x>0){
   x--;
   gotoxy(x,y);

   }
   else if (x==0 && y>1)
   {
   x=79;
   y--;
   gotoxy(x,y);

   }

}



void arrowr() //SAG OK
{
   if(y>1){
   if((((y-1)*80)+x)<total_ch)
    {
   if(x!=80){
    x++;
    gotoxy(x,y);

   }
   else if (x==80){
    y++;
    x=1;
    gotoxy(x,y);
   }
   }
   }
   else
   {
    if(x<total_ch)
    {
    if(x!=80){
    x++;
    gotoxy(x,y);

    }
    else if (x==80){
    y++;
    x=1;
    gotoxy(x,y);
    }
    }


   }
}
void arrowu() //YUKARI OK
{
    if(y>1){
    y--;
    gotoxy(x,y);
    }
}
void arrowd() //ASAGI OK
{
  if(total_ch>y*x){
  if(y>=1){
  y++;
  gotoxy(x,y);
  }
  else
    gotoxy(x,y);
  }

}
void tab() //TAB TUSU
{   int i;
	for ( i = 0; i < 8; i++)
	{
		add(' ');
	}
	writeScreen();
}


void enter() //ENTER TUSU
{
int i;
for(i=x;i<=80;i++){
    add(' ');
}

    writeScreen();
    gotoxy(1,y);

}
void space() //BOSLUK TUSU
{
    add(' ');
    writeScreen();
    gotoxy(x,y);
}
void writeFile() //ELEMANLARI DOSYAYA YAZMA
{
            fp = fopen(name,"w+");
            while(head != NULL)
            {
            fputc(head->data,fp);
                head = head->next;
            }

}
void writeScreen() //ELEMANLARI EKRANA YAZMA
{           if(y<26 && a==1){
            system("cls");
            list *temp2 = head;
            while(temp2 != NULL)
            {
                printf("%c", temp2->data);
                temp2 = temp2->next;
            }
            }
            else
            {
            writeScreen2();
            a++;
            }
}
void writeScreen2() //SAYFA DEGISIMI
{
            if(a==2)
            {
                x=0;
                y=0;
                total_ch=0;
                gotoxy(x,y);

            }
            system("cls");
            int i;
            list *temp2 = head;
            if(a>=2){
            for(i=1;i<2000;i++)
                temp2=temp2->next;
            }

            while (temp2!=NULL){
              printf("%c", temp2->data);
              temp2=temp2->next;
            }


}
void openFile(char *name)
{
    if(fp==NULL){
        fp = fopen(name,"w+");
    }
    else{

        int i = 0;

        for(i=0;!feof(fp);i++)
        {
            char a;
            a=fgetc(fp);

                if(head == NULL)
                {
                    newNode =malloc(sizeof(list));
                    newNode->data = a;
                    newNode->next = NULL;
                    newNode->prev = NULL;
                    head = newNode;
                    tail = newNode;
                    iter=head;

                    if(x!=80)
                       x++;
                    else{
                         x=1;
                         y++;

                   }
                     total_ch++;



                }
                else
                {

                    while(iter->next != NULL)
                    {
                        iter = iter->next;
                    }

                    newNode = malloc(sizeof(list));
                    newNode->data = a;
                    newNode->next = NULL;
                    iter->next = newNode;
                    tail = newNode;
                    newNode->prev=iter;



                    if(x!=80)
                      x++;
                    else{
                      x=1;
                      y++;

                    }
                    total_ch++;

                }
        }
      }

}
int main()
{

      int w;
      printf("Text Editor (Cikmak icin ESC tusuna basiniz)\n\n");
      printf("Yeni dosya=1 \n");
      printf("Dosya acma=2 \n\n");
      printf("Seciminiz:");
      scanf("%d", &w);
      printf("Dosyanin ismi:");
      scanf("%s", &name);

      fp=fopen(name,"r+"); //DOSYA ACMA
      if(w==2)
      {
         openFile(name);
      }
      writeScreen();
      while (!data.esc) //SUREKLI GIRIS ALMA
      {
      input();
      }
      int q;
      printf("\n\nKaydedilsin mi?");
      printf("  (1=EVET 2=HAYIR) :");
      scanf("%d", &q);

      if(q==1)
        writeFile();

      fclose(fp);

    return 0;
}
