#!/bin/bash
openssl dgst -sha256 -sign private.pem -passin pass:Password1, -out /tmp/sign.sha256 $1
openssl base64 -in /tmp/sign.sha256 -out $2
