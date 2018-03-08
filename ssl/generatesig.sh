#!/bin/bash
openssl dgst -sha256 -sign private.pem -out /tmp/sign.sha256 $1
openssl base64 -in /tmp/sign.sha256 -out $2
