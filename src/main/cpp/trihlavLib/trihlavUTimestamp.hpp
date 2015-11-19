/*
 * yuSerUTimestamp.hpp
 *
 *  Created on: 10.03.2015
 *      Author: grobap
 */

#ifndef YUSERLIB_YUSERTIMESTAMP_HPP_
#define YUSERLIB_YUSERTIMESTAMP_HPP_

#include <yubikey.h>

namespace trihlav {

	/**
	 * Allow easier acces to Yubikeys timestamp.
	 */
	union UTimestamp {
		/** Low/high access as in Yubkeys struct. */
		struct {
            /** Fill the struct to 32 bit */
            uint8_t filler;
		    /** Timestamp (high part). */
		    uint8_t tstph;
            /** Timestamp incremented by approx 8Hz (low part). */
            uint16_t tstpl;
        } tstp;
		/** Access timestamp as an integer. */
		int tstp_int;

        UTimestamp() :tstp_int(0){}
        UTimestamp(const int pAsInt) :tstp_int(pAsInt){}
    } ;

} // end namespace yuSerApi


#endif /* YUSERLIB_YUSERTIMESTAMP_HPP_ */
