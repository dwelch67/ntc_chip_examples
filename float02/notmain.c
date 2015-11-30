
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
extern unsigned int ifdummy ( float );
extern float fdummy ( float );
extern float vdiv ( float, float );
extern unsigned int ftoi ( float );
extern float itof ( unsigned int );

//-------------------------------------------------------------------------
int notmain ( void )
{
    uart_init();
    hexstring(0x12345678);
    hexstring(ifdummy(1.0F));
    hexstring(ifdummy(2.0F));
    hexstring(ifdummy(3.0F));
    hexstring(ifdummy(1234.0F));
    hexstring(ifdummy(1.2F));
    hexstring(ifdummy(vdiv(1234.0F,1.20F)));
    hexstring(ftoi(vdiv(1234.0F,1.20F)));
    hexstring(ftoi(1234.0F/1.20F));
    hexstring(ftoi(1234.0F/fdummy(1.20F)));
    hexstring(1234.0F/fdummy(1.20F));
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
