#/bin/sh

# Test ft_ping
# Usage: ./tester.sh

LOG=log/
FILE=${LOG}ft_ping.log
COMP=${LOG}ping.log
DIFF=${LOG}diff.log

test() {

    # Usage: test arg
    
    echo "ft_ping $1" >> $FILE
    ./bin/ft_ping $1 >> $FILE 2>&1
    echo "" >> $FILE
    echo "ping $1" >> $COMP
    ping $1 >> $COMP 2>&1
    echo "" >> $COMP
}

# INIT

make
mkdir -p $LOG
> $FILE
> $COMP
> $DIFF

# TEST AMBIGUITY

test --i
test --p

# COMPARE

sed -i 's/ft_ping/ping/g' $FILE # Replace ft_ping with ping
sed -i 's/ '\''--program-name'\''//g' $COMP # Remove --program-name (flag absent from ping --help)
diff $FILE $COMP > $DIFF
sed -i 's/ping/ft_ping/g' $FILE # Replace ping with ft_ping