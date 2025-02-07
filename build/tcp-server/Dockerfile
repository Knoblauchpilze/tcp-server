
FROM ubuntu:22.04 AS dev-tools
# https://docs.docker.com/build/building/best-practices/#apt-get
# https://docs.datadoghq.com/security/code_security/static_analysis/static_analysis_rules/docker-best-practices/apt-pin-version/
RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential=12.9ubuntu3 \
  cmake=3.22.1-1ubuntu1.22.04.2 \
  libasio-dev=1:1.18.1-1 \
  rsync=3.2.7-0ubuntu0.22.04.4 \
  && rm -rf /var/lib/apt/lists/*

FROM dev-tools AS builder
WORKDIR /build
COPY . ./
RUN make sandbox

FROM ubuntu:22.04
ARG GIT_COMMIT_HASH="undefined"
ARG SERVER_PORT=2323
ENV GIT_COMMIT_HASH=$GIT_COMMIT_HASH
ENV PORT=$SERVER_PORT
WORKDIR /app
COPY --from=builder build/sandbox .
# https://docs.docker.com/reference/dockerfile/#shell-and-exec-form
# https://stackoverflow.com/questions/40454470/how-can-i-use-a-variable-inside-a-dockerfile-cmd
CMD ["sh", "-c", "./run.sh server ${PORT}"]
