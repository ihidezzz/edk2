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
#include <Library\UefiLib.h>
#include <Library\UefiBootServicesTableLib.h>

#include <Library/BaseMemoryLib.h>

#include <Library\BaseLib.h>


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  gST->ConOut->OutputString(gST->ConOut, L"version:1.0\n\r");
  EFI_STATUS Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gGraphicsOutput;

  UINT32 frameWidth, frameHeight;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorBuf[1000];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackGroundColor = {192, 0, 0, 0};

  Status = gBS->LocateProtocol(
    &gEfiGraphicsOutputProtocolGuid,
    NULL,
    &gGraphicsOutput
  );

  frameWidth = (UINT32)gGraphicsOutput->Mode->Info->HorizontalResolution;
  frameHeight = (UINT32)gGraphicsOutput->Mode->Info->VerticalResolution;

  Print(L"frameWidth is %d, frameHeight is %d\n", frameWidth, frameHeight);

  Status = gGraphicsOutput->Blt(
    gGraphicsOutput,
    &BackGroundColor,
    EfiBltVideoFill,
    0, 0, frameWidth / 2, frameHeight / 2, frameWidth / 2, frameHeight / 2, 0);

  gBS->SetMem(ColorBuf, 1000 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0);
  Status = gGraphicsOutput->Blt(
    gGraphicsOutput,
    ColorBuf,
    EfiBltBufferToVideo,
    0, 0, 0, 0, frameWidth / 2, frameHeight / 2,
    100 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  );

  Status = gGraphicsOutput->Blt(
    gGraphicsOutput,
    ColorBuf,
    EfiBltBufferToVideo,
    0, 5, 20, 60, 100, 5,
    100 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  );

  Status = gGraphicsOutput->Blt(
    gGraphicsOutput,
    0,
    EfiBltVideoToVideo,
    20, 20, 200, 60,
    100, 10, 0
  );

  Status = gGraphicsOutput->Blt(
    gGraphicsOutput,
    ColorBuf,
    EfiBltVideoToBltBuffer,
    20, 20, 0, 0, 100, 10,
    100 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  );
  
  return EFI_SUCCESS;
}

