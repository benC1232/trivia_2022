using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.responseStructs
{
    internal struct GetRoomStateResponse
    {
        public int status;
        public int hasGameBegun;
        public string players;
        public int questionCount;
        public int answerTimeout;
    }
}