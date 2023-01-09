#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging
import subprocess

from flask import Flask, Response, jsonify, request
from flask_cors import CORS

from db import Courses


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
    db = Courses(args.database)

    # Initialize application
    app = Flask(__name__)
    CORS(app)

    # Define endpoints
    # /all
    @app.get("/all")
    def all() -> Response:
        return jsonify(db.all)
    # /gen
    @app.get("/gen")
    def gen() -> Response:
        # Extract courses
        courses = request.args["courses"]
        courses = f"-c{courses}"
        # Extract constraints
        constraints = request.args.get("constraints")
        constraints = f"-x{constraints}" if constraints else ""
        # Run subprocess
        out = subprocess.run([args.algo, f"{courses}"], capture_output=True)
        # Return output
        return out.stdout

    # Run app
    app.run(
        debug=args.debug,
        port=args.port
    )


if __name__ == "__main__":
    main()
