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


TlcSerial::TlcSerial( const string &serialDevicePath, int numTlcs )
{
    mSerialDevicePath   = serialDevicePath;
    mSerial             = nullptr;
    mDataPacket         = new unsigned char[DATA_PACKET_SIZE];
    mNumTlcs            = min( numTlcs, MAX_NUM_TLCS );
    
    setZeros();

    // Initialised Serial
    try
    {
        Serial::Device dev  = Serial::findDeviceByNameContains( mSerialDevicePath );
        mSerial             = new Serial( dev, BAUD_RATE );
        
        console() << "Connected to serial device: " << mSerialDevicePath << endl;
    }
    catch ( ... )
    {
        console() << "Cannot connect to serial device: " << mSerialDevicePath << endl;
        exit(-1);
    }
}


TlcSerial::~TlcSerial()
{
    delete []mDataPacket;
}


void TlcSerial::setZeros()
{
    memset (mDataPacket, 0 ,DATA_PACKET_SIZE);
}


void TlcSerial::setValue( int ch, float valNorm )
{
    if ( ch >= mNumTlcs * TLC_NUM_CHANNELS )
        return;
    
    uint16_t val            = TLC_MAX_VALUE * valNorm;
    mDataPacket[ch*2]       = ( val & 0xFF00 ) >> 8;        // high byte
    mDataPacket[ch*2+1]     = val & 0x00FF;                 // low byte
}


void TlcSerial::sendData()
{
    if ( mSerial )
        mSerial->writeBytes( mDataPacket, mNumTlcs * TLC_NUM_CHANNELS * 2 );
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

