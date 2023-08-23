/** @file
  This is a simple shell application

  Copyright (c) 2008, Intel Corporation                                                         
  All rights reserved. This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/ShellCEntryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

INTN EFIAPI ShellAppMain (IN UINTN Argc, IN CHAR16 **Argv)
{
  EFI_TIME curTime;
  Print(L"Hello, this is Entry of main!\n");
  gBS->Stall(2000);
  gRT->GetTime(&curTime, NULL);
  Print(L"Gurrent Time: %d-%d-%d %02d:%02d:%02d\n", \
          curTime.Year, curTime.Month, curTime.Day, \
          curTime.Hour, curTime.Minute, curTime.Second);
  gST->ConOut->OutputString(gST->ConOut, L"Test SystemTable...\n\r");
  return(0);
}

