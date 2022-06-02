#include "DeviceTest.h"


EFI_STATUS
EFIAPI
memTestDevice (
    IN EFI_PHYSICAL_ADDRESS* Address,
    IN UINT64              Length,
    VOID *Context,
    EFI_SYSTEM_TABLE *system_table
){
    unsigned long offset;
    unsigned long nWords = Length / sizeof(EFI_PHYSICAL_ADDRESS);

    // Create a pattern
    UINT32 pattern;
    UINT32 antiPattern;

    for(pattern = 1, offset = 0; offset < nWords; pattern++, offset++){
        Address[offset] = pattern;
    }

    // Check each location and invert it for the second pass
    for(pattern = 1, offset = 0; offset < nWords; pattern++, offset++){
        if(Address[offset] != pattern){
            system_table->ConOut->OutputString(system_table->ConOut, L"Memory test failed!\n");
            return EFI_DEVICE_ERROR;
        }
        antiPattern = ~pattern;
        Address[offset] = antiPattern;
    }


    // Check each location for the inverted pattern and zero it
    for(pattern = 1, offset = 0; offset < nWords; pattern++, offset++){
        antiPattern = ~pattern;
        if(Address[offset] != antiPattern){
            system_table->ConOut->OutputString(system_table->ConOut, L"Memory test failed!\n");
            return EFI_DEVICE_ERROR;
        }
        Address[offset] = 0;
    }

    return EFI_SUCCESS;
}