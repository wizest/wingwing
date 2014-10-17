#ifndef	__FLASH_H
#define __FLASH_H

#define LOAD_ADDRESS (0x04000000L)
#define SAVE_ADDRESS (0xE4000000L)
#define DATA_SIZE	 (0xBFF0)

typedef unsigned int word;
typedef unsigned char byte;

extern void SaveProgram();
extern void CopyMemory(byte far* Destination,byte far* Source,word Size);
extern void CopyMemoryFLASH(byte far* Destination,byte far* Source,word Size);

#endif