const Feedback = require('../models/feedback');

exports.submitFeedback = (req, res) => {
    const feedbackData = {
        name: req.body.name,
        email: req.body.email,
        message: req.body.message
    };

    Feedback.create(feedbackData, (err, result) => {
        if (err) {
            return res.status(500).send('Error saving feedback');
        }
        res.status(200).send('Feedback submitted successfully!');
    });
};
