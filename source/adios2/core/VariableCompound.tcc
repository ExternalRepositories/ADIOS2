/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * VariableCompound.tcc
 *
 *  Created on: May 16, 2017
 *      Author: William F Godoy godoywf@ornl.gov
 */

#ifndef ADIOS2_CORE_VARIABLECOMPOUND_TCC_
#define ADIOS2_CORE_VARIABLECOMPOUND_TCC_

#include "VariableCompound.h"

#include "adios2/ADIOSConfig.h"

namespace adios
{

template <class T>
void VariableCompound::InsertMember(const std::string name, const size_t offset)
{
    m_Elements.push_back(Element{name, GetType<T>(), offset});
}

} // end namespace

#endif /* ADIOS2_CORE_VARIABLECOMPOUND_TCC_ */
