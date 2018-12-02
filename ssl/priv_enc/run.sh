echo test | openssl rsautl -inkey private.pem -sign > signed1

openssl rsautl -inkey public.pem -pubin -in signed1

