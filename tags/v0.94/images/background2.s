.rodata
.balign 32
.globl pic34length
.globl pic34data

pic34length:	.long	picdataend - pic34data
pic34data:
.incbin "../images/background2.png"
picdataend:


