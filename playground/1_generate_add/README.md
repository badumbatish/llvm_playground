# Generate addition 

Let's try to create an executable that is just a function that returns the sum of two numbers. 

The file for the playground 




# Running it
```bash
cmake -S . -B build && cmake --build build \
&& ./build/generate_add > temp.ll \
&& llc -filetype=obj temp.ll && clang temp.o -o temp && ./temp
```


# Output

## LLVM IR
```llvm
; ModuleID = 'top'
source_filename = "top"

; Declare the string constant as a global constant  
@0 = private unnamed_addr constant [10 x i8] c"Sum : %f\0A\00", align 1

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0, float 1.500000e+01)
  ret i32 0
}

declare i32 @printf(ptr, ...)

```


# Practice

See if you can make it work with multiply :) 

And what about division?
