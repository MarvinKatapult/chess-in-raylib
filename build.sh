
project="chess_in_raylib"

inc_raylib="-Lraylib/src/ -lraylib -Iraylib/src"
inc_terra="-Lterra -lterra -Iterra/include"

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

######### Compiling Raylib #########
    cd raylib/src/ 
    make PLATFORM=PLATFORM_DESKTOP -j
    error_code=$?
    echo -n "Compiling Raylib "
    if [ $error_code -eq 0 ]; then
        green_echo "finished"
    else
        red_echo "failed"
    fi
    cd ../..
####################################

########## Compiling Binary ##########
    echo -n "Compiling "
    yellow_echo "$project"
######### Add Source Files #########
    g++ -o $project -Wextra -Wall -pedantic -g -Iinclude \
        src/main.cpp \
        $inc_raylib $inc_terra -lm
###################################
    error_code=$?
    echo -n "Compiling "
    if [ $error_code -eq 0 ]; then
        green_echo "finished" 
    else
        red_echo "failed" 
    fi
