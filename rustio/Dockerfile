FROM debian:stretch

ENV PATH="/root/.cargo/bin:${PATH}"

COPY rustio /build/rustio
WORKDIR /build/rustio

RUN apt-get -y update &&\
  apt-get -y install crossbuild-essential-armhf curl

RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
RUN mkdir /.cargo && \
  echo "[target.armv7-unknown-linux-gnueabihf]\nlinker = \"arm-linux-gnueabihf-gcc\"" >> /root/.cargo/config
RUN rustup target add armv7-unknown-linux-gnueabihf

RUN cargo build --target=armv7-unknown-linux-gnueabihf --release
#RUN mv target/armv7-unknown-linux-gnueabihf/release/rustio gpio

##########################################################

FROM scratch
COPY --from=0 /build/rustio/target/armv7-unknown-linux-gnueabihf/release/rustio /gpio
CMD ["/gpio"]
