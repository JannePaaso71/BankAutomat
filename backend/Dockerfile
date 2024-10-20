FROM node:latest

WORKDIR /app
COPY . .
RUN npm install && mv node_modules ..
EXPOSE 3000

CMD node start


