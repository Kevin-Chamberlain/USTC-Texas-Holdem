CC       := gcc
CFLAGS   := -std=c11 -O2 -g -I.
LDFLAGS  :=

TARGET   := poker.exe
SRCS     := \
    game/main.c \
    game/card.c \
    game/judgement.c \
    game/library.c \
    game/m_ai.c \
    game/procedure.c \
    game/action.c \
    game/var_global.c \
    welcome/menu_ANSI.c \
    welcome/posix_getch.c
OBJS     := $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

# 关断言