.rodata
.balign 32
.globl pic35length
.globl pic35data

pic35length:	.long	picdataend - pic35data
pic35data:
.incbin "../images/background3.png"
picdataend:


