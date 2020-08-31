# Destructo

This is small 2D c++ engine with several renderers to switch between, while running.

## Getting Started

### Prerequisites


[DirectX SDK 2010](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

In case of Error Code 'S1023' try deinstalling:
* Microsoft Visual C++ 2010 x86 Redistributable
* Microsoft Visual C++ 2010 x64 Redistributable

with following commands in command promt as admin:
```
MsiExec.exe /passive /X{F0C3E5D1-1ADE-321E-8167-68EF0DE699A5}
MsiExec.exe /passive /X{1D8E6291-B0D5-35EC-8441-6616F567A0F7} 
```
### Installing

Copy fmod.dll from
```
Destructo\Middleware\fmod\api\lowlevel\lib
```
into
```
Destructo\Debug
```
(same folder as program .exe)


## Built With

* [FMOD](http://www.fmod.com/) - Sound API

## Authors

* **Daniel Emig** - https://github.com/skyteks
* **Sebastian Mechler** - https://github.com/SebastianMechler

## Acknowledgments

* **Osama Zaqout** - Ubisoft Blue Byte
* **Arne Claus** - trivago

