﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient.requestStructs
{
    internal struct signinRequest
    {
        public string username;
        public string password;
        public string email;
    }
}