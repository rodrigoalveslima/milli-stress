FROM ubuntu:20.04

# Install make & gcc
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y make gcc

# Copy and build milli-stress
COPY . /opt/milli-stress
WORKDIR /opt/milli-stress
RUN make

# The entrypoint command allows the container to be used
# as if it was the normal executable,
# passing through all arguments
ENTRYPOINT ["./milli-stress"]
