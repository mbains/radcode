#!/bin/bash
openssl genrsa -aes128 -passout pass:Password1, -out private.pem 4096
openssl rsa -in private.pem -passin pass:Password1, -pubout -out public.pem
