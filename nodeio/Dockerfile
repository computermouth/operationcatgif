FROM scratch

ENV nodever="v6.11.0"
ADD https://nodejs.org/dist/${nodever}/node-${nodever}-linux-armv7l.tar.xz /

##########################################

FROM arm32v7/debian:stretch-slim
ENV nodever="v6.11.0"
COPY --from=0 /node-${nodever}-linux-armv7l/bin/node /
#COPY --from=0 /node-${nodever}-linux-armv7l/bin     ./bin
#COPY --from=0 /node-${nodever}-linux-armv7l/include ./include
#COPY --from=0 /node-${nodever}-linux-armv7l/lib     ./lib
#COPY --from=0 /node-${nodever}-linux-armv7l/share   ./share

COPY index.js /
COPY package.json /

CMD ["./node", "./index.js"]
