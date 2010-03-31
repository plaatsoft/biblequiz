.rodata
.balign 32
.globl pic2length
.globl pic2data

pic2length:	.long	picdataend - pic2data
pic2data:
.incbin "../images/button1.png"
picdataend:


