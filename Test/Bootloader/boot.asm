[org 0x7c00]                        





;;Data Section : : 
KERNEL_LOCATION equ 0x8200
;data:


jmp main

;*************************************************;
;   OEM Parameter block
;*************************************************;

; Error Fix 2 - Removing the ugly TIMES directive -------------------------------------

;;  TIMES 0Bh-$+start DB 0                  ; The OEM Parameter Block is exactally 3 bytes
                                ; from where we are loaded at. This fills in those
                                ; 3 bytes, along with 8 more. Why?

bpbOEM          db "My OS   "               ; This member must be exactally 8 bytes. It is just
                                ; the name of your OS :) Everything else remains the same.

bpbBytesPerSector:      DW 512
bpbSectorsPerCluster:   DB 1
bpbReservedSectors:     DW 1
bpbNumberOfFATs:        DB 2
bpbRootEntries:         DW 224
bpbTotalSectors:        DW 2880
bpbMedia:               DB 0xF0
bpbSectorsPerFAT:       DW 9
bpbSectorsPerTrack:     DW 18
bpbHeadsPerCylinder:    DW 2
bpbHiddenSectors:       DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber:          DB 0
bsUnused:               DB 0
bsExtBootSignature:     DB 0x29
bsSerialNumber:         DD 0xa0a1a2a3
bsVolumeLabel:          DB "MOS FLOPPY "
bsFileSystem:           DB "FAT12   "

;before main we have to make things up:


;************************************************;
;   Prints a string
;   DS=>SI: 0 terminated string
;************************************************;
Print:
            lodsb               ; load next byte from string from SI to AL
            or  al, al          ; Does AL=0?
            jz  PrintDone       ; Yep, null terminator found-bail out
            mov ah, 0eh         ; Nope-Print the character
            int 10h
            jmp Print           ; Repeat until null terminator found
    PrintDone:
            ret             ; we are done, so return


absoluteSector db 0x00
absoluteHead   db 0x00
absoluteTrack  db 0x00

;************************************************;
; Convert CHS to LBA
; LBA = (cluster - 2) * sectors per cluster
;************************************************;

ClusterLBA:
          sub     ax, 0x0002                          ; zero base cluster number
          xor     cx, cx
          mov     cl, BYTE [bpbSectorsPerCluster]     ; convert byte to word
          mul     cx
          add     ax, WORD [datasector]               ; base data sector
          ret

;************************************************;
; Convert LBA to CHS
; AX=>LBA Address to convert
;
; absolute sector = (logical sector / sectors per track) + 1
; absolute head   = (logical sector / sectors per track) MOD number of heads
; absolute track  = logical sector / (sectors per track * number of heads)
;
;************************************************;

LBACHS:
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbSectorsPerTrack]           ; calculate
          inc     dl                                  ; adjust for sector 0
          mov     BYTE [absoluteSector], dl
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbHeadsPerCylinder]          ; calculate
          mov     BYTE [absoluteHead], dl
          mov     BYTE [absoluteTrack], al
          ret


;************************************************;
; Reads a series of sectors
; CX=>Number of sectors to read
; AX=>Starting sector
; ES:BX=>Buffer to read to
;************************************************;

ReadSectors:
     .MAIN
          mov     di, 0x0005                          ; five retries for error
     .SECTORLOOP
          push    ax
          push    bx
          push    cx
          call    LBACHS                              ; convert starting sector to CHS
          mov     ah, 0x02                            ; BIOS read sector
          mov     al, 0x01                            ; read one sector
          mov     ch, BYTE [absoluteTrack]            ; track
          mov     cl, BYTE [absoluteSector]           ; sector
          mov     dh, BYTE [absoluteHead]             ; head
          mov     dl, BYTE [bsDriveNumber]            ; drive
          int     0x13                                ; invoke BIOS
          jnc     .SUCCESS                            ; test for read error
          xor     ax, ax                              ; BIOS reset disk
          int     0x13                                ; invoke BIOS
          dec     di                                  ; decrement error counter
          pop     cx
          pop     bx
          pop     ax
          jnz     .SECTORLOOP                         ; attempt to read again
          int     0x18
     .SUCCESS
          mov     si, msgProgress
          call    Print
          pop     cx
          pop     bx
          pop     ax
          add     bx, WORD [bpbBytesPerSector]        ; queue next buffer
          inc     ax                                  ; queue next sector
          loop    .MAIN                               ; read next sector
          ret





main:                                    

mov [BOOT_DISK], dl                 

                                    
xor ax, ax                  ;reseting all the segments;        
mov es, ax                  ;extra segment
mov ds, ax
mov bp, 0x8000              ; stack at real mode starts at 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 60 ;reading 60 sectors. before it was only 2, the size was too small.

mov ah, 0x02        
mov al, dh 
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13               



                                    
mov ah, 0x0
mov al, 0x3
int 0x10                ; text mode, enabling A20


CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli                     ;clear interrupts . moving to protectted mode
lgdt [GDT_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax


jmp CODE_SEG:start_protected_mode

jmp $ ; jumping here is like hlt;
                                    
BOOT_DISK: db 0

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start





;%include "/home/user/OS/operating-system/Test/Memory/memory.asm"



[bits 32]



start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000        ; 32 bit stack base pointer
    mov esp, ebp


    ;;enabling A20 line : 
    in al, 0x92
    or al, 0x02
    out 0x92, al


    jmp KERNEL_LOCATION
    jmp $
                                     


msgProgress db ".", 0x00
datasector  dw 0x0000


times 510-($-$$) db 0              
dw 0xaa55

