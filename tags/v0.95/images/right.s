.rodata
.balign 32
.globl pic25length
.globl pic25data

pic25length:	.long	picdataend - pic25data
pic25data:
.incbin "../images/right.png"
picdataend:


