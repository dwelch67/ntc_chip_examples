
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

//-------------------------------------------------------------------------
int notmain ( unsigned int sp )
{
    uart_init();
    hexstring(0x12345678);
    hexstring(sp);
    hexstring(MIDR());
    hexstring(ID_PFR0());
    hexstring(ID_PFR1());
    hexstring(ID_DFR0());
    hexstring(ID_AFR0());
    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
