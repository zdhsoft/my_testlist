import mysql from 'mysql2';
import { dbcfg } from './config';

const connection = mysql.createConnection(dbcfg);
