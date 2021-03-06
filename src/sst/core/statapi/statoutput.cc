// Copyright 2009-2016 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2009-2016, Sandia Corporation
// All rights reserved.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include "sst_config.h"

#include "sst/core/output.h"
#include <sst/core/statapi/statoutput.h>
#include <sst/core/stringize.h>

namespace SST {
namespace Statistics {

////////////////////////////////////////////////////////////////////////////////    
    
StatisticOutput::StatisticOutput(Params& outputParameters)
 : Module()
{
    m_statOutputName = "StatisticOutput";
    m_outputParameters = outputParameters;
    m_highestFieldHandle = 0;
    m_currentFieldCompName = "";
    m_currentFieldStatName = "";
    m_statLoadLevel = 0;
}

StatisticOutput::~StatisticOutput()
{
}

// Start / Stop of register
void StatisticOutput::startRegisterFields(StatisticBase *statistic)
{
    m_currentFieldCompName = statistic->getCompName();
    m_currentFieldStatName = statistic->getStatName();
    implStartRegisterFields(statistic);
}

void StatisticOutput::stopRegisterFields()
{
    implStopRegisterFields();
    m_currentFieldCompName = "";
    m_currentFieldStatName = "";
}

StatisticFieldInfo* StatisticOutput::addFieldToLists(const char* fieldName, fieldType_t fieldType)
{
    StatisticFieldInfo* NewStatFieldInfo;
    StatisticFieldInfo* ExistingStatFieldInfo;

    // Create a new Instance of a StatisticFieldInfo
    NewStatFieldInfo = new StatisticFieldInfo(m_currentFieldStatName.c_str(), fieldName, fieldType);
    
    // Now search the FieldNameMap_t of type for a matching entry
    FieldNameMap_t::const_iterator found = m_outputFieldNameMap.find(NewStatFieldInfo->getFieldUniqueName());
    if (found != m_outputFieldNameMap.end()) {
        // We found a map entry, now get the StatFieldInfo from the m_outputFieldInfoArray at the index given by the map
        // and then delete the NewStatFieldInfo to prevent a leak
        ExistingStatFieldInfo = m_outputFieldInfoArray[found->second];
        delete NewStatFieldInfo;
        return ExistingStatFieldInfo;
    }

    // If we get here, then the New StatFieldInfo does not exist so add it to both
    // the Array and to the map
    m_outputFieldInfoArray.push_back(NewStatFieldInfo);
    m_outputFieldNameMap[NewStatFieldInfo->getFieldUniqueName()] = m_outputFieldInfoArray.size() - 1;
    
    return NewStatFieldInfo;
}

StatisticOutput::fieldHandle_t StatisticOutput::generateFileHandle(StatisticFieldInfo* FieldInfo)
{
    // Check to see if this field info has a handle assigned
    if (-1 == FieldInfo->getFieldHandle()) {
        // Not assigned, so assign it and increment the handle
        FieldInfo->setFieldHandle(m_highestFieldHandle);
        m_highestFieldHandle++;
    }
    return FieldInfo->getFieldHandle();
}

//// Routines to Manipulate Fields (For Future Support)
//void StatisticOutput::setFieldHierarchy(fieldHandle_t fieldHandle, uint32_t Level, fieldHandle_t parent) 
//{
//}

StatisticFieldInfo* StatisticOutput::getRegisteredField(fieldHandle_t fieldHandle)
{
    if (fieldHandle <= m_highestFieldHandle) {
        return m_outputFieldInfoArray[fieldHandle];
    }
    return NULL;
}

void StatisticOutput::startOutputEntries(StatisticBase* statistic)
{
    m_currentFieldCompName = statistic->getCompName();
    m_currentFieldStatName = statistic->getStatName();
    // Call the Derived class method
    implStartOutputEntries(statistic);
}

void StatisticOutput::stopOutputEntries()
{
    m_currentFieldCompName = "";
    m_currentFieldStatName = "";
    // Call the Derived class method
    implStopOutputEntries();
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, int32_t data)  
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, uint32_t data)  
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, int64_t data)  
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, uint64_t data)  
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, float data)  
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

void StatisticOutput::outputField(fieldHandle_t fieldHandle, double data)
{
    // Call the Derived class method
    implOutputField(fieldHandle, data);
}

const char* StatisticOutput::getFieldTypeShortName(fieldType_t type)
{
    return StatisticFieldInfo::getFieldTypeShortName(type);
}

} //namespace Statistics
} //namespace SST
