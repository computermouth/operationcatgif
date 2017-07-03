FROM debian:stretch

ENV PATH="/root/.cargo/bin:${PATH}"

RUN apt-get -y update &&\
  apt-get -y install crossbuild-essential-armhf curl

RUN curl https://sh.rustup.rs -sSf | sh -s -- -y

RUN rustup target add armv7-unknown-linux-gnueabihf

COPY rustio /build/rustio
WORKDIR /build/rustio

RUN mkdir /.cargo && \
  echo "[target.armv7-unknown-linux-gnueabihf]\nlinker = \"arm-linux-gnueabihf-gcc\"" >> /root/.cargo/config

RUN cargo build --target=armv7-unknown-linux-gnueabihf --release


FROM arm32v7/debian:stretch-slim
COPY --from=0 /build/rustio/target/armv7-unknown-linux-gnueabihf/release/rustio /gpio
CMD ["./gpio"]
