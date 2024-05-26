
project="cheli"

inc_terra="-Iterra/include -Lterra/ -lterra"

red_echo() {
    local text=$1
    echo -e "\e[31m$text\e[0m"
}

green_echo() {
    local text=$1
    echo -e "\e[32m$text\e[0m"
}

yellow_echo() {
    local text=$1
    echo -e "\e[33m$text\e[0m"
}

echo -n "Compiling all files for project "
yellow_echo "$project"

########## Compiling Terra ##########
if [ ! -f ./terra/libterra.a ]; then
    cd terra && ./build.sh -lib
    error_code=$?

    cd ../

    echo -n "Compiling Terra "
    if [ $error_code -eq 0 ]; then
        green_echo "finished"
    else
        red_echo "failed"
    fi
fi
#####################################

if [ "$1" == "-so" ]; then
########## Compiling Static Library ##########
    echo -n "Generating shared object Library "
    yellow_echo "lib$project.so"

    # Check if debug directory exists
    if [ ! -d "./debug" ]; then
        mkdir debug
    fi 
#############################################

######### Add Source Files #########
    g++ -c src/board.cpp        -Iinclude -fPIC -o debug/board.o $inc_terra -lm && \
    g++ -c src/square.cpp       -Iinclude -fPIC -o debug/square.o $inc_terra -lm && \
    g++ -c src/piece.cpp        -Iinclude -fPIC -o debug/piece.o $inc_terra -lm && \
    g++ -c src/move.cpp         -Iinclude -fPIC -o debug/move.o $inc_terra -lm && \
    g++ -c src/logic.cpp        -Iinclude -fPIC -o debug/logic.o $inc_terra -lm && \
    g++ -shared debug/* -fPIC -o lib${project}.so $inc_terra
###################################
    error_code=$?

    echo -n "Compiling library "
    if [ $error_code -eq 0 ]; then
        echo -n "was "
        green_echo "successfull"
    else
        red_echo "failed"
    fi
###################################

########## Compiling Static Library ##########
elif [ "$1" == "-lib" ]; then
    echo -n "Generating static Library "
    yellow_echo "lib$project.a"

    # Check if debug directory exists
    if [ ! -d "./debug" ]; then
        mkdir debug
    fi 
#############################################

######### Add Source Files #########
    g++ -c src/board.cpp    -Iinclude      -o debug/board.o $inc_terra -lm && \
    g++ -c src/square.cpp   -Iinclude      -o debug/square.o $inc_terra -lm && \
    g++ -c src/piece.cpp    -Iinclude      -o debug/piece.o $inc_terra -lm && \
    g++ -c src/move.cpp     -Iinclude      -o debug/move.o $inc_terra -lm && \
    g++ -c src/logic.cpp    -Iinclude      -o debug/logic.o $inc_terra -lm && \
    ar rcs lib$project.a debug/*
    error_code=$?

    echo -n "Compiling library "
    if [ $error_code -eq 0 ]; then
        echo -n "was "
        green_echo "successfull"
    else
        red_echo "failed"
    fi

###################################

########## Compiling Binary ##########
else 
######### Add Source Files #########
    g++ -o $project -Wextra -Wall -pedantic -g -Iinclude \
        src/main.cpp \
        src/board.cpp \
        src/piece.cpp \
        src/square.cpp \
        src/move.cpp \
        src/logic.cpp \
        $inc_terra -lm \
###################################
    error_code=$?
    echo -n "Compiling $project "
    if [ $error_code -eq 0 ]; then
        green_echo "finished" 
    else
        red_echo "failed" 
    fi
fi
