# syntax=docker/dockerfile:1
FROM debian:buster
WORKDIR /tmp
RUN apt update -y && apt install -y wget curl
RUN wget https://github.com/gohugoio/hugo/releases/download/v0.84.0/hugo_0.84.0_Linux-64bit.deb
RUN apt install ./hugo_0.84.0_Linux-64bit.deb

RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash -
RUN apt-get install -y nodejs

COPY ./ /tmp/soundseeker
WORKDIR /tmp/soundseeker
RUN ./build.sh


FROM nginx:alpine

COPY --from=0 /tmp/soundseeker/public /usr/src/public
COPY --from=0 /tmp/soundseeker/nginx.default.conf /etc/nginx/conf.d/default.conf
EXPOSE 80

ENTRYPOINT ["nginx","-g","daemon off;"]