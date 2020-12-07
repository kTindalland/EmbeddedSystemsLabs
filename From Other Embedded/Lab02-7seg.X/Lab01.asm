#INCLUDE<P16F877A.INC>

    __CONFIG _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC
	org	    00h
	
	; Predefined Values
    outer_delay	equ 050h
    inner_delay	equ 050h
   main
	banksel TRISD
	clrf TRISD
	movlw 0x06
	movwf ADCON1
	movlw 0x00
	movwf TRISA
	clrf STATUS
	clrf PORTD
	clrf PORTA
	comf PORTD,1


	loop

	clrf PORTA
	bsf PORTA,0
	call make_b
	call delay
	
	bcf PORTA,0
	bsf PORTA,1
	call make_o
	call delay
		
	bcf PORTA,1
	bsf PORTA,2
	call make_o
	call delay
	
	bcf PORTA,2
	bsf PORTA,3
	call make_b
	call delay
	
	bcf PORTA,3
	bsf PORTA,4
	call make_s
	call delay
	

	goto loop
	
	
	make_b
	
	bcf PORTD,0
	bcf PORTD,1
	bcf PORTD,2
	bcf PORTD,3
	bcf PORTD,4
	bcf PORTD,5
	bcf PORTD,6
	bsf PORTD,7
	
	return
	
	make_o
	
	bcf PORTD,0
	bcf PORTD,1
	bcf PORTD,2
	bcf PORTD,3
	bcf PORTD,4
	bcf PORTD,5
	bsf PORTD,6
	bsf PORTD,7
	
	return
	
	make_s
	
	bcf PORTD,0
	bsf PORTD,1
	bcf PORTD,2
	bcf PORTD,3
	bsf PORTD,4
	bcf PORTD,5
	bcf PORTD,6
	bsf PORTD,7
	
	return

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
	end

	end