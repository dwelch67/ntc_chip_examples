
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void ASMDELAY ( unsigned int );
extern void uart_init(void);
extern void hexstrings ( unsigned int );
extern void hexstring ( unsigned int );

//-------------------------------------------------------------------------
int notmain ( unsigned int sp )
{
    uart_init();
    hexstring(0x12345678);
    hexstring(sp);
    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
