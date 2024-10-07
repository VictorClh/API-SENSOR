from flask import Flask, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__, template_folder="views", static_folder="../public")

db = SQLAlchemy()

def create_app():
    app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://postgres:123456789@localhost/aula'
    app.config["SQLALCHEMY_TRACK_MODIFICATION"] = False
    app.config["SECRET_KEY"] = 'secret'
    app.config['JWT_SECRET_KEY'] = 'secret'
    
    db.init_app(app)
    
    return app

