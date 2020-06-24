#!/bin/bash

exe=project

##### NPUsim run usage #####
print_help() {
    echo -e "Usage: $0        for running"
    echo -e "Usage: $0 [gdb]  for debugging"
    exit 0
}

# Print usage help 
if [[ "$#" -gt 1 || $1 = '-h' || $1 = '--help' ]];  then
    print_help
fi

# for running
if [[ "$#" -eq 0  ]];  then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/ext/DRAMsim3
    ./$exe
fi

# for debugging
if [[ "$#" -eq 1  ]];  then
    action=$1; shift
    if [[ $action != gdb ]]; then
        echo -e "Error: unknown action $action"
        print_help
    fi
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/ext/DRAMsim3
    gdb $exe
fi
