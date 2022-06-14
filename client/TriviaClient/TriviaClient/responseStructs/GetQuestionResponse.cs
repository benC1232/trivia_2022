using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.responseStructs
{
    internal struct GetQuestionResponse
    {
        public int status;
        public string question;
        public string answers;
    }
}