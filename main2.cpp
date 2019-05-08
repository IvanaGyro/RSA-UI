#include "mainwindow.h"
#include <QApplication>
#include <bigint.h>
#include <iostream>

#include<time.h>

Bigint power(Bigint a, Bigint b, Bigint c)
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

int mr(Bigint n)
{
    int c=0,temp=0,i=0;
    if (n < 2){
        return 0;
    }
    Bigint a(n.getbytes4_num()*32),u(n.getbytes4_num()*32),x(n.getbytes4_num()*32),sq(n.getbytes4_num()*32);
    sq=2;
    while(c<1){
        temp=c;
        i=0;
        /*a.random();
        a %= (n-1);
        while(a<2){
            a.random();
            a %= (n-1);
        }*/
        a=12;
        u = n-1;
        int t = 0;
        while (u % 2 == 0) {
            u >>= 1;
            t++;
        }
        //u.print_bin();
        //printf("%d",t);
        x = power(a, u, n);   // x = a ^ u % n;
        if (x == 1 || x == n-1)
            return 1;
        while(i<t-1){
            x = power(x, sq , n);   // x = x * x % n;
            //x.print_bin();
            if (x == 1){
                return 0;
            }
            if (x == (n-1)){
                c++;
                if(c==1)
                    return 1;
                break;
            }
            i++;
        }
        if(c==temp){
            //printf("%d",c);
            return 0;
        }
    }
}

Bigint CRT(Bigint p,Bigint q,Bigint d,Bigint x,Bigint &cp,Bigint &cq)
{
    Bigint dp(p.getbytes4_num()*32),dq(q.getbytes4_num()*32),xp(p.getbytes4_num()*32),xq(q.getbytes4_num()*32);
    Bigint yp(p.getbytes4_num()*32),yq(q.getbytes4_num()*32)/*,cp(p.getbytes4_num()*32),cq(q.getbytes4_num()*32)*/;
    dp=d%(p-1);
    //dp.print_bin();
    dq=d%(q-1);
    xp=x%p;
    xq=x%q;
    yp=power(xp,dp,p);
    yq=power(xq,dq,q);
    if(cp==0&&cq==0){
        cp=power(q,(p-2),p);
        cq=power(p,(q-2),q);
    }
    //cp.print_bin();
    return (q*cp*yp+p*cq*yq)%(p*q);
}

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);

   Bigint p(64),q(64),r(p.getbytes4_num()*64),e(r.getbytes4_num()*32),d(r.getbytes4_num()*32);
   Bigint m(r.getbytes4_num()*32),n(r.getbytes4_num()*32),c(r.getbytes4_num()*32);
   Bigint m2(r.getbytes4_num()*32);
   /*p.random();
   while(mr(p)==0)
       p.random();
   q.random();
   while(mr(q)==0)
       q.random();*/
   p=5;
   q=7;
   n=p*q;
   r=(p-1)*(q-1);
   e=3;
   d=power(e,(r-2),r);
   c=power(m,e,n);
   m2=power(c,d,n);
   d.print_bin();





   return 0;

   //return a.exec();
}

