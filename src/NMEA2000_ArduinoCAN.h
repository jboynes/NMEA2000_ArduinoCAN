#if !defined(__NMEA2000_ARDUINOCAN__)
#define __NMEA2000_ARDUINOCAN__

#include "Arduino.h"
#include "Arduino_CAN.h"
#include <NMEA2000.h>

class tNMEA2000_ArduinoCAN : public tNMEA2000 {
protected:
    bool CANOpen() {
        return CAN.begin(CanBitRate::BR_250k);
    }

    bool CANSendFrame(unsigned long id, unsigned char len, const unsigned char *buf, bool wait_sent) {
        auto msg = CanMsg{CanExtendedId(id), len, buf};
        return CAN.write(msg) >= 0;
    }

    bool CANGetFrame(unsigned long &id, unsigned char &len, unsigned char *buf) {
        if (CAN.available()) {
            CanMsg msg = CAN.read();
            id = msg.id;
            len = msg.data_length;
            memcpy(buf, msg.data, len);
            return true;
        } else {
            return false;
        }
    }

};

tNMEA2000 &NMEA2000=*(new tNMEA2000_ArduinoCAN());
#endif