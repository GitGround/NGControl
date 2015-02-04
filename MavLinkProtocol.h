#ifndef MAVLINKPROTOCOL_H
#define MAVLINKPROTOCOL_H

#include <mavlink.h>
#include <SerialLink.h>  //for serial port and thread communication class
class MAVLinkProtocol
{
public:
    MAVLinkProtocol();
    ~MAVLinkProtocol();
     void sendHeartbeat();
     void setCurrentPortName(QString currentPortName);
     QString serialPortName;
     bool isConnected();

private:
     void sendMessage(mavlink_message_t message);

     //just set as default for now
     static const int systemId = 255;
     static const int componentId = 0;
     static const int linkId = 1;
     SerialLink serialLink; //for serial port and thread communication class

};

#endif // MAVLINKPROTOCOL_H
