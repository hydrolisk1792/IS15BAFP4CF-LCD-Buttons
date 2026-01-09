/* This file is required to fix the PIC18 errata 2.3.1, "TBLRD Requires NVMREG Value to Point to Appropriate Memory"
    http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18LF26-45-46K40-Errata-80000712F.pdf
    */
    #include <xc.inc>
    GLOBAL powerup, start
    PSECT powerup, class=CODE, delta=1, reloc=2
powerup:
    BSF NVMCON1, 7
    GOTO start
    end 