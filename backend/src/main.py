#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging
import subprocess
import os

from flask import Flask, Response, jsonify, render_template
import datetime 
import ttb

x = datetime.datetime.now()

def __repr__(self):
    return "<Articles %r>" % self.title
            
def main():
    # Initialize logging
    logging.basicConfig(
        format="[%(asctime)s %(levelname)s %(name)s] %(message)s", level=logging.INFO
    )

    # Initialize parser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--algo",
        default="./bin/algo",
        type=str,
        help="Path to the compiled scheduler binary",
    )
    parser.add_argument(
        "-db",
        "--database",
        default="./data/courses.csv",
        type=str,
        help="Path to the course database file",
    )
    parser.add_argument(
        "--debug",
        action="store_true",
        help="Run in debug mode",
    )
    parser.add_argument(
        "-p",
        "--port",
        default="5000",
        type=int,
        help="Port number to listen on"
    )
    parser.add_argument(
        "-n",
        "--natalia",
        action="store_true",
        help="Use if running on ug machines"
    )
    # Parse args
    args = parser.parse_args()

    # Read the course database
    db = ttb.Courses(args.database)
    
    # Initialize application
    app = Flask(__name__, template_folder='templates')
    # Define endpoints
    @app.get("/all")
    def all() -> Response:
        return jsonify(db.all)
    @app.get("/gen")
    def gen() -> Response:
        out = subprocess.run([args.algo, "query"], capture_output=True)
        return out.stdout
    @app.route("/data")
    def get_time():
        # Returning an api for showing in  reactjs
        return {
            'Name':"geek", 
            "Age":"22",
            "Date":x, 
            "programming":"python"
            }
    #@app.route('/move_forward')
    #def move_forward():
        # Returning an api for showing in  reactjs
        #out = "BUTTON PRESSED "
    @app.route('/')
    @app.route('/main')
    def main_page():
        return 'Want to see a schedule? <a href="/basic-schedule">Yes!</a>'
    @app.route('/basic-schedule')
    def micah_schedule():
        #out = subprocess.run([args.algo, "get_schedule"], capture_output=True)
        
        #make a schedule
        #return out.stdout
        
        #2d array: [course_id, course_name, course_type, section_id]
        return [
            ["ECE231", "101", "TUT"],
            ["ECE231", "102", "TUT"],
            ["ECE231", "103", "TUT"],
            ["ECE231", "101", "PRA"],
            
        ]
    @app.route("/send-request", methods=["POST"])
    def add_articles():
        print("hi")
        #body = request.json['body']
        #body = jsonify(body)
        body = "this is the body"
        print("body is being requested")
        body.headers.add('Access-Control-Allow-Origin', '*')
        return body
    # Run app
    """
    if (parser.parse_args(['-n'])):
        app.run(
            host="ug214",
            debug=args.debug,
            port=args.port
        )
    else:
        app.run(
            debug=args.debug,
            port=args.port
        )
    """
    app.run(
        debug=args.debug,
        port=args.port
    )

if __name__ == "__main__":
    main()
