import path from 'node:path';
import dotenv from 'dotenv';

import express, { Express, Response, Request, NextFunction } from 'express';
import cors from 'cors';

dotenv.config({ path: path.resolve('./build/.env') });

const SERVER_PORT: number = Number(process.env.SERVER_PORT) || 8080;

const app: Express = express();

app.use(express.static(path.resolve('./build/Views')));

app.use(cors({
  origin: '*',
  methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
  allowedHeaders: [
    'Content-Type', 'Authorization',
    'Accept', 'Origin', 'X-Requested-With'
  ]
}));

app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use((error: any, req: Request, res: Response, next: NextFunction) => {
  if (error) {
    console.error(error);
    return res.send({
      status: 'error',
      message: 'INTERNAL SERVER ERROR.'
    });
  }

  return next();
});

app.use('*', (req, res) => res.sendFile(path.resolve('./build/Views/index.html')));

app.listen(SERVER_PORT, () => {
  console.log(`Server is running on http://localhost:${SERVER_PORT}`);
});