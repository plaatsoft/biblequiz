.rodata
.balign 32
.globl xml1length
.globl xml1data

xml1length:	.long	xmldataend - xml1data
xml1data:
.incbin "../xml/languages.xml"
xmldataend:


