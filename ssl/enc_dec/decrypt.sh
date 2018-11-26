#!/bin/bash
openssl rsautl -decrypt -inkey private.pem -passin pass:Password1, -in file.ssl
