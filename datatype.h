#ifndef DATATYPE_H
#define DATATYPE_H

#define ADDRNUM 20
#define DATANUM 16
#define SEC 1000

static int sClock = 0;//仿真时钟
namespace MicroCom{
//引脚号
enum Pins{
    AD1=0,
    AD2=1,
    AD3=2,
    AD4=3,
    AD5=4,
    AD6=5,
    AD7=6,
    AD8=7,
    AD9=8,
    AD10=9,
    AD11=10,
    AD12=11,
    AD13=12,
    AD14=13,
    AD15=14,
    AD16=15,
    AS17=16,
    AS18=17,
    AS19=18,
    AS20=19,
    rd=20,
    wr=21,
    Mio=22,
    ALE=23,
    DTr=24,
    den=25,
    bhe=26,
    NMI=27,
    INTR=28,
    inta=29,
    READY=30,
    RESET=31,
    test=32,
    CLK=33,
    gnd=50,
    vcc=51
};

//内部寄存器号
enum Regs{
    ax=1,
    bx=2,
    cx=3,
    dx=4,
    cs=5,
    ds=6,
    es=7,
    ss=8,
    ip=9,
    flags=10,
    bp=11,
    sp=12,
    si=13,
    di=14,
    io=15,   //8255A
    ct=16,  //counter 8253/8254
    al=17,
    bl=18,
    cl=19,
    dl=20,
    ah=21,
    bh=22,
    ch=23,
    dh=24
};

enum RegsLen{
    dbyte=16,
    byte=8
};

enum Mode{
    write,
    read
};

enum ClockType{
    lowPulse=0,
    highPulse=1
};

}

//引脚电平
enum Voltage{
    high=5,
    low=0,
    himped=-1
};


#endif // DATATYPE_H
