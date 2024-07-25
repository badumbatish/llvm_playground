#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

auto create_const_int_add(IRBuilder<> &Builder, int L, int R) -> Value * {
  // Create constants for the numbers 5 and 10
  Value *LHS = ConstantInt::get(Type::getInt32Ty(Builder.getContext()), L);
  Value *RHS = ConstantInt::get(Type::getInt32Ty(Builder.getContext()), R);
  // Add the two numbers
  Value *Sum = Builder.CreateAdd(LHS, RHS, "sum");
  return Sum;
}

auto create_const_float_add(IRBuilder<> &Builder, float L, float R) -> Value * {
  // Create constants for the numbers 5 and 10
  Value *LHS = ConstantFP::get(Type::getFloatTy(Builder.getContext()), L);
  Value *RHS = ConstantFP::get(Type::getFloatTy(Builder.getContext()), R);
  // Add the two numbers
  Value *Sum = Builder.CreateFAdd(LHS, RHS, "sum");
  return Sum;
}

// Function to set up the printf function
FunctionCallee setup_printf(Module *M, IRBuilder<> &Builder) {
  std::vector<Type *> printf_arg_types;
  printf_arg_types.push_back(PointerType::getUnqual(Builder.getInt8Ty()));
  FunctionType *printf_type =
      FunctionType::get(Builder.getInt32Ty(), printf_arg_types, true);
  return M->getOrInsertFunction("printf", printf_type);
}

int main() {
  LLVMContext Context;
  auto M = std::unique_ptr<Module>(new Module("top", Context));

  // Create the main function: int main() { ... }
  FunctionType *FT =
      FunctionType::get(Type::getInt32Ty(M->getContext()), false);
  Function *F =
      Function::Create(FT, Function::ExternalLinkage, "main", M.get());
  BasicBlock *BB = BasicBlock::Create(Context, "entry", F);

  // Create the builder and set the insertion point to the entry block
  IRBuilder<> Builder(BB);
  auto Sum = create_const_float_add(Builder, 5, 10);
  // Declare the printf function
  auto printf_func = setup_printf(M.get(), Builder);
  // Create the format string
  Value *format_str = Builder.CreateGlobalStringPtr("Sum : %f\n");

  // Call printf to print the result
  Builder.CreateCall(printf_func, {format_str, Sum});

  // Return the sum
  Builder.CreateRet(Builder.getInt32(0));

  // Verify the module
  verifyModule(*M, &errs());

  // Print the generated LLVM IR
  M->print(outs(), nullptr);

  return 0;
}
