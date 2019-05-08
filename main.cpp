#include "mainwindow.h"
#include <QApplication>

/*Bigint power(Bigint a, Bigint b, Bigint c)
{
  Bigint temp(32);
  if (b == 0){
    temp=1;
    return temp;
  }
  else if (b == 1)
    return a;
  // k >=2
  Bigint f(b.getbytes4_num()*32),s(a.getbytes4_num()*64);
  f=0;
  *(f.getnum()+f.getbytes4_num()-1)=0x80000000;

  s=1;
  while((f&b)==0){//find first 1
    f>>=1;
  }
  while((!(f==0))){
       s=s*s;
       s %= c;
     if(!((f&b)==0)){
     s=a*s;
     s %= c;
     }
     f>>=1;
  }
  return s;
}
*/
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);



   MainWindow w;
   w.show();

   /*

   Bigint bb(64), cc(32), dd(96);
   bb.random();
   cc.random();
   bb.print_bin();
   cc.print_bin();
   bb &= cc;
   bb.print_bin();
   */

   return a.exec();
}





