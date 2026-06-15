
FROM ubuntu:24.04 AS dev-tools
# https://docs.docker.com/build/building/best-practices/#apt-get
# https://docs.datadoghq.com/security/code_security/static_analysis/static_analysis_rules/docker-best-practices/apt-pin-version/
RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential=12.10ubuntu1 \
  cmake=3.28.3-1build7 \
  libasio-dev=1:1.28.1-0.2 \
  rsync=3.2.7-1ubuntu1.5 \
  && rm -rf /var/lib/apt/lists/*

FROM dev-tools AS builder
WORKDIR /build
COPY . ./
RUN make copyRelease

FROM ubuntu:24.04
ARG GIT_COMMIT_HASH="undefined"
ARG SERVER_PORT=2323
ENV GIT_COMMIT_HASH=$GIT_COMMIT_HASH
ENV PORT=$SERVER_PORT
WORKDIR /app
# https://stackoverflow.com/questions/26504846/copy-directory-to-another-directory-using-add-command
COPY --from=builder build/sandbox/lib ./lib
COPY --from=builder build/sandbox/bin ./bin
COPY --from=builder build/sandbox/data ./data
# https://docs.docker.com/reference/dockerfile/#shell-and-exec-form
# https://docs.docker.com/reference/dockerfile/#entrypoint
ENTRYPOINT ["./bin/server"]
