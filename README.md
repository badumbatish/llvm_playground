# Hola
Hi there, welcome :)

Let's try to build something with llvm shall we?


# Installation
Install llvm via brew 
```
brew install llvm
```

Do a `brew info llvm`

then run this in your .zshrc or your .bashrc to help CMake find the llvm installation    
```
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc \
&& echo 'export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"' >> ~/.zshrc \
&& echo 'export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"' >> ~/.zshrc
```

