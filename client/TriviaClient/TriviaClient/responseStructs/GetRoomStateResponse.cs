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
        public bool hasGameBegun;
        public string players;
        public int questionCount;
        public int answerTimeout;
    }
}