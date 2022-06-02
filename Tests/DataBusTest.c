#include "DataBusTest.h"


EFI_STATUS
EFIAPI
DataBusTest(
    IN EFI_PHYSICAL_ADDRESS Address,
    IN UINT64 Length,
    IN UINTN PassNumber,
    VOID *Context,
    EFI_SYSTEM_TABLE *system_table
) {
    // Loop over the length of the memory
    for (UINT64 i = 0; i < Length; i++) {
        // Get the address of the current byte
        UINT8 *AddressOfByte = (UINT8 *) (Address + i);
        UINT8 pattern = 1u << (i % 8);
        // Set the current byte to pattern
        *AddressOfByte = pattern;
        // Read the current byte if different from pattern return EFI_FAILURE
        if (*AddressOfByte != pattern) {
            system_table->ConOut->OutputString(system_table->ConOut, L"Databus test failed!\n");
            return EFI_DEVICE_ERROR;
        }
    }
    return EFI_SUCCESS;
}