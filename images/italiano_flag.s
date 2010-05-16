.rodata
.balign 32
.globl pic45length
.globl pic45data

pic45length:	.long	picdataend - pic45data
pic45data:
.incbin "../images/italiano_flag.png"
picdataend:


