/* Copyright (C) 2019-2020 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT). */

#include "MWutls.h"

using namespace TWE;

// Serial Writer Object
TWE_PutChar_Serial<HardwareSerial> TWE::WSer(Serial); // Serial Writer for Serial
#ifdef ESP32
TWE_PutChar_Serial<HardwareSerial> TWE::WSer2(Serial2); // Serial Writer for Serial2
#endif