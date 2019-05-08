#ifndef FUNC_BIGINT_H
#define FUNC_BIGINT_H

#include <Bigint.h>

class Func_Bigint
{
public:
    Func_Bigint();
    static Bigint power(const Bigint&,const Bigint&,const Bigint&);
    static int mr(const Bigint& n, unsigned int times);
    static Bigint CRT(Bigint p,Bigint q,Bigint d,Bigint x,Bigint &cp,Bigint &cq);
    static Bigint xGCD(Bigint a, Bigint b, Bigint &x, Bigint &y, bool& xp, bool& yp);
};

#endif // FUNC_BIGINT_H
