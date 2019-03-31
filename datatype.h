#ifndef DATATYPE_H
#define DATATYPE_H

namespace MicroCom{
//引脚号
enum Pins{
    AD1=1,
    AD2=2,
    AD3=3,
    AD4=4,
    AD5=5,
    AD6=6,
    AD7=7,
    AD8=8,
    AD9=9,
    AD10=10,
    AD11=11,
    AD12=12,
    AD13=13,
    AD14=14,
    AD15=15,
    AD16=16,
    AS17=17,
    AS18=18,
    AS19=19,
    AS20=20,
    rd=21,
    wr=22,
    Mio=23,
    ALE=24,
    DTr=25,
    den=26,
    bhe=27,
    NMI=28,
    INTR=29,
    inta=30,
    READY=31,
    RESET=32,
    test=33,
    CLK=34,
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
    bp=9,
    sp=10,
    si=11,
    di=12,
    ip=13,
    flags=14,
    al=15,
    bl=16,
    cl=17,
    dl=18,
    io=19,   //8255A
    ct=20,  //counter 8253/8254
    ah=30,
    bh=31,
    ch=32,
    dh=33
};

enum RegsLen{
    dbyte=16,
    byte=8
};
}

//引脚电平
enum Voltage{
    high=5,
    low=0,
    himped=-1
};


#endif // DATATYPE_H
