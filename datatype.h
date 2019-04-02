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

}

//引脚电平
enum Voltage{
    high=5,
    low=0,
    himped=-1
};


#endif // DATATYPE_H
