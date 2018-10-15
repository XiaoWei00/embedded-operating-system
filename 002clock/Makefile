
CC := arm-linux-gcc

LD := arm-linux-ld

LDS := s3c2440.lds

INSRCS := $(wildcard *.c)

SRCS := $(wildcard *.c *.S)

OBJS := $(patsubst %.c,%.o,$(SRCS))

OBJS := $(patsubst %.S,%.o,$(OBJS))

TARGET := main.elf 

.PHONY : all
all:$(TARGET)

$(TARGET):$(OBJS)
	$(LD) -T $(LDS)  $^	-o $(TARGET)
	
%.o:%.c %.S 
	$(CC) -c -o $@ $<
	
sinclude $(INSRCS:.c=.d)
%.d:%.c 
	$(CC) -MM $^ > $@.$$$$;\
	sed 's/\($*.o\)/\1 $@/g' < $@.$$$$ > $@;\
	rm -f $@.$$$$	


.PHONY : bin
bin :
	arm-linux-objcopy -O binary -S  $(TARGET) main.bin
	
.PHONY : dis
dis:
	arm-linux-objdump -D $(TARGET) > main.dis

.PHONY :clean
clean:
	rm -f *.elf *.bin *.o *.dis *.i *.d
    
