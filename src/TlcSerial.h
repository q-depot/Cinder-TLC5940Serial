/*
 *  TlcSerial.h
 *
 *  Created by Andrea Cuius
 *  The MIT License (MIT)
 *  Copyright (c) 2015 Nocte Studio Ltd.
 *
 *  www.nocte.co.uk
 *
 */

#ifndef TLC5940_SERIAL
#define TLC5940_SERIAL

#pragma once

#include "cinder/Serial.h"

#define TLC_BAUD_RATE       115200
#define TLC_MAX_NUM_DEVICES 12                                      // max number of TLCs in the daisy chain
#define TLC_NUM_CHANNELS    16                                      // number of outputs for each TLC
#define TLC_MAX_VALUE       4095
#define TLC_CMD_BYTE        0x80
#define TLC_DATA_BYTE       0x7F
#define TLC_HIGH_BYTE       0xFF80


typedef std::shared_ptr<class TlcSerial> TlcSerialRef;


class TlcSerial{

public:
  
    static TlcSerialRef create( const std::string &serialDevicePath, int numTlcs = 1 )
    {
        return TlcSerialRef( new TlcSerial( serialDevicePath, numTlcs ) );
    }
    
	~TlcSerial();
    
    //! Set the normalised channel value
    void    setValue( int ch, float valNorm );

    //! Return the channel value normalised
    float   getValue( int ch );
    
    //! Send data to Arduino
    void sendData();

    //! Set all channels to zero
    void setZeros();

    //! Get the current device name
    std::string  getDeviceName() { return mSerialDeviceName; }
    
    //! Get the total number of TLCs
    uint8_t getNumTlcs() { return mNumTlcs; }
    
    //! Get the total number of channels
    uint8_t getNumChannels() { return mNumTlcs * TLC_NUM_CHANNELS; }
    
public:
    
    //! List the available serial devices
    static void listDevices();

    //! Get a list of the available serial devices
    static std::vector<std::string> getDevicesList();
    
private:
    
    TlcSerial( const std::string &serialDevicePath, int numTlcs );

private:
    
    uint8_t             *mDataPacket;
    uint8_t             mDataPacketSize;
    ci::Serial          *mSerial;
    std::string         mSerialDeviceName;		// usb serial device name
    uint8_t             mNumTlcs;

};


#endif

