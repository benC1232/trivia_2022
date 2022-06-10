import json
import os
import sys
#import sqlite
import sqlite3
from time import sleep

json_file = "questions.json"

#download the json file from the link https://opentdb.com/api.php?amount=50&type=multiple
#and save it to the json_file

import requests
def download_json_file():
    #get the json file from the link
    response = requests.get("https://opentdb.com/api.php?amount=50&type=multiple")
    #save the json file to the json_file
    with open(json_file, "w") as f:
        json.dump(response.json(), f)
    




#conver the json to list
def json_to_list(json_file):
    with open(json_file) as f:
        data = json.load(f)
    data = data['results']
    return data
    #remove duplicates from the list


#every dictionary in the list is a question
#for every question in the list add a new row to the database to the table questions that is built like thist:
"""
CREATE TABLE IF NOT EXISTS questions
  (
     questionid    INTEGER PRIMARY KEY,
     question      TEXT NOT NULL,
     correctanswer TEXT NOT NULL,
     wronganswer1  TEXT NOT NULL,
     wronganswer2  TEXT NOT NULL,
     wronganswer3  TEXT NOT NULL
  ); """


#this is an exeample of a question in the list
'''
{"category":"Entertainment: Video Games","type":"multiple","difficulty":"medium","question":"What is the punishment for playing Postal 2 in New Zealand?","correct_answer":"10 years in prison and a fine of $50,000","incorrect_answers":["Fine of $5,000","Nothing","15 years in prison and a fine of $10,000"]}
'''

#create a function that goes over the list and adds the questions to the database
def add_questions_to_database(list_of_questions,db: str):
    #connect to the database
    conn = sqlite3.connect(db)
    c = conn.cursor()
    #create the table
    c.execute('''CREATE TABLE IF NOT EXISTS questions
        (
            questionid    INTEGER PRIMARY KEY,
            question      TEXT NOT NULL,
            correctanswer TEXT NOT NULL,
            wronganswer1  TEXT NOT NULL,
            wronganswer2  TEXT NOT NULL,
            wronganswer3  TEXT NOT NULL
        ); ''')
    #loop over the list of questions and add them to the database
    for question in list_of_questions:
        #get the question
        question_text = question['question'].replace('&quot;','\"').replace('&#039;',"'")
        #check if the name of the question is already in the database if it is skip it
        c.execute("SELECT * FROM questions WHERE question = ?", (question_text,))
        if c.fetchone() is not None:
            print("skipping question: " + question_text)
            continue
        #get the correct answer
        correct_answer = question['correct_answer']
        #get the wrong answers
        wrong_answers = question['incorrect_answers']
        #add the question to the database
        c.execute("INSERT INTO questions (question,correctanswer,wronganswer1,wronganswer2,wronganswer3) VALUES (?,?,?,?,?)",(question_text,correct_answer,wrong_answers[0],wrong_answers[1],wrong_answers[2]))
    #commit the changes
    conn.commit()
    #close the connection
    conn.close()

def main():
    #download the json file
    download_json_file()
    #convert the json to a list
    data = json_to_list(json_file)
    #add the questions to the database "\server\Trivia_Server\Trivia_Server\Trivia.sqlite"
    add_questions_to_database(data, "/server/Trivia_Server/Trivia_Server/Trivia.sqlite")

if __name__ == "__main__":
    for i in range(40):
        main()
        