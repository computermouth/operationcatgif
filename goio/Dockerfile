FROM golang

WORKDIR /build
COPY gpio.go /build/
RUN GOOS=linux GOARCH=arm go build -o gpio -v .

FROM scratch
COPY --from=0 /build/gpio .
CMD ["./gpio"]
