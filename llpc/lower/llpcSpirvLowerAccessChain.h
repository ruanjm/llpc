/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All Rights Reserved.
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
 * @file  llpcSpirvLowerAccessChain.h
 * @brief LLPC header file: contains declaration of class Llpc::SpirvLowerAccessChain.
 ***********************************************************************************************************************
 */
#pragma once

#include "llpcSpirvLower.h"
#include "llvm/IR/InstVisitor.h"

namespace Llpc {

// =====================================================================================================================
// Represents the pass of SPIR-V lowering opertions for access chain.
class SpirvLowerAccessChain : public LegacySpirvLower, public llvm::InstVisitor<SpirvLowerAccessChain> {
public:
  SpirvLowerAccessChain();

  virtual bool runOnModule(llvm::Module &module);
  virtual void visitGetElementPtrInst(llvm::GetElementPtrInst &getElemPtrInst);

  static char ID; // ID of this pass

private:
  SpirvLowerAccessChain(const SpirvLowerAccessChain &) = delete;
  SpirvLowerAccessChain &operator=(const SpirvLowerAccessChain &) = delete;

  llvm::GetElementPtrInst *tryToCoalesceChain(llvm::GetElementPtrInst *getElemPtr, unsigned addrSpace);
};

} // namespace Llpc
