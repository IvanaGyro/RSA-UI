#include "func_bigint.h"
#include <iostream>

Func_Bigint::Func_Bigint()
{

}

Bigint Func_Bigint::power(const Bigint& a, const Bigint& b, const Bigint& c)
{
  Bigint temp(32);
  if (b == 0){
    temp=1;
    return Bigint(temp);
  }
  else if (b == 1){
      return a;
  }

  // k >=2
  Bigint f(b.getbytes4_num()*32),s(a.getbytes4_num()*64);
  f=0;
  *(f.getnum()+f.getbytes4_num()-1)=0x80000000;

  s=1;
  while((f&b)==0){//find first 1
      f>>=1;
  }
  while(!(f==0)){
       s=s*s;
       s %= c;
     if(!((f&b)==0)){
     s=a*s;
     s %= c;
     }
     f>>=1;
  }
  return Bigint(s);
}

int Func_Bigint::mr(const Bigint& n, unsigned int times)
{
    if ((n < 2) || ((n&1) == 0)){
        return 0;
    }
    if(n == 3) return 1;

    unsigned int c = 0, i = 0, t = 0;
    unsigned int a_list[5] = {2, 3, 5, 7, 11};
    Bigint a(n.getbytes4_num()*32),u(n.getbytes4_num()*32),x(n.getbytes4_num()*32),sq(n.getbytes4_num()*32);
    sq=2;

    u = n-1;
    while ((u&1) == 0) {
        u >>= 1;
        t++;
    }

    while(c<times){
        i=0;
        if(c < 5){
            a = a_list[c];
            a %= (n-1);
        }
        else{
            a.random();
            a %= (n-1);
            while(a < 2){
                a.random();
                a %= (n-1);
            }
        }
        x = power(a, u, n);   // x = a ^ u % n;
        if (x != 1 && x != n-1){
            while(i<t-1){
                x = power(x, sq , n);   // x = x * x % n;
                if (x == (n-1)) i = t-1;
                i++;
            }
            if (i == t-1) return 0;
        }
        c++;
    }
    return 1;
}

Bigint Func_Bigint::CRT(Bigint p,Bigint q,Bigint d,Bigint x,Bigint &cp,Bigint &cq)
{
    Bigint dp(p.getbytes4_num()*32),dq(q.getbytes4_num()*32),xp(p.getbytes4_num()*32),xq(q.getbytes4_num()*32);
    Bigint yp(p.getbytes4_num()*32),yq(q.getbytes4_num()*32)/*,cp(p.getbytes4_num()*32),cq(q.getbytes4_num()*32)*/;
    dp=d%(p-1);
    dq=d%(q-1);
    xp=x%p;
    xq=x%q;
    yp=power(xp,dp,p);
    yq=power(xq,dq,q);
    if(cp==0&&cq==0){
        cp=power(q,(p-2),p);
        cq=power(p,(q-2),q);
    }
    return (q*cp*yp+p*cq*yq)%(p*q);
}

Bigint Func_Bigint::xGCD(Bigint a, Bigint b, Bigint &x, Bigint &y, bool& xp, bool& yp) {
    if(b == 0) {
       x = 1;
       y = 0;
       xp = true;
       yp = true;
       return Bigint(a);
    }

    Bigint x1((a.getbytes4_num()+b.getbytes4_num())*32), y1((a.getbytes4_num()+b.getbytes4_num())*32);
    Bigint gcd((a.getbytes4_num()+b.getbytes4_num())*32);
    bool xp1, yp1;
    gcd = xGCD(b, a%b, x1, y1, xp1, yp1);

    x = y1;
    xp = yp1;
    Bigint a_b(a/b*y1);
    //y = x1 - (a / b) * y1;
    if(xp1 && yp1){
        if(a_b > x1){
            y = a_b - x1;
            yp = false;
        }
        else{
            y = x1 - a_b;
            yp = true;
        }
    }
    else if(xp1 && !yp1){
        y = x1 + a_b;
        yp = true;
    }
    else if(!xp1 && yp1){
        y = x1 + a_b;
        yp = false;
    }
    else{
        if(a_b > x1){
            y = a_b - x1;
            yp = true;
        }
        else{
            y = x1 - a_b;
            yp = false;
        }
    }

    return Bigint(gcd);
}

