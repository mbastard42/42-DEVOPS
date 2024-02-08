#/bin/sh

# Test ft_ping's parsing against ping's parsing
# Usage: ./tester.sh
#
# VARIABLES AND FUNCTIONS

    LOG=log/

    FILE=${LOG}ft_ping.log
    COMP=${LOG}ping.log
    DIFF=${LOG}diff.log

    test() {

        # Usage: test arg
        
        echo "ft_ping $1" >> $FILE
        ./bin/ft_ping $1 >> $FILE 2>&1
        echo $? >> $FILE
        echo "" >> $FILE
        echo "ping $1" >> $COMP
        ping $1 >> $COMP 2>&1
        echo $? >> $COMP
        echo "" >> $COMP
    }
#
# INIT

    make
    mkdir -p $LOG
    > $FILE
    > $COMP
    > $DIFF
#
# TEST AMBIGUITY (exept --r for --router, not present in ping --help)

    test --a
    test --c
    test --d
    test --e
    test --f
    test --h
    test --i
    test --l
    test --m
    test --n
    test --p
    test --q
    test --s
    test --t
    test --t
    test --u
    test --v
#
# TEST BOOLEAN (exept --version, of course)

    test --a
    test --address
    test --address=
    test -d
    test --d
    test --debug
    test --debug=
    test --e
    test --echo
    test --echo=
    test -f
    test --f
    test --flood
    test --flood=
    test -?
    test --h
    test --help
    test --help=
    test -r
    test --ig
    test --ignore-routing
    test --ignore-routing=
    test --m
    test --mask
    test --mask=
    test -n
    test --n
    test --numeric
    test --numeric=
    test -q
    test --q
    test --quit
    test --quit=
    test -R
    # test --r Ambiguity with --router
    test --route
    test --route=
    test --times
    test --timestamp
    test --timestamp=
    test -v
    test --verb
    test --verbose
    test --verbose=
#
# TEST VALUES

    # TEST COUNT

        test -c
        test --count
        test --count=
        test --count=example
        test --count=123example
        test -c 0
        test --count 123
        test --count -1
        test --count=2147483647
        test --count=2147483648
        test --count=+2147483647
        test --count=-2147483647
        test --count=-2147483648
        test --count=FFF
        test --count=0x123FFF
        test --count=0x-123FFF
        test --count=0x+123FFF
        test --count=0x123-FFF
        test --count=+0x123FFF
        test --count=-0x123FFF
    #
    # TEST INTERVAL

        test -i
        test --interval
        test --interval=
        test --interval=example
        test --interval=123example
        test -i 0
        test --interval 123
        test --interval -1
        test --interval=2147483647
        test --interval=2147483648
        test --interval=+2147483647
        test --interval=-2147483647
        test --interval=-2147483648
        test --interval=FFF
        test --interval=0x123FFF
        test --interval=0x-123FFF
        test --interval=0x+123FFF
        test --interval=0x123-FFF
        test --interval=+0x123FFF
        test --interval=-0x123FFF
    #
    # TEST IP-TIMESTAMP

        test -t
        test --timestamp
        test --timestamp tsonly
        test --timestamp tsaddr
        test --timestamp=
        test --timestamp=example
        test --timestamp=123example
        test -t 0
        test --timestamp 123
        test --timestamp -1
        test --timestamp=2147483647
        test --timestamp=2147483648
        test --timestamp=+2147483647
        test --timestamp=-2147483647
        test --timestamp=-2147483648
        test --timestamp=FFF
        test --timestamp=0x123FFF
        test --timestamp=0x-123FFF
        test --timestamp=0x+123FFF
        test --timestamp=0x123-FFF
        test --timestamp=+0x123FFF
        test --timestamp=-0x123FFF
    #
    # TEST LINGER

        test -l
        test --linger
        test --linger=
        test --linger=example
        test --linger=123example
        test -l 0
        test --linger 123
        test --linger -1
        test --linger=2147483647
        test --linger=2147483648
        test --linger=+2147483647
        test --linger=-2147483647
        test --linger=-2147483648
        test --linger=FFF
        test --linger=0x123FFF
        test --linger=0x-123FFF
        test --linger=0x+123FFF
        test --linger=0x123-FFF
        test --linger=+0x123FFF
        test --linger=-0x123FFF
    #
    # TEST PATTERN

        test -p
        test --pattern
        test --pattern=
        test --pattern=example
        test --pattern=123example
        test -p 0
        test --pattern 123
        test --pattern -1
        test --pattern=2147483647
        test --pattern=2147483648
        test --pattern=+2147483647
        test --pattern=-2147483647
        test --pattern=-2147483648
        test --pattern=FFF
        test --pattern=0x123FFF
        test --pattern=0x-123FFF
        test --pattern=0x+123FFF
        test --pattern=0x123-FFF
        test --pattern=+0x123FFF
        test --pattern=-0x123FFF
    #
    # TEST PRELOAD

        test -p
        test --preload
        test --preload=
        test --preload=example
        test --preload=123example
        test -p 0
        test --preload 123
        test --preload -1
        test --preload=2147483647
        test --preload=2147483648
        test --preload=+2147483647
        test --preload=-2147483647
        test --preload=-2147483648
        test --preload=FFF
        test --preload=0x123FFF
        test --preload=0x-123FFF
        test --preload=0x+123FFF
        test --preload=0x123-FFF
        test --preload=+0x123FFF
        test --preload=-0x123FFF
    #
    # TEST SIZE

        test -s
        test --size
        test --size=
        test --size=example
        test --size=123example
        test -s 0
        test --size 123
        test --size -1
        test --size=65399
        test --size=65400
        test --size=+65399
        test --size=-2147483647
        test --size=-2147483648
        test --size=FFF
        test --size=0x123FFF
        test --size=0x-123FFF
        test --size=0x+123FFF
        test --size=0x123-FFF
        test --size=+0x123FFF
        test --size=-0x123FFF
    #
#
# COMPARE

    sed -i 's/ft_ping/ping/g' $FILE # Replace ft_ping with ping
    sed -i 's/ '\''--program-name'\''//g' $COMP # Remove --program-name (flag absent from ping --help)
    diff $FILE $COMP > $DIFF
    sed -i 's/ping/ft_ping/g' $FILE # Replace ping with ft_ping
#
# RESULT

    if [ -s $DIFF ]
    then
        echo "\e[0;31mKO\033[0m"
        echo "Check $DIFF"
    else
        echo "\e[0;32mOK\033[0m"
    fi
#