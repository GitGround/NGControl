#include "MavLinkProtocol.h"
#include <Driver/SerialPortLink.h>
#include <QDebug>

MAVLinkProtocol::MAVLinkProtocol() {

}

MAVLinkProtocol::~MAVLinkProtocol() {

}

void MAVLinkProtocol::setCurrentPortName(QString currentPortName) {
    serialPortName = currentPortName;
}

void MAVLinkProtocol::sendMessage(mavlink_message_t message) {
    // Create buffer
    static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    // Rewriting header to ensure correct link ID is set
    static uint8_t messageKeys[256] = MAVLINK_MESSAGE_CRCS;
    //if (link->getId() != 0)
    mavlink_finalize_message_chan(&message, systemId, componentId, linkId,
            message.len, messageKeys[message.msgid]);
    // Write message into buffer, prepending start sign
    int len = mavlink_msg_to_send_buffer(buffer, &message);


    serialPortLink.setCurrentPortName(serialPortName);
    serialPortLink.writeBytes((const char*) buffer, len);  //send data and data length to be written at serial port

    /*
    [#Example]: for declearing new object, just for further REF

    SerialPortLink* serialLink = new SerialPortLink(serialPortName);

    */

}

void MAVLinkProtocol::sendHeartbeat() {
    mavlink_message_t beat;
    //default for now: systemId = 255; ComponentID = 0;
    mavlink_msg_heartbeat_pack(255, 0, &beat, MAV_TYPE_GCS,
            MAV_AUTOPILOT_INVALID, MAV_MODE_MANUAL_ARMED, 0, MAV_STATE_ACTIVE);
    sendMessage(beat);
}

bool MAVLinkProtocol::isConnected(){
return serialPortLink.isConnected();
}

