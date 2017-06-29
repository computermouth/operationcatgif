FROM arm32v7/debian:stretch-slim

RUN apt-get -yqq update &&\
 apt-get -y --no-install-recommends install nginx-light &&\
 apt-get -y clean &&\
 rm -rf /var/lib/apt/lists/*

COPY index.html /var/www/html/index.html
COPY cat.gif /var/www/html/cat.gif
COPY entireframework.min.css /var/www/html/entireframework.min.css
