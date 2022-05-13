namespace HomeSensors.Console
{
    internal class Update
    {
        public string Message { get; }
        public DateTime ReceivedAt { get; }

        public Update(string message, DateTime receivedAt)
        {
            Message = message;
            ReceivedAt = receivedAt;
        }
    }
}
