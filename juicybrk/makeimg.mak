
MYCURDIR := e:/prog/gba/juicybrk/juicybrk
DATA := $(MYCURDIR)/data
IMG := $(MYCURDIR)/img
#SPR := $(MYCURDIR)/spr

BMPFILES = $(wildcard $(IMG)/*.bmp)
#SPRFILES = $(wildcard $(SPR)/*.bmp)

IMGFILES = $(patsubst $(IMG)/%.bmp, $(DATA)/%.img.bin, $(BMPFILES))
#SPRIMGFILES = $(patsubst $(SPR)/%.bmp, $(DATA)/%.img.bin, $(SPRFILES))

PALFILES = $(patsubst $(IMG)/%.bmp, $(DATA)/%.pal.bin, $(BMPFILES))
#SPRPALFILES = $(patsubst $(SPR)/%.bmp, $(DATA)/%.pal.bin, $(SPRFILES))

all: $(IMGFILES) $(PALFILES) #$(SPRIMGFILES) $(SPRPALFILES)

$(IMGFILES) $(PALFILES) : $(BMPFILES)

#$(SPRIMGFILES) $(SPRPALFILES) : $(SPRFILES)

$(DATA)/%.img.bin $(DATA)/%.pal.bin : $(IMG)/%.bmp
	@grit  $< -o $@ -ftb -fh! -g -gt -gB4 -gu32 -gzl -p -pu32 -pzl -gT FF00FF
	
#$(DATA)/%.img.bin $(DATA)/%pal.bin : $(SPR)/%.bmp
#	@grit  $< -o $@ -ftb -fh! -g -gt -gB4 -gu32 -gz! -p -pu32 -pzl -gT FF00FF
