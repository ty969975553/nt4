/*++

Copyright (c) 1991  Microsoft Corporation

Module Name:

    jxsysint.c

Abstract:

    This module implements the HAL enable/disable system interrupt, and
    request interprocessor interrupt routines for a MIPS R3000 or R4000
    Jazz system.

Author:

    David N. Cutler (davec) 6-May-1991

Environment:

    Kernel mode

Revision History:

--*/

#include "halp.h"
#include "jazzint.h"

//
// Define reference to the builtin device interrupt enables.
//

extern USHORT HalpBuiltinInterruptEnable;

VOID
HalDisableSystemInterrupt (
    IN ULONG Vector,
    IN KIRQL Irql
    )

/*++

Routine Description:

    This routine disables the specified system interrupt.

Arguments:

    Vector - Supplies the vector of the system interrupt that is disabled.

    Irql - Supplies the IRQL of the interrupting source.

Return Value:

    None.

--*/

{

    KIRQL OldIrql;

    //
    // Raise IRQL to the highest level.
    //

    KeRaiseIrql(HIGH_LEVEL, &OldIrql);

    //
    // If the vector number is within the range of builtin devices, then
    // disable the builtin device interrupt.
    //

    if ((Vector >= (DEVICE_VECTORS + 1)) && (Vector <= MAXIMUM_BUILTIN_VECTOR)) {
        HalpBuiltinInterruptEnable &= ~(1 << (Vector - DEVICE_VECTORS - 1));
        WRITE_REGISTER_USHORT(&((PINTERRUPT_REGISTERS)INTERRUPT_VIRTUAL_BASE)->Enable,
                              HalpBuiltinInterruptEnable);
    }

    //
    // If the vector number is within the range of the EISA interrupts, then
    // disable the EISA interrrupt.
    //

    if (Vector >= EISA_VECTORS &&
        Vector < EISA_VECTORS + MAXIMUM_EISA_VECTOR &&
        Irql == EISA_DEVICE_LEVEL) {
        HalpDisableEisaInterrupt(Vector);
    }

    //
    // Lower IRQL to the previous level.
    //

    KeLowerIrql(OldIrql);
    return;
}

BOOLEAN
HalEnableSystemInterrupt (
    IN ULONG Vector,
    IN KIRQL Irql,
    IN KINTERRUPT_MODE InterruptMode
    )

/*++

Routine Description:

    This routine enables the specified system interrupt.

Arguments:

    Vector - Supplies the vector of the system interrupt that is enabled.

    Irql - Supplies the IRQL of the interrupting source.

    InterruptMode - Supplies the mode of the interrupt; LevelSensitive or
        Latched.

Return Value:

    TRUE if the system interrupt was enabled

--*/

{

    KIRQL OldIrql;

    //
    // Raise IRQL to the highest level.
    //

    KeRaiseIrql(HIGH_LEVEL, &OldIrql);

    //
    // If the vector number is within the range of builtin devices, then
    // enable the builtin device interrupt.
    //

    if ((Vector >= (DEVICE_VECTORS + 1)) && (Vector <= MAXIMUM_BUILTIN_VECTOR)) {
        HalpBuiltinInterruptEnable |= (1 << (Vector - DEVICE_VECTORS - 1));
        WRITE_REGISTER_USHORT(&((PINTERRUPT_REGISTERS)INTERRUPT_VIRTUAL_BASE)->Enable,
                              HalpBuiltinInterruptEnable);
    }

    //
    // If the vector number is within the range of the EISA interrupts, then
    // enable the EISA interrrupt and set the Level/Edge register.
    //

    if (Vector >= EISA_VECTORS &&
        Vector < EISA_VECTORS + MAXIMUM_EISA_VECTOR &&
        Irql == EISA_DEVICE_LEVEL) {
        HalpEnableEisaInterrupt( Vector, InterruptMode);
    }

    //
    // Lower IRQL to the previous level.
    //

    KeLowerIrql(OldIrql);
    return TRUE;
}

ULONG
HalGetInterruptVector(
    IN INTERFACE_TYPE  InterfaceType,
    IN ULONG BusNumber,
    IN ULONG BusInterruptLevel,
    IN ULONG BusInterruptVector,
    OUT PKIRQL Irql,
    OUT PKAFFINITY Affinity
    )

/*++

Routine Description:

    This function returns the system interrupt vector and IRQL level
    corresponding to the specified bus interrupt level and/or vector.
    The system interrupt vector and IRQL are suitable for use in a
    subsequent call to KeInitializeInterrupt.

Arguments:

    InterfaceType - Supplies the type of bus which the vector is for.

    BusNumber - Supplies the bus number for the device.

    BusInterruptLevel - Supplies the bus specific interrupt level.

    BusInterruptVector - Supplies the bus specific interrupt vector.

    Irql - Returns the system request priority.

    Affinity - Returns the affinity for the requested vector.

Return Value:

    Returns the system interrupt vector corresponding to the specified device.

--*/

{

    //
    // ****** temp ******
    //
    // MP code to be added
    //
    // ****** temp ******
    //

    *Affinity = 1;

    //
    // If this is for the internal bus then just return the passed parameter.
    //

    if (InterfaceType == Internal) {

        //
        // Return the passed parameters.
        //

        *Irql = (UCHAR)BusInterruptLevel;
        return(BusInterruptVector);
    }

    if (InterfaceType != Isa && InterfaceType != Eisa) {

        //
        // Not on this system return nothing.
        //

        *Affinity = 0;
        *Irql = 0;
        return(0);

    }

    //
    // Jazz only has one I/O bus which is an EISA, so the bus number and the
    // bus interrupt vector are unused.
    //
    // The IRQL level is always equal to the EISA level.
    //

    *Irql = EISA_DEVICE_LEVEL;

    //
    // Bus interrupt level 2 is actually mapped to bus level 9 in the Eisa
    // hardware.
    //

    if (BusInterruptLevel == 2) {
        BusInterruptLevel = 9;
    }

    //
    // The vector is equal to the specified bus level plus the EISA_VECTOR.
    //

    return(BusInterruptLevel + EISA_VECTORS);

}

VOID
HalRequestIpi (
    IN ULONG Mask
    )

/*++

Routine Description:

    This routine requests an interprocessor interrupt on a set of processors.

    N.B. This routine must ensure that the interrupt is posted at the target
         processor(s) before returning.

Arguments:

    Mask - Supplies the set of processors that are sent an interprocessor
        interrupt.

Return Value:

    None.

--*/

{

    ULONG Target;

    //
    // Scan the processor set and request an interprocessor interrupt on
    // each of the specified targets.
    //

#if !defined(NT_UP)

    Target = 0;
    do {
        if ((Mask & 1) != 0) {

            //
            // Request interprocessor interrupt on target.
            //

        }

        Mask >>= 1;
        Target += 1;
    } while (Mask != 0);

#endif

    return;
}
