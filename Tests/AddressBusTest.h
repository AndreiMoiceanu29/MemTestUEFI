#include <efi.h>


EFI_STATUS
EFIAPI
AddressBusTest (
    IN EFI_PHYSICAL_ADDRESS* Address,
    IN UINT64              Length,
    VOID *Context,
    EFI_SYSTEM_TABLE *system_table
);