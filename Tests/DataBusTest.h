#include <efi.h>

EFI_STATUS EFIAPI DataBusTest(
    IN EFI_PHYSICAL_ADDRESS Address,
    IN UINT64 Length,
    IN UINTN PassNumber,
    VOID *Context,
    EFI_SYSTEM_TABLE *system_table
);