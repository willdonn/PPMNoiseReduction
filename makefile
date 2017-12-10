CFLAGS = -Wall -g -pg -ansi
OBJS1 = main.o readPPM.o writePPM.o denoiseImage.o timing.o

all: denoise

denoise: $(OBJS1)
	$(CC) -o $@ $?


clean:
	rm -rf $(OBJS1) denoise
