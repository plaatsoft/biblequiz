.rodata
.balign 32
.globl pic38length
.globl pic38data

pic38length:	.long	picdataend - pic38data
pic38data:
.incbin "../images/player4_point.png"
picdataend:


