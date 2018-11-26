#!/bin/bash
openssl rsautl -encrypt -inkey public.pem -passin pass:Password1, -pubin -in file.txt -out file.ssl
