.rodata
.balign 32
.globl pic36length
.globl pic36data

pic36length:	.long	picdataend - pic36data
pic36data:
.incbin "../images/player2_point.png"
picdataend:


