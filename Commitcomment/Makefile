SRCS = main.c
LIBSRCS = getdate.c
CC = gcc
OPTS = -Wall -g
LIBS = -L. -lcommitcomment
OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)

TARG = cc
LARS = libcommitcomment.a

make: $(TARG)
$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static
$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)
$.0: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(TARG)
