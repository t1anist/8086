#ifndef DATATYPE_H
#define DATATYPE_H

#define ADDRNUM 20
#define DATANUM 16

/** 常量 **/
const short SEC = 1000;
const short LATCH_PIN_NUM = 18;
const short CPU_PIN_NUM = 36;
const short CPU_REG_NUM = 14;
const short DECODER_PIN_NUM = 14;
const short BUFFER_PIN_NUM = 18;

namespace MicroCom{

//引脚号
enum Pins{
    /** CPU-Pins(1-33) **/
    CP_AD0=0,
    CP_AD1=1,
    CP_AD2=2,
    CP_AD3=3,
    CP_AD4=4,
    CP_AD5=5,
    CP_AD6=6,
    CP_AD7=7,
    CP_AD8=8,
    CP_AD9=9,
    CP_AD10=10,
    CP_AD11=11,
    CP_AD12=12,
    CP_AD13=13,
    CP_AD14=14,
    CP_AD15=15,
    CP_AS16=16,
    CP_AS17=17,
    CP_AS18=18,
    CP_AS19=19,
    CP_rd=20,
    CP_wr=21,
    CP_Mio=22,
    CP_ALE=23,
    CP_DTr=24,
    CP_den=25,
    CP_bhe=26,
    CP_NMI=27,
    CP_INTR=28,
    CP_inta=29,
    CP_READY=30,
    CP_RESET=31,
    CP_test=32,
    CP_CLK=33,
    /** Latch-Pins(40-57) **/
    LA_DI0=40,
    LA_DI1=41,
    LA_DI2=42,
    LA_DI3=43,
    LA_DI4=44,
    LA_DI5=45,
    LA_DI6=46,
    LA_DI7=47,
    LA_DO0=48,
    LA_DO1=49,
    LA_DO2=50,
    LA_DO3=51,
    LA_DO4=52,
    LA_DO5=53,
    LA_DO6=54,
    LA_DO7=55,
    LA_G=56,
    LA_oe=57,

    /** Decoder-Pins(60-73) **/
    DE_G1=60,
    DE_G2a=61,
    DE_G2b=62,
    DE_C=63,
    DE_B=64,
    DE_A=65,
    DE_y0=66,
    DE_y1=67,
    DE_y2=68,
    DE_y3=69,
    DE_y4=70,
    DE_y5=71,
    DE_y6=72,
    DE_y7=73,

    /** Buffers244-Pins(80-97) **/
    BF4_1I1=80,
    BF4_1I2=81,
    BF4_1I3=82,
    BF4_1I4=83,
    BF4_1O1=84,
    BF4_1O2=85,
    BF4_1O3=86,
    BF4_1O4=87,
    BF4_2I1=88,
    BF4_2I2=89,
    BF4_2I3=90,
    BF4_2I4=91,
    BF4_2O1=92,
    BF4_2O2=93,
    BF4_2O3=94,
    BF4_2O4=95,
    BF4_Ga=96,
    BF4_Gb=97,

    /** Buffers245-Pins(100-117) **/
    BF5_A0=100,
    BF5_A1=101,
    BF5_A2=102,
    BF5_A3=103,
    BF5_A4=104,
    BF5_A5=105,
    BF5_A6=106,
    BF5_A7=107,
    BF5_B0=108,
    BF5_B1=109,
    BF5_B2=110,
    BF5_B3=111,
    BF5_B4=112,
    BF5_B5=113,
    BF5_B6=114,
    BF5_B7=115,
    BF5_DIR=116,
    BF5_g=117
};

//寄存器号
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
    io=15,      //8255A
    ct=16,      //counter 8253/8254
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

enum ClockType{
    lowPulse=0,
    highPulse=1
};

}

//引脚电平
enum Voltage{
    high=5,
    low=0,
    inf=-1
};

//模板类，用于类的计数
template<typename T>
class Counter {
public:
    Counter() { ++count; }
    Counter(const Counter&) { ++count; }
    ~Counter() { --count; }
    static int howMany()
    { return count; }

private:
    static int count;
};

template<typename T>
int
Counter<T>::count = 0; // this now can go in header


#endif // DATATYPE_H
