#/bin/sh

# Test parsing of ft_ping
# Usage: ./parsing_tester.sh

FILE=tester.log

test() {

    # Usage: test arg
    
    echo "ping $1" >> $FILE
    ping $1 >> $FILE 2>&1
    echo "---------------------------------------------------- VS ----------------------------------------------------" >> $FILE
    echo "./bin/ft_ping $1" >> $FILE
    ./bin/ft_ping $1 >> $FILE 2>&1
    echo "" >> $FILE
    echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> $FILE
    echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> $FILE
    echo "" >> $FILE
}

> $FILE
test --i
test --cou