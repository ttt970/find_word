CC     := gcc
CFLAGS := -Wall -g

TARGET := dict
OBJS   := main.o search.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)
