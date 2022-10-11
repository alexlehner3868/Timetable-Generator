#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging
import subprocess

from flask import Flask, Response, jsonify
import datetime 
import ttb

x = datetime.datetime.now()

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
    # Parse args
    args = parser.parse_args()

    # Read the course database
    db = ttb.Courses(args.database)

    # Initialize application
    app = Flask(__name__)
    # Define endpoints
    @app.get("/all")
    def all() -> Response:
        return jsonify(db.all)
    @app.get("/gen")
    def gen() -> Response:
        out = subprocess.run([args.algo, "query"], capture_output=True)
        print(out)
        return out.stdout
    @app.route('/data')
    def get_time():
        # Returning an api for showing in  reactjs
        return {
            'Name':"geek", 
            "Age":"22",
            "Date":x, 
            "programming":"python"
            }
    @app.route('/move_forward')
    def move_forward():
        # Returning an api for showing in  reactjs
        out = "BUTTON PRESSED "
        return out.stdout
    
    # Run app
    app.run(
        debug=args.debug,
        port=args.port
    )

if __name__ == "__main__":
    main()
