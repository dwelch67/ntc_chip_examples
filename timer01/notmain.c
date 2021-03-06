
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void ASMDELAY ( unsigned int );
extern void uart_init(void);
extern void hexstrings ( unsigned int );
extern void hexstring ( unsigned int );



#define ATMRCTL   0x01C20C10
#define ATMRLD    0x01C20C14
#define ATMRCV    0x01C20C18

#define ASYNC_TMR_BASE 0x01C20C00
#define ASYNC_TMR_CTRL_REG (ASYNC_TMR_BASE+0x10)
#define ASYNC_TMR_INTV_VALUE_REG (ASYNC_TMR_BASE+0x14)
#define ASYNC_TMR_CURNT_VALUE_REG (ASYNC_TMR_BASE+0x18)

//-------------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;
    uart_init();
    hexstring(0x12345678);

    PUT32(ATMRCTL,0);
    PUT32(ATMRLD,0xFFFFFFFF);
    PUT32(ATMRCTL,7);

    if(0)
    {
        ra=0;
        while(1)
        {
            rb=GET32(ATMRCV);
            if(rb!=ra)
            {
                ra=rb;
                hexstring(rb);
            }
        }
    }
    if(1)
    {
        ra=0;
        while(1)
        {
            rb=GET32(ATMRCV);
            if((rb&0xF0000000)!=(ra&0xF0000000))
            {
                ra=rb;
                hexstring(rb);
            }
        }
    }

    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
