.rodata
.balign 32
.globl pic28length
.globl pic28data

pic28length:	.long	picdataend - pic28data
pic28data:
.incbin "../images/sound.png"
picdataend:


