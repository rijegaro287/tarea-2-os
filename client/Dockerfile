FROM node:18-alpine
ENV NODE_ENV=production
WORKDIR ./
COPY . .
RUN npm install --production
CMD ["npm", "run", "start"]