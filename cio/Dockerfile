FROM debian:stretch-slim

WORKDIR .
RUN apt-get -yqq update 
RUN apt-get install -y crossbuild-essential-armhf
COPY gpio.c .
RUN arm-linux-gnueabihf-gcc gpio.c -o gpio -static

FROM scratch
COPY --from=0 gpio .
CMD ["./gpio"]
