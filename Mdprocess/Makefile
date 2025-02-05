SRCS = main.c
LIBSRCS = test.c
CC = gcc
OPTS = -Wall -g
LIBS = -L. -lmdprocess
OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)

TARG = mp
LARS = libmdprocess.a

make: $(TARG)
$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static
$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)
$.O: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(TARG)
