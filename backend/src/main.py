#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging

from flask import Flask
from flask_restful import Resource, Api

import ttb


# Initialize application
app = Flask(__name__)

def main():
    # Initialize logging
    logging.basicConfig(
        format="[%(asctime)s %(levelname)s %(name)s] %(message)s", level=logging.INFO
    )

    # Initialize parser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b",
        "--backend",
        default="../build/bin/main",
        type=str,
        help="Path to the compiled scheduler binary",
    )
    parser.add_argument(
        "-d",
        "--debug",
        action="store_true",
        type=bool,
        help="Run in debug mode.",
    )
    parser.add_argument(
        "-p",
        "--port",
        default="7979",
        type=int,
        help="Port number to listen on"
    )
    # Parse args
    args = parser.parse_args()

    # Initialize API
    api = Api(app)
    api.add_resource(ttb.Courses, "/courses")

    # Run app
    app.run(
        debug=args.debug,
        port=args.port
    )


if __name__ == "__main__":
    main()
