#Cinder-TLC5940Serial
CinderBlock for the [SparkFun LED Driver Breakout - TLC5940 (16 Channel)](https://www.sparkfun.com/products/10616) controlled with Arduino over the serial port.

Cinder-TLC5940Serial works with the Arduino sketch included in this repository.  
`TlcParser` simply send serial data, the Arduino sketch parse the data and send it to the TLCs.

At the moment the `numTlcs` variable used to initialised `TlcSerial`, __must__ match the `numTlcs` variable set in the Arduino sketch at line #59.

###Arduino and TLC 5940 tutorial
http://bildr.org/2012/03/servos-tlc5940-arduino/

##Get the code
```
cd CINDER_PATH/blocks  
git clone git@github.com:q-depot/Cinder-TLC5940Serial.git
```

##How to use it

```C++

#include "TlcSerial.h"

// ..
TlcSerialRef        mTlcSerial;


void BasicApp::setup()
{
	// list the available serial devices
    TlcSerial::listDevices();

    // this MUST match the numTlcs in the Arduino sketch
    int numTlcs			= 1;				

   	// the serial device name(accepts full or partial name)
    string deviceName 	= "tty."			
    
    mTlcSerial			= TlcSerial::create( deviceName numTlcs );
}

void BasicApp::update()
{
    float val;

    // set some channel data
    for( auto ch=0; ch < mTlcSerial->getNumChannels(); ch++ )
    {
    	val = 1.0f;							
        mTlcSerial->setValue( ch, val );        // set the value(normalised)
    }
    
    // send serial data
    mTlcSerial->sendData();
}
```

--

### License
The MIT License (MIT)

Copyright (c) 2015 Nocte Studio Ltd. - [www.nocte.co.uk](http://www.nocte.co.uk)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.