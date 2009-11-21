.rodata
.balign 32
.globl pic29length
.globl pic29data

pic29length:	.long	picdataend - pic29data
pic29data:
.incbin "../images/exit.png"
picdataend:


