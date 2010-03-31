.rodata
.balign 32
.globl pic24length
.globl pic24data

pic24length:	.long	picdataend - pic24data
pic24data:
.incbin "../images/france_flag.png"
picdataend:


