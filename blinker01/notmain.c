
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void ASMDELAY ( unsigned int );
extern void uart_init(void);
extern void hexstrings ( unsigned int );
extern void hexstring ( unsigned int );
extern unsigned int MIDR ( void );
extern unsigned int ID_PFR0 ( void );
extern unsigned int ID_PFR1 ( void );
extern unsigned int ID_DFR0 ( void );
extern unsigned int ID_AFR0 ( void );

#define ATMRCTL   0x01C20C10
#define ATMRLD    0x01C20C14
#define ATMRCV    0x01C20C18

#define UART_THR 0x01C28400

#define PA_DAT 0x01C20810
#define PB_DAT 0x01C20834
#define PC_DAT 0x01C20858
#define PD_DAT 0x01C2087C
#define PE_DAT 0x01C208A0
#define PF_DAT 0x01C208C4
#define PG_DAT 0x01C208E8

#define PB_CFG0 0x01C20824
#define PD_CFG0 0x01C2086C

//-------------------------------------------------------------------------
int notmain ( unsigned int sp )
{
    unsigned int ra,rb,rc;

    uart_init();
    hexstring(0x12345678);

    PUT32(PD_CFG0,0x100);

    PUT32(ATMRCTL,0);
    PUT32(ATMRLD,0xFFFFFFFF);
    PUT32(ATMRCTL,7);

    ra=GET32(ATMRCV);
    while(1)
    {
        while(1)
        {
            rb=GET32(ATMRCV);
            rc=ra-rb;
            if(rc>=24000000) break;
        }
        PUT32(PD_DAT,4);
        PUT32(UART_THR,0x55);
        while(1)
        {
            ra=GET32(ATMRCV);
            rc=rb-ra;
            if(rc>=24000000) break;
        }
        PUT32(PD_DAT,0);
        PUT32(UART_THR,0x56);
    }
    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
