#!/bin/bash

    echo "File to turn into capital"

    read filename
    cat $filename | tr 'a-z' 'A-Z'
