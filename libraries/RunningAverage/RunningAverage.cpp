//
//    FILE: RunningAverage.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.07
//    DATE: 2015-mar-16
// PURPOSE: RunningAverage library for Arduino
//
// The library stores N individual values in a circular buffer,
// to calculate the running average.
//
// HISTORY:
// 0.1.00 - 2011-01-30 initial version
// 0.1.01 - 2011-02-28 fixed missing destructor in .h
// 0.2.00 - 2012-??-?? Yuval Naveh added trimValue (found on web)
//          http://stromputer.googlecode.com/svn-history/r74/trunk/Arduino/Libraries/RunningAverage/RunningAverage.cpp
// 0.2.01 - 2012-11-21 refactored
// 0.2.02 - 2012-12-30 refactored trimValue -> fillValue
// 0.2.03 - 2013-11-31 getElement
// 0.2.04 - 2014-07-03 added memory protection
// 0.2.05 - 2014-12-16 changed float -> double
// 0.2.06 - 2015-03-07 all size uint8_t
// 0.2.07 - 2015-03-16 added getMin() and getMax() functions
//
// Released to the public domain
//

#include "RunningAverage.h"
#include <stdlib.h>

RunningAverage::RunningAverage(uint8_t size)
{
    _size = size;
    _ar = (double*) malloc(_size * sizeof(double));
    if (_ar == NULL) _size = 0;
    clear();
	_min = NAN;
	_max = NAN;
}

RunningAverage::~RunningAverage()
{
    if (_ar != NULL) free(_ar);
}

// resets all counters
void RunningAverage::clear()
{
    _cnt = 0;
    _idx = 0;
    _sum = 0.0;
    for (uint8_t i = 0; i< _size; i++)
    {
        _ar[i] = 0.0; // keeps addValue simple
    }
}

// adds a new value to the data-set
void RunningAverage::addValue(double value)
{
    if (_ar == NULL) return;
    _sum -= _ar[_idx];
    _ar[_idx] = value;
    _sum += _ar[_idx];
    _idx++;
    if (_idx == _size) _idx = 0;  // faster than %
	if (_cnt == 0) _min = _max = f;
	if (f < _min) _min = f;
	if (f > _max) _max = f;
    if (_cnt < _size) _cnt++;
}

// returns the average of the data-set added sofar
double RunningAverage::getAverage()
{
    if (_cnt == 0) return NAN;
    return _sum / _cnt;
}

// returns the lowest value added to the data-set
double RunningAverage::getMin()
{
    if (_cnt == 0) return NAN;
    return _min;
}

// returns the highest value added to the data-set
double RunningAverage::getMax())
{
    if (_cnt == 0) return NAN;
    return _max;
}

// returns the value of an element if exist, 0 otherwise
double RunningAverage::getElement(uint8_t idx)
{
    if (idx >=_cnt ) return NAN;
    return _ar[idx];
}

// fill the average with a value
// the param number determines how often value is added (weight)
// number should preferably be between 1 and size
void RunningAverage::fillValue(double value, uint8_t number)
{
    clear(); // TODO conditional?  if (clr) clear();

    for (uint8_t i = 0; i < number; i++)
    {
        addValue(value);
    }
}
// END OF FILE