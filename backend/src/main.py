#!/usr/bin/env python3
# File:        main.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

import argparse
import logging
import subprocess
import os
import numpy as np

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
    # Parse args
    args = parser.parse_args()

    # Read the course database
    db = ttb.Courses(args.database)
    
    # Initialize application
    app = Flask(__name__, template_folder='templates')
    print("Access-Control-Allow-Origin: *")

    fall_courses = []
    winter_courses = []
    constraints = [0]*12
    constraints_input = []

    # Define endpoints
    @app.get("/all")
    def all() -> Response:
        #return jsonify(db.all)
        print("all")
    @app.get("/gen")
    def gen() -> Response:
        out = subprocess.run([args.algo, "query"], capture_output=True)
        #print(out.stdout)
        return ""
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
    @app.route('/basic-schedule', methods=["POST", "GET"])
    def micah_schedule():
        if request.method == 'POST' or request.method =='GET':
            
            print(request.data)
            out = subprocess.run([args.algo, "get_schedule"], capture_output=True)
            #print(out.stdout)
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
            len_classes = len(lines)
            idx = 0
            course_codes = []
            # first line in the lines is the success/error message 
            result_message  = "Successfully found timetables" #  lines[0] TODO: uncomment when backend and algo are connected
            #lines.pop(0) TODO: uncomment when backend and algo are connected 
            for line in lines:
                course_codes.append((line.split("_"))[3])
                courses = []
            [courses.append(x) for x in course_codes if x not in courses] 
            for i in range(0, 55):
                item = lines[idx].split("_")
                if (item[0] == 'S'):
                    break
                time = int(i/5) + 9
                day = int(i%5) + 1
                

                #if element exists add to return array
                if int(item[2]) == day and int(item[1]) == time:
                    #the class and time match, yay
                    formatted_timetable.append([item[3], str(int(item[5])+100), (str(item[4]))[0:3], courses.index(item[3])+1])
                    #move to check next class
                    idx += 1
                    if idx >= len_classes:
                        i = 55
                elif int(item[2]) == day and int(item[1]) != time:
                    #correct day but wrong time
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
                elif int(item[2]) != day and int(item[1]) == time:
                    #correct day but wrong time
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
                else:
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
            if (len(formatted_timetable) != 55):
                for i in range(0, 55-len(formatted_timetable)):
                    formatted_timetable.append(["", "", "", 0])
            for i in range(0, 55):
                item = lines[idx].split("_")
                time = int(i/5) + 9
                day = int(i%5) + 1
                #if element exists add to return array
                if int(item[2]) == day and int(item[1]) == time:
                    #the class and time match, yay
                    formatted_timetable.append([item[3], str(int(item[5])+100), (str(item[4]))[0:3], courses.index(item[3])+1])

                    #move to check next class
                    idx += 1
                    if idx >= len_classes:
                        break
                elif int(item[2]) == day and int(item[1]) != time:
                    #correct day but wrong time
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
                elif int(item[2]) != day and int(item[1]) == time:
                    #correct day but wrong time
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
                else:
                    #element doesn't exist in timetable, fill with empty array
                    formatted_timetable.append(["", "", "", 0])
            
            if (len(formatted_timetable) < 110):
                for i in range(0, 110 - len(formatted_timetable)):
                    formatted_timetable.append(["", "", "", 0])
            #2d array: [course_id, course_type, section_id]
            print(formatted_timetable)
            return [result_message, formatted_timetable]
        else:
            return []
        #else:
            #return []
        """
        Return format:
        
        [
            ["ECE231", "101", "TUT", 1], [],
            ["ECE231", "102", "TUT", 1],
            ["ECE231", "103", "TUT", 1],
            ["ECE231", "101", "PRA", 1],
            
        ]"""
    @app.route("/send-request", methods=["POST", "GET"])
    def add_classes():
        if request.method == 'GET':
            #LOAD THE PAGE HERE IF VISITED
            return "Hello"
        #prints true if request comes with data
        #print(request.want_form_data_parsed)
        #the data that was sent
        #print(request.data)
        #print(type(request.data.decode()))
        outputted = request.data.decode()
        
        if len(outputted) > 14:
            class_name = ""
            for i in range(15, len(outputted)):
                if (outputted[i]) == '"':
                    break
                class_name = class_name + (outputted[i])
            #here we need to add the course to the plan
            if class_name in fall_courses:
                print("This course is already in your fall schedule.")
            elif class_name in winter_courses:
                print("This course is already in your winter schedule.")
            elif len(fall_courses) > 5:
                print("You are already taking 6 courses in the fall.")
            elif len(winter_courses) > 5:
                print("You are already taking 6 courses in the winter.")
            elif class_name == '' or class_name == "":
                pass
            else:
                print("Adding " + class_name + " to your schedule.")
                fall_courses.append(class_name)
                print(fall_courses)

            return []
        else:
            print("Please specify a valid course ID")
            return []
    @app.route('/add-course', methods=["POST", "GET"])
    def add_course():
        if request.method == 'POST':
            print("trying to add a course")
            print(request.data)
            out = subprocess.run([args.algo, "get_schedule"], capture_output=True)
        else:
            print("page GET request")
    @app.route("/remove-class", methods=["POST", "GET"])
    def remove_course():
        if request.method == 'POST':
            print("Trying to remove a course")
            print(request.data)
            
            outputted = request.data.decode()
            if len(outputted) > 14:
                class_name = ""
                for i in range(15, len(outputted)):
                    if (outputted[i]) == '"':
                        break
                    class_name = class_name + (outputted[i])
                #here we need to add the course to the plan
                if class_name in fall_courses:
                    print(class_name + " is being deleted from your fall schedule.")
                    fall_courses.remove(class_name)
                elif class_name in winter_courses:
                    print(class_name + " is being deleted from your winter schedule.")
                    winter_courses.remove(class_name)
                elif class_name == '' or class_name == "":
                    return []
                else:
                    print(class_name + " could not be removed from your schedule.")
                    print(fall_courses)

                    return []
            else:
                print("Please specify a valid course ID")
                return []
        else:
            pass
        return []
    @app.route("/add-constraint", methods=["POST", "GET"])
    def add_constraint():
        if request.method == 'POST':
            #add a constraint
            print("Added a Constraint")
            return []
        else:
            return []
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