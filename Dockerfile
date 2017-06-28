FROM arm32v7/debian:stretch-slim

RUN apt-get -yqq update
RUN apt-get -y install nginx

COPY index.html /var/www/html/index.html
COPY cat.gif /var/www/html/cat.gif
COPY entireframework.min.css /var/www/html/entireframework.min.css

CMD ["/usr/sbin/nginx -g 'daemon on; master_process on;'"]
