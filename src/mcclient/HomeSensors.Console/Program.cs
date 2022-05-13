using HomeSensors.Console;
using System.IO.Ports;

Console.WriteLine("Hello, World!");

SerialPort _port = InitPort();

_ = Task.Run(() =>
{
    while(true)
    {
        var message = _port.ReadLine();
        var update = new Update(message, DateTime.UtcNow);
        NotifyUpdate(update);
    }
});

Console.WriteLine("Started listening port");

while (true)
{
    var input = Console.ReadLine();
    if (input == "exit") break;
}
Exit();

static void NotifyUpdate(Update update)
{
    Console.WriteLine($"[{update.ReceivedAt}] {update.Message}");
}

void Exit()
{
    Console.WriteLine("Terminating...");
    _port.Close();
    Console.ReadKey();
}

static SerialPort InitPort()
{
    var port = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One);
    port.Open();
    port.NewLine = "\r";
    return port;
}
