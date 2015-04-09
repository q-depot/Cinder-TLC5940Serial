/*
 *  TlcSerial.cpp
 *
 *  Created by Andrea Cuius
 *  The MIT License (MIT)
 *  Copyright (c) 2015 Nocte Studio Ltd.
 *
 *  www.nocte.co.uk
 *
 */

#include "cinder/app/App.h"
#include "TlcSerial.h"

using namespace ci;
using namespace ci::app;
using namespace std;


TlcSerial::TlcSerial( const string &deviceName, int numTlcs )
{
    mSerialDeviceName   = deviceName;
    mSerial             = nullptr;
    mNumTlcs            = min( numTlcs, TLC_MAX_NUM_DEVICES );
    mDataPacketSize     = mNumTlcs * TLC_NUM_CHANNELS * 2 + 1;      // data + 1 cmd byte
    mDataPacket         = new unsigned char[ mDataPacketSize ];
    
    setZeros();

    // Initialised Serial
    try
    {
        Serial::Device dev  = Serial::findDeviceByNameContains( mSerialDeviceName );
        mSerial             = new Serial( dev, TLC_BAUD_RATE );
        
        console() << "Connected to serial device: " << mSerialDeviceName << endl;
    }
    catch ( ... )
    {
        console() << "Cannot connect to serial device: " << mSerialDeviceName << endl;
        exit(-1);
    }
}


TlcSerial::~TlcSerial()
{
    memset( mDataPacket, 0 ,mDataPacketSize );
    
    if ( mSerial )
        mSerial->writeBytes( mDataPacket, mDataPacketSize );
    
    delete []mDataPacket;
}


void TlcSerial::setZeros()
{
    memset( mDataPacket, 0 ,mDataPacketSize );
    
    mDataPacket[0] = TLC_CMD_BYTE;
}


void TlcSerial::setValue( int ch, float valNorm )
    {   
    if ( ch >= mNumTlcs * TLC_NUM_CHANNELS )
        return;
    
    uint16_t val            = TLC_MAX_VALUE * valNorm;
    mDataPacket[1+ch*2]     = ( val >> 7 ) & TLC_DATA_BYTE;        // high byte
    mDataPacket[1+ch*2+1]   = val & TLC_DATA_BYTE;                 // low byte
}


void TlcSerial::sendData()
{
    if ( mSerial )
        mSerial->writeBytes( mDataPacket, mDataPacketSize );
}


void TlcSerial::listDevices()
{
    console() << "--- List serial devices ---" << endl;
    
    std::vector<Serial::Device> devices = Serial::getDevices(true);
    for( vector<Serial::Device>::const_iterator deviceIt = devices.begin(); deviceIt != devices.end(); ++deviceIt )
        console() << deviceIt->getPath() << endl;
    
    console() << "---------------------------" << endl;
}


vector<std::string> TlcSerial::getDevicesList()
{
    vector<string> devicesList;
    
    const vector<Serial::Device> &devices( Serial::getDevices(true) );
    
    for( vector<Serial::Device>::const_iterator deviceIt = devices.begin(); deviceIt != devices.end(); ++deviceIt )
        devicesList.push_back( deviceIt->getPath() );
    
    return devicesList;
}

