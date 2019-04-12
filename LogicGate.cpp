#include "LogicGate.h"

LogicGate::LogicGate(MicroCom::GateType type, QString gateName)
{
    QString temp;
    gateType=static_cast<int>(type);
    switch(type){
    case MicroCom::AND:
        temp="AND";
        break;
    case MicroCom::OR:
        temp="OR";
        break;
    case MicroCom::NOT:
        temp="NOT";
        pins[MicroCom::LG_I2-LG_START]=low;
        break;
    case MicroCom::NAND:
        temp="NAND";
        break;
    case MicroCom::NOR:
        temp="NOR";
        break;
    default:
        temp="XOR";
        break;
    }
    if(gateName==nullptr){
        gateName = temp+QString::number(c.howMany());
    }
    setHardwareName(gateName);
    for(int i=0;i<LGATE_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void LogicGate::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-LG_START]=value;
    emit pinVolChanged(pin);
}

Voltage LogicGate::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-LG_START];
}

void LogicGate::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-LG_START] = value;
    bool judge = true;;
    Voltage inputA = LogicGate::getPinVoltage(MicroCom::LG_I1);
    Voltage inputB = LogicGate::getPinVoltage(MicroCom::LG_I2);
    if(inputA == inf || inputB == inf){
        return;
    }
    qDebug()<<"==========="<<getHardwareName()<<"START===========";
    switch(gateType){
    case MicroCom::AND:
        judge = (inputA == high && inputB ==high);
        break;
    case MicroCom::OR:
        judge = (inputA == high || inputB ==high);
        break;
    case MicroCom::NOT:
        judge = (inputA == low);
        break;
    case MicroCom::NAND:
        judge = (inputA == low || inputB == low);
        break;
    case MicroCom::NOR:
        judge = (inputA == low && inputB == low);
        break;
    default:
        judge = (inputA != inputB);
        break;
    }
    if(judge==true){
        LogicGate::setPinVoltage(MicroCom::LG_O,high);
    }
    else{
        LogicGate::setPinVoltage(MicroCom::LG_O,low);
    }
    qDebug()<<"==========="<<getHardwareName()<<"END===========";
    return;
}
