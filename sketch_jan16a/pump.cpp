#pragma once // dette sørger for at pump.cpp, kun inkluderes én gang - virker på samme måde som en #ifndef som #include guard

#include "enums.h"
#include "Arduino.h" //for at få digitalWrite til at fungere herinde

class Pump {
  private:
    long period = 10000; //delayet (ms) mellem pumpe intervaller
    Status stat = OFF;

    void start_pump() {
        stat = ON;
        digitalWrite(6, HIGH);
    }

    void stop_pump() {
        stat = OFF;
        digitalWrite(6, LOW);
    }


  public:
    Status get_status() {
      return stat;
    }

    void changeCycle() {
      if (stat == ON) {
        stop_pump();
      } else {
        start_pump();
      }
    }
};