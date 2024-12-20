from flask import Flask

# Initialize the Flask app
app = Flask(__name__)

# Define a route
@app.route('/')
def home():
    return "<b>Hello, From the FLASK APP!</b>"

# Run the app
if __name__ == "__main__":
    app.run(debug=True)
