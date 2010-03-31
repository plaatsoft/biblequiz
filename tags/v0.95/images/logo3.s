.rodata
.balign 32
.globl pic40length
.globl pic40data

pic40length:	.long	picdataend - pic40data
pic40data:
.incbin "../images/logo3.jpg"
picdataend:


