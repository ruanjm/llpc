/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2020 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  vkgcUtil.h
 * @brief VKGC header file: contains the definition of VKGC internal types and utility functions
 ***********************************************************************************************************************
 */
#pragma once

#include "vkgcDefs.h"

namespace Vkgc
{

// Invalid value
static const unsigned InvalidValue  = ~0u;

// Gets name string of the abbreviation for the specified shader stage.
const char* getShaderStageAbbreviation(ShaderStage shaderStage, bool upper = false);

// Create directory.
bool createDirectory(const char* dir);

// Translate enum "ResourceMappingNodeType" to string
const char* getResourceMappingNodeTypeName(ResourceMappingNodeType type);

// =====================================================================================================================
// Increments a pointer by nBytes by first casting it to a uint8_t*.
//
// Returns incremented pointer.
inline void* voidPtrInc(
    const void* p,         // [in] Pointer to be incremented.
    size_t      numBytes)  // Number of bytes to increment the pointer by
{
    void* ptr = const_cast<void*>(p);
    return (static_cast<uint8_t*>(ptr) + numBytes);
}

// ===================================================================================
// Finds the expected structure in Vulkan structure chain with the specified info.
template<class T>
inline const T* findVkStructInChain(
    VkStructureType type,    // Vulkan structure type
    const void*     next)   // Base pointer of Vulkan structure
{
    struct VkStructHeader
    {
        VkStructureType type;
        VkStructHeader* next;
    };

    const VkStructHeader* structHeader = reinterpret_cast<const VkStructHeader*>(next);
    while(structHeader != nullptr)
    {
        if (structHeader->type == type)
        {
            break;
        }
        else
        {
            structHeader = structHeader->next;
        }
    }

    return reinterpret_cast<const T*>(structHeader);
}

} // Vkgc
