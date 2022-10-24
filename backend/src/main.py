#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging
import subprocess
import os

from flask import Flask, Response, jsonify, render_template, request
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
        out = subprocess.run([args.algo, "get_schedule"], capture_output=True)
        
        #make a schedule
        num_lines = ((out.stdout).decode("utf-8")).count("\n")
        timetable_str = ((out.stdout).decode("utf-8"))
        #print(timetable_str)
        # loop through items in timetable
        formatted_timetable = []
        #first day monday is 1
        day = 1
        #first hour is 9am
        time = 9
        lines = timetable_str.splitlines()
        idx = 0
        for i in range(0, 50):
            item = lines[idx].split("_")
            time = int(i/5) + 9
            day = int(i%5) + 1

            #if element exists add to return array
            if int(item[2]) == day and int(item[1]) == time:
                #the class and time match, yay
                formatted_timetable.append([item[3], str(int(item[5])+100), str(item[4]), 3])
                #move to check next class
                idx += 1
            elif int(item[2]) == day and int(item[1]) != time:
                #correct day but wrong time
                pass
            elif int(item[2]) != day and int(item[1]) == time:
                #correct day but wrong time
                pass
            else:
                #element doesn't exist in timetable, fill with empty array
                formatted_timetable.append(["", "", "", 0])

        #2d array: [course_id, course_type, section_id]
        return formatted_timetable
        """[
            ["ECE231", "101", "TUT", 1], [],
            ["ECE231", "102", "TUT", 1],
            ["ECE231", "103", "TUT", 1],
            ["ECE231", "101", "PRA", 1],
            
        ]"""
    @app.route("/send-request", methods=["POST", "GET"])
    def add_articles():
        if request.method == 'GET':
            #LOAD THE PAGE HERE IF VISITED
            return "Hello"
        
        #body = request.json['body']
        request.headers.add('Access-Control-Allow-Origin', '*')
        #body = JSON.stringify(body)
        
        return request
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
