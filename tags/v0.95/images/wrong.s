.rodata
.balign 32
.globl pic26length
.globl pic26data

pic26length:	.long	picdataend - pic26data
pic26data:
.incbin "../images/wrong.png"
picdataend:


