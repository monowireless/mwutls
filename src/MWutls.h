#pragma once

/* Copyright (C) 2019-2020 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT). */

#include <Arduino.h>

#include "mwutls/twe_common.hpp"

#include "mwutls/twe_utils.hpp"
#include "mwutls/twe_utils_fixedque.hpp"
#include "mwutls/twe_utils_simplebuffer.hpp"
#include "mwutls/twe_utils_unicode.hpp"

#include "mwutls/twe_sys.hpp"
#include "mwutls/twe_stream.hpp"
#include "mwutls/twe_console.hpp"
#include "mwutls/twe_printf.hpp"
#include "mwutls/twe_serial.hpp"

// Serial Writer Object
namespace TWE {
	extern TWE::TWE_PutChar_Serial<HardwareSerial> WSer; // Serial Writer for Serial
	#ifdef ESP32
	extern TWE::TWE_PutChar_Serial<HardwareSerial> WSer2; // Serial Writer for Serial2
	#endif
}

// namespace
using namespace TWE;