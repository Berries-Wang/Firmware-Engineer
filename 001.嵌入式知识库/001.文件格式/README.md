# 文件格式 <sup>选择对应的文件格式，否则单片机无法正常运行</sup>
&nbsp;&nbsp;Linux OS下，ELF通常就是可执行文件，通常'gcc -o test test.c'生成的test文件就是ELF格式的，在Linux Shell下输入./test就可以执行。在Embedded（嵌入式）中，上电开始运行，没有OS系统，如果将ELF格式的文件烧写进去，包含一些ELF格式的东西，arm运行碰到这些指令，就会导致失败，如果用bin文件，程序就可以一步一步运行。
> HEX和bin文件可以在裸机上运行，而ELF文件是在有OS的环境中运行的。如:000.STM32/000.STM32F103C8T6/000.STM32F103C8T6_1/000.STM32F103C8T6_1/CMakeLists.txt,需要将.bin文件烧录到STM32中，STM32才能正常运行。
