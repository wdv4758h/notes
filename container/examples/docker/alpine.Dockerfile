FROM alpine:3.7

# install ca-certificates so that HTTPS works consistently
# the other runtime dependencies for Python are installed later
RUN apk add --no-cache ca-certificates

# Extra Resource:
# * Example for CPython: https://github.com/docker-library/python/blob/master/3.6/alpine3.7/Dockerfile
