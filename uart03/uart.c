
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void PUT32 ( unsigned int , unsigned int  );
unsigned int GET32 ( unsigned int );

//-------------------------------------------------------------------

#define UART_BASE 0x01C28400

#define UART_RBR (UART_BASE + 0x00 )
#define UART_THR (UART_BASE + 0x00 )
#define UART_DLL (UART_BASE + 0x00 )
#define UART_IER (UART_BASE + 0x04 )
#define UART_DLM (UART_BASE + 0x04 )
#define UART_FCR (UART_BASE + 0x08 )
#define UART_LCR (UART_BASE + 0x0C )
#define UART_MCR (UART_BASE + 0x10 )
#define UART_LSR (UART_BASE + 0x14 )
#define UART_MSR (UART_BASE + 0x18 )
#define UART_SCR (UART_BASE + 0x1C )

//-------------------------------------------------------------------
void uart_send ( unsigned int x )
{
    while (( GET32(UART_LSR) & 0x20) == 0) continue;
    PUT32(UART_THR,x);
}
//-------------------------------------------------------------------
unsigned int uart_recv ( void )
{
    while (( GET32(UART_LSR) & 0x01) == 0) continue;
    return(GET32(UART_RBR));
}
//-------------------------------------------------------------------
void uart_init(void)
{
}
//-------------------------------------------------------------------
void uart_fifo_flush ( void )
{
    while (( GET32(UART_LSR) & 0x40) == 0) continue;
}
//-------------------------------------------------------------------------
void hexstrings ( unsigned int d )
{
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}
//-------------------------------------------------------------------------
void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
