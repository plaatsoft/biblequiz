.rodata
.balign 32
.globl pic19length
.globl pic19data

pic19length:	.long	picdataend - pic19data
pic19data:
.incbin "../images/button3select.png"
picdataend:


