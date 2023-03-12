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
        all_args = [args.algo]
        # Extract courses
        courses = request.args["courses"]
        if courses:
            all_args.append(f"-c{courses}")
        # Extract constraints
        constraints = request.args.get("constraints")
        if constraints:
            all_args.append(f"-x{constraints}")
        num_timetables = request.args.get("numtimetables")
        if (num_timetables):
            if int(num_timetables) > 0:
                all_args.append(f"-n{num_timetables}")
        # Run subprocess
        if (courses):
            out = subprocess.run(all_args, capture_output=True)
            print(all_args)
            # Return output
            return out.stdout
        else:
            return []

    # Run app
    app.run(
        debug=args.debug,
        port=args.port
    )


if __name__ == "__main__":
    main()
