#include <efi.h>
#include "Tests/DataBusTest.h"
#include "Tests/DeviceTest.h"
#include "Tests/AddressBusTest.h"
// Define a function that does walking ones and asserts memory is correct


EFI_STATUS
EFIAPI
efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
    // Write hello world to the System Table's ConOut
    system_table->ConOut->OutputString(system_table->ConOut, L"Hello, UEFI!\n");
    // Call the DataBusTest function
    EFI_STATUS status = DataBusTest(0x0, 0x1000, 1, NULL, system_table);
    if(status == EFI_SUCCESS){
        system_table->ConOut->OutputString(system_table->ConOut, L"DataBusTest passed, continuing with the next tests!\n");
    }
    else{
        system_table->ConOut->OutputString(system_table->ConOut, L"DataBusTest failed!\n");
        return EFI_DEVICE_ERROR;
    }
    // Call the AddressBusTest function
    status = AddressBusTest(0x0, 0x1000, NULL, system_table);
    if(status == EFI_SUCCESS){
        system_table->ConOut->OutputString(system_table->ConOut, L"AddressBusTest passed, continuing with the next tests!\n");
    }
    else{
        system_table->ConOut->OutputString(system_table->ConOut, L"AddressBusTest failed!\n");
        return EFI_DEVICE_ERROR;
    }
    // Call the DeviceTest function
    status = memTestDevice(0x0, 0x1000, NULL, system_table);
    if(status == EFI_SUCCESS){
        system_table->ConOut->OutputString(system_table->ConOut, L"DeviceTest passed, continuing with the next tests!\n");
    }
    else{
        system_table->ConOut->OutputString(system_table->ConOut, L"DeviceTest failed!\n");
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}