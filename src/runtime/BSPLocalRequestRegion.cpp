/*
 * BSPLocalRequestRegion.cpp
 *
 *  Created on: 2014-8-20
 *      Author: junfeng
 */

#include "BSPLocalRequestRegion.hpp"

using namespace BSP;

LocalRequestRegion::LocalRequestRegion(ArrayShape &shape) :
LocalRequest(shape) {
    _nRegions = 0;
    for (unsigned iDim = 0; iDim < _numberOfDimensions; iDim++) {
        _nComponentsAlongDim[iDim] = 0;
        _lowerIndexAlongDim[iDim] = NULL;
        _upperIndexAlongDim[iDim] = NULL;
        _stepAlongDim[iDim] = NULL;
    }
}

LocalRequestRegion::~LocalRequestRegion() {
    for (unsigned iDim = 0; iDim < _numberOfDimensions; iDim++) {
        if (_nComponentsAlongDim[iDim] == 0)
            continue;
        delete[] _lowerIndexAlongDim[iDim];
        delete[] _upperIndexAlongDim[iDim];
        delete[] _stepAlongDim[iDim];
    }
}

void LocalRequestRegion::allocateComponents() {
    for (unsigned iDim = 0; iDim < _numberOfDimensions; iDim++) {
        if (_lowerIndexAlongDim[iDim] != NULL
                || _upperIndexAlongDim[iDim] != NULL)
            throw ENotAvailable();
        if (_nComponentsAlongDim[iDim] == 0)
            throw EInvalidArgument();
        _lowerIndexAlongDim[iDim] = new uint64_t[_nComponentsAlongDim[iDim]];
        _upperIndexAlongDim[iDim] = new uint64_t[_nComponentsAlongDim[iDim]];
        _stepAlongDim[iDim] = new int32_t[_nComponentsAlongDim[iDim]];
        if (_lowerIndexAlongDim[iDim] == NULL
                || _upperIndexAlongDim[iDim] == NULL
                || _stepAlongDim[iDim] == NULL)
            throw ENotEnoughMemory();
    }
}

uint64_t LocalRequestRegion::getRegionWidth(const unsigned iDim,
        const uint64_t iComponent) {
    if (iDim >= _numberOfDimensions)
        throw EInvalidArgument();
    if (iComponent >= _nComponentsAlongDim[iDim])
        throw EInvalidArgument();
    return ((int64_t)_upperIndexAlongDim[iDim][iComponent]
            - (int64_t)_lowerIndexAlongDim[iDim][iComponent]) 
        / _stepAlongDim[iDim][iComponent] + 1;
}


