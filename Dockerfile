FROM rust:slim as dep_rust

RUN apt-get update && apt-get install -y g++ \
            git \
            cmake \
            python3
