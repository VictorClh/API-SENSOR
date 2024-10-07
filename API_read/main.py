from flask import Flask, jsonify
from flask_restful import Api
from app import create_app
from flask_jwt_extended import JWTManager
from app.routes import Sensor_modelo, Sensors_modelo

app = create_app()
api = Api(app)
jwt = JWTManager(app)

api.add_resource(Sensor_modelo, '/sensor_api')
api.add_resource(Sensors_modelo, '/sensor_api/<string:id>')

if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=False)
