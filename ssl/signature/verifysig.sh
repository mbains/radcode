#!/bin/bash
openssl base64 -d -in $1 -out /tmp/sign.sha256
openssl dgst -sha256 -verify public.pem -signature /tmp/sign.sha256 $2
