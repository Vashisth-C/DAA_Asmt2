from flask import Flask, render_template
from flask_cors import CORS

app = Flask(__name__)
CORS(app, resources={r"/api/*": {"origins": "*"}})

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/about_us')
def about_us():
    return render_template('about_us.html')

@app.route('/intro')
def info():
    return render_template('intro.html')

@app.route('/comp_analysis')
def comp_analysis():
    return render_template('comp_analysis.html')

@app.route('/documentation')
def documentation():
    return render_template('documentation.html')

@app.route('/intro')
def intro():
    return render_template('intro.html')

if __name__ == '__main__':
    app.run(debug=True)