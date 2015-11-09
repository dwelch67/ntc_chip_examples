
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

//-------------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    
    uart_init();
    hexstring(0x12345678);
    while(1)
    {
        ra=uart_recv();
        if(ra==0x0D) uart_send(0x0A);
        uart_send(ra);
    }
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
