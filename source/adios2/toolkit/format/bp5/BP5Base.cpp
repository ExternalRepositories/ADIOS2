/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * BP5Serializer.h
 *
 */

#include "adios2/core/Attribute.h"
#include "adios2/core/Engine.h"
#include "adios2/core/IO.h"

#include "BP5Base.h"

#include <string.h>

#ifdef _WIN32
#pragma warning(disable : 4250)
#endif

namespace adios2
{
namespace format
{

void BP5Base::FFSBitfieldSet(struct FFSMetadataInfoStruct *MBase, int Bit)
{
    int Element = Bit / (sizeof(size_t) * 8);
    int ElementBit = Bit % (sizeof(size_t) * 8);
    if (Element >= MBase->BitFieldCount)
    {
        MBase->BitField =
            (size_t *)realloc(MBase->BitField, sizeof(size_t) * (Element + 1));
        memset(MBase->BitField + MBase->BitFieldCount, 0,
               (Element - MBase->BitFieldCount + 1) * sizeof(size_t));
        MBase->BitFieldCount = Element + 1;
    }
    MBase->BitField[Element] |= ((size_t)1 << ElementBit);
}

int BP5Base::FFSBitfieldTest(struct FFSMetadataInfoStruct *MBase, int Bit)
{
    int Element = Bit / (sizeof(size_t) * 8);
    int ElementBit = Bit % (sizeof(size_t) * 8);
    if (Element >= MBase->BitFieldCount)
    {
        MBase->BitField =
            (size_t *)realloc(MBase->BitField, sizeof(size_t) * (Element + 1));
        memset(MBase->BitField + MBase->BitFieldCount, 0,
               (Element - MBase->BitFieldCount + 1) * sizeof(size_t));
        MBase->BitFieldCount = Element + 1;
    }
    return ((MBase->BitField[Element] & ((size_t)1 << ElementBit)) ==
            ((size_t)1 << ElementBit));
}
}
}
