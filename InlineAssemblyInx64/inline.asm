.code

    DivInt64 PROC

	    mov rax, rcx  ; dividend
	    mov rbx, rdx  ; divisor
        xor rdx, rdx

	    div rbx

	    ret

    DivInt64 ENDP

END
