#include "AddressBusTest.h"

 
EFI_STATUS
EFIAPI
AddressBusTest(
    IN EFI_PHYSICAL_ADDRESS* Address,
    IN UINT64 Length,
    VOID *Context,
    EFI_SYSTEM_TABLE *system_table
) {
    unsigned long addressMask = (Length/sizeof(EFI_PHYSICAL_ADDRESS)) - 1;
    unsigned long offset;
    unsigned long testOffset;

    // Create a pattern
    UINT32 pattern = 0xAAAAAAAA;
    UINT32 antiPattern = 0x55555555;

    for(offset = 1; (offset & addressMask) != 0; offset <<= 1) {

        // Read the current byte if different from pattern return EFI_FAILURE
        if (*(UINT32 *) (Address + offset) != pattern) {
            system_table->ConOut->OutputString(system_table->ConOut, L"AddressBus test failed!\n");
            return EFI_DEVICE_ERROR;
        }
    }
    Address[testOffset] = pattern;
    for(testOffset = 1; (testOffset & addressMask) != 0; testOffset <<= 1) {
        Address[testOffset] = antiPattern;
        if (Address[0] != pattern) {
            system_table->ConOut->OutputString(system_table->ConOut, L"AddressBus test failed!\n");
            return EFI_DEVICE_ERROR;
        }

        for(offset = 1; (offset & addressMask) != 0; offset <<= 1) {
            if ((Address[offset] != pattern) && (offset != testOffset)) {
                system_table->ConOut->OutputString(system_table->ConOut, L"AddressBus test failed!\n");
                return EFI_DEVICE_ERROR;
            }
        }
    }
    return EFI_SUCCESS;
}