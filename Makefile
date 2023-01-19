CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 #-g -fsanitize=leak,address,undefined

SRC_PATH	=	./src
OBJ_PATH	=	obj
INC_PATH	=	./inc
TEST_LOGS	=	./tester

SRC			=	${SRC_PATH}/main.cpp

HEADERS		=	${wildcard ${INC_PATH}/*.hpp}

HEAD_DEP	=	${HEADERS:${INC_PATH}/%.hpp=${INC_PATH}/%.hpp}

OBJ			=	${SRC:${SRC_PATH}/%.cpp=${OBJ_PATH}/%.o}

TEST		=	tests

TEST_SRC	=	${SRC_PATH}/tester_map.cpp	\
				${SRC_PATH}/tester_stack.cpp \
				${SRC_PATH}/tester_vector.cpp \
				${SRC_PATH}/tester_main.cpp	\
				${SRC_PATH}/tester.cpp

TEST_OBJ	=	${TEST_SRC:${SRC_PATH}/%.cpp=${OBJ_PATH}/%.o}

NAME		=	containers

.PHONY : all clean fclean re

all: ${NAME} ${TEST}

${TEST}: ${TEST_OBJ} | ${TEST_LOGS}
	${CC} ${CFLAGS} $^ -o $@

run : all
	@./${NAME}
	@./${TEST}

${OBJ_PATH} : 
	mkdir ${OBJ_PATH}

${TEST_LOGS}:
	mkdir -p ${TEST_LOGS}

${OBJ_PATH}/%.o : ${SRC_PATH}/%.cpp ${HEAD_DEP} | ${OBJ_PATH} ${TESTER_FOLDER}
	${CC} ${CFLAGS} -o $@ -c $< -I${INC_PATH}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -rf ${OBJ_PATH}
	rm -rf ${TEST_LOGS}

fclean: clean
	rm -f ${NAME}
	rm -f ${TEST}

re : fclean all
