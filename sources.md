# Source arrangement

All code is split into these top level folders:
> - [arch](#arch) - architecture specific code and include files, has subdirectories for each supported architecture (for now only arm), the subfolder are structured like these top level folders (without the arch folder ofcourse), there exists an `asm` folder which is soft linked to the current architecture
> - [include](#include) - most of the include files, the arch specific files are located in `arch/*/include`
> - [init](#init) - the initialization code for the kernel
> - [mm](#mm) - all of the memory management code, the arch specific code is in `arch/*/mm`
> - [kernel](#kernel) - the main kernel code, again the arch specific stuff is in `arch/*/kernel`
> - [lib](#lib) - contains the kernels library code, as with the preceding folders, the architecture specific code is located in `arch/*/lib`
### arch
### include
### init
### mm
### kernel
### lib