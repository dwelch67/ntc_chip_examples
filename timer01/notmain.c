
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void ASMDELAY ( unsigned int );
extern void uart_init(void);
extern void hexstrings ( unsigned int );
extern void hexstring ( unsigned int );


#define ASYNC_TMR_BASE 0x01C20C00

#define ASYNC_TMR_CTRL_REG (ASYNC_TMR_BASE+0x10)
#define ASYNC_TMR_INTV_VALUE_REG (ASYNC_TMR_BASE+0x14)
#define ASYNC_TMR_CURNT_VALUE_REG (ASYNC_TMR_BASE+0x18)


#define SYNC_TMR_BASE 0x01C60000
#define SYNC_TMR0_CTRL_REG (SYNC_TMR_BASE+0x10)
#define SYNC_TMR0_INTV_LO_REG (SYNC_TMR_BASE+0x14)
#define SYNC_TMR0_INTV_HI_REG (SYNC_TMR_BASE+0x18)
#define SYNC_TMR0_CURNT_LO_REG (SYNC_TMR_BASE+0x1C)
#define SYNC_TMR0_CURNT_HI_REG (SYNC_TMR_BASE+0x20)
#define AHB_GATING_REG0 0x01C20060
//-------------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;
    uart_init();
    hexstring(0x12345678);
    PUT32(ASYNC_TMR_CTRL_REG,0);
    PUT32(ASYNC_TMR_INTV_VALUE_REG,0xFFFFFFFF);
    PUT32(ASYNC_TMR_CTRL_REG,7);
    if(0)
    {
        ra=0;
        while(1)
        {
            rb=GET32(ASYNC_TMR_CURNT_VALUE_REG);
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
            rb=GET32(ASYNC_TMR_CURNT_VALUE_REG);
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
