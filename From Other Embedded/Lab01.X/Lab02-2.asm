#INCLUDE<P16F877A.INC>

    __CONFIG _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC
    
    ; Predefined Values
    outer_delay	equ 0ffh
    inner_delay	equ 0ffh
    last_pin	equ 080h
    for_loop	equ 32h
    memdata	equ 33h
	
    org	00h
   main
    clrf PORTC
    incf PORTC
    clrf PORTB
    banksel TRISC
    clrf TRISC
    clrf TRISB
    clrf TRISA
    clrf STATUS
	
	loop
	
	call do_C
	call do_B
	
	goto loop
	
	; Delay loops
	delay
	movlw outer_delay
	movwf 30h
	outer_loop
	movlw	inner_delay
	movwf	31h
	inner_loop
	decfsz	31h,1
	goto	inner_loop
	
	decfsz	30h,1
	goto	outer_loop
	return
	
	do_C
	
	clrf PORTC
	incf PORTC
	call delay
	
	inner_while
	
	movfw PORTC
	addwf PORTC,1
	call delay
	
	btfss PORTC,7
	goto inner_while
	
	clrf PORTC
	return
	
	do_B
	
	clrf PORTB
	incf PORTB
	call delay
	
	inner_while_B
	
	movfw PORTB
	addwf PORTB,1
	call delay
	
	btfss PORTB,7
	goto inner_while_B
	
	clrf PORTB
	return
	
	end


