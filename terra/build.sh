
project="terra"

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
    g++ -c src/tmatrix.cpp      -Iinclude -fPIC -o debug/tmatrix.o && \
    g++ -c src/tlist.cpp        -Iinclude -fPIC -o debug/tlist.o && \
    g++ -c src/tlog.cpp         -Iinclude -fPIC -o debug/tlog.o && \
    g++ -c src/tstring.cpp      -Iinclude -fPIC -o debug/tstring.o && \
    g++ -c src/tfile.cpp        -Iinclude -fPIC -o debug/tfile.o && \
    g++ -c src/tvector.cpp      -Iinclude -fPIC -o debug/tvector.o && \
    g++ -c src/tstringlist.cpp  -Iinclude -fPIC -o debug/tstringlist.o && \
    g++ -c src/thash.cpp        -Iinclude -fPIC -o debug/thash.o && \
    g++ -shared debug/* -fPIC -o lib${project}.so 
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
    g++ -c src/tmatrix.cpp      -Iinclude  -fPIC    -o debug/tmatrix.o && \
    g++ -c src/tlist.cpp        -Iinclude  -fPIC    -o debug/tlist.o && \
    g++ -c src/tlog.cpp         -Iinclude  -fPIC    -o debug/tlog.o && \
    g++ -c src/tstring.cpp      -Iinclude  -fPIC    -o debug/tstring.o && \
    g++ -c src/tfile.cpp        -Iinclude  -fPIC    -o debug/tfile.o && \
    g++ -c src/tvector.cpp      -Iinclude  -fPIC    -o debug/tvector.o && \
    g++ -c src/tstringlist.cpp  -Iinclude  -fPIC    -o debug/tstringlist.o && \
    g++ -c src/thash.cpp        -Iinclude  -fPIC    -o debug/thash.o && \
    ar rcs lib$project.a debug/*
###################################
    error_code=$?

    echo -n "Compiling library "
    if [ $error_code -eq 0 ]; then
        echo -n "was "
        green_echo "successfull"
    else
        red_echo "failed"
    fi

########## Compiling Binary ##########
else 
    echo -n "Compiling all files for project "
    yellow_echo "$project"
######### Add Source Files #########
    g++ -o $project -Wextra -Wall -pedantic -g -Iinclude \
        src/main.cpp \
        src/tmatrix.cpp \
        src/tlog.cpp \
        src/tlist.cpp \
        src/tstring.cpp \
        src/tfile.cpp \
        src/tvector.cpp \
        src/tstringlist.cpp \
        src/thash.cpp \
###################################
    error_code=$?
    echo -n "Compiling "
    if [ $error_code -eq 0 ]; then
        green_echo "finished" 
    else
        red_echo "failed" 
    fi
fi
