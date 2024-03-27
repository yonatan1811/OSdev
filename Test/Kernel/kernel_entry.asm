[bits 32]

[extern main]
call main		     
jmp $

%include "../Memory/paging.asm"
