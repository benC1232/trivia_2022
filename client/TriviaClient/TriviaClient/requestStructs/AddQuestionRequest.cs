using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace TriviaClient.requestStructs
{
    public struct AddQuestionRequest
    {
        public string question;
        public string correctAnswer;
        public string wrongAnswer1;
        public string wrongAnswer2;
        public string wrongAnswer3;


    }
}
