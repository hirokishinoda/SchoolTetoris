SRC=main.cpp
OBJS=$(SRC:.c=.o)
PROG=main.exe
CC=g++
CFLAGS=-Wall -O3
LIBS = C:\MinGW\lib\DxLib -DDX_GCC_COMPILE -DDX_NON_INLINE_ASM
LDFLAGS = -lDxLib\
-lDxUseCLib \
-lDxDrawFunc \
-ljpeg \
-lpng \
-lzlib \
-ltiff \
-ltheora_static \
-lvorbis_static \
-lvorbisfile_static \
-logg_static \
-lbulletdynamics \
-lbulletcollision \
-lbulletmath \
-lopusfile \
-lopus \
-lsilk_common \
-lcelt \

RM=rm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -m32 $(OBJS) -L $(LIBS) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(OBJS)
