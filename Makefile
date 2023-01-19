CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 #-g -fsanitize=leak,address,undefined

SRC_PATH	=	./src
OBJ_PATH	=	obj
INC_PATH	=	./inc
TESTER_FOLDER	=	./tester

SRC			=	$(wildcard ${SRC_PATH}/*.cpp)

HEADERS		=	${wildcard ${INC_PATH}/*.hpp}

HEAD_DEP	=	${HEADERS:${INC_PATH}/%.hpp=${INC_PATH}/%.hpp}

OBJ			=	${SRC:${SRC_PATH}/%.cpp=${OBJ_PATH}/%.o}

NAME		=	containers

.PHONY : all clean fclean re

all: ${NAME}

run : all
	@./${NAME}

${OBJ_PATH} : 
	mkdir ${OBJ_PATH}

${TESTER_FOLDER}:
	mkdir -p ${TESTER_FOLDER}

${OBJ_PATH}/%.o : ${SRC_PATH}/%.cpp ${HEAD_DEP} | ${OBJ_PATH} ${TESTER_FOLDER}
	${CC} ${CFLAGS} -o $@ -c $< -I${INC_PATH}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -rf ${OBJ_PATH}
	rm -rf ${TESTER_FOLDER}

fclean: clean
	rm -f ${NAME}

re : fclean all
