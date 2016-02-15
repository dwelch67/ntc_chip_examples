
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void ASMDELAY ( unsigned int );
extern void uart_init(void);
extern void hexstrings ( unsigned int );
extern void hexstring ( unsigned int );
extern void uart_send ( unsigned int );
extern unsigned int uart_recv ( void );
extern unsigned int CPSR ( void );


//------------------------------------------------------------------------
unsigned int next_prand ( unsigned int x )
{
    if(x&1)
    {
        x=x>>1;
        x=x^0xBF9EC099;
    }
    else
    {
        x=x>>1;
    }
    return(x);
}
//-------------------------------------------------------------------------
int notmain ( unsigned int sp )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int rx;

    unsigned int seed;
    unsigned int prand;
    
    uart_init();
    hexstring(0x12345678);
    hexstring(sp);
    hexstring(CPSR());

    seed=0x12345;
    for(rx=0;rx<10;rx++)
    {
        hexstrings(rx); hexstring(rx);
        prand=seed;
        for(ra=0x40000000;ra<0x50000000;ra+=4)
        {
            if((ra&0xFFFFFF)==0) hexstring(ra);
            prand=next_prand(prand);
            rb=prand;
            PUT32(ra,rb);
        }
        prand=seed;
        for(ra=0x40000000;ra<0x50000000;ra+=4)
        {
            if((ra&0xFFFFFF)==0) hexstring(ra);
            prand=next_prand(prand);
            rb=prand;
            rc=GET32(ra);
            if(rb!=rc)
            {
                hexstrings(ra);
                hexstrings(rc);
                hexstring(rb);
            }
        }
        prand=next_prand(prand);
        prand=next_prand(prand);
        prand=next_prand(prand);
        seed=prand;
    }
    

    
    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
