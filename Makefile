CFLAGS    += -O3 -g -I./include -DDEBUG
LDFLAGS   += -g -L./lib -lcunit

CFLAGS    += -fopenmp

CSRC      := src/cmat.c
OBJS      := $(patsubst %.c,%.o, $(CSRC))

TARGET    := lib/libcmat.a

all: $(TARGET)

$(TARGET): $(OBJS)
	@if [ ! -e $(dir $(TARGET)) ];then mkdir -p $(dir $(TARGET));fi
	ar rcs $@ $^
	ranlib $@

src/cmat.c: include/cmat.h


test:
	make -C tests

benchmark:
	make -C tests benchmark

clean:
	rm -rf $(dir $(TARGET)) $(OBJS)

clean-test:
	make -C tests $@

