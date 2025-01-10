const mysql = require('mysql2');
require('dotenv').config();

const dbConfig = {
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_NAME,
    port: process.env.DB_PORT,
    connectTimeout: 60000, // 60 seconds
};

const pool = mysql.createPool(dbConfig);
const promisePool = pool.promise();

const testConnection = async () => {
    try {
        const [rows, fields] = await promisePool.query('SELECT 1');
        console.log('Database connected successfully');
        await createFeedbackTable();
    } catch (error) {
        console.error('Error connecting to the database:', error);
    }
};

const createFeedbackTable = async () => {
    const createTableQuery = `
        CREATE TABLE IF NOT EXISTS feedback (
            id INT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(255) NOT NULL,
            email VARCHAR(255) NOT NULL,
            message TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    `;
    
    try {
        await promisePool.query(createTableQuery);
        console.log('Feedback table checked/created successfully');
    } catch (error) {
        console.error('Error creating table:', error);
    }
};

testConnection();

const Feedback = {
    create: async (feedback) => {
        try {
            const [result] = await promisePool.query(
                'INSERT INTO feedback (name, email, message) VALUES (?, ?, ?)',
                [feedback.name, feedback.email, feedback.message]
            );
            return result;
        } catch (error) {
            console.error('Error creating feedback:', error);
            throw error;
        }
    }
};

module.exports = Feedback;
