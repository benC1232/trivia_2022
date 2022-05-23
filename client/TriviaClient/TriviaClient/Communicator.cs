using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;

namespace TriviaClient
{
    public class Communicator
    {
        private TcpClient client;
        private NetworkStream stream;
        private IPEndPoint endPoint;
        private int port;
        private string host;
        public bool connected;
        public bool signoutFlag;

        public Communicator()
        {
            this.host = "127.0.0.1";
            this.port = 6969;
            this.connected = false;
        }

        public void Connect()
        {
            if (!this.connected)
            {
                this.client = new TcpClient();
                this.endPoint = new IPEndPoint(IPAddress.Parse(this.host), this.port);
                this.client.Connect(this.endPoint);
                this.stream = this.client.GetStream();
                this.connected = true;
            }
            else
            {
                throw new Exception("the connect function was called when the user was Already connected");
            }
        }

        public void Disconnect()
        {
            if (this.connected)
            {
                if (this.signoutFlag)
                {
                    byte[] arr = new byte[1];
                    arr[0] = 0;
                    this.Send(8, arr);
                }
                this.stream.Close();
                this.client.Close();
                this.connected = false;
            }
            else
            {
                throw new Exception("the dissconnect function was called when the user was Not connected");
            }
        }

        public void Send(int code, byte[] message)
        {
            byte codeByte = (byte)code;
            byte[] messageLengthBytes = intToFourByteArr(message.Length);
            byte[] messageBytes = message;
            byte[] messageToSend = new byte[messageLengthBytes.Length + messageBytes.Length + 1];
            messageToSend[0] = codeByte;
            for (int i = 0; i < messageLengthBytes.Length; i++)
            {
                messageToSend[i + 1] = messageLengthBytes[i];
            }
            for (int i = 0; i < messageBytes.Length; i++)
            {
                messageToSend[i + messageLengthBytes.Length + 1] = messageBytes[i];
            }
            this.stream.Write(messageToSend, 0, messageToSend.Length);
            this.stream.Flush();
        }

        public Tuple<int, byte[]> Recieve()
        {
            try
            {
                byte[] recieveBytes = new byte[4096];
                this.stream.Read(recieveBytes, 0, 4096);
                return parseResponse(recieveBytes);
            }
            catch (Exception e)
            {
                throw e;
            }
        }

        public Tuple<int, byte[]> parseResponse(byte[] arr)
        {
            int code = arr[0];
            int messageLength = fourByteArrToInt(arr, 1);
            byte[] message = new byte[messageLength];
            for (int i = 0; i < messageLength; i++)
            {
                message[i] = arr[i + 5];
            }
            return new Tuple<int, byte[]>(code, message);
        }

        private int fourByteArrToInt(byte[] arr, int startIndex)
        {
            int result = 0;
            for (int i = 0; i < 4; i++)
            {
                result += arr[startIndex + i] << (8 * i);
            }
            return result;
        }

        private byte[] intToFourByteArr(int num)
        {
            byte[] arr = new byte[4];
            arr[0] = (byte)(num >> 24);
            arr[1] = (byte)(num >> 16);
            arr[2] = (byte)(num >> 8);
            arr[3] = (byte)(num);
            return arr;
        }
    }
}