# valgrind

FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app

RUN make

CMD ["valgrind", "./exec/philo"]
