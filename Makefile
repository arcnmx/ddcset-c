BINARY  = ddcset.exe
CFLAGS  = -g -O3 -march=native -Wall -Werror -I./ -I../common # -DDEBUG
LDFLAGS = -ldxva2

CFLAGS  += -ffast-math
CFLAGS  += -fdata-sections -ffunction-sections
CFLAGS  += -I../ -I.
LDFLAGS += -Wl,--gc-sections
CFLAGS  += -DWINVER=0x0602

PREFIX ?= x86_64-w64-mingw32-
STRIP  = $(PREFIX)strip
CC     = $(PREFIX)cc
CXX    = $(PREFIX)c++
LD     = $(CXX)

BUILD  ?= .build
BIN    ?= bin

OBJS   = main.o

BUILD_OBJS = $(foreach obj,$(OBJS),$(BUILD)/$(obj))

all: $(BIN)/$(BINARY)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CFLAGS) -o $@ $<

$(BIN)/$(BINARY): $(BUILD_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ $^ $(LDFLAGS)
	$(STRIP) -s $@

clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: clean
