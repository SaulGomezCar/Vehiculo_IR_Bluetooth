//LIBRERIAS-----------------------------------------------------------------------------
#include <IRremote.h>
#include "Motores.h"
//PINES---------------------------------------------------------------------------------
IRrecv IR(15);
//SETUP---------------------------------------------------------------------------------
void IR_setup(){
  IR.enableIRIn();
  Serial.println("<-Inicializado Recepción de Señales IR: PIN 15->");  
}
//FUNCIONES-----------------------------------------------------------------------------
void RecibirIR(){
  if (IR.decode()) {
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    switch (IR.decodedIRData.decodedRawData) {
      case 0x9F600707:
        MoverMotores(velocidad,CW,CW);
        EncenderLED(ledUR);
        EncenderLED(ledUL);
        break;
      case 0x9E610707:
        MoverMotores(velocidad,CCW,CCW);
        EncenderLED(ledDR);
        EncenderLED(ledDL);
        break;
      case 0x9D620707:
        MoverMotores(velocidad,CW,CCW);
        EncenderLED(ledUR);
        EncenderLED(ledDR);
        break;
      case 0x9A650707:
        MoverMotores(velocidad,CCW,CW);
        EncenderLED(ledUL);
        EncenderLED(ledDL);
        break;
      case 0xFB040707:
        ApagarLEDVel();
        velocidad = 37;
        EncenderLED(ledLOW);
        break;
      case 0xFA050707:
        ApagarLEDVel();
        velocidad = 44;
        EncenderLED(ledMID);
        break;
      case 0xF9060707:
        ApagarLEDVel();
        velocidad = 99;
        EncenderLED(ledHIGH);
        break;
      case 0xA7580707:
        Servominus();
        Serial.println(servoPositionTarget);
        break;
      case 0xD22D0707:
        Servoplus();
        Serial.println(servoPositionTarget);
        break;
      case 0xB44B0707:
        GradosServo(0);
        Serial.println(servoPositionTarget);
        break;
      case 0x738C0707:
        GradosServo(45);
        Serial.println(servoPositionTarget);
        break;
      case 0xE51A0707:
        GradosServo(90);
        Serial.println(servoPositionTarget);
        break;
      case 0xFC030707:
        GradosServo(135);
        Serial.println(servoPositionTarget);
        break;
      case 0xE01F0707:
        GradosServo(180);
        Serial.println(servoPositionTarget);
        break;
      case 0x936C0707:
        Bailar();
        break;
      case 0xEB140707:
        Negar();
        break;
      case 0xEA150707:
        Demo_Velocidad();
        break;
      case 0xEC130707:
        GirarDerecha();
        break;
      case 0xDC230707:
        GirarIzquierda();
        break;
      default:
        Stop(); // Detenerse por defecto si se recibe un comando desconocido
        break;
    }
    IR.resume(); // Receive the next value
  }
  delay(100);
}
