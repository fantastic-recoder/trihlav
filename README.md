# Trihlav OTP validation server

## Concepts
C++ backend, web frontend.

## Features
1. Yubikey OTP support
2. Web configuration UI
3. PAM module

## Build
### Dependencies
1. Python  used only to trigger the build, and it only calls CMake)
2. CMake
3. Yubiko libraries
4. Boost
5. WT++ C++ Web toolkit, used for the web GUI

## TODO
0. Check all ranges when creating a key.
1. Add PIN as a second factor.
2. Configure user ID. 
3. Implement PAM module.