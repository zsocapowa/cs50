FROM nginx:1.25.4-alpine
WORKDIR /usr/share/nginx/html
RUN rm -rf ./*
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./public .
CMD ["nginx", "-g", "daemon off;"]
