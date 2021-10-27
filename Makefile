CC=gcc
DEBUG= -g3 -fsanitize=address
#CC=clang
#DEBUG=-g3 -fsanitize=leak
FLAGS=-Wall -Wextra -Werror
INCLUDES= -I includes/

SRC_PATH=./src/
UTILS_PATH=./utils/
OBJS_SRC_PATH=./src_obj/
OBJS_UTILS_PATH=./utils_obj/
TARGET=my_curl

SRC := $(wildcard $(SRC_PATH)*.c)
UTILS := $(wildcard $(UTILS_PATH)*.c)

SRC_NAMES := $(notdir $(SRC))
UTILS_NAMES := $(notdir $(UTILS))
SRC_OBJS := $(addprefix $(OBJS_SRC_PATH), $(SRC_NAMES:.c=.o))
UTILS_OBJS := $(addprefix $(OBJS_UTILS_PATH), $(UTILS_NAMES:.c=.o))

all: $(TARGET)

$(TARGET): $(SRC_OBJS) $(UTILS_OBJS)
	@$(CC) $(FLAGS) $(DEBUG) $(INCLUDES) $(SRC_OBJS) $(UTILS_OBJS) -o $@

$(OBJS_SRC_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJS_SRC_PATH)
	@$(CC) $(FLAGS) $(DEBUG) $(INCLUDES) -c $< -o $@

$(OBJS_UTILS_PATH)%.o: $(UTILS_PATH)%.c
	@mkdir -p $(OBJS_UTILS_PATH)
	@$(CC) $(FLAGS) $(DEBUG) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJS_SRC_PATH) $(OBJS_UTILS_PATH)

fclean: clean
	@/bin/rm -rf $(TARGET)

re: fclean $(TARGET)

.PHONY: clean fclean all
