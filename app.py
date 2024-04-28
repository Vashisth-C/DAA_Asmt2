from flask import Flask, render_template, request
from flask_cors import CORS
import time
import subprocess

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

@app.route('/comparitive_analysis')
def comparitive_analysis():
    return render_template('comparitive_analysis.html')


@app.route('/documentation')
def documentation():
    return render_template('documentation.html')

@app.route('/intro')
def intro():
    return render_template('intro.html')

@app.route('/demo')
def demo():
    return render_template('demonstrate.html')

@app.route('/submit', methods=['POST'])
def submit():
    content = request.form['content']
    with open('static/data/input.txt', 'w') as f:
        f.write(content)

    content_length = len(str(len(content)))
    base_pause_duration = 0.5
    pause_duration = base_pause_duration * content_length

    cpp_executable_path = './a.out'
    time.sleep(pause_duration)
    subprocess.Popen([cpp_executable_path])
    time.sleep(pause_duration)

    with open('static/data/output.txt', 'r') as file:
        output_content = file.read()
    return output_content

@app.route('/demonstrate')
def demonstrate():
    return render_template('demonstrate.html')

@app.route('/algowriteup')
def algowriteup():
    return render_template('algowriteup.html')

@app.route('/algorithm')
def algorithm():
    return render_template('algorithm.html')

if __name__ == '__main__':
    app.run(debug=True)