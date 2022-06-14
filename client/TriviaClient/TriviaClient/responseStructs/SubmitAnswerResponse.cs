using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.responseStructs
{
    internal struct SubmitAnswerResponse
    {
        public int status;
        public bool isCorrect;
    }
}