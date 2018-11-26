#!/bin/bash
./generatekey.sh
./generatesig.sh foo signedfoo 
./verifysig.sh signedfoo foo
