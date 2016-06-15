
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

#define SCL 0
#define SDA 1

//#define SCL 2
//#define SDA 3


static void i2c_delay ( void )
{
    ASMDELAY(1);
}
static void scl_high ( void )
{
    unsigned int ra;

    ra=GET32(PB_DAT);
    ra|=(1<<SCL);
    PUT32(PB_DAT,ra);
}
static void scl_low ( void )
{
    unsigned int ra;

    ra=GET32(PB_DAT);
    ra&=~(1<<SCL);
    PUT32(PB_DAT,ra);
}
static void sda_high ( void )
{
    unsigned int ra;

    ra=GET32(PB_DAT);
    ra|=(1<<SDA);
    PUT32(PB_DAT,ra);
}
static void sda_low ( void )
{
    unsigned int ra;

    ra=GET32(PB_DAT);
    ra&=~(1<<SDA);
    PUT32(PB_DAT,ra);
}

static void scl_out ( void )
{
    unsigned int ra;
    
    ra=GET32(PB_CFG0);
    ra&=~(7<<(SCL<<2));
    ra|=0x1<<(SCL<<2);  
    PUT32(PB_CFG0,ra);    
}
static void sda_out ( void )
{
    unsigned int ra;
    
    ra=GET32(PB_CFG0);
    ra&=~(7<<(SDA<<2));
    ra|=0x1<<(SDA<<2);  
    PUT32(PB_CFG0,ra);    
}
static void sda_in ( void )
{
    unsigned int ra;
    
    ra=GET32(PB_CFG0);
    ra&=~(7<<(SDA<<2));
    //ra|=0x0<<(SDA<<2);  
    PUT32(PB_CFG0,ra);    
}
static unsigned int sda_read ( void )
{
    return(GET32(PB_DAT)&(1<<SDA));
}

static void i2c_start ( void )
{
    scl_high();
    i2c_delay();
    sda_low();
    i2c_delay();
    scl_low();
    i2c_delay();
}
static void i2c_stop ( void )
{
    sda_low();
    i2c_delay();
    scl_high();
    i2c_delay();
    sda_high();
    i2c_delay();
}
static void i2c_one ( void )
{
    sda_high();
    i2c_delay();
    scl_high();
    i2c_delay();
    scl_low();
    i2c_delay();
    sda_low();
    i2c_delay();
}
static void i2c_zero ( void )
{
    sda_low();
    i2c_delay();
    scl_high();
    i2c_delay();
    scl_low();
    i2c_delay();
}
static unsigned int i2c_read ( void )
{
    unsigned int data;
    sda_in();
    i2c_delay();
    scl_high();
    i2c_delay();
    data=sda_read();
    i2c_delay();
    scl_low();
    i2c_delay();
    sda_out();
    i2c_delay();
    return(data);
}
//static unsigned int i2c_read_byte ( unsigned int addr, unsigned int reg )
//{
    //unsigned int rb;
    //unsigned int rc;
    //unsigned int rd;

    //rc=0;
   
    //i2c_start();
    //for(rb=0x40;rb;rb>>=1)
    //{
        //if(rb&addr) i2c_one(); else i2c_zero();
    //}
    //i2c_zero(); //write bit
    ////i2c_one(); //read bit
    //if(i2c_read())
    //{
    //}
    //else
    //{
        //rc++;
    //}
    //for(rb=0x80;rb;rb>>=1)
    //{
        //if(rb&reg) i2c_one(); else i2c_zero();
    //}
    //if(i2c_read())
    //{
    //}
    //else
    //{
        //rc++;
    //}
    //i2c_stop();

    //i2c_start();
    //for(rb=0x40;rb;rb>>=1)
    //{
        //if(rb&addr) i2c_one(); else i2c_zero();
    //}
    ////i2c_zero(); //write bit
    //i2c_one(); //read bit
    //if(i2c_read())
    //{
    //}
    //else
    //{
        //rc++;
    //}
    //rd=0;
    //for(rb=0;rb<8;rb++)
    //{
        //rd<<=1;
        //if(i2c_read()) rd|=1;
    //}
    ////if(i2c_read())
    ////{
    ////}
    ////else
    ////{
        ////rc++;
    ////}
    //i2c_one(); //master drives ack
    //i2c_stop();
    

////hexstrings(addr);
////hexstrings(reg);
////hexstrings(rd);
////hexstring(rc);
    //return(rd);
//}
    
static unsigned int i2c_write_byte ( unsigned int addr, unsigned int reg, unsigned int data )
{
    unsigned int rb;
    unsigned int rc;

    rc=0;
   
    i2c_start();
    for(rb=0x40;rb;rb>>=1)
    {
        if(rb&addr) i2c_one(); else i2c_zero();
    }
    i2c_zero(); //write bit
    //i2c_one(); //read bit
    if(i2c_read())
    {
    }
    else
    {
        rc++;
    }
    for(rb=0x80;rb;rb>>=1)
    {
        if(rb&reg) i2c_one(); else i2c_zero();
    }
    if(i2c_read())
    {
    }
    else
    {
        rc++;
    }
    for(rb=0x80;rb;rb>>=1)
    {
        if(rb&data) i2c_one(); else i2c_zero();
    }
    if(i2c_read())
    {
    }
    else
    {
        rc++;
    }
    i2c_stop();

//hexstrings(addr);
//hexstrings(reg);
//hexstring(rc);
    return(0);
}
  
//-------------------------------------------------------------------------
int notmain ( unsigned int sp )
{
    unsigned int ra,rb,rc;
    unsigned int addr;

    uart_init();
    hexstring(0x12345678);

    scl_out();
    sda_out();
    scl_high();
    sda_high();

//xdel=0x100000;

    i2c_delay();
    i2c_delay();
    i2c_delay();
    i2c_delay();
    i2c_delay();

    addr=0x34;

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
        i2c_write_byte(addr,0x93,0);
        PUT32(UART_THR,0x55);
        while(1)
        {
            ra=GET32(ATMRCV);
            rc=rb-ra;
            if(rc>=24000000) break;
        }
        i2c_write_byte(addr,0x93,7);
        PUT32(UART_THR,0x56);
    }


    hexstring(0x12345678);
    return(0);
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------------
