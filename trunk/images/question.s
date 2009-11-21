.rodata
.balign 32
.globl pic31length
.globl pic31data

pic31length:	.long	picdataend - pic31data
pic31data:
.incbin "../images/question.png"
picdataend:


