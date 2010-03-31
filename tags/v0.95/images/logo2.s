.rodata
.balign 32
.globl pic39length
.globl pic39data

pic39length:	.long	picdataend - pic39data
pic39data:
.incbin "../images/logo2.jpg"
picdataend:


